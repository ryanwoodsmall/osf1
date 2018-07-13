/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
#ifndef lint
static char *rcsid = "@(#)$RCSfile: arch.c,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1993/10/29 22:01:15 $";
#endif

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*-
 * arch.c --
 *	Functions to manipulate libraries, archives and their members.
 *
 *	Once again, cacheing/hashing comes into play in the manipulation
 * of archives. The first time an archive is referenced, all of its members'
 * headers are read and hashed and the archive closed again. All hashed
 * archives are kept on a list which is searched each time an archive member
 * is referenced.
 *
 * The interface to this module is:
 *	Arch_ParseArchive   	Given an archive specification, return a list
 *	    	  	    	of GNode's, one for each member in the spec.
 *	    	  	    	FAILURE is returned if the specification is
 *	    	  	    	invalid for some reason.
 *
 *	Arch_Touch	    	Alter the modification time of the archive
 *	    	  	    	member described by the given node to be
 *	    	  	    	the current time.
 *
 *	Arch_MTime	    	Find the modification time of a member of
 *	    	  	    	an archive *in the archive*. The time is also
 *	    	  	    	placed in the member's GNode. Returns the
 *	    	  	    	modification time.
 *
 *	Arch_MemTime	    	Find the modification time of a member of
 *	    	  	    	an archive. Called when the member doesn't
 *	    	  	    	already exist. Looks in the archive for the
 *	    	  	    	modification time. Returns the modification
 *	    	  	    	time.
 *
 *	Arch_FindLib	    	Search for a library along a path. The
 *	    	  	    	library name in the GNode should be in
 *	    	  	    	-l<name> format.
 *
 *	Arch_LibOODate	    	Special function to decide if a library node
 *	    	  	    	is out-of-date.
 *
 *	Arch_Init 	    	Initialize this module.
 */

#include    <sys/types.h>
#include    <sys/stat.h>
#include    <sys/time.h>
#include    <ctype.h>
#include    <ar.h>
#include    <ranlib.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    "make.h"
#include    "hash.h"
#include    "pmake_msg.h"

#define     AR_EFMT1 "#1/"	/* extended format */

/*
 * ARCHTRACE macro used only during development for tracing ARCH module.
 * Use the compiler option -DARCHTRACE or -DALLTRACE to turn on.
 */

#if defined(ARCHTRACE) || defined(ALLTRACE)
#undef ARCHTRACE
#define ARCHTRACE(message) { \
   printf("ARCHTRACE: %s.\n",message);\
   }
#else
#define ARCHTRACE(message)
#endif


extern nl_catd	  catd;
static Lst	  ARCHIVES_LST;   /* Lst of archives we've already examined */

typedef struct Arch {
    char	  *name;      /* Name of archive */
    Hash_Table	  members;    /* All the members of the archive described
			       * by <name, struct ar_hdr *> key/value pairs */
} Arch;

static FILE *ArchFindMember(char *archive, char *member, struct ar_hdr *arhPtr, char *mode);

/*-
 *-----------------------------------------------------------------------
 * Arch_ParseArchive --
 *	Parse the archive specification in the given line and find/create
 *	the nodes for the specified archive members, placing their nodes
 *	on the given list.
 *
 * Results:
 *	SUCCESS if it was a valid specification. The linePtr is updated
 *	to point to the first non-space after the archive spec. The
 *	nodes for the members are placed on the given list.
 *
 * Side Effects:
 *	Some nodes may be created. The given list is extended.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Arch_ParseArchive (char **linePtr, Lst nodeLst, GNode *ctxt)
{
  /*  char	    **linePtr;      Pointer to start of specification */
  /*  Lst	    nodeLst;   	    Lst on which to place the nodes */
  /*  GNode   	    *ctxt;  	    Context in which to expand variables */

    char            *cp;	    		    /* Pointer into line */
    GNode	    *gn;     	    /* New node */
    char	    *libName;  	    /* Library-part of specification */
    char	    *memName;  	    /* Member-part of specification */
    char	    *nameBuf;	    /* temporary place for node name */
    char	    saveChar;  	    /* Ending delimiter of member-name */
    Boolean 	    subLibName;	    /* TRUE if libName should have/had
				     * variable substitution performed on it */

    ARCHTRACE("Arch_ParseArchiv: Parse the archive specification");

    libName = *linePtr;
    
    subLibName = FALSE;

    for (cp = libName; *cp != '(' && *cp != '\0'; cp++) {
	if (*cp == '$') {	/* expand macro */
	    /*
	     * Variable spec, so call the Var module to parse the puppy
	     * so we can safely advance beyond it...
	     */
	    int 	length;
	    Boolean	freeIt;
	    char	*result;
	    
	    result=Var_Parse(cp, ctxt, TRUE, &length, &freeIt);
	    if (result == var_Error) {
		return(FAILURE);
	    } else {
		subLibName = TRUE;
	    }
	    
	    if (freeIt) {
		free(result);
	    }
	    cp += length-1;
	}
    }

    *cp++ = '\0';
    if (subLibName) {
	libName = Var_Subst(libName, ctxt, TRUE);
    }
    

    while (1) {
	/*
	 * First skip to the start of the member's name, mark that
	 * place and skip to the end of it (either white-space or
	 * a close paren).
	 */
	Boolean	doSubst = FALSE; /* TRUE if need to substitute in memName */

	while (*cp != '\0' && *cp != ')' && isspace (*cp)) {
	    cp++;
	}
	memName = cp;
	while (*cp != '\0' && *cp != ')' && !isspace (*cp)) {
	    if (*cp == '$') {
		/*
		 * Variable spec, so call the Var module to parse the puppy
		 * so we can safely advance beyond it...
		 */
		int 	length;
		Boolean	freeIt;
		char	*result;

		result=Var_Parse(cp, ctxt, TRUE, &length, &freeIt);
		if (result == var_Error) {
		    return(FAILURE);
		} else {
		    doSubst = TRUE;
		}

		if (freeIt) {
		    free(result);
		}
		cp += length;
	    } else {
		cp++;
	    }
	}

	/*
	 * If the specification ends without a closing parenthesis,
	 * chances are there's something wrong (like a missing backslash),
	 * so it's better to return failure than allow such things to happen
	 */
	if (*cp == '\0') {
	    printf(catgets(catd, MS_MAKE, NOCLSPAREN,
		   "No closing parenthesis in archive specification\n"));
	    return (FAILURE);
	}

	/*
	 * If we didn't move anywhere, we must be done
	 */
	if (cp == memName) {
	    break;
	}

	saveChar = *cp;
	*cp = '\0';

	/*
	 * XXX: This should be taken care of intelligently by
	 * SuffExpandChildren, both for the archive and the member portions.
	 */
	/*
	 * If member contains variables, try and substitute for them.
	 * This will slow down archive specs with dynamic sources, of course,
	 * since we'll be (non-)substituting them three times, but them's
	 * the breaks -- we need to do this since SuffExpandChildren calls
	 * us, otherwise we could assume the thing would be taken care of
	 * later.
	 */
	if (doSubst) {
	    char    *buf;
	    char    *sacrifice;
	    char    *oldMemName = memName;
	    
	    memName = Var_Subst(memName, ctxt, TRUE);

	    /*
	     * Now form an archive spec and recurse to deal with nested
	     * variables and multi-word variable values.... The results
	     * are just placed at the end of the nodeLst we're returning.
	     */
	    buf = sacrifice = (char *)emalloc(strlen(memName)+strlen(libName)+3);

	    sprintf(buf, "%s(%s)", libName, memName);

	    if (index(memName, '$') && strcmp(memName, oldMemName) == 0) {
		/*
		 * Must contain dynamic sources, so we can't deal with it now.
		 * Just create an ARCHV node for the thing and let
		 * SuffExpandChildren handle it...
		 */
		gn = Targ_FindNode(buf, TARG_CREATE);

		if (gn == NILGNODE) {
		    free(buf);
		    return(FAILURE);
		} else {
		    gn->type |= OP_ARCHV;
		    (void)Lst_AtEnd(nodeLst, (ClientData)gn);
		}
	    } else if (Arch_ParseArchive(&sacrifice, nodeLst, ctxt)!=SUCCESS) {
		/*
		 * Error in nested call -- free buffer and return FAILURE
		 * ourselves.
		 */
		free(buf);
		return(FAILURE);
	    }
	    /*
	     * Free buffer and continue with our work.
	     */
	    free(buf);
	} else {
	    nameBuf = (char *)emalloc(strlen(libName)+strlen(memName)+3);
	    sprintf(nameBuf, "%s(%s)", libName, memName);
	    gn = Targ_FindNode (nameBuf, TARG_CREATE);
	    if (gn == NILGNODE) {
		return (FAILURE);
	    } else {
		/*
		 * We've found the node, but have to make sure the rest of the
		 * world knows it's an archive member, without having to
		 * constantly check for parentheses, so we type the thing with
		 * the OP_ARCHV bit before we place it on the end of the
		 * provided list.
		 */
		gn->type |= OP_ARCHV;
		(void) Lst_AtEnd (nodeLst, (ClientData)gn);
	    }
	}
	if (doSubst) {
	    free(memName);
	}
	
	*cp = saveChar;
    }

    /*
     * If substituted libName, free it now, since we need it no longer.
     */
    if (subLibName) {
	free(libName);
    }

    /*
     * We promised the pointer would be set up at the next non-space, so
     * we must advance cp there before setting *linePtr... (note that on
     * entrance to the loop, cp is guaranteed to point at a ')')
     */
    do {
	cp++;
    } while (*cp != '\0' && isspace (*cp));

    *linePtr = cp;
    return (SUCCESS);
}

/*-
 *-----------------------------------------------------------------------
 * ArchFindArchive --
 *	See if the given archive is the one we are looking for. Called
 *	From ArchStatMember and ArchFindMember via Lst_Find.
 *
 * Results:
 *	0 if it is, non-zero if it isn't.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static int
ArchFindArchive (Arch *ar, char *archName)
{
    /* Arch	  *ar;	      	  Current list element */
    /* char	  *archName;  	  Name we want */


    ARCHTRACE("ArchFindArchive: See if the given archive is the one we are looking for");

    return (strcmp (archName, ar->name));
}

/*-
 *-----------------------------------------------------------------------
 * ArchStatMember --
 *	Locate a member of an archive, given the path of the archive and
 *	the path of the desired member.
 *
 * Results:
 *	A pointer to the current struct ar_hdr structure for the member. Note
 *	That no position is returned, so this is not useful for touching
 *	archive members. This is mostly because we have no assurances that
 *	The archive will remain constant after we read all the headers, so
 *	there's not much point in remembering the position...
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
static struct ar_hdr *
ArchStatMember (char *archive_name, char *member_name, Boolean hash)
{
    /* char	  *archive_name;   Path to the archive_name */
    /* char	  *member_name;    Name of member. If it is a path, only the */
    /*			      last component is used. */
    /* Boolean	  hash;	      TRUE if archive should be hashed if not */
    /*                        already so. */

    FILE *	  arch;	      /* Stream to archive */
    int		  size;       /* Size of archive member */
    char	  *cp;	      /* Useful character pointer */
    char	  magic[SARMAG];
    int		  len;
    LstNode	  ln;	      /* Lst member containing archive descriptor */
    Arch	  *arArch;	      /* Archive descriptor */
    Hash_Entry	  *he;	       /* Entry containing member's description */
    struct ar_hdr arh;         /* archive-member header for reading archive */

    struct ar_hdr *return_arh; /* archive-member for return  */

    char	  memName[NAME_MAX+1]; /* Current member name while hashing */
    char	  sizebuf[sizeof(arh.ar_size)+1];
    int		  retval;

    /*
     * Because of space constraints and similar things, files are archived
     * using their final path components, not the entire thing, so we need
     * to point 'member' to the final component, if there is one, to make
     * the comparisons easier...
     */

    ARCHTRACE("ArchStatMember: Locate a member of an archive");

    cp = rindex (member_name, '/');
    if (cp != (char *) NULL) {
	member_name = cp + 1;
    }

    ln = Lst_Find (ARCHIVES_LST, (ClientData) archive_name, (int(*)(void*,void*))ArchFindArchive);
    if (ln != NILLNODE) {
	arArch = (Arch *) Lst_Datum (ln);

	he = Hash_FindEntry (&arArch->members, (Address) member_name);

	if (he != (Hash_Entry *) NULL) 
        {
            return_arh =  ((struct ar_hdr *) Hash_GetValue (he));
	    return ((struct ar_hdr *) Hash_GetValue (he));
	} else {
	    return ((struct ar_hdr *) NULL);
	}
    }

    if (!hash) {
	/*
	 * Caller doesn't want the thing hashed, just use ArchFindMember
	 * to read the header for the member out and close down the stream
	 * again. Since the archive is not to be hashed, we assume there's
	 * no need to allocate extra room for the header we're returning,
	 * so just declare it static.
	 */
	 static struct ar_hdr	sarh;

	 arch = ArchFindMember(archive_name, member_name, &sarh, "r");

	 if (arch == (FILE *)NULL) {
	    return ((struct ar_hdr *)NULL);
	} else {
	    fclose(arch);
	    return (&sarh);
	}
    }

    /*
     * We don't have this archive on the list yet, so we want to find out
     * everything that's in it and cache it so we can get at it quickly.
     */
    arch = fopen (archive_name, "r");
    if (arch == (FILE *) NULL) {
	return ((struct ar_hdr *) NULL);
    }
    
    /*
     * We use the ARMAG string to make sure this is an archive we
     * can handle...
     */
    if ((fread (magic, SARMAG, 1, arch) != 1) ||
    	(strncmp (magic, ARMAG, SARMAG) != 0)) {
	fclose (arch);
	return ((struct ar_hdr *) NULL);
    }

    arArch = (Arch *)emalloc (sizeof (Arch));
    arArch->name = strdup (archive_name);
    Hash_InitTable (&arArch->members, -1);
    
    while (fread ((char *)&arh, sizeof (struct ar_hdr), 1, arch) == 1) {
	if (strncmp ( arh.ar_fmag, ARFMAG, sizeof (arh.ar_fmag)) != 0) {
badhdr:	     /*
	      * The header is bogus, so the archive is bad
	      * and there's no way we can recover...
	      */
	     fclose (arch);
	     Hash_DeleteTable (&arArch->members);
	     free ((Address)arArch);
	     return ((struct ar_hdr *) NULL);
	}
	bcopy(arh.ar_size, sizebuf, sizeof(sizebuf)-1);
	sizebuf[sizeof(sizebuf)] = 0;
	(void) sscanf (sizebuf, "%10d", &size);
	if (size&1) size++;
	if (bcmp(arh.ar_name, AR_EFMT1, sizeof(AR_EFMT1)-1) == 0 &&
	    arh.ar_name[sizeof(AR_EFMT1)-1] != ' ') {
	    len = atoi(arh.ar_name+sizeof(AR_EFMT1)-1);
	    if (len <= 0 || len > NAME_MAX)
		goto badhdr;
	    retval = fread(memName, (size_t) 1, (size_t) len, arch);
	    if (retval != len)
		goto badhdr;
	    memName[len] = 0;
	    size -= len;
	} else {
	    bcopy(arh.ar_name, memName, sizeof(arh.ar_name));
	    memName[sizeof(arh.ar_name)] = 0;
	    cp = strchr(memName, '/');
	    if (cp)
		*cp = 0;		/* Mark end of member */
	    else {
		cp = memName + sizeof(arh.ar_name) - 1;
		while (cp > memName && *cp == ' ')
		  cp--;
		*++cp = 0;
	    }
	}

	he = Hash_CreateEntry (&arArch->members, strdup (memName),
			       (Boolean *)NULL);
	Hash_SetValue (he, (ClientData)emalloc (sizeof (struct ar_hdr)));
	bcopy ((Address)&arh, (Address)Hash_GetValue (he), 
	    sizeof (struct ar_hdr));
	/*
	 * We need to advance the stream's pointer to the start of the
	 * next header. Files are padded with newlines to an even-byte
	 * boundary, so we need to extract the size of the file from the
	 * 'size' field of the header and round it up during the seek.
	 */
	fseek (arch, size, 1);
    }

    fclose (arch);

    (void) Lst_AtEnd (ARCHIVES_LST, (ClientData) arArch);

    /*
     * Now that the archive has been read and cached, we can look into
     * the hash table to find the desired member's header.
     */
    he = Hash_FindEntry (&arArch->members, (Address) member_name);

    if (he != (Hash_Entry *) NULL) {
        return_arh =  ((struct ar_hdr *) Hash_GetValue (he));
	return ((struct ar_hdr *) Hash_GetValue (he));
    } else {
	return ((struct ar_hdr *) NULL);
    }
}

/*-
 *-----------------------------------------------------------------------
 * ArchFindMember --
 *	Locate a member of an archive, given the path of the archive and
 *	the path of the desired member. If the archive is to be modified,
 *	the mode should be "r+", if not, it should be "r".
 *
 * Results:
 *	An FILE *, opened for reading and writing, positioned at the
 *	start of the member's struct ar_hdr, or NULL if the member was
 *	nonexistent. The current struct ar_hdr for member.
 *
 * Side Effects:
 *	The passed struct ar_hdr structure is filled in.
 *
 *-----------------------------------------------------------------------
 */
static FILE *
ArchFindMember (char *archive, char *member, struct ar_hdr *arhPtr, char *mode)
{   
    /* char	  *archive;   Path to the archive */
    /* char	  *member;    Name of member. If it is a path, only the */
    /*			      last component is used. */
    /* struct ar_hdr *arhPtr; Pointer to header structure to be filled in */
    /* char	  *mode;      The mode for opening the stream */

    FILE *	  arch;	      /* Stream to archive */
    int		  size;       /* Size of archive member */
    char	  *cp;	      /* Useful character pointer */
    char	  magic[SARMAG];
    int		  len;
    char	  memName[NAME_MAX+1];
    char	  sizebuf[sizeof(arhPtr->ar_size)+1];
    int		  retval;


    ARCHTRACE("ArchFindMember: Locate a member of an archive");

    arch = fopen (archive, mode);
    if (arch == (FILE *) NULL) {
	return ((FILE *) NULL);
    }
    
    /*
     * We use the ARMAG string to make sure this is an archive we
     * can handle...
     */
    if ((fread (magic, SARMAG, 1, arch) != 1) ||
    	(strncmp (magic, ARMAG, SARMAG) != 0)) {
	fclose (arch);
	return ((FILE *) NULL);
    }

    /*
     * Because of space constraints and similar things, files are archived
     * using their final path components, not the entire thing, so we need
     * to point 'member' to the final component, if there is one, to make
     * the comparisons easier...
     */
    cp = rindex (member, '/');
    if (cp != (char *) NULL) {
	member = cp + 1;
    }
    
    while (fread ((char *)arhPtr, sizeof (struct ar_hdr), 1, arch) == 1) {
	if (strncmp(arhPtr->ar_fmag, ARFMAG, sizeof (arhPtr->ar_fmag) ) != 0) {
	     /*
	      * The header is bogus, so the archive is bad
	      * and there's no way we can recover...
	      */
	     fclose (arch);
	     return ((FILE *) NULL);
	}
	bcopy(arhPtr->ar_size, sizebuf, sizeof(sizebuf)-1);
	sizebuf[sizeof(sizebuf)] = 0;
	(void) sscanf (sizebuf, "%10d", &size);
	if (size&1) size++;
	if (bcmp(arhPtr->ar_name, AR_EFMT1, sizeof(AR_EFMT1)-1) == 0 &&
	    arhPtr->ar_name[sizeof(AR_EFMT1)-1] != ' ') {
	    len = atoi(arhPtr->ar_name+sizeof(AR_EFMT1)-1);
	    if (len <= 0 || len > NAME_MAX) {
		fclose (arch);
		return ((FILE *) NULL);
	    }
	    retval = fread(memName, (size_t) 1, (size_t) len, arch);
	    if (retval != len) {
		fclose (arch);
		return ((FILE *) NULL);
	    }
	    memName[len] = 0;
	    size -= len;
	} else {
	    bcopy(arhPtr->ar_name, memName, sizeof(arhPtr->ar_name));
	    memName[sizeof(arhPtr->ar_name)] = 0;
	    cp = strchr(memName, '/');
	    if (cp)
		*cp = 0;		/* Mark end of member */
	    else {
		cp = memName + sizeof(arhPtr->ar_name) - 1;
		while (cp > memName && *cp == ' ')
		  cp--;
		*++cp = 0;
	    }
	    len = 0;
	}
	if (strcmp (member, memName) == 0) {
	    /*
	     * To make life easier, we reposition the file at the start
	     * of the header we just read before we return the stream.
	     * In a more general situation, it might be better to leave
	     * the file at the actual member, rather than its header, but
	     * not here...
	     */
	    fseek (arch, -(sizeof(struct ar_hdr) + len), 1);
	    return (arch);
	}
	/*
	 * This isn't the member we're after, so we need to advance the
	 * stream's pointer to the start of the next header. Files are
	 * padded with newlines to an even-byte boundary, so we need to
	 * extract the size of the file from the 'size' field of the
	 * header and round it up during the seek.
	 */
	fseek (arch, size, 1);
    }

    /*
     * We've looked everywhere, but the member is not to be found. Close the
     * archive and return NULL -- an error.
     */
    fclose (arch);
    return ((FILE *) NULL);
}

/*-
 *-----------------------------------------------------------------------
 * Arch_Touch --
 *	Touch a member of an archive.
 *
 * Results:
 *	The 'time' field of the member's header is updated.
 *
 * Side Effects:
 *	The modification time of the entire archive is also changed.
 *	For a library, this could necessitate the re-ranlib'ing of the
 *	whole thing.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_Touch (GNode *gn)
{
    /* GNode	  *gn;	  Node of member to touch */

    FILE *	  arch;	  /* Stream open to archive, positioned properly */
    struct ar_hdr arh;	  /* Current header describing member */


    ARCHTRACE("Arch_Touch: Touch a member of an archive");

    arch = ArchFindMember(Var_Value (ARCHIVE, gn),
			  Var_Value (MEMBER, gn),
			  &arh, "r+");
    sprintf(arh.ar_date, "%-12d", now);

    if (arch != (FILE *) NULL) {
	(void)fwrite ((char *)&arh, sizeof (struct ar_hdr), 1, arch);
	fclose (arch);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Arch_MTime --
 *	Return the modification time of a member of an archive.
 *
 * Results:
 *	The modification time (seconds).
 *
 * Side Effects:
 *	The mtime field of the given node is filled in with the value
 *	returned by the function.
 *
 *-----------------------------------------------------------------------
 */
int
Arch_MTime (GNode *gn)
{
    /* GNode	  *gn;	      Node describing archive member */

    struct ar_hdr *arhPtr;    /* Header of desired member */
    int		  modTime;    /* Modification time as an integer */


    ARCHTRACE("Arch_MTime: Return the modification time of a member of an archive");

    arhPtr = ArchStatMember (Var_Value (ARCHIVE, gn),
			     Var_Value (MEMBER, gn),
			     TRUE);
    if (arhPtr != (struct ar_hdr *) NULL) {
	(void)sscanf (arhPtr->ar_date, "%12d", &modTime);
    } else {
	modTime = 0;
    }

    if (DEBUG(ARCH)) {
      if ( arhPtr != (struct ar_hdr *) NULL) {
	printf ("Arch_MTime: \"%s\" was modified %s .\n", gn->name, Targ_FmtTime(modTime));
      } else {
	printf ("Arch_MTime: \"%s\" is considered \"non-existent\".\n",gn->name);
      }
    }

    
    /*
     * If we have made our associated member node, then we want to
     * update ourselves to correspond to his time so that our library
     * will consider us out-of-date.
     */

 /*   if (gn->mtime && gn->cmtime > gn->mtime) */
 /*	modTime = gn->cmtime;                  */

    if (DEBUG(ARCH)) {
     printf ("Arch_MTime: Returning %s for \"%s\".\n",Targ_FmtTime(modTime),gn->name);
   }

    gn->mtime = modTime;
    return (modTime);
}

/*-
 *-----------------------------------------------------------------------
 * Arch_MemMTime --
 *	Given a non-existent archive member's node, get its modification
 *	time from its archived form, if it exists.
 *
 * Results:
 *	The modification time.
 *
 * Side Effects:
 *	The mtime field is filled in.
 *
 *-----------------------------------------------------------------------
 */
int
Arch_MemMTime (GNode *gn)
{
    /* GNode   	  *gn; */

    LstNode 	  ln;
    GNode   	  *pgn;
    char    	  *nameStart,
		  *nameEnd;


    ARCHTRACE("Arch_MemMTime: Given a non-existent archive member's node, get its modification time");

    if (Lst_Open (gn->parents) != SUCCESS) {
	gn->mtime = 0;
	return (0);
    }
    while ((ln = Lst_Next (gn->parents)) != NILLNODE) {
	pgn = (GNode *) Lst_Datum (ln);

	if (pgn->type & OP_ARCHV) {
	    /*
	     * If the parent is an archive specification and is being made
	     * and its member's name matches the name of the node we were
	     * given, record the modification time of the parent in the
	     * child. We keep searching its parents in case some other
	     * parent requires this child to exist...
	     */
	    nameStart = index (pgn->name, '(') + 1;
	    nameEnd = index (nameStart, ')');

	    if (pgn->make &&
		strncmp(nameStart, gn->name, nameEnd - nameStart) == 0) {
				     gn->mtime = Arch_MTime(pgn);
	    }
	} else if (pgn->make) {
	    /*
	     * Something which isn't a library depends on the existence of
	     * this target, so it needs to exist.
	     */
	    gn->mtime = 0;
	    break;
	}
    }

    Lst_Close (gn->parents);

    return (gn->mtime);
}

/*-
 *-----------------------------------------------------------------------
 * Arch_Init --
 *	Initialize things for this module.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The 'ARCHIVES_LST' list is initialized.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_Init (void)
{

    ARCHTRACE("Arch_Init: Initialize things for this module");

    ARCHIVES_LST = Lst_Init (FALSE);
}


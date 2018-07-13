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
#ifdef REV_INFO
#ifndef lint
static char SCCSID[] = "OSF/Motif: %W% %E%";
#endif /* lint */
#endif /* REV_INFO */
/******************************************************************************
*******************************************************************************
*
*  (c) Copyright 1989, 1990, OPEN SOFTWARE FOUNDATION, INC.
*  (c) Copyright 1989, 1990, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
*  ALL RIGHTS RESERVED
*  
*  	THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED
*  AND COPIED ONLY IN ACCORDANCE WITH THE TERMS OF SUCH LICENSE AND
*  WITH THE INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR
*  ANY OTHER COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE
*  AVAILABLE TO ANY OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF THE
*  SOFTWARE IS HEREBY TRANSFERRED.
*  
*  	THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT
*  NOTICE AND SHOULD NOT BE CONSTRUED AS A COMMITMENT BY OPEN SOFTWARE
*  FOUNDATION, INC. OR ITS THIRD PARTY SUPPLIERS  
*  
*  	OPEN SOFTWARE FOUNDATION, INC. AND ITS THIRD PARTY SUPPLIERS,
*  ASSUME NO RESPONSIBILITY FOR THE USE OR INABILITY TO USE ANY OF ITS
*  SOFTWARE .   OSF SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
*  KIND, AND OSF EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES, INCLUDING
*  BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
*  FITNESS FOR A PARTICULAR PURPOSE.
*  
*  Notice:  Notwithstanding any other lease or license that may pertain to,
*  or accompany the delivery of, this computer software, the rights of the
*  Government regarding its use, reproduction and disclosure are as set
*  forth in Section 52.227-19 of the FARS Computer Software-Restricted
*  Rights clause.
*  
*  (c) Copyright 1989, 1990, Open Software Foundation, Inc.  Unpublished - all
*  rights reserved under the Copyright laws of the United States.
*  
*  RESTRICTED RIGHTS NOTICE:  Use, duplication, or disclosure by the
*  Government is subject to the restrictions as set forth in subparagraph
*  (c)(1)(ii) of the Rights in Technical Data and Computer Software clause
*  at DFARS 52.227-7013.
*  
*  Open Software Foundation, Inc.
*  11 Cambridge Center
*  Cambridge, MA   02142
*  (617)621-8700
*  
*  RESTRICTED RIGHTS LEGEND:  This computer software is submitted with
*  "restricted rights."  Use, duplication or disclosure is subject to the
*  restrictions as set forth in NASA FAR SUP 18-52.227-79 (April 1985)
*  "Commercial Computer Software- Restricted Rights (April 1985)."  Open
*  Software Foundation, Inc., 11 Cambridge Center, Cambridge, MA  02142.  If
*  the contract contains the Clause at 18-52.227-74 "Rights in Data General"
*  then the "Alternate III" clause applies.
*  
*  (c) Copyright 1989, 1990, Open Software Foundation, Inc.
*  ALL RIGHTS RESERVED 
*  
*  
* Open Software Foundation is a trademark of The Open Software Foundation, Inc.
* OSF is a trademark of Open Software Foundation, Inc.
* OSF/Motif is a trademark of Open Software Foundation, Inc.
* Motif is a trademark of Open Software Foundation, Inc.
* DEC is a registered trademark of Digital Equipment Corporation
* DIGITAL is a registered trademark of Digital Equipment Corporation
* X Window System is a trademark of the Massachusetts Institute of Technology
*
*******************************************************************************
******************************************************************************/

/*
 * This module contains routines responsible for writing the .h files
 * produced by WML. All files are written into the current directory.
 *
 * Input:
 *	The resolved objects
 *
 * Output:
 *	UilSymGen.h
 *	UilSymArTy.h
 *	UilSymRArg.h
 *	UilUrmClas.h
 *	UilConst.h
 *	UilSymReas.h
 *	UilSymArTa.h
 *	UilSymCtl.h
 *	UilSymNam.h
 *	UilSymEnum.h
 *	UilSymCSet.h
 */


#include "wml.h"

#ifdef NULL
#undef NULL
#endif
#include <stdio.h>


/*
 * Routines used only in this module
 */
void wmlOutputUilSymGen ();
void wmlOutputUilSymArTy ();
void wmlOutputUilSymRArg ();
void wmlOutputUilUrmClas ();
void wmlOutputUilConst ();
void wmlOutputUilSymReas ();
void wmlOutputUilSymArTa ();
void wmlOutputUilSymCtl ();
void wmlOutputUilSymNam ();
void wmlOutputUilSymEnum ();
void wmlOutputUilSymCSet ();

/*
 * globals
 */

static char		*canned_warn =
"/*\n\
**\tThis file is automatically generated.  Do not edit it by hand.\n\
**/\n";

/*
 * Used to create masks for bytes in bit vectors. Accessed by bit numbers
 * from 1 - 8.
 */
static char		*bit_masks[] =	{""
					," | 1"		/* bit 1 */
					," | 2"		/* bit 2 */
					," | 4"		/* bit 3 */
					," | 8"		/* bit 4 */
					," | 16"	/* bit 5 */
					," | 32"	/* bit 6 */
					," | 64"	/* bit 7 */
					," | 128"};	/* bit 8 */

/*
 * To pick up maximum code values
 */
static int		max_object_code = 0;
static int		max_reason_code = 0;
static int		max_arg_code = 0;
static int		max_enumset_code = 0;
static int		max_enumval_code = 0;
static int		max_charset_code = 0;



/*
 * Output control routine, which simply outputs each .h file in turn.
 */

void wmlOutputHFiles ()

{

wmlOutputUilSymGen ();
wmlOutputUilSymArTy ();
wmlOutputUilSymRArg ();
wmlOutputUilUrmClas ();
wmlOutputUilConst ();
wmlOutputUilSymReas ();
wmlOutputUilSymArTa ();
wmlOutputUilSymCtl ();
wmlOutputUilSymNam ();
wmlOutputUilSymEnum ();
wmlOutputUilSymCSet ();

}



/*
 * Routine to write out UilSymGen.h
 *
 * This file defines the sym_k... literals for UIL. Each set of literals
 * typiclly increases monotonically from 1, with 0 used as en error value.
 *
 *	sym_k_<class>_object
 *		<class> is widget class name in lexicographic order
 *		gadgets are not include.
 *
 *	bit masks for table access
 *
 *	sym_k_<reason>_reason
 *		literals specifying all reasons, lexicographically ordered 
 *
 *	sym_k_<argument>_arg
 *		literals for all arguments, lexicographically ordered.
 *		Constraints are included, and ordered with the arguments.
 *
 *	sym_k_<enumset>_enumset
 *		literals naming each enumeration set, lexicographically ordered
 *
 *	Fixed literals naming character set character sizes
 *	sym_k_<charset>_charset
 *		literals naming each character set, lexicographically ordered
 */

void wmlOutputUilSymGen ()

{

char		*canned1 =
"\n/*  Define literals for objects */\n";


char		*canned3 =
"\n/*  Define literals for reasons */\n\n";


char		*canned4 =
"\n/*  Define literals for arguments */\n\n";

char		*canned5 =
"\n/*  Define literals for enumeration sets */\n\n";

char		*canned6 =
"\n/*  Define literals for enumeration values */\n\n";

char		*canned7 =
"\n/*  Define literals for character sets */\n\n";

FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlClassDefPtr		clsobj;		/* class object */
WmlDataTypeDefPtr	datobj;		/* data type object */
WmlResourceDefPtr	resobj;		/* resource object */
WmlEnumSetDefPtr	enumsetobj;	/* enumeration set object */
WmlEnumValueDefPtr	enumvalobj;	/* enumeration value object */
WmlCharSetDefPtr	charsetobj;	/* character set object */


/*
 * Open the output file. Write the canned header stuff
 */
outfil = fopen ("UilSymGen.h", "w");
fprintf (outfil, canned_warn);

/*
 * Write the sym_k..._object literals
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_object\t%d\n",
	     clsobj->tkname,
	     clsobj->sym_code);
    if ( clsobj->sym_code > max_object_code )
	max_object_code = clsobj->sym_code;
    }

/*
 * Define the sym_k_..._reason literals
 */
fprintf (outfil, canned3);
for ( ndx=0 ; ndx<wml_obj_reason_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_reason_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_reason\t%d\n",
	     resobj->tkname,
	     resobj->sym_code);
    if ( resobj->sym_code > max_reason_code )
	max_reason_code = resobj->sym_code;
    }

/*
 * Define the sym_k_..._arg literals
 */
fprintf (outfil, canned4);
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_arg\t%d\n",
	     resobj->tkname,
	     resobj->sym_code);
    if ( resobj->sym_code > max_arg_code )
	max_arg_code = resobj->sym_code;
    }

/*
 * Define the sym_k_..._enumset structs and literals
 */
fprintf (outfil, canned5);
for ( ndx=0 ; ndx<wml_obj_enumset_ptr->cnt ; ndx++ )
    {
    enumsetobj = (WmlEnumSetDefPtr) wml_obj_enumset_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_enumset\t%d\n",
	     enumsetobj->tkname,
	     enumsetobj->sym_code);
    if ( enumsetobj->sym_code > max_enumset_code )
	max_enumset_code = enumsetobj->sym_code;
    }

/*
 * Define the sym_k_..._enumval literals
 */
fprintf (outfil, canned6);
for ( ndx=0 ; ndx<wml_obj_enumval_ptr->cnt ; ndx++ )
    {
    enumvalobj = (WmlEnumValueDefPtr) wml_obj_enumval_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_enumval\t%d\n",
	     enumvalobj->syndef->name,
	     enumvalobj->sym_code);
    if ( enumvalobj->sym_code > max_enumval_code )
	max_enumval_code = enumvalobj->sym_code;
    }

/*
 * Define the sym_k_..._charsize literals
 * Define the sym_k_..._charset literals
 */
fprintf (outfil, canned7);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    charsetobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    fprintf (outfil, "#define sym_k_%s_charset\t%d\n",
	     charsetobj->syndef->name,
	     charsetobj->sym_code);
    if ( charsetobj->sym_code > max_charset_code )
	max_charset_code = charsetobj->sym_code;
    }

/*
 * close the output file
 */
printf ("\nCreated UilSymGen.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymArTy.h
 *
 * A table of data types accessed by argument type (sym_k_<arg>_arg, in
 * the form
 *	...
 *	sym_k_<data_type>_value,
 */

void wmlOutputUilSymArTy ()

{

char			*canned1 =
"/*  Table of the types of arguments\n\
    The table is indexed by argument with each entry the\n\
    permitted type for that argument.\n\
*/\n\
\n\
static unsigned char argument_type_table_vec[] =\n\
  {\n\
    0,\n";

char			*canned1a =
"  };\n\
externaldef(uil_sym_glbl) unsigned char *argument_type_table =\n\
\t argument_type_table_vec;\n";

FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlDataTypeDefPtr	datobj;		/* data type object */
WmlResourceDefPtr	resobj;		/* resource object */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymArTy.h", "w");
fprintf (outfil, canned_warn);

/*
 * Create table entries, similar to writing sym_k...
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    datobj = resobj->dtype_def;
    fprintf (outfil, "    sym_k_%s_value,\n",
	     datobj->tkname);
    }
fprintf (outfil, canned1a);

/*
 * close the output file
 */
printf ("\nCreated UilSymArTy.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymRArg.h
 *
 * Related argument table
 */

void wmlOutputUilSymRArg ()

{

char			*canned1 =
"/*	Related argument table. Each non-zero entry is the code\n\
	of the related argument.\n\
 */\n\
\n\
static unsigned short int related_argument_table_vec[] =\n\
  {\n\
    0,\n";

char			*canned1a =
"  };\n\
externaldef(uil_sym_glbl) unsigned short int *related_argument_table =\n\
\t\trelated_argument_table_vec;\n";

FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlResourceDefPtr	resobj;		/* resource object */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymRArg.h", "w");
fprintf (outfil, canned_warn);

/*
 * Create table entries, similar to writing sym_k...
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    fprintf (outfil, "    %d,\n",
	     resobj->related_code);
    }
fprintf (outfil, canned1a);

/*
 * close the output file
 */
printf ("\nCreated UilSymRArg.h");
fclose (outfil);

}



/*
 * Routine to write out UilUrmClas.h
 *
 * Table of convenience function names indexed by the sym_k_<class> literal
 *	for both widgets and gadgets
 * Table of resource names indexed by the sym_k_<argument>_arg and
 *	sym_k_<reason>_reason codes.
 */

void wmlOutputUilUrmClas ()

{

char			*canned1 =
"\n/*  Define mapping of UIL widget types to convenience functions.  */\n\
static char *uil_widget_funcs_vec[] = {\n\
  \"\",\t  /* NOT USED */\n";

char			*canned2 =
"};\n\
externaldef(uil_sym_glbl) char **uil_widget_funcs = uil_widget_funcs_vec;\n\
\n\
/*  Define mapping of UIL widget classes to matching gadget class.  */\n\
static unsigned short int uil_gadget_variants_vec[] = {\n\
  0,\t  /* NOT USED */\n";

char			*canned3 =
"};\n\
externaldef(uil_sym_glbl) unsigned short int *uil_gadget_variants =\n\
\t\tuil_gadget_variants_vec;\n\
\n\
/*  Define mapping of dialog types to non-dialog URM widget classes.  */\n\
static unsigned short int uil_urm_nondialog_class_vec[] = {\n\
  0,\t/* NOT USED */\n";

char			*canned4 =
"};\n\
externaldef(uil_sym_glbl) unsigned short int *uil_urm_nondialog_class =\n\
\t\tuil_urm_nondialog_class_vec;\n\
\n\
/*  Define mapping of widget controls to a (subtree) resource.  */\n\
static unsigned short int uil_urm_subtree_resource_vec[] = {\n\
  0,\t/* NOT USED */\n";

char			*canned5 =
"};\n\
externaldef(uil_sym_glbl) unsigned short int *uil_urm_subtree_resource =\n\
\t\tuil_urm_subtree_resource_vec;\n\
\n\
/*  Define mapping of arguments to toolkit names.  */\n\
static char *uil_argument_toolkit_names_vec[] = {\n\
  \"\",\t  /* NOT USED */\n";

char			*canned6 =
"};\n\
externaldef(uil_sym_glbl) char **uil_argument_toolkit_names =\n\
\t\tuil_argument_toolkit_names_vec;\n\
\n\
/*  Define mapping of reasons to toolkit names.  */\n\
static char *uil_reason_toolkit_names_vec[] = {\n\
  \"\",\t/* NOT USED */\n";

char			*canned7 =
"};\n\
externaldef(uil_sym_glbl) char **uil_reason_toolkit_names =\n\
\t\tuil_reason_toolkit_names_vec;\n";



FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlClassDefPtr		clsobj;		/* class object */
WmlSynClassDefPtr	synobj;		/* syntactic object */
WmlClassDefPtr		varobj;		/* variant (widget) class object */
WmlResourceDefPtr	resobj;		/* argument/reason object */
WmlSynResourceDefPtr	synres;		/* arg/reason syntactic object */
WmlResourceDefPtr	mapresobj;	/* controls map to resource object */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilUrmClas.h", "w");
fprintf (outfil, canned_warn);

/*
 * Write entries for widgets
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    if ( clsobj->sym_code == 0 ) continue;
    synobj = clsobj->syndef;
    if ( synobj->int_lit != NULL )
	fprintf (outfil, "  \"%s\",\n", synobj->convfunc);
    else 
	fprintf (outfil, "  \"%s\",\t\n", synobj->convfunc);
    }
fprintf (outfil, canned2);

/*
 * Write entries for gadget variants of widget classes
 */
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    if ( clsobj->sym_code == 0 ) continue;
    varobj = clsobj->variant;
    synobj = clsobj->syndef;
    if ( varobj==NULL || synobj->type==WmlClassTypeGadget )
	fprintf (outfil, "  0,\n");
    else 
	{
	synobj = varobj->syndef;
	if ( synobj->int_lit != NULL )
	    fprintf (outfil, "  sym_k_%s_object,\n",
		     synobj->int_lit);
	else 
	    fprintf (outfil, "  sym_k_%s_object,\n",
		     synobj->name);
	}
    }
fprintf (outfil, canned3);

/*
 * Write entries for non-dialog widgets
 */
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    if ( clsobj->sym_code == 0 ) continue;
    varobj = clsobj->nondialog;
    synobj = clsobj->syndef;
    if ( varobj == NULL )
	fprintf (outfil, "  0,\n");
    else
	{
	synobj = varobj->syndef;
	if ( synobj->int_lit != NULL )
	    fprintf (outfil, "  sym_k_%s_object,\n",
		     synobj->int_lit);
	else 
	    fprintf (outfil, "  sym_k_%s_object,\n",
		     synobj->name);
	}
    }
fprintf (outfil, canned4);

/*
 * Write entries for the resource a widget's controls map to
 */
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    if ( clsobj->sym_code == 0 ) continue;
    synobj = clsobj->syndef;
    mapresobj = clsobj->ctrlmapto;
    if ( mapresobj == NULL )
	fprintf (outfil, "  0,\n");
    else
	fprintf (outfil, "  sym_k_%s_arg,\n", mapresobj->tkname);
    }
fprintf (outfil, canned5);

/*
 * Write entries for arguments
 */
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    synres = resobj->syndef;
    if ( resobj->sym_code == 0 ) continue;
    fprintf (outfil, "  %s,\n",
	     synres->resliteral);
    }
fprintf (outfil, canned6);

/*
 * Write entries for reasons
 */
for ( ndx=0 ; ndx<wml_obj_reason_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_reason_ptr->hvec[ndx].objptr;
    synres = resobj->syndef;
    if ( resobj->sym_code == 0 ) continue;
    fprintf (outfil, "  %s,\n",
	     synres->resliteral);
    }
fprintf (outfil, canned7);

/*
 * close the output file
 */
printf ("\nCreated UilUrmClas.h");
fclose (outfil);

}



/*
 * Routine to write out UilConst.h
 *
 * A bit vector showing which arguments are constraints.
 */

void wmlOutputUilConst ()

{

char			*canned1 =
"/* Table indexed by argument indicating whether\n\
   argument is a constraint (TRUE) or a regular\n\
   argument (FALSE).  Each entry is one bit.\n\
   Index and mask macros are defined to simplify\n\
   access to the table\n\
*/\n\
\n\
static unsigned char constraint_tab_vec[] = {\n";

char			*canned1a =
"};\n\
externaldef(uil_sym_glbl) unsigned char *constraint_tab =\n\
\t\tconstraint_tab_vec;\n";


FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlResourceDefPtr	resobj;		/* resource object */
WmlSynResourceDefPtr	synobj;		/* syntactic object */
char			maskbuf[100];	/* to constuct each mask */
int			bitno;		/* current bit number, from code */

/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilConst.h", "w");
fprintf (outfil, canned_warn);

/*
 * Process the arguments in code order. We start with 1, and write out
 * the mask after processing 8 codes.
 */
fprintf (outfil, canned1);
strcpy (maskbuf, "0");
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    synobj = resobj->syndef;
    bitno = resobj->sym_code % 8;
    if ( bitno == 0 ) bitno = 8;
    if ( synobj->type == WmlResourceTypeConstraint )
	strcat (maskbuf, bit_masks[bitno]);
    if ( bitno == 8 )
	{
	fprintf (outfil, "%s,\n", maskbuf);
	strcpy (maskbuf, "0");
	}
    }
if ( bitno != 8 )
    fprintf (outfil, "%s", maskbuf);
fprintf (outfil, canned1a);

/*
 * close the output file
 */
printf ("\nCreated UilConst.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymReas.h
 *
 * This file defines the reasons supported by each class. For each
 * reason, there is a bit vector with the bit for each supporting class
 * turned on if the reason is supported. There is then a vector pointing
 * to these bit vectors for all reasons. This vector is accessed by
 * sym_k_..._reason to find the reasons bit vector, then by sym_k_..._object
 * to check the bit.
 */

void wmlOutputUilSymReas ()

{

char			*canned1 =
"\n/*\n\
 * Bit vectors for each reason. The entries in the vector correspond\n\
 * to each class.\n\
 */\n";

char			*bvechdr =
"\n\
/* sym_k_%s_reason */\n\
static unsigned char reason_class_vec%d[] =\n\
  {\n";

char			*canned2 =
"\n/*\n\
 * Table of bit vectors accessed by sym_k_..._reason\n\
 */\n\
static unsigned char *allowed_reason_table_vec[] =\n\
  {\n\
  NULL,\t/* UNUSED */\n";

char			*canned3 =
"  };\n\
externaldef(uil_sym_glbl) unsigned char **allowed_reason_table =\n\
\t\tallowed_reason_table_vec;\n";

FILE			*outfil;	/* output file */
int			resndx;		/* outer loop index */
WmlResourceDefPtr	resobj;		/* current reason */
int			clsndx;		/* inner loop index */
WmlClassDefPtr		clsobj;		/* current class object */
WmlClassResDefPtr	resref;		/* class' resource reference */
int			itemno;		/* item in bye */
char			maskbuf[500];	/* current mask buffer */
char			itembuf[100];	/* for current item */
int			donl;		/* TRUE if append \n to mask */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymReas.h", "w");
fprintf (outfil, canned_warn);
fprintf (outfil, canned1);

/*
 * Generate the bit vectors for each class. Outer loop on the reason code,
 * inner loop on the class code.
 */
for ( resndx=0 ; resndx<wml_obj_reason_ptr->cnt ; resndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_reason_ptr->hvec[resndx].objptr;
    fprintf (outfil, bvechdr, resobj->tkname, resobj->sym_code);

    /*
     * inner loop on widget class.
     */
    strcpy (maskbuf, " ");
    for ( clsndx=0 ; clsndx<wml_obj_class_ptr->cnt ; clsndx++ )
	{
	clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[clsndx].objptr;
	itemno = (clsobj->sym_code+1) % 8;
	donl = FALSE;
	resref = wmlResolveResIsMember (resobj, clsobj->reasons);
	if ( resref != NULL )
	    if ( resref->exclude != WmlAttributeTrue )
		{
		sprintf (itembuf, " _BIT_MASK(sym_k_%s_object) |",
			 clsobj->tkname);
		strcat (maskbuf, itembuf);
		donl = TRUE;
		}
	if ( donl )
	    strcat (maskbuf, "\n ");
	if ( itemno == 0 )
	    {
	    fprintf (outfil, "%s 0", maskbuf);
	    strcpy (maskbuf, ",");
	    }
	}
    if ( itemno != 0 )
	fprintf (outfil, "%s 0};\n", maskbuf);
    else
	fprintf (outfil, "};\n");
    }

/*
 * Write the vector of vectors.
 */
fprintf (outfil, canned2);
for ( resndx=0 ; resndx<wml_obj_reason_ptr->cnt ; resndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_reason_ptr->hvec[resndx].objptr;
    fprintf (outfil, "  reason_class_vec%d,\n", resobj->sym_code);
    }
fprintf (outfil, canned3);

/*
 * close the output file
 */
printf ("\nCreated UilSymReas.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymArTa.h
 *
 * This file defines the arguments supported by each class. For each
 * argument, there is a bit vector with the bit for each supporting class
 * turned on if the argument is supported. There is then a vector pointing
 * to these bit vectors for all arguments. This vector is accessed by
 * sym_k_..._arg to find the arguments bit vector, then by sym_k_..._object
 * to check the bit.
 */

void wmlOutputUilSymArTa ()

{

char			*canned1 =
"\n/*\n\
 * Bit vectors for each argument. The entries in the vector correspond\n\
 * to each class.\n\
 */\n";

char			*bvechdr =
"\n\
/* sym_k_%s_arg */\n\
static unsigned char arg_class_vec%d[] =\n\
  {\n";

char			*canned2 =
"\n/*\n\
 * Table of bit vectors accessed by sym_k_..._arg\n\
 */\n\
static unsigned char *allowed_argument_table_vec[] =\n\
  {\n\
  NULL,\t/* UNUSED */\n";

char			*canned3 =
"  };\n\
externaldef(uil_sym_glbl) unsigned char **allowed_argument_table =\n\
\t\tallowed_argument_table_vec;\n";

FILE			*outfil;	/* output file */
int			resndx;		/* outer loop index */
WmlResourceDefPtr	resobj;		/* current argument */
int			clsndx;		/* inner loop index */
WmlClassDefPtr		clsobj;		/* current class object */
WmlClassResDefPtr	resref;		/* class' resource reference */
int			itemno;		/* item in bye */
char			maskbuf[500];	/* current mask buffer */
char			itembuf[100];	/* for current item */
int			donl;		/* TRUE if append \n to mask */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymArTa.h", "w");
fprintf (outfil, canned_warn);
fprintf (outfil, canned1);

/*
 * Generate the bit vectors for each class. Outer loop on the argument code,
 * inner loop on the class code.
 */
for ( resndx=0 ; resndx<wml_obj_arg_ptr->cnt ; resndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[resndx].objptr;
    fprintf (outfil, bvechdr, resobj->tkname, resobj->sym_code);

    /*
     * inner loop on widget class.
     */
    strcpy (maskbuf, " ");
    for ( clsndx=0 ; clsndx<wml_obj_class_ptr->cnt ; clsndx++ )
	{
	clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[clsndx].objptr;
	itemno = (clsobj->sym_code+1) % 8;
	donl = FALSE;
	resref = wmlResolveResIsMember (resobj, clsobj->arguments);
	if ( resref != NULL )
	    if ( resref->exclude != WmlAttributeTrue )
		{
		sprintf (itembuf, " _BIT_MASK(sym_k_%s_object) |",
			 clsobj->tkname);
		strcat (maskbuf, itembuf);
		donl = TRUE;
		}
	if ( donl )
	    strcat (maskbuf, "\n ");
	if ( itemno == 0 )
	    {
	    fprintf (outfil, "%s 0", maskbuf);
	    strcpy (maskbuf, ",");
	    }
	}
    if ( itemno != 0 )
	fprintf (outfil, "%s 0};\n", maskbuf);
    else
	fprintf (outfil, "};\n");
    }

/*
 * Write the vector of vectors.
 */
fprintf (outfil, canned2);
for ( resndx=0 ; resndx<wml_obj_arg_ptr->cnt ; resndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[resndx].objptr;
    fprintf (outfil, "  arg_class_vec%d,\n", resobj->sym_code);
    }
fprintf (outfil, canned3);

/*
 * close the output file
 */
printf ("\nCreated UilSymArTa.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymCtl.h
 *
 * This file defines the controls supported by each class. For each
 * object, there is a bit vector with the bit for each supporting class
 * turned on if the object is supported. There is then a vector pointing
 * to these bit vectors for all objects. This vector is accessed by
 * sym_k_..._object to find the objects bit vector, then by sym_k_..._object
 * to check the bit.
 */

void wmlOutputUilSymCtl ()

{

char			*canned1 =
"\n/*\n\
 * Bit vectors for each control. The entries in the vector correspond\n\
 * to each class.\n\
 */\n";

char			*bvechdr =
"\n\
/* sym_k_%s_object */\n\
static unsigned char object_class_vec%d[] =\n\
  {\n";

char			*canned2 =
"\n/*\n\
 * Table of bit vectors accessed by sym_k_..._object\n\
 */\n\
static unsigned char *allowed_control_table_vec[] =\n\
  {\n\
  NULL,\t/* UNUSED */\n";

char			*canned3 =
"  };\n\
externaldef(uil_sym_glbl) unsigned char **allowed_control_table =\n\
\t\tallowed_control_table_vec;\n";

FILE			*outfil;	/* output file */
int			ctlndx;		/* outer loop index */
WmlClassDefPtr		ctlobj;		/* current class allowing controls */
int			clsndx;		/* inner loop index */
WmlClassDefPtr		clsobj;		/* current class object */
int			itemno;		/* item in bye */
char			maskbuf[500];	/* current mask buffer */
char			itembuf[100];	/* for current item */
int			donl;		/* TRUE if append \n to mask */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymCtl.h", "w");
fprintf (outfil, canned_warn);
fprintf (outfil, canned1);

/*
 * Generate the bit vectors for each class. Outer loop on the class code,
 * inner loop on the class code.
 */
for ( ctlndx=0 ; ctlndx<wml_obj_class_ptr->cnt ; ctlndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ctlndx].objptr;
    fprintf (outfil, bvechdr, clsobj->tkname, clsobj->sym_code);

    /*
     * inner loop on widget class.
     */
    strcpy (maskbuf, " ");
    for ( clsndx=0 ; clsndx<wml_obj_class_ptr->cnt ; clsndx++ )
	{
	ctlobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[clsndx].objptr;
	itemno = (ctlobj->sym_code+1) % 8;
	donl = FALSE;
	if ( wmlResolveCtlIsMember(clsobj,ctlobj->controls) != NULL)
	    {
	    sprintf (itembuf, " _BIT_MASK(sym_k_%s_object) |",
		     ctlobj->tkname);
	    strcat (maskbuf, itembuf);
	    donl = TRUE;
	    }
	if ( donl )
	    strcat (maskbuf, "\n ");
	if ( itemno == 0 )
	    {
	    fprintf (outfil, "%s 0", maskbuf);
	    strcpy (maskbuf, ",");
	    }
	}
    if ( itemno != 0 )
	fprintf (outfil, "%s 0};\n", maskbuf);
    else
	fprintf (outfil, "};\n");
    }

/*
 * Write the vector of vectors.
 */
fprintf (outfil, canned2);
for ( ctlndx=0 ; ctlndx<wml_obj_class_ptr->cnt ; ctlndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ctlndx].objptr;
    fprintf (outfil, "  object_class_vec%d,\n", clsobj->sym_code);
    }
fprintf (outfil, canned3);

/*
 * close the output file
 */
printf ("\nCreated UilSymCtl.h");
fclose (outfil);

}



/*
 * Predicate to indicate if a class object is in a controls list.
 */

int wmlResolveCtlIsMember (ctlobj, ctlref)
    WmlClassDefPtr		ctlobj;
    WmlClassCtrlDefPtr		ctlref;

{

while ( ctlref != NULL )
    {
    if ( ctlref->ctrl == ctlobj ) return TRUE;
    ctlref = ctlref->next;
    }
return FALSE;

}



/*
 * Routine to write out UilSymNam.h
 *
 * Tables of names of object indexed by their various sym_k_ literals.
 */

void wmlOutputUilSymNam ()

{

char			*canned1 =
"/*  Define mapping of sym_k_..._object codes to widget names.  */\n\
\n\
externaldef(uil_sym_glbl) int uil_max_object = %d;\n\
static char *uil_widget_names_vec[] = {\n\
    \"\",\t/* NOT USED */\n";

char			*canned2 =
"};\n\
externaldef(uil_sym_glbl) char **uil_widget_names =\n\
\t\tuil_widget_names_vec;\n\
\n\n\
/*  Define mapping of sym_k_..._arg codes to argument names.  */\n\
\n\
externaldef(uil_sym_glbl) int uil_max_arg = %d;\n\
static char *uil_argument_names_vec[] = {\n\
    \"\",\t/* NOT USED */\n";

char			*canned3 =
"};\n\
externaldef(uil_sym_glbl) char **uil_argument_names =\n\
\t\tuil_argument_names_vec;\n\
\n\n\
/*  Define mapping of sym_k_..._reason to reason names.  */\n\
\n\
externaldef(uil_sym_glbl) int uil_max_reason = %d;\n\
static char *uil_reason_names_vec[] = {\n\
    \"\",\t/* NOT USED */\n";

char			*canned4 =
"};\n\
externaldef(uil_sym_glbl) char **uil_reason_names =\n\
\t\tuil_reason_names_vec;\n\
\n\n\
/*  Define mapping of sym_k_..._enumval to enumeration value names.  */\n\
\n\
externaldef(uil_sym_glbl) int uil_max_enumset = %d;\n\
externaldef(uil_sym_glbl) int uil_max_enumval = %d;\n\
static char *uil_enumval_names_vec[] = {\n\
    \"\",\t/* NOT USED */\n";

char			*canned5 =
"};\n\
externaldef(uil_sym_glbl) char **uil_enumval_names =\n\
\t\tuil_enumval_names_vec;\n\
\n\n\
/*  Define mapping of sym_k_..._charset to enumeration value names.  */\n\
\n\
externaldef(uil_sym_glbl) int uil_max_charset = %d;\n\
static char *uil_charset_names_vec[] = {\n\
    \"\",\t/* NOT USED */\n\
    \"<userdefined>\",\n";

char			*canned6 =
"};\n\
externaldef(uil_sym_glbl) char **uil_charset_names =\n\
\t\tuil_charset_names_vec;\n";


FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlClassDefPtr		clsobj;		/* class object */
WmlClassDefPtr		varobj;		/* gadget class object */
WmlSynClassDefPtr	synobj;		/* syntactic object */
WmlResourceDefPtr	resobj;		/* argument/reason object */
WmlSynResourceDefPtr	synres;		/* arg/reason syntactic object */
WmlEnumValueDefPtr	evobj;		/* enumeration value object */
WmlSynEnumValueDefPtr	synev;		/* enumeration value syntactic obj */
WmlCharSetDefPtr	csobj;		/* character set object */
WmlSynCharSetDefPtr	syncs;		/* character set syntactic obj */


/*
 * Open the output file. Write canned header.
 */
outfil = fopen ( "UilSymNam.h", "w");
fprintf (outfil, canned_warn);

/*
 * Write entries for widgets
 */
fprintf (outfil, canned1, max_object_code);
for ( ndx=0 ; ndx<wml_obj_class_ptr->cnt ; ndx++ )
    {
    clsobj = (WmlClassDefPtr) wml_obj_class_ptr->hvec[ndx].objptr;
    if ( clsobj->sym_code == 0 ) continue;
    synobj = clsobj->syndef;
    fprintf (outfil, "    \"%s\",\n",
	     synobj->name);
    }

/*
 * Write entries for arguments
 */
fprintf (outfil, canned2, max_arg_code);
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    synres = resobj->syndef;
    if ( resobj->sym_code == 0 ) continue;
    fprintf (outfil, "    \"%s\",\n",
	     synres->name);
    }

/*
 * Write entries for reasons
 */
fprintf (outfil, canned3, max_reason_code);
for ( ndx=0 ; ndx<wml_obj_reason_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_reason_ptr->hvec[ndx].objptr;
    synres = resobj->syndef;
    if ( resobj->sym_code == 0 ) continue;
    fprintf (outfil, "    \"%s\",\n",
	     synres->name);
    }

/*
 * Write entries for enumeration values
 */
fprintf (outfil, canned4, max_enumset_code, max_enumval_code);
for ( ndx=0 ; ndx<wml_obj_enumval_ptr->cnt ; ndx++ )
    {
    evobj = (WmlEnumValueDefPtr) wml_obj_enumval_ptr->hvec[ndx].objptr;
    synev = evobj->syndef;
    if ( evobj->sym_code == 0 ) continue;
    fprintf (outfil, "    \"%s\",\n",
	     synev->name);
    }

/*
 * Write entries for character sets
 */
fprintf (outfil, canned5, max_charset_code);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    fprintf (outfil, "    \"%s\",\n",
	     syncs->name);
    }
fprintf (outfil, canned6);

/*
 * close the output file
 */
printf ("\nCreated UilSymNam.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymEnum.h
 *
 * This file defines the enumeration sets recognized by UIL. There is an
 * entry in this file for each enumeration set. The definitions are accessed
 * by the sym_k_..._enumset code. Each consists of a structure containing
 * a vector of enumeration value descriptors, each of which is the name
 * of the value and its value.
 *
 * UilSymEnum.h contains:
 *	- Vectors of value descriptors for each table entry
 *	- The table itself.
 *	- A table given the sym_k_..._enumset code for each argument which
 *	  has an enumeration set.
 *	- A table accessed by sym_k_..._enumval code giving the actual value
 *	  for each enumeration value.
 *
 * The typedefs for the tables are in UilSymGen.h
 */

void wmlOutputUilSymEnum ()

{

char			*canned1 =
"\n\
/*\n\
 * Enumeration value vectors for each enumeration set\n\
 */\n\
\n";

char			*valhdr =
"\n\
static unsigned short int enum_value_vec%d[] =\n\
  {\n";

char			*canned3 =
"\n\
/*\n\
 * Enumeration set descriptor table\n\
 */\n\
static UilEnumSetDescDef enum_set_table_vec[] =\n\
  {\n\
    {0,NULL},\n";

char			*canned4 =
"  };\n\
externaldef(uil_sym_glbl) UilEnumSetDescDef *enum_set_table =\n\
\t\tenum_set_table_vec;\n\
/*\n\
 * Enumeration set table, accessed by sym_k_..._arg code. Each non-zero entry\n\
 * is the sym_k_..._enumset code for the argument's enumeration set.\n\
 */\n\
static unsigned short int argument_enumset_table_vec[] =\n\
  {\n\
    0,\n";

char			*canned5 =
"  };\n\
externaldef(uil_sym_glbl) unsigned short int *argument_enumset_table =\n\
\t\targument_enumset_table_vec;\n\
/*\n\
 * Enumeration value table, accessed by sym_k_..._enumval code. Each entry is\n\
 * the actual value associated with the code.\n\
 */\n\
static int enumval_values_table_vec[] =\n\
  {\n\
  0,\n";

char			*canned5a =
"  };\n\
externaldef(uil_sym_glbl) int *enumval_values_table =\n\
\t\tenumval_values_table_vec;\n";


FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlEnumSetDefPtr	enumsetobj;	/* enumeration set object */
WmlEnumSetValDefPtr	esvobj;		/* current enum set value list element */
WmlEnumValueDefPtr	evobj;		/* current enumeration value object */
WmlResourceDefPtr	resobj;		/* resource object */


/*
 * Open the output file. Write the canned header stuff
 */
outfil = fopen ("UilSymEnum.h", "w");
fprintf (outfil, canned_warn);

/*
 * Generate the enumeration value vectors for each enumeration set.
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_enumset_ptr->cnt ; ndx++ )
    {
    enumsetobj = (WmlEnumSetDefPtr) wml_obj_enumset_ptr->hvec[ndx].objptr;
    fprintf (outfil, valhdr, enumsetobj->sym_code);
    for ( esvobj=enumsetobj->values ; esvobj!=NULL ; esvobj=esvobj->next )
	{
	evobj = esvobj->value;
	fprintf (outfil, "    %d,\n",
		 evobj->sym_code);
	}
    fprintf (outfil, "  };\n");
    }

/*
 * Generate the enumeration set tables
 */
fprintf (outfil, canned3);
for ( ndx=0 ; ndx<wml_obj_enumset_ptr->cnt ; ndx++ )
    {
    enumsetobj = (WmlEnumSetDefPtr) wml_obj_enumset_ptr->hvec[ndx].objptr;
    fprintf (outfil, "    {%d,enum_value_vec%d},\n",
	     enumsetobj->values_cnt,
	     enumsetobj->sym_code);
    }

/*
 * Create enumset table entries for arguments, similar to writing sym_k...
 */
fprintf (outfil, canned4);
for ( ndx=0 ; ndx<wml_obj_arg_ptr->cnt ; ndx++ )
    {
    resobj = (WmlResourceDefPtr) wml_obj_arg_ptr->hvec[ndx].objptr;
    if ( resobj->enumset_def == NULL )
	fprintf (outfil, "    0,\n");
    else
	fprintf (outfil, "    %d,\n",
		 resobj->enumset_def->sym_code);
    }

/*
 * Create the enumval values table.
 */
fprintf (outfil, canned5);
for ( ndx=0 ; ndx<wml_obj_enumval_ptr->cnt ; ndx++ )
    {
    evobj = (WmlEnumValueDefPtr) wml_obj_enumval_ptr->hvec[ndx].objptr;
    fprintf (outfil, "  %s,\n", evobj->syndef->enumlit);
    }
fprintf (outfil, canned5a);

/*
 * close the output file
 */
printf ("\nCreated UilSymEnum.h");
fclose (outfil);

}



/*
 * Routine to write out UilSymCSet.h
 *
 * This file specifies the various attributes for the character sets
 * recognized by UIL. There is a table for each of the following
 * attributes:
 *	- Standards name associated with the character set
 *	- Writing direction, from XmSTRING_DIRECTION_...
 *	- Parsing direction, from XmSTRING_DIRECTION_...
 *	- Bytes per character, from sym_k_..._charsize (in UilSymGen.h)
 *	- A pair of tables for recognizing $LANG settings:
 *		o a table of all names under which a character set might
 *		  be legally recognized (upper case).
 *		o the sym_k_..._charset code for each entry
 *		o a variable giving the number of entries in the table
 *
 * All tables are accessed by the sym_k_..._charset 
 *
 */

void wmlOutputUilSymCSet ()

{

char			*canned1 =
"\n\
/*\n\
 * Character set XmString name table, accessed by sym_k_..._charset code.\n\
 * Each entry is the name which identifies the character set in a XmString.\n\
 */\n\
static char *charset_xmstring_names_table_vec[] =\n\
  {\n\
    0,\n\
    \"<userdefined>\",\n";

char			*canned2 =
"};\n\
externaldef(uil_sym_glbl) char **charset_xmstring_names_table =\n\
\t\tcharset_xmstring_names_table_vec;\n\
/*\n\
 * Character set writing direction table, accessed by sym_k_..._charset code.\n\
 * Each entry is the XmSTRING_DIRECTION_... code which identifies the\n\
 * writing direction for the character set in a XmString.\n\
 */\n\
static unsigned char charset_wrdirection_table_vec[] =\n\
  {\n\
    0,\n\
    0,\t/* userdefined */\n";

char			*canned3 =
"};\n\
externaldef(uil_sym_glbl) unsigned char *charset_writing_direction_table =\n\
\t\tcharset_wrdirection_table_vec;\n\
/*\n\
 * Character set parsing direction table, accessed by sym_k_..._charset code.\n\
 * Each entry is the XmSTRING_DIRECTION_... code which identifies the\n\
 * parsing direction for the character set in a XmString.\n\
 */\n\
static unsigned char charset_parsdirection_table_vec[] =\n\
  {\n\
    0,\n\
    0,\t/* userdefined */\n";

char			*canned4 =
"};\n\
externaldef(uil_sym_glbl) unsigned char *charset_parsing_direction_table =\n\
\t\tcharset_parsdirection_table_vec;\n\
/*\n\
 * Character set character size table, accessed by sym_k_..._charset code.\n\
 * Each entry is the sym_k_..._charsize literal which names the character\n\
 * size for the character set in a XmString.\n\
 */\n\
static unsigned char charset_charsize_table_vec[] =\n\
  {\n\
    0,\n\
    0,\t/* userdefined */\n";

char			*canned5 =
"};\n\
externaldef(uil_sym_glbl) unsigned char *charset_character_size_table =\n\
\t\tcharset_charsize_table_vec;\n\
/*\n\
 * All the names under which a character set may be legally named in a \n\
 * $LANG variable (upper case).\n\
 */\n\
static char *charset_lang_names_table_vec[] =\n\
  {\n";

char			*canned6 =
"};\n\
externaldef(uil_sym_glbl) char **charset_lang_names_table =\n\
\t\tcharset_lang_names_table_vec;\n\
/*\n\
 * The sym_k_..._charset codes for charset_lang_names\n\
 */\n\
static unsigned short int charset_lang_codes_table_vec[] =\n\
  {\n";

char			*canned7 =
"};\n\
externaldef(uil_sym_glbl) unsigned short int *charset_lang_codes_table =\n\
\t\tcharset_lang_codes_table_vec;\n\
/*\n\
 * The number of entries in charset_lang_..._table tables\n\
 */\n\
externaldef(uil_sym_glbl) unsigned short int charset_lang_table_max = %d;\n";


FILE			*outfil;	/* output file */
int			ndx;		/* loop index */
WmlCharSetDefPtr	csobj;		/* character set object */
WmlSynCharSetDefPtr	syncs;		/* character set syntactic obj */
int			lang_max;	/* max value for $LANG tables */
int			alias_ndx;	/* alias loop index */
char			uname[200];	/* name converted to upper case */


/*
 * Open the output file. Write the canned header stuff
 */
outfil = fopen ("UilSymCSet.h", "w");
fprintf (outfil, canned_warn);

/*
 * Generate the standards name table
 */
fprintf (outfil, canned1);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    fprintf (outfil, "    \"%s\",\t/* %s */\n",
	     syncs->xms_name, syncs->name);
    }

/*
 * Generate the writing direction table
 */
fprintf (outfil, canned2);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    switch ( syncs->direction )
	{
	case WmlCharSetDirectionLtoR:
	    fprintf (outfil, "    XmSTRING_DIRECTION_L_TO_R,\t/* %s */\n",
		     syncs->name);
	    break;
	case WmlCharSetDirectionRtoL:
	    fprintf (outfil, "    XmSTRING_DIRECTION_R_TO_L,\t/* %s */\n",
		     syncs->name);
	    break;
	}
    }

/*
 * Generate the parsing direction table
 */
fprintf (outfil, canned3);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    switch ( syncs->parsedirection )
	{
	case WmlCharSetDirectionLtoR:
	    fprintf (outfil, "    XmSTRING_DIRECTION_L_TO_R,\t/* %s */\n",
		     syncs->name);
	    break;
	case WmlCharSetDirectionRtoL:
	    fprintf (outfil, "    XmSTRING_DIRECTION_R_TO_L,\t/* %s */\n",
		     syncs->name);
	    break;
	}
    }

/*
 * Generate the character size table
 */
fprintf (outfil, canned4);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    switch ( syncs->charsize )
	{
	case WmlCharSizeOneByte:
	    fprintf (outfil, "    sym_k_onebyte_charsize,\t/* %s */\n",
		     syncs->name);
	    break;
	case WmlCharSizeTwoByte:
	    fprintf (outfil, "    sym_k_twobyte_charsize,\t/* %s */\n",
		     syncs->name);
	    break;
	case WmlCharSizeMixed1_2Byte:
	    fprintf (outfil, "    sym_k_mixed1_2byte_charsize,\t/* %s */\n",
		     syncs->name);
	    break;
	}
    }

/*
 * Generate the $LANG name recognition table
 */
fprintf (outfil, canned5);
lang_max = 0;
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    strcpy (uname, syncs->name);
    wmlUpperCaseString (uname);
    fprintf (outfil, "    \"%s\",\t/* %s */\n",
	     uname, syncs->name);
    lang_max += 1;
    strcpy (uname, syncs->xms_name);
    wmlUpperCaseString (uname);
    fprintf (outfil, "    \"%s\",\t/* %s */\n",
	     uname, syncs->name);
    lang_max += 1;
    for ( alias_ndx=0 ; alias_ndx<syncs->alias_cnt ; alias_ndx++ )
	{
	strcpy (uname, syncs->alias_list[alias_ndx]);
	wmlUpperCaseString (uname);
	fprintf (outfil, "    \"%s\",\t/* %s */\n",
		 uname, syncs->name);
	lang_max += 1;
	}
    }

/*
 * Generate the $LANG code lookup table, in upper case
 */
fprintf (outfil, canned6);
for ( ndx=0 ; ndx<wml_obj_charset_ptr->cnt ; ndx++ )
    {
    csobj = (WmlCharSetDefPtr) wml_obj_charset_ptr->hvec[ndx].objptr;
    syncs = csobj->syndef;
    if ( csobj->sym_code == 0 ) continue;
    fprintf (outfil, "    sym_k_%s_charset,\n", syncs->name);
    fprintf (outfil, "    sym_k_%s_charset,\n", syncs->name);
    for ( alias_ndx=0 ; alias_ndx<syncs->alias_cnt ; alias_ndx++ )
	fprintf (outfil, "    sym_k_%s_charset,\n", syncs->name);
    }

/*
 * Generate the number of entries in the previous two tables
 */
fprintf (outfil, canned7, lang_max);

/*
 * close the output file
 */
printf ("\nCreated UilSymCSet.h");
fclose (outfil);

}



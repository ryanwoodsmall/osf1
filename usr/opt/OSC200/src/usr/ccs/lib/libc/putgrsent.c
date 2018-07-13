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
static char	*sccsid = "@(#)$RCSfile: putgrsent.c,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/06/07 23:37:10 $";
#endif 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
#if !defined(lint) && !defined(_NOIDENT)

#endif
/*
 * COMPONENT_NAME: (LIBCADM) Standard C Library System Admin Functions 
 *
 * FUNCTIONS: putgrsent 
 *
 * ORIGINS: 27 
 *
 * IBM CONFIDENTIAL -- (IBM Confidential Restricted when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989 
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * putgrsent.c	1.3  com/lib/c/adm,3.1,8943 9/13/89 10:44:20
 */

/* name space pollution clean up */
#ifdef _NAME_SPACE_WEAK_STRONG
#include "pollution.h"
#if !defined(_THREAD_SAFE)
#pragma weak putgrsent = __putgrsent
#endif
#endif
#include <stdio.h>
#include <grp.h>

/*                                                                    
 * FUNCTION: format a security/group file entry in stanza format
 *
 * RETURN VALUE DESCRIPTIONS:
 *	     - 0 on success
 *	     - nonzero on failure
 */

int
putgrsent(g, fp)
register struct group  *g;
FILE		       *fp;
{

	(void) fprintf (fp,"%s:\n", g->gr_name);
	if (*(g->gr_passwd) != NULL)
		(void) fprintf (fp,"\tpassword = %s\n", g->gr_passwd);

	/* end the stanza with a blank line */
	(void) putc('\n', fp);

	return (ferror (fp));
}

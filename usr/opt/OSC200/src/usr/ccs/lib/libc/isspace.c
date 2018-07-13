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
static char	*sccsid = "@(#)$RCSfile: isspace.c,v $ $Revision: 4.2.5.3 $ (DEC) $Date: 1993/10/05 21:02:23 $";
#endif 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * COMPONENT_NAME: (LIBCCHR) LIBC Character Classification Funcions
 *
 * FUNCTIONS: isspace
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991 
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * 1.2  com/lib/c/chr/isspace.c, libcchr, bos320, 9132320 7/23/91 18:18:18
 */
/*
 *
 * FUNCTION: Determines if a character is a space
 *	    
 *
 * PARAMETERS: c  -- character to be classified
 *
 *
 * RETURN VALUES: 0 -- if c is not a space
 *                >0 - If c is a space
 *
 *
 */
/* name space pollution clean up */
#ifdef _NAME_SPACE_WEAK_STRONG
#include "pollution.h"
#endif
#include <sys/localedef.h>
#include <ctype.h>

#ifdef isspace
#undef isspace
#endif

#pragma weak NCisspace = isspace

int 
isspace(int c)
{
	if (METHOD(__lc_ctype, iswctype) == NULL)
		return __iswctype_sb((wint_t)c, _ISSPACE, __lc_ctype);
	else
		return METHOD(__lc_ctype, iswctype)
			( (wint_t)c, _ISSPACE, __lc_ctype);
}

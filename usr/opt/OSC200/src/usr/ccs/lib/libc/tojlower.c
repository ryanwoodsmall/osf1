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
static char	*sccsid = "@(#)$RCSfile: tojlower.c,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/06/07 23:32:45 $";
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
 * COMPONENT_NAME: (LIBCGEN/KJI) Standard C Library Conversion Functions
 *
 * FUNCTIONS: tojlower
 *
 * ORIGINS: 10
 *
 * IBM CONFIDENTIAL -- (IBM Confidential Restricted when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   
/* tojlower.c	1.1  com/lib/c/gen/KJI,3.1,9021 10/19/89 17:27:23 */
/**********************************************************************/
/*								      */
/* SYNOPSIS							      */
/*	int							      */
/*	tojlower (c)						      */
/*	register c;						      */
/*								      */
/* DESCRIPTION							      */
/*	tojlower returns the Shift-JIS lowercase equivalent of a      */
/*	Shift-JIS uppercase letter.  The input should be the	      */
/*	Shift-JIS form of an uppercase ASCII letter.		      */
/*								      */
/* DIAGNOSTICS							      */
/*	If the input character is not the Shift-JIS form of an	      */
/*	uppercase ASCII letter, the function returns the input value. */
/*								      */
/**********************************************************************/
/* name space pollution clean up */
#ifdef _NAME_SPACE_WEAK_STRONG
#include "pollution.h"
#endif
#ifdef KJI
#include <NLctype.h>

int
tojlower (c)
register c;
{
	if (c < 0x8260 || c > 0x8279)
		/* c is outside the range [A-Z] & has no lowercase equivalent */
		return (c);
	return (_tojlower (c));
}
#endif  /* KJI */

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
/*	
 *	@(#)$RCSfile: __udivsi3.s,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 03:10:07 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Temporary version of divide for the GNU c compiler 
 * since libc doesn't get linked with the gnu library
 * Taken directly from the gnulib c source.
 */
	.verstamp	1 31
	.text	
	.align	2
	.file	2 "gnulib.c"
	.globl	__udivsi3
	.loc	2 64
 #  64	{
	.ent	__udivsi3 2
__udivsi3:
	.option	O1
	.frame	$sp, 0, $31
	.loc	2 65
 #  65	  return a / b;
	divu	$2, $4, $5
	j	$31
	.end	__udivsi3

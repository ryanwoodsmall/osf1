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
 *	@(#)$RCSfile: AuthUtils.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/19 23:59:14 $
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
#ifdef SEC_BASE

#ifndef _AuthUtils_h_
#define _AuthUtils_h_

/*
	filename:
		AuthUtils.h
	
	copyright:
		Copyright (c) 1990 SecureWare, Inc.
		ALL RIGHTS RESERVED
	
	function:
		Get/Write Information routines for interface packages
*/

int
	GetUserInfo(),
	GetDeviceInfo(),
	GetTerminalInfo(),
	GetSystemInfo(),

	WriteUserInfo(),
	WriteDeviceInfo(),
	WriteTerminalInfo(),
	WriteSystemInfo();

#endif /* _AuthUtils_h_ */
#endif /* SEC_BASE */

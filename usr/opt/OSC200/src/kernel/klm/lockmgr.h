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
 * @(#)$RCSfile: lockmgr.h,v $ $Revision: 1.1.5.2 $ (DEC) $Date: 1993/07/14 18:19:01 $
 */
/*	@(#)lockmgr.h	2.2 90/07/02 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 * From SUN 1.6
 */
#ifndef _KLM_LOCKMGR_H_ 
#define _KLM_LOCKMGR_H_ 
/*
 * Header file for Kernel<->Network Lock-Manager implementation
 */

/* NOTE: size of a lockhandle-id should track the size of an fhandle */
#define KLM_LHSIZE	32

/* the lockhandle uniquely describes any file in a domain */
typedef struct {
	struct vnode *lh_vp;			/* vnode of file */
	char *lh_servername;			/* file server machine name */
	struct {				/* fhandle (sort of) */
		struct __lh_ufsid {
			fsid_t		__lh_fsid;
			struct fid	__lh_fid;
		} __lh_ufs;
	} lh_id; /* 32 bytes */
} lockhandle_t;
#define lh_fsid	lh_id.__lh_ufs.__lh_fsid
#define lh_fid	lh_id.__lh_ufs.__lh_fid


/* define 'well-known' information */
#define KLM_PROTO	IPPROTO_UDP

/* define public routines */
int  klm_lockctl();

#endif

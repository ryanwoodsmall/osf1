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
static char *rcsid = "@(#)$RCSfile: xdr_klm.c,v $ $Revision: 1.1.3.3 $ (DEC) $Date: 1993/02/15 15:26:18 $";
#endif
#ifndef lint
static char sccsid[] = "%w% 90/07/23 NFSSRC4.0 Copyr 1984 Sun Micro";
#endif

/* 
 * Compiled from klm_prot.x using rpcgen.
 * DO NOT EDIT THIS FILE!
 * This is NOT source code!
 */

#include <rpc/rpc.h>
#include "klm_prot.h"

bool_t
xdr_klm_stats(xdrs, objp)
	XDR *xdrs;
	klm_stats *objp;
{
	if (!xdr_enum(xdrs, (enum_t *)objp)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_lock(xdrs, objp)
	XDR *xdrs;
	klm_lock *objp;
{
	if (!xdr_string(xdrs, &objp->server_name, LM_MAXSTRLEN)) {
		return (FALSE);
	}
	if (!xdr_netobj(xdrs, &objp->fh)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->base)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->length)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->type)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->granted)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->color)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->LockID)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->pid)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->class)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->rsys)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->rpid)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_holder(xdrs, objp)
	XDR *xdrs;
	klm_holder *objp;
{
	if (!xdr_bool(xdrs, &objp->exclusive)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->base)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->length)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->type)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->granted)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->color)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->LockID)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->pid)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->class)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->rsys)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->rpid)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_stat(xdrs, objp)
	XDR *xdrs;
	klm_stat *objp;
{
	if (!xdr_klm_stats(xdrs, &objp->stat)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_testrply(xdrs, objp)
	XDR *xdrs;
	klm_testrply *objp;
{
	if (!xdr_klm_stats(xdrs, &objp->stat)) {
		return (FALSE);
	}
	switch (objp->stat) {
	case klm_denied:
		if (!xdr_klm_holder(xdrs, &objp->klm_testrply_u.holder)) {
			return (FALSE);
		}
		break;
	}
	return (TRUE);
}

bool_t
xdr_klm_lockargs(xdrs, objp)
	XDR *xdrs;
	klm_lockargs *objp;
{
	if (!xdr_bool(xdrs, &objp->block)) {
		return (FALSE);
	}
	if (!xdr_bool(xdrs, &objp->exclusive)) {
		return (FALSE);
	}
	if (!xdr_klm_lock(xdrs, &objp->alock)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_testargs(xdrs, objp)
	XDR *xdrs;
	klm_testargs *objp;
{
	if (!xdr_bool(xdrs, &objp->exclusive)) {
		return (FALSE);
	}
	if (!xdr_klm_lock(xdrs, &objp->alock)) {
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_klm_unlockargs(xdrs, objp)
	XDR *xdrs;
	klm_unlockargs *objp;
{
	if (!xdr_klm_lock(xdrs, &objp->alock)) {
		return (FALSE);
	}
	return (TRUE);
}

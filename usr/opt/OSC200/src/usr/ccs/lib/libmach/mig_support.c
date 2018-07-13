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
static char	*sccsid = "@(#)$RCSfile: mig_support.c,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:11:14 $";
#endif 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *  Abstract:
 *	Routines to set and deallocate the mig reply port.
 *	They are called from mig generated interfaces.
 */

#include <mach.h>
#include <stdio.h>
#include <mach_error.h>


static port_t	mig_reply_port;

void mig_init(first)
/*****************************************************
 *  Called by mach_init. This is necessary after
 *  a fork to get rid of bogus port  number.
 ****************************************************/
    int	first;
{	if (first == 0)
		mig_reply_port = PORT_NULL;
	else
	{   fprintf(stderr,"Calling non-threads version of mig_int\n");
	    fflush(stderr);
	}
}


port_t mig_get_reply_port()
/********************************************************
 *  Called by mig interfaces whenever they  need a reply port.
 *  Used to provide the same interface as multi-threaded tasks need.
 ********************************************************/
{
   kern_return_t	retcode;

 	if (mig_reply_port == PORT_NULL)
	{	mig_reply_port = thread_reply();
		retcode = port_allocate(task_self(), &mig_reply_port);
		if (retcode != KERN_SUCCESS)
		     mach_error("get_reply_port: failed allocating new reply port.",
				retcode);
	}
	return(mig_reply_port);
}

void mig_dealloc_reply_port()
/*************************************************************
 *  Called by mig interfaces after a timeout on the port.
 *  Could be called by user.
 ***********************************************************/
{
   port_t		tmp_port;

	if (mig_reply_port != PORT_NULL)
	{	tmp_port = mig_reply_port;
		mig_reply_port = thread_reply();
		(void) port_deallocate(task_self(), tmp_port);
		mig_reply_port = PORT_NULL;
	}
}


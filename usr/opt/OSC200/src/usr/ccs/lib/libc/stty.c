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
static char	*sccsid = "@(#)$RCSfile: stty.c,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/06/07 23:09:57 $";
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
 * LIBCTTY: stty
 *                                                                    
 * ORIGIN: IBM
 *
 * IBM CONFIDENTIAL
 * Copyright International Business Machines Corp. 1988
 * Unpublished Work
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 *
 *
 * FUNCTION:	Berkeley backward compatable routine to set a tty's
 *		characteristics.
 *
 * RETURN VALUE DESCRIPTION:	
 *		Returns 0 open success.  Possible errors are EFAULT, EPERM,
 *		and EINVAL.
 *
 * stty.c	1.1  com/lib/c/tty,3.1,8943 3/22/89 13:42:44
 */

/* name space pollution clean up */
#ifdef _NAME_SPACE_WEAK_STRONG
#include "pollution.h"
#if !defined(_THREAD_SAFE)
#pragma weak stty = __stty
#endif
#endif
#include <sgtty.h>
int stty(int fd, struct sgttyb *sg)
{
    return ioctl(fd, TIOCSETP, sg);
}

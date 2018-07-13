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
static char *rcsid = "@(#)$RCSfile: sigset.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/08/24 19:49:31 $";
#endif

#include <sys/signal.h>
#include <sys/errno.h>

/*
 * libsys5 version of sigset(). This differs from the libc version
 * only in how it handles the sigstet(SIGCHLD, SIG_IGN) case.
 * SVR4 wants this to mean that the children of the caller will
 * not become zombies on exit.
 *
 * NOTE: Fixes to the libc version should be tracked here somehow.
 * They should be rare occurrences, nevertheless.
 */
void
#ifdef __STDC__
(*sigset(int sig, void (*func)(int)))(int)
#else
(*sigset(sig, func))()
int sig;
void (*func)(int);
#endif
{
	struct sigaction nact;	/* new signal action structure */
	struct sigaction oact;  /* returned signal action structure */ 
	sigset_t set, oset;	/* new and old signal masks */
	int	rc;		/* return value from sigaction */

	/*
	 * Error handling put in here to trap sigset(SIGKILL/STOP,SIG_DFL) 
	 * and also to avoid return value checking for each call to
         * sigaddset,sigprocmask,sigismember
	 */
	if (sig <= 0 || sig > SIGMAX || sig == SIGKILL || sig == SIGSTOP) {
		_Seterrno(EINVAL);
		return(SIG_ERR);
	}
		
	sigprocmask(SIG_BLOCK, NULL, &oset);

	/*
	 * If function is SIG_HOLD mask this signal using sigprocmask
         * and clear the flag using sigaction to let the
	 * kernel know we are using the ATT sigset semantics.
	 */
	if (func == SIG_HOLD) {
		sigemptyset(&set);
		sigaddset(&set, sig);
		sigprocmask(SIG_BLOCK, &set, NULL);
		rc = sigaction(sig, NULL, &oact);
	} else {
        	/*
		 * Set new handler, set mask to ignore this signal when 
                 * handler is executing and clear flags.
		 */
		nact.sa_handler = func;
		sigemptyset(&nact.sa_mask);
		sigaddset(&nact.sa_mask, sig);
		/*
		 * This behavior diverts from BSD/OSF sigset().
		 */
		if (func == SIG_IGN && sig == SIGCHLD)
			nact.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
		else
			nact.sa_flags = 0;
		rc = sigaction(sig, &nact, &oact);
	}

	if (rc == -1)
		return(SIG_ERR);

 	/*
	 * If previous action was SIG_HOLD, return SIG_HOLD.
	 */
	if (sigismember(&oset, sig) == 1)  {
	        /* If new function installed clear the previous HOLD */
		if (func != SIG_HOLD) {
			sigemptyset(&set);
			sigaddset(&set, sig);
			sigprocmask(SIG_UNBLOCK, &set, NULL);
		}
		return(SIG_HOLD);
	}
	return (oact.sa_handler);
}

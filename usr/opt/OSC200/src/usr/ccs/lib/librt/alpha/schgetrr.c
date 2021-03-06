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
static char *rcsid = "@(#)$RCSfile: schgetrr.c,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1993/01/08 15:02:31 $";
#endif
/*
 * sched_get_rr_interval
 *
 * Returns the quantum for the POSIX 1003.4 Round Robin (SCHED_RR) policy.
 *
 * This will need to be changed if the quantum is made configurable.  Somehow,
 * the library routine will have to be able to access the global constant
 * which holds the configured value.  Not sure how to do this yet.
 *
 * NOTE: Draft 10 is schizophrenic about this function.  It says that it is
 *	 a void function, and that it never fails.  However, passing it an
 *	 invalid pointer will cause it to fail, and the Errors section says
 *	 that it should return -1 if it fails.  The prototype has been changed
 *	 from void to int.
 *
 *	Revision History:
 *
 * 08-Jan-92    Ron Krueger
 *      Changes to upgrade from D10 to D11.  Added a new rr_interval routine 
 *      for the draft 10 specific stuff.  Modifed the existing rr_interval 
 *      stuff to take as input a pid and to check the pid.
 *
 * 11-Oct-91	Amy Kessler
 *	Change syscall to new one with additional parameters.
 *
 * 05-Jun-91	Peter H. Smith
 *	Fix overflow problem by doing nanosecond caluation in double float.
 *	Report ENOSYS if the RT kernel is not installed.
 *
 * 03-May-91	Peter H. Smith
 *	New file.
 *	
 */

#include <syscall.h>
#include <errno.h>
#include <sched.h>
#include <mach/policy.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#ifdef _THREAD_SAFE
#define SETERRNO(errval) seterrno(errval)
#else /* _THREAD_SAFE */
#define SETERRNO(errval) errno = (errval)
#endif /* _THREAD_SAFE */

int sched_get_rr_interval_d10(min)
  register struct timespec *min;
{
  return(sched_get_rr_interval((pid_t) NULL, min));
}

int sched_get_rr_interval(pid, min)
  pid_t pid;
     register struct timespec *min;
{
  register int sts;
  int hz;

  /*
   * Trap a null pointer.  Doesn't catch all invalid memory, but at least it
   * gets the obvious one.
   */
  if (min == 0) {
    SETERRNO(EINVAL);
    return -1;
  }

  /*
   * If the RT Update was not installed on the running kernel, let
   * the caller know.  This syscall just tests for the presence of the
   * RT support code.  It also checks that the pid is valid.
   */
  sts = rt_getprio( PRIO_POSIX, pid, 0, 0, 0);
  if (sts == -1) {
    SETERRNO(ENOSYS);
    return(-1);
  }

  /*
   * Return the quantum in seconds and nanoseconds.  Currently, the quantum
   * is just a little shorter than .1 second. getsysinfo() gives us the
   * kernel's value for hz, out of which we can construct the ns/quantum
   * value we need.
   */
  sts = getsysinfo(GSI_CLK_TCK, &hz, sizeof(hz), NULL, NULL);
  if (sts <= 0) {
	  SETERRNO(ENOSYS);
	  return(hz);
  }
  min->tv_sec = 0;
  /*
   * This calculation emulates how the kernel calculates rt_sched_rr_interval,
   * which is the number of milliseconds in a quantum. The integer division
   * forces the same "rounding" effects seen in the kernel. Multiplying by
   * 1,000,000 then converts ms to ns.
   * Thus:
   * (hz / 10) = ticks per quantum
   *     (ticks per quantum * 1000) / hz = milliseconds per quantum
   *     * 1E6 = nanosecond per quantum
   */
  min->tv_nsec = (((hz / 10) * 1000) / hz)  * 1E6;

  return 0;
}

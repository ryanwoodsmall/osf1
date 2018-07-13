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
static char *rcsid = "@(#)$RCSfile: str_shead.c,v $ $Revision: 4.3.5.5 $ (DEC) $Date: 1993/10/04 18:01:01 $";
#endif
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/*
 * str_shead.c - the stream head module routines.
 *
 * Based on pieces of Mentat's "sth.c"
 */

/** Copyright (c) 1989-1991  Mentat Inc.  **/

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/signal.h>
/* #include <sys/siginfo.h> */
#include <kern/parallel.h>
#include <kern/sched_prim.h>
#include <sys/poll.h>
#include <sys/stat.h>

#include <streams/str_stream.h>
#include <streams/str_proto.h>
#include <streams/str_debug.h>
#include <sys/stropts.h>
#include <streams/memdebug.h>

staticf int     sth_wsrv(queue_t *);
staticf void    sth_sigpoll_wakeup(STHP, int, int);
void    sth_err_wakeup(STHP, int, int);
staticf void    sth_m_setopts(STHP, MBLKP);

static struct module_info minfo =  {
	0, "sth", 0, 32000, 2048, 1024
};

static struct qinit rinit = {
	sth_rput,   NULL, NULL, NULL, NULL, &minfo
};

static struct qinit winit = {
	putq, sth_wsrv, NULL, NULL, NULL, &minfo
};

struct streamtab sthinfo = {
	&rinit, &winit
};

int
sth_rput (q, mp)
	queue_t	* q;
reg	MBLKP	mp;
{
reg	STHP	sth = (STHP)q->q_ptr;
	struct qband *qb;
	int	flushmode;
	int	putq_rc, err;
	MBLKP	mp1;

	switch (mp->b_datap->db_type) {
	case M_PCPROTO:
		/*
		 * If there is already an M_PCPROTO message here,
		 * ditch this one.
		 */
		for ( mp1 = q->q_first; mp1; mp1 = mp1->b_next ) {
			if ( mp1->b_datap->db_type < QPCTL )
				break;
			if ( mp1->b_datap->db_type == M_PCPROTO ) {
				freemsg(mp);
				return 0;
			}
		}
		putq_rc = putq_owned(q, mp);
		if (sth_sigs_active(sth)  ||  sth_poll_active(sth))
			sth_sigpoll_wakeup(sth, S_HIPRI, POLLPRI);
		osrq_wakeup(&sth->sth_read_osrq);
		goto out;
	case M_DATA:
		if (sth->sth_read_mode & RPROTCOMPRESS)
			mp->b_flag |= MSGCOMPRESS;
		/* fall through */
	case M_PROTO:
	case M_PASSFP:
		if (!q->q_first
		&&  (sth_sigs_active(sth) || sth_poll_active(sth))) {
			int	pollevents;
			int	sigmask;

			if (mp->b_band == 0) {
				pollevents = POLLIN | POLLRDNORM;
				sigmask = S_INPUT | S_RDNORM;
			} else {
				pollevents = POLLIN | POLLRDBAND;
				sigmask = S_INPUT | S_RDBAND;
			}
			putq_rc = putq_owned(q, mp);
			sth_sigpoll_wakeup(sth, sigmask, pollevents);
		} else
			putq_rc = putq_owned(q, mp);
		osrq_wakeup(&sth->sth_read_osrq);
		goto out;
	case M_SIG:
	case M_PCSIG:
		if (mp->b_rptr == mp->b_wptr)
			break;
		putq_rc = putq_owned(q, mp);
		/*
		 * If the message is at the front of the queue,
		 * deliver the signal now.  Otherwise, the signal
		 * will be delivered by sth_getq when the message
		 * reaches the front of the queue.
		 */
		if (q->q_first != mp)
			goto out;
		(void) getq(q);
		if ((int)*mp->b_rptr == SIGPOLL)
			sth_sigpoll_wakeup(sth, S_MSG, POLLMSG);
		else {
			sth_sigpoll_wakeup(sth, S_MSG, 0);
			sth_pgsignal(sth, (int)*mp->b_rptr);
		}
		break;
	case M_ERROR:
		if (mp->b_rptr == mp->b_wptr)
			break;
		err = mp->b_rptr[0];
		if (mp->b_wptr - mp->b_rptr == 1) {
			/* Old style M_ERROR with a one byte error value */
			if (err == 0)
				err = ENXIO;
			sth->sth_read_error = err;
			sth->sth_write_error = err;
			sth->sth_flags |= (F_STH_READ_ERROR|F_STH_WRITE_ERROR);
			flushmode = FLUSHRW;
			flushq(WR(q), FLUSHALL);
		} else {
			flushmode = 0;
			/*
			 * Set the read-side error state from the first
			 * byte of the message.
			 */
			switch (err) {
			case NOERROR:	/* don't change the read state */
				break;
			case 0:		/* clear the read-side error state */
				sth->sth_read_error = 0;
				sth->sth_flags &= ~F_STH_READ_ERROR;
				break;
			default:	/* set the read-side error state */
				sth->sth_read_error = err;
				sth->sth_flags |= F_STH_READ_ERROR;
				flushmode |= FLUSHR;
				break;
			}
			/*
			 * Set the write-side error state from the second
			 * byte of the message.
			 */
			err = mp->b_rptr[1];
			switch (err) {
			case NOERROR:	/* don't change the write state */
				break;
			case 0:		/* clear the write-side error state */
				sth->sth_write_error = 0;
				sth->sth_flags &= ~F_STH_WRITE_ERROR;
				break;
			default:	/* set the write-side error state */
				sth->sth_write_error = err;
				sth->sth_flags |= F_STH_WRITE_ERROR;
				flushmode |= FLUSHW;
				flushq(WR(q), FLUSHALL);
				break;
			}
		}
		if (sth->sth_flags & (F_STH_READ_ERROR | F_STH_WRITE_ERROR)) {
			flushq(WR(q), FLUSHALL);
			sth_err_wakeup(sth, S_ERROR, POLLERR);
			/*putctl1(WR(q)->q_next, M_FLUSH, flushmode);*/
			mp->b_wptr = mp->b_rptr = mp->b_datap->db_base;
			*mp->b_wptr++ = flushmode;
			mp->b_datap->db_type = M_FLUSH;
			qreply(q, mp);
			qenable(sth->sth_wq);
			return 0;
		}
		break;
	case M_FLUSH:
		if (mp->b_wptr - mp->b_rptr > 2)
			break;
		flushmode = FLUSHALL;
		if (mp->b_flag & MSGNOTIFY)
			flushmode |= FLUSH_NOTIFYONLY;
		if (*mp->b_rptr & FLUSHR) {
			if ((*mp->b_rptr & FLUSHBAND)
			&&  mp->b_wptr - mp->b_rptr == 2)
				flushband(q, mp->b_rptr[1], flushmode);
			else
				flushq(q, flushmode);
		}
		if (*mp->b_rptr & FLUSHW) {
			flushq(WR(q), flushmode);
			qenable(sth->sth_wq);
			*mp->b_rptr &= ~FLUSHR;
			if (!(sth->sth_flags & F_STH_FIFO))
			         qreply(q, mp);
			return 0;
		}
		break;
	case M_HANGUP:
		sth->sth_flags |= F_STH_HANGUP;
		if (sth->sth_write_error == 0)
			sth->sth_write_error =
				(sth->sth_flags & F_STH_PIPE) ? EPIPE : ENXIO;
		sth_err_wakeup(sth, S_HANGUP, POLLHUP);
		sth_pgsignal(sth, SIGHUP);
		break;
	case M_IOCACK:
	case M_IOCNAK:
		if (sth->sth_ioc_id && !sth->sth_ioc_mp &&
		    ((struct iocblk *)mp->b_rptr)->ioc_id == sth->sth_ioc_id) {
			sth->sth_ioc_mp = mp;
			osrq_wakeup(&sth->sth_ioctl_osrq);
			return 0;
		}
		break;
	case M_COPYIN:
	case M_COPYOUT:
		if (sth->sth_ioc_id && !sth->sth_ioc_mp &&
		    ((struct copyreq *)mp->b_rptr)->cq_id == sth->sth_ioc_id) {
			sth->sth_ioc_mp = mp;
			osrq_wakeup(&sth->sth_ioctl_osrq);
		} else
			sth_iocdata(sth, mp, EINVAL);
		return 0;
	case M_SETOPTS:
		sth_m_setopts(sth, mp);
		break;
	case M_MI:
		putq_rc = putq_owned(q, mp);
		osrq_wakeup(&sth->sth_read_osrq);
		goto out;
	default:
		break;
	}
	freemsg(mp);
	return 0;
out:
	/* Not much we can do if banded message won't go on queue. */
	if (putq_rc == 0 && mp)
		freemsg(mp);
	return 0;
}

/*
 * sth_getq - top level routine to get a message
 * sth_getq calls getq to get the next message available and returns this
 * pointer.  If a message is found, sth_getq also checks for any
 * signal messages (M_SIG or M_PCSIG) that now may be at the front
 * of the queue.  All such messages at the front are consumed.
 */
MBLKP
sth_getq (sth)
	STHP	sth;
{
reg	MBLKP	mp;
	MBLKP	mp1;
	queue_t	* q;
	unsigned char	type;

	q = sth->sth_rq;
	if (mp = q->q_first) {
		(void) getq(q);
		/*
		 * Check for any signal messages now at the front of the
		 * queue.  We look at q_first directly to avoid the
		 * overhead of getq on normal messages.
		 */
		for (;;) {
			mp1 = q->q_first;
			if (!mp1)
				break;
			type = mp1->b_datap->db_type;
			if (type != M_SIG  &&  type != M_PCSIG)
				break;
			(void) getq(q);
			if ((int)*mp1->b_rptr == SIGPOLL)
				sth_sigpoll_wakeup(sth, S_MSG, POLLMSG);
			else {
				sth_sigpoll_wakeup(sth, S_MSG, 0);
				sth_pgsignal(sth, (int)*mp1->b_rptr);
			}
			freemsg(mp1);
		}
	}
	return mp;
}

void
sth_iocdata (sth, mp, rval)
	STHP	sth;
	MBLKP	mp;
	int	rval;
{
	((struct copyresp *)mp->b_rptr)->cp_rval = rval;
	mp->b_datap->db_type = M_IOCDATA;
	if (rval != 0  &&  mp->b_cont) {
		freemsg(mp->b_cont);
		mp->b_cont = nil(MBLKP);
	}
	putnext(sth->sth_wq, mp);
}

/*
 * Return whether stream head is writable.
 * Messages leave the stream head directly if possible, else
 * from its queue. Used in select, write, fdinsert, putmsg, putpmsg.
 * Note: no need to q_lock the sth_wq for banding tests.
 *
 * Return values:
 *	3 = puttable at sth_wq->q_next
 *	2 = puttable at sth_wq, no messages there
 *	1 = puttable at sth_wq
 *	0 = not puttable
 */
int
sth_canput (sth, pri)
	STHP		sth;
	int		pri;
{
	queue_t *	q = sth->sth_wq;
	MBLKP		mp;
	int		ret = 0;

	if (pri == 0)
		mp = q->q_first;
	else
		mp = (pri <= q->q_nband) ? q->q_bandp[pri-1].qb_first : 0;
	if (mp == 0) {
		q = q->q_next;
		ret = 2;
	}
	ret += bcanput(q, pri);
	sth->sth_prev_band = pri;
	if (/*(sth->sth_flags & F_STH_???) &&*/ ret < 3)
		ret = 0;
	return ret;
}

staticf int
sth_wsrv (q)
reg	queue_t	* q;
{
reg	MBLKP	mp;
	int	poll_events = 0;
	int	sig_mask = 0;
	STHP	sth;

	sth = (STH *)q->q_ptr;
	while (mp = getq(q)) {
		if (sth->sth_flags & (F_STH_WRITE_ERROR | F_STH_HANGUP)) {
			freemsg(mp);
			continue;
		}
		sth->sth_prev_band = mp->b_band;
		if (!bcanput(q->q_next, sth->sth_prev_band)) {
			(void) putbq(q, mp);
			break;
		}
		putnext(q, mp);
		if (sth->sth_prev_band) {
			poll_events |= POLLWRBAND;
			sig_mask |= S_WRBAND;
		} else {
			poll_events |= POLLWRNORM;
			sig_mask |= S_WRNORM;
		}
	}
	if (/*(sth->sth_flags & F_STH_???) &&*/ !poll_events
	&&  bcanput(q->q_next, sth->sth_prev_band)) {
		/* Deal with single event on non-queued streams */
		if (sth->sth_prev_band) {
			poll_events = POLLWRBAND;
			sig_mask = S_WRBAND;
		} else {
			poll_events = POLLWRNORM;
			sig_mask = S_WRNORM;
		}
	}
	if (sig_mask || poll_events) {
		osrq_wakeup(&sth->sth_write_osrq);
		if (sth_poll_active(sth))
			poll_events |= POLLOUT;
		else
			poll_events = 0;
		if (sth_sigs_active(sth))
			sig_mask |= S_OUTPUT;
		else
			sig_mask = 0;
		if (sig_mask || poll_events)
			sth_sigpoll_wakeup(sth, sig_mask, poll_events);
	}
	/* Awaken when closing and last message leaves stream head */
	if ((sth->sth_flags & F_STH_CLOSING) && mp && !q->q_first)
		osrq_wakeup(&sth->sth_ioctl_osrq);
	return 0;
}

/*
 * Subroutines.
 */

staticf void
sth_sigpoll_wakeup (sth, sig_mask, poll_event)
	STHP	sth;
	int	sig_mask;
	int	poll_event;
{
reg	OSRP	osr;
	struct proc *	p;
	int	sig1, sig2;
reg	SIGSP	sigs;

	if (sig_mask) {
		for (sigs  = (SIGSP)sth->sth_sigsq.next;
		     sigs != (SIGSP)&sth->sth_sigsq;
		     sigs  = (SIGSP)sigs->ss_link) {
			sig1 = sig2 = 0;
			if (sigs->ss_mask & sig_mask) {
				if ((sig_mask & S_RDBAND)
				&&  (sigs->ss_mask & S_BANDURG))
					sig1 = SIGURG;
				else
					sig1 = SIGPOLL;
			}
			/* BSD FIOASYNC support - what about SIGURG? */
			if (sigs->ss_async & sig_mask)
				sig2 = SIGIO;
			if (sig1 || sig2) {
				p = sigs->ss_procp;
				if (P_REF(p)) {
					if (sig1) psignal(p,sig1);
					if (sig2) psignal(p,sig2);
					P_UNREF(p);
				}
			}
		}
	}
	if (poll_event)
		select_wakeup(&sth->sth_pollq);
}


void
sth_err_wakeup (sth, sig_mask, poll_event)
	STHP	sth;
	int	sig_mask;
	int	poll_event;
{
	osrq_wakeup(&sth->sth_ioctl_osrq);
	osrq_wakeup(&sth->sth_read_osrq);
	osrq_wakeup(&sth->sth_write_osrq);
	sth_sigpoll_wakeup(sth, sig_mask, poll_event);
}

staticf void
sth_m_setopts (sth, mp)
	STHP	sth;
	MBLKP	mp;
{
	int	flags;
	int	read_mode;
	qband_t	* qb;
	struct	stroptions	* stropt;

	if ((mp->b_wptr - mp->b_rptr) < sizeof(struct stroptions))
		return;
	stropt = (struct stroptions *)mp->b_rptr;
	flags = stropt->so_flags;
	if (flags & SO_READOPT) {
		stropt->so_readopt &= READ_OPTIONS_MASK;
		read_mode = stropt->so_readopt;
		if ((read_mode & READ_MODE_MASK) == 0)
			read_mode |= (sth->sth_read_mode & READ_MODE_MASK);
		if ((read_mode & READ_PROTO_MASK) == 0)
			read_mode |= (sth->sth_read_mode & READ_PROTO_MASK);
		sth->sth_read_mode = read_mode;
	}
	if ((flags & SO_WROFF)
	&&  (STRMSGSZ > 0 && stropt->so_wroff < STRMSGSZ))
		sth->sth_wroff = stropt->so_wroff;
	if (flags & SO_MINPSZ)
		sth->sth_rq->q_minpsz = stropt->so_minpsz;
	if (flags & SO_MAXPSZ)
		sth->sth_rq->q_maxpsz = stropt->so_maxpsz;
	if (flags & SO_HIWAT) {
		if (flags & SO_BAND)
			(void)strqset(sth->sth_rq, QHIWAT, stropt->so_band,
				stropt->so_hiwat);
		else
			(void)strqset(sth->sth_rq, QHIWAT, 0, stropt->so_hiwat);
	}
	if (flags & SO_LOWAT) {
		if (flags & SO_BAND)
			(void)strqset(sth->sth_rq, QLOWAT, stropt->so_band,
				stropt->so_lowat);
		else
			(void)strqset(sth->sth_rq, QLOWAT, 0, stropt->so_lowat);
	}
	if (flags & SO_MREADON)
		sth->sth_flags |= F_STH_MREADON;
	if (flags & SO_MREADOFF)
		sth->sth_flags &= ~F_STH_MREADON;
	if (flags & SO_NDELON)
		sth->sth_flags |= F_STH_NDELON;
	if (flags & SO_NDELOFF)
		sth->sth_flags &= ~F_STH_NDELON;
	if (flags & SO_ISTTY)
		sth->sth_flags |= F_STH_ISATTY;
	if (flags & SO_ISNTTY)
		sth->sth_flags &= ~F_STH_ISATTY;
	if (flags & SO_TOSTOP)
		sth->sth_flags |= F_STH_TOSTOP;
	if (flags & SO_TONSTOP)
		sth->sth_flags &= ~F_STH_TOSTOP;
}

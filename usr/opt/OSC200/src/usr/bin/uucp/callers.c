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
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: callers.c,v $ $Revision: 4.3.8.2 $ (DEC) $Date: 1993/09/07 16:04:02 $";
#endif
/* 
 * COMPONENT_NAME: UUCP callers.c
 * 
 * FUNCTIONS: chgc_cflag, dial801, dkcall, exphone, gdial, open801, 
 *            opendevice, processdev, repphone, sytcall, tcpcall, 
 *            translate, unetcall 
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*	uucp:callers.c	1.19.1.1
*/
#include "uucp.h"
/* VERSION("callers.c	7.3 - 87/07/08 - 16:33:07"); */
/*
callers.c	1.5  com/cmd/uucp,3.1,9013 11/29/89 14:20:14";
*/

#if defined(BSD4_2) || defined(BSDTCP)
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif
#ifdef UNET
#include  "UNET/unetio.h"
#include  "UNET/tcp.h"
#endif

static gdial();
static void translate();

int alarmtr();
extern jmp_buf Sjbuf;
extern char *fdig();

/*
 *	to add a new caller:
 *	declare the function that knows how to call on the device,
 *	add a line to the callers table giving the name of the device
 *	(from Devices file) and the name of the function
 *	add the function to the end of this file
 */

#ifdef DIAL801
int	dial801();
#endif

#ifdef DATAKIT
int	dkcall();
#endif

#ifdef TCP
int	unetcall();
int	tcpcall();
#endif

#ifdef SYTEK
int	sytcall();
#endif

struct caller Caller[] = {

#ifdef DIAL801
	{"801",		dial801},
	{"212",		dial801},
#endif

#ifdef TCP
#if defined(BSD4_2) || defined(BSDTCP)
	{"TCP",		tcpcall},	/* 4.2BSD sockets */
#else
#ifdef UNET
	{"TCP",		unetcall},	/* 3com implementation of tcp */
	{"Unetserver",	unetcall},
#endif
#endif
#endif

#ifdef DATAKIT
	{"DK",		dkcall},	/* standard btl datakit caller */
#endif

#ifdef SYTEK
	{"Sytek",	sytcall},	/* untested but should work */
#endif

	{NULL, 		0}		/* this line must be last */
};

/***
 *	exphone - expand phone number for given prefix and number
 *
 *	return code - none
 */

static void
exphone(in, out)
char *in, *out;
{
	FILE *fn;
	char pre[MAXPH], npart[MAXPH], tpre[MAXPH], p[MAXPH];
	char buf[BUFSIZ];
	char *s1;

	if (!isalpha(*in)) {
		(void) strcpy(out, in);
		return;
	}

	s1=pre;
	while (isalpha(*in))
		*s1++ = *in++;
	*s1 = NULLCHAR;
	s1 = npart;
	while (*in != NULLCHAR)
		*s1++ = *in++;
	*s1 = NULLCHAR;

	tpre[0] = NULLCHAR;
	fn = fopen(DIALFILE, "r");
	if (fn != NULL) {
		while (fgets(buf, BUFSIZ, fn)) {
			if ( sscanf(buf, "%s%s", p, tpre) < 1)
				continue;
			if (EQUALS(p, pre))
				break;
			tpre[0] = NULLCHAR;
		}
		fclose(fn);
	}

	(void) strcpy(out, tpre);
	(void) strcat(out, npart);
	return;
}

/*
 * repphone - Replace \D and \T sequences in arg with phone
 * expanding and translating as appropriate.
 */
static char *
repphone(arg, phone, trstr)
register char *arg, *phone, *trstr;
{
	static char pbuf[2*(MAXPH+2)];
	register char *fp, *tp;

	for (tp=pbuf; *arg; arg++) {
		if (*arg != '\\') {
			*tp++ = *arg;
			continue;
		} else {
			switch (*(arg+1)) {
			case 'T':
				exphone(phone, tp);
				translate(trstr, tp);
				for(; *tp; tp++)
				    ;
				arg++;
				break;
			case 'D':
				for(fp=phone; *tp = *fp++; tp++)
				    ;
				arg++;
				break;
			default:
				*tp++ = *arg;
				break;
			}
		}
	}
	*tp = '\0';
	return(pbuf);
}

/*
 * processdev - Process a line from the Devices file
 *
 * return codes:
 *	file descriptor  -  succeeded
 *	FAIL  -  failed
 */

processdev(flds, dev)
register char *flds[], *dev[];
{
	register int dcf = -1;
	int dcf2 = -1;
	register struct caller	*ca;
	char *args[D_MAX+1], dcname[20];
	register char **sdev;
	register nullfd;
	char *phonecl;			/* clear phone string */
	char phoneex[2*(MAXPH+2)];	/* expanded phone string */
	unsigned int c_cflag = 0;	/* place to save tty c_cflag */
	unsigned int chgc_cflag();

	sdev = dev;
	for (ca = Caller; ca->CA_type != NULL; ca++) {
		/* This will find built-in caller functions */
		if (EQUALS(ca->CA_type, dev[D_CALLER])) {
			DEBUG(5, "Internal caller type %s\n", dev[D_CALLER]);
			if (dev[D_ARG] == NULL) {
				/* if NULL - assume translate */
				dev[D_ARG+1] = NULL;	/* needed for for loop later to mark the end */
				dev[D_ARG] = "\\T";
			}
			dev[D_ARG] = repphone(dev[D_ARG], flds[F_PHONE], "");
			if ((dcf = (*(ca->CA_caller))(flds, dev)) < 0)
				return(dcf) ;
			dev += 2; /* Skip to next CALLER and ARG */
			break;
		}
	}
	if (dcf == -1) {
		/* Here if not a built-in caller function */
		if (ttylock(dev[D_LINE]) == FAIL) { /* Lock the line */
			DEBUG(5, "ttylock %s failed\n", dev[D_LINE]);
			Uerror = SS_LOCKED_DEVICE;
			return(FAIL);
		}
		DEBUG(5, "ttylock %s succeeded\n", dev[D_LINE]);
		/*
		 * Open the line
		 */
		(void) sprintf(dcname, "/dev/%s", dev[D_LINE]);
		/* take care of the possible partial open fd */
		(void) close(nullfd = open("/", 0));
		/* Open the tty, don't block waiting for carrier */
		dcf = opendevice(dcname, O_RDWR|O_NDELAY);
		if (dcf < 0)  {
			(void) close(nullfd);
			DEBUG(1, "generic open timeout\n", "");
			logent(MSGSTR(MSG_CALLERS_L1, "generic open"), 
			       MSGSTR(MSG_CALLERS_L2, "TIMEOUT"));
			Uerror = SS_CANT_ACCESS_DEVICE;
			goto bad;
		}
		fixline(dcf, atoi(fdig(flds[F_CLASS])), D_DIRECT);
		/* Turn modem control off until we are connected */
		c_cflag = chgc_cflag( dcf, CLOCAL );
		(void) fcntl(dcf,F_SETFL,0);	/* Turn off O_NDELAY. */
		/* kluge warning!  AIX V2 */
		/* We have to reopen the tty to get CLOCAL to change the 
		   the behavior of the tty */
		/* Open the tty with CLOCAL on and O_NDELAY off */
		dcf2 = opendevice(dcname, O_RDWR);
		if (dcf2 < 0)
			goto bad;
		(void) close(dcf);
		dcf = dcf2;   /* CLOCAL on, O_NDELAY off */
	}
	/*
	 * Now loop through the remaining callers and chat
	 * according to scripts in dialers file.
	 */
	for (; dev[D_CALLER] != NULL; dev += 2) {
		register int w;
		/*
		 * Scan Dialers file to find an entry
		 */
		if ((w = gdial(dev[D_CALLER], args, D_MAX)) < 1) {
			DEBUG(1, "%s not found in Dialers file\n", dev[D_CALLER]);
			logent(MSGSTR(MSG_CALLERS_L4, "generic call to gdial"), 
			       MSGSTR(MSG_CALLERS_L3, "FAILED"));
			Uerror = SS_CANT_ACCESS_DEVICE;
			goto bad;
		}
		if (w <= 2)	/* do nothing - no chat */
			break;
		/*
		 * Translate the phone number
		 */
		if (dev[D_ARG] == NULL) {
			/* if NULL - assume no translation */
			dev[D_ARG+1] = NULL; /* needed for for loop to mark the end */
			dev[D_ARG] = "\\D";
		}
		
		phonecl = repphone(dev[D_ARG], flds[F_PHONE], args[1]);
		exphone(phonecl, phoneex);
		translate(args[1], phoneex);
		/*
		 * Chat
		 */
		if (chat(w-2, &args[2], dcf, phonecl, phoneex) != SUCCESS) {
			Uerror = SS_CHAT_FAILED;
			goto bad;
		}
	}
	/*
	 * Success at last!
	 */
	/* Restore modem control if we turned it off. */
	if (c_cflag)
		(void)chgc_cflag( dcf, c_cflag );
	strcpy(Dc, sdev[D_LINE]);
	return(dcf);
bad:
	(void)close(dcf);
	ttyunlock(sdev[D_LINE]);
	return(FAIL);
}

opendevice(dcname, oflag)
char * dcname;
int oflag;
{
	register int dcf;

	DEBUG(4, "Attempting to open %s\n", dcname);
	/* set a longjump location for alarm */
	if (setjmp(Sjbuf)) {
		DEBUG(1, "generic open timeout\n", "");
		logent("generic open", "FAILED");
		Uerror = SS_CANT_ACCESS_DEVICE;
		return(-2);	
	}
	(void) signal(SIGALRM, (void(*)(int)) alarmtr);
	(void) alarm(10);
	dcf = open(dcname, oflag);
	(void) alarm(0);
	if (dcf < 0) {
		DEBUG(1, "generic open failed, errno = %d\n", errno);
		logent("generic open", "FAILED");
		Uerror = SS_CANT_ACCESS_DEVICE;
	}
	return(dcf);
}  /* end opendevice() */

unsigned int
chgc_cflag( dcf, c_cflag)
int dcf;
unsigned int c_cflag;
{
	struct termio ttbuf;
	int tmpdcf;
	unsigned int ccflag;

	if (ioctl(dcf, TCGETA, &ttbuf) != 0)
		return(0);
	ccflag = ttbuf.c_cflag;
	/* If a baud rate included, replace the c_cflag */
	if ((c_cflag & CBAUD) != 0)
		ttbuf.c_cflag = (unsigned short)c_cflag;
	/* Otherwise or in the new bits */
	else
		ttbuf.c_cflag |= (unsigned short)c_cflag;
	DEBUG(5,"Changing tty c_cflags from 0%o\n",ccflag);
	DEBUG(5,"Changing tty c_cflags to   0%o\n",ttbuf.c_cflag);
	(void) ioctl(dcf, TCSETA, &ttbuf);
	return(ccflag);  /* return the old c_cflag */
}  /* end chgc_cflag() */

/*
 * translate the pairs of characters present in the first
 * string whenever the first of the pair appears in the second
 * string.
 */
static void
translate(ttab, str)
register char *ttab, *str;
{
	register char *s;

	for(;*ttab && *(ttab+1); ttab += 2)
		for(s=str;*s;s++)
			if(*ttab == *s)
				*s = *(ttab+1);
}

#define MAXLINE	512
/*
 * Get the information about the dialer.
 * gdial(type, arps, narps)
 *	type	-> type of dialer (e.g., penril)
 *	arps	-> array of pointers returned by gdial
 *	narps	-> number of elements in array returned by gdial
 * Return value:
 *	-1	-> Can't open DIALERFILE
 *	0	-> requested type not found
 *	>0	-> success - number of fields filled in
 */
static
gdial(type, arps, narps)
register char *type, *arps[];
register int narps;
{
	static char info[MAXLINE];
	register FILE *ldial;
	register na;

	DEBUG(2, "gdial(%s) called\n", type);
	if ((ldial = fopen(DIALERFILE, "r")) == NULL)
		return(-1);
	while (fgets(info, sizeof(info), ldial) != NULL) {
		if ((info[0] == '#') || (info[0] == ' ') ||
		    (info[0] == '\t') || (info[0] == '\n'))
			continue;
		if ((na = getargs(info, arps, narps)) == 0)
			continue;
		if (EQUALS(arps[0], type)) {
			(void)fclose(ldial);
			bsfix(arps);
			return(na);
		}
	}
	(void)fclose(ldial);
	return(0);
}


#ifdef DATAKIT

/***
 *	dkcall(flds, dev)	make datakit ps connection
 *			datakit ps is a trademark of att (or is it bell labs?)
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

#include "dk.h"

dkcall(flds, dev)
char *flds[], *dev[];
{
	register fd;

	DEBUG(4, "dkcall(%s)\n", dev[D_ARG]);
	if (setjmp(Sjbuf)) {
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	(void) signal(SIGALRM, alarmtr);
	(void) alarm(15);
#ifndef STANDALONE
	if (*dev[D_LINE] == '0')
#endif
		fd = dkdial(dev[D_ARG], 0, 0);
#ifndef STANDALONE
	else
		fd = dkdial(dev[D_ARG], dev[D_LINE], 0);
#endif
	(void) alarm(0);
	(void) strcpy(Dc, "DK");
	if (fd < 0) {
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	else
		return(fd);
}

#endif /* DATAKIT */

#ifdef TCP

/***
 *	tcpcall(flds, dev)	make ethernet/socket connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

#ifndef BSDTCP
/*ARGSUSED*/
tcpcall(flds, dev)
char	*flds[], *dev[];
{
	Uerror = SS_NO_DEVICE;
	return(FAIL);
}
#else /* BSDTCP */
tcpcall(flds, dev)
char *flds[], *dev[];
{
	int ret;
	short port;
	extern int	errno, sys_nerr;
	extern char *sys_errlist[];
	struct servent *sp;
	struct hostent *hp;
	struct sockaddr_in sin;

	port = atoi(dev[D_ARG]);
	if (port == 0) {
		sp = getservbyname("uucp", "tcp");
		ASSERT(sp != NULL, MSGSTR(MSG_CALLERS_A1,"No uucp server"), 
			0, 0);
		port = sp->s_port;
	}
	else port = htons(port);
	hp = gethostbyname(flds[F_NAME]);
	if (hp == NULL) {
		logent("tcpopen", MSGSTR(MSG_CALLERS_L6, "no such host"));
		Uerror = SS_NO_DEVICE;
		return(FAIL);
	}
	DEBUG(4, "tcpdial host %s, ", flds[F_NAME]);
	DEBUG(4, "port %d\n", ntohs(port));

	ret = socket(AF_INET, SOCK_STREAM, 0);
	if (ret < 0) {
		if (errno < sys_nerr) {
			DEBUG(5, "no socket: %s\n", sys_errlist[errno]);
			logent(MSGSTR(MSG_CALLERS_L10, "no socket"), 
			sys_errlist[errno]);
		}
		else {
			DEBUG(5, "no socket, errno %d\n", errno);
			logent("tcpopen", MSGSTR(MSG_CALLERS_L7, "NO SOCKET"));
		}
		Uerror = SS_NO_DEVICE;
		return(FAIL);
	}
	sin.sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (caddr_t)&sin.sin_addr, hp->h_length);
	sin.sin_port = port;
	if (setjmp(Sjbuf)) {
		DEBUG(4, "timeout tcpopen\n", "");
		logent("tcpopen", MSGSTR(MSG_CALLERS_L2, "TIMEOUT"));
		Uerror = SS_NO_DEVICE;
		return(FAIL);
	}
	(void) signal(SIGALRM, (void(*)(int)) alarmtr);
	(void) alarm(30);
	DEBUG(7, "family: %d\n", sin.sin_family);
	DEBUG(7, "port: %d\n", sin.sin_port);
	DEBUG(7, "addr: %08x\n",*((int *) &sin.sin_addr));
	if (connect(ret, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
		(void) alarm(0);
		(void) close(ret);
		if (errno < sys_nerr) {
			DEBUG(5, "connect failed: %s\n", sys_errlist[errno]);
			logent(MSGSTR(MSG_CALLERS_L8, "connect failed"), 
			sys_errlist[errno]);
		}
		else {
			DEBUG(5, "connect failed, errno %d\n", errno);
			logent("tcpopen", "CONNECT FAILED");
		}
		Uerror = SS_NO_DEVICE;
		return(FAIL);
	}
	(void) signal(SIGPIPE, SIG_IGN);  /* watch out for broken ipc link...*/
	(void) alarm(0);
	(void) strcpy(Dc, "IPC");
	return(ret);
}

#endif /* BSDTCP */

/***
 *	unetcall(flds, dev)	make ethernet connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

#ifndef UNET
unetcall(flds, dev)
char	*flds[], *dev[];
{
	Uerror = SS_NO_DEVICE;
	return(FAIL);
}
#else /* UNET */
unetcall(flds, dev)
char *flds[], *dev[];
{
	int ret;
	int port;
	extern int	errno;

	port = atoi(dev[D_ARG]);
	DEBUG(4, "unetdial host %s, ", flds[F_NAME]);
	DEBUG(4, "port %d\n", port);
	(void) alarm(30);
	ret = tcpopen(flds[F_NAME], port, 0, TO_ACTIVE, "rw");
	(void) alarm(0);
	endhnent();
	if (ret < 0) {
		DEBUG(5, "tcpopen failed: errno %d\n", errno);
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	(void) strcpy(Dc, "UNET");
	return(ret);
}
#endif /* UNET */

#endif /* TCP */

#ifdef SYTEK

/****
 *	sytcall(flds, dev)	make a sytek connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

/*ARGSUSED*/
sytcall(flds, dev)
char *flds[], *dev[];
{
	extern int errno;
	int dcr, dcr2, nullfd, ret;
	char dcname[20], command[BUFSIZ];

	(void) sprintf(dcname, "/dev/%s", dev[D_LINE]);
	DEBUG(4, "dc - %s, ", dcname);
	dcr = open(dcname, O_WRONLY|O_NDELAY);
	if (dcr < 0) {
		Uerror = SS_DIAL_FAILED;
		DEBUG(4, "OPEN FAILED %s\n", dcname);
		ttyunlock(dev[D_LINE]);
		return(FAIL);
	}

	sytfixline(dcr, atoi(fdig(dev[D_CLASS])), D_DIRECT);
	(void) sleep(2);
	(void) sprintf(command,"\r\rcall %s\r",flds[F_PHONE]);
	ret = write(dcr, command, strlen(command));
	(void) sleep(1);
	DEBUG(4, "COM1 return = %d\n", ret);
	sytfix2line(dcr);
	(void) close(nullfd = open("/", 0));
	(void) signal(SIGALRM, (void(*)(int)) alarmtr);
	if (setjmp(Sjbuf)) {
		DEBUG(4, "timeout sytek open\n", "");
		(void) close(nullfd);
		(void) close(dcr2);
		(void) close(dcr);
		Uerror = SS_DIAL_FAILED;
		ttyunlock(dev[D_LINE]);
		return(FAIL);
	}
	(void) alarm(10);
	dcr2 = open(dcname,O_RDWR);
	(void) alarm(0);
	(void) close(dcr);
	if (dcr2 < 0) {
		DEBUG(4, "OPEN 2 FAILED %s\n", dcname);
		Uerror = SS_DIAL_FAILED;
		(void) close(nullfd);	/* kernel might think dc2 is open */
		ttyunlock(dev[D_LINE]);
		return(FAIL);
	}
	return(dcr2);
}

#endif /* SYTEK */

#ifdef DIAL801

/***
 *	dial801(flds, dev)	dial remote machine on 801/801
 *	char *flds[], *dev[];
 *
 *	return codes:
 *		file descriptor  -  succeeded
 *		FAIL  -  failed
 *
 *	unfortunately, open801() is different for usg and non-usg
 */

/*ARGSUSED*/
dial801(flds, dev)
char *flds[], *dev[];
{
	char dcname[20], dnname[20], phone[MAXPH+2], *fdig();
	int dcf = -1, speed;

	if (ttylock(dev[D_LINE]) == FAIL) {
		DEBUG(5, "ttylock %s failed\n", dev[D_LINE]);
		Uerror = SS_LOCKED_DEVICE;
		return(FAIL);
	}
	(void) sprintf(dnname, "/dev/%s", dev[D_CALLDEV]);
	(void) sprintf(phone, "%s%s", dev[D_ARG]   , ACULAST);
	(void) sprintf(dcname, "/dev/%s", dev[D_LINE]);
	CDEBUG(1, "Use Port %s, ", dcname);
	DEBUG(4, "acu - %s, ", dnname);
	CDEBUG(1, "Phone Number  %s\n", phone);
	VERBOSE("Trying modem - %s, ", dcname);	/* for cu */
	VERBOSE("acu - %s, ", dnname);	/* for cu */
	VERBOSE("calling  %s:  ", phone);	/* for cu */
	speed = atoi(fdig(dev[D_CLASS]));
	dcf = open801(dcname, dnname, phone, speed);
	if (dcf >= 0) {
		fixline(dcf, speed, D_ACU);
		(void) strcpy(Dc, dev[D_LINE]);	/* for later unlock() */
		VERBOSE("SUCCEEDED\n", 0);
	} else {
		ttyunlock(dev[D_LINE]);
		VERBOSE("FAILED\n", 0);
	}
	return(dcf);
}


#ifndef ATTSV
/*ARGSUSED*/
open801(dcname, dnname, phone, speed)
char *dcname, *dnname, *phone;
{
	int nw, lt, pid = -1, dcf = -1, nullfd, dnf = -1;
	unsigned timelim;

	if ((dnf = open(dnname, 1)) < 0) {
		DEBUG(5, "can't open %s\n", dnname);
		Uerror = SS_CANT_ACCESS_DEVICE;
		return(FAIL);
	}
	DEBUG(5, "%s is open\n", dnname);

	(void) close(nullfd = open("/dev/null", 0));	/* partial open hack */
	if (setjmp(Sjbuf)) {
		DEBUG(4, "timeout modem open\n", "");
		logent(MSGSTR(MSG_CALLERS_L9, "801 open"), 
		       MSGSTR(MSG_CALLERS_L2, "TIMEOUT"));
		(void) close(nullfd);
		(void) close(dcf);
		(void) close(dnf);
		if (pid > 0) {
			kill(pid, 9);
			wait((int *) 0);
		}
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	(void) signal(SIGALRM, alarmtr);
	timelim = 5 * strlen(phone);
	(void) alarm(timelim < 30 ? 30 : timelim);
	if ((pid = fork()) == 0) {
		sleep(2);
		nw = write(dnf, phone, lt = strlen(phone));
		if (nw != lt) {
			DEBUG(4, "ACU write error %d\n", errno);
			logent(MSGSTR(MSG_CALLERS_L5, "ACU write"), 
			       MSGSTR(MSG_CALLERS_L3, "FAILED"));
			exit(1);
		}
		DEBUG(4, "ACU write ok%s\n", "");
		exit(0);
	}
	/*  open line - will return on carrier */
	dcf = open(dcname, 2);

	DEBUG(4, "dcf is %d\n", dcf);
	if (dcf < 0) {	/* handle like a timeout */
		(void) alarm(0);
		longjmp(Sjbuf, 1);
	}

	/* modem is open */
	while ((nw = wait(&lt)) != pid && nw != -1)
		;
	(void) alarm(0);

	(void) close(dnf);	/* no reason to keep the 801 open */
	if (lt != 0) {
		DEBUG(4, "Fork Stat %o\n", lt);
		(void) close(dcf);
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	return(dcf);
}

#else /* ATTSV */

open801(dcname, dnname, phone, speed)
char *dcname, *dnname, *phone;
{
	int nw, lt, dcf = -1, nullfd, dnf = -1, ret;
	unsigned timelim;

	(void) close(nullfd = open("/", 0));	/* partial open hack */
	if (setjmp(Sjbuf)) {
		DEBUG(4, "DN write %s\n", "timeout");
		(void) close(dnf);
		(void) close(dcf);
		(void) close(nullfd);
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	}
	(void) signal(SIGALRM, (void(*)(int)) alarmtr);
	timelim = 5 * strlen(phone);
	(void) alarm(timelim < 30 ? 30 : timelim);

	if ((dnf = open(dnname, O_WRONLY)) < 0 ) {
		DEBUG(5, "can't open %s\n", dnname);
		Uerror = SS_CANT_ACCESS_DEVICE;
		return(FAIL);
	}
	DEBUG(5, "%s is open\n", dnname);
	if (  (dcf = open(dcname, O_RDWR | O_NDELAY)) < 0 ) {
		DEBUG(5, "can't open %s\n", dcname);
		Uerror = SS_CANT_ACCESS_DEVICE;
		return(FAIL);
	}

	DEBUG(4, "dcf is %d\n", dcf);
	fixline(dcf, speed, D_ACU);
	nw = write(dnf, phone, lt = strlen(phone));
	if (nw != lt) {
		(void) alarm(0);
		DEBUG(4, "ACU write error %d\n", errno);
		(void) close(dnf);
		(void) close(dcf);
		Uerror = SS_DIAL_FAILED;
		return(FAIL);
	} else 
		DEBUG(4, "ACU write ok%s\n", "");

	(void) close(dnf);
	(void) close(nullfd = open("/", 0));	/* partial open hack */
	ret = open(dcname, 2);  /* wait for carrier  */
	(void) alarm(0);
	(void) close(ret);	/* close 2nd modem open() */
	if (ret < 0) {		/* open() interrupted by alarm */
		DEBUG(4, "Line open %s\n", "failed");
		Uerror = SS_DIAL_FAILED;
		(void) close(nullfd);		/* close partially opened modem */
		return(FAIL);
	}
	(void) fcntl(dcf,F_SETFL, fcntl(dcf, F_GETFL, 0) & ~O_NDELAY);
	return(dcf);
}
#endif /* ATTSV */

#endif /* DIAL801 */

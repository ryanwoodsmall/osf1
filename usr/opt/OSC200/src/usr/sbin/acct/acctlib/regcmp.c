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
static char	*sccsid = "@(#)$RCSfile: regcmp.c,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 05:59:01 $";
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
#if !defined( lint) && !defined(_NOIDENT)

#endif
/*
 * IBM CONFIDENTIAL
 * Copyright International Business Machines Corp. 1989
 * Unpublished Work
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 
#if !lint
static char sccsid[] = "regcmp.c	1.1  com/cmd/acct/lib,3.1,8935 5/15/89 17:18:54";
#endif
#define SSIZE	50
#define TGRP	48
#define A256	02
#define ZERO	01
#define	NBRA	10
#define CIRCFL	32;
#define SLOP	5
#define	EOF	0

#define	CBRA	60
#define GRP	40
#define SGRP	56
#define PGRP	68
#define EGRP	44
#define RNGE	03
#define	CCHR	20
#define	CDOT	64
#define	CCL	24
#define	NCCL	8
#define	CDOL	28
#define	CEOF	52
#define	CKET	12

#define	STAR	01
#define PLUS	02
#define MINUS	16

int	*__sp_;
char	*__stmax;
int	__i_size;
char *
regcmp(cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9,cs10) 
char *cs1,*cs2,*cs3,*cs4,*cs5,*cs6,*cs7,*cs8,*cs9,*cs10;
{
	register c;
	register char *ep, *sp;
	int *adx;
	int i,cflg;
	char *lastep, *sep, *eptr;
	char bracket[NBRA], *bracketp;
	int nbra,ngrp;
	int cclcnt;
	char stack[SSIZE];
	extern char *malloc();
	extern void free();

	__sp_ = (int *)stack;
	*__sp_ = -1;
	__stmax = &stack[SSIZE];

	adx = (int *)&cs1;
	i = nbra = ngrp = 0;
	while(*adx)  i += __size((char *)*adx++);
	adx = (int *)&cs1;
	sp = (char *)*adx++;
	if((sep = ep = (char *)malloc((unsigned)(2*i+SLOP))) == (char *)0)
		return(0);
	bracketp = bracket;
	if ((c = *sp++) == EOF) goto cerror;
	if (c=='^') {
		c = *sp++;
		*ep++ = CIRCFL;
	}
	if ((c=='*') || (c=='+') || (c=='{'))
		goto cerror;
	sp--;
	for (;;) {
		if ((c = *sp++) == EOF) {
			if (*adx) {
				sp = (char *)*adx++;
				continue;
			}
			*ep++ = CEOF;
			if (--nbra > NBRA || *__sp_ != -1)
				goto cerror;
			__i_size = ep - sep;
			return(sep);
		}
		if ((c!='*') && (c!='{')  && (c!='+'))
			lastep = ep;
		switch (c) {

		case '(':
			if (!__rpush(ep)) goto cerror;
			*ep++ = CBRA;
			*ep++ = -1;
			continue;
		case ')':
			if (!(eptr=(char *)__rpop())) goto cerror;
			if ((c = *sp++) == '$') {
				if ('0' > (c = *sp++) || c > '9')
					goto cerror;
				*ep++ = CKET;
				*ep++ = *++eptr = nbra++;
				*ep++ = (c-'0');
				continue;
			}
			*ep++ = EGRP;
			*ep++ = ngrp++;
			sp--;
			switch (c) {
			case '+':
				*eptr = PGRP;
				break;
			case '*':
				*eptr = SGRP;
				break;
			case '{':
				*eptr = TGRP;
				break;
			default:
				*eptr = GRP;
				continue;
			}
			i = ep - eptr - 2;
			for (cclcnt = 0; i >= 256; cclcnt++)
				i -= 256;
			if (cclcnt > 3) goto cerror;
			*eptr |= cclcnt;
			*++eptr = i;
			continue;

		case '\\':
			*ep++ = CCHR;
			if ((c = *sp++) == EOF)
				goto cerror;
			*ep++ = c;
			continue;

		case '{':
			*lastep |= RNGE;
			cflg = 0;
		nlim:
			if ((c = *sp++) == '}') goto cerror;
			i = 0;
			do {
				if ('0' <= c && c <= '9')
					i = (i*10+(c-'0'));
				else goto cerror;
			} while (((c = *sp++) != '}') && (c != ','));
			if (i>255) goto cerror;
			*ep++ = i;
			if (c==',') {
				if (cflg++) goto cerror;
				if((c = *sp++) == '}') {
					*ep++ = -1;
					continue;
				}
				else {
					sp--;
					goto nlim;
				}
			}
			if (!cflg) *ep++ = i;
			else if ((ep[-1]&0377) < (ep[-2]&0377)) goto cerror;
			continue;

		case '.':
			*ep++ = CDOT;
			continue;

		case '+':
			if (*lastep==CBRA || *lastep==CKET)
				goto cerror;
			*lastep |= PLUS;
			continue;

		case '*':
			if (*lastep==CBRA || *lastep==CKET)
			goto cerror;
			*lastep |= STAR;
			continue;

		case '$':
			if ((*sp != EOF) || (*adx))
				goto defchar;
			*ep++ = CDOL;
			continue;

		case '[':
			*ep++ = CCL;
			*ep++ = 0;
			cclcnt = 1;
			if ((c = *sp++) == '^') {
				c = *sp++;
				ep[-2] = NCCL;
			}
			do {
				if (c==EOF)
					goto cerror;
				if ((c=='-') && (cclcnt>1) && (*sp!=']')) {
					*ep = ep[-1];
					ep++;	/* lint complains about *ep++ */
					ep[-2] = MINUS;
					cclcnt++;
					continue;
				}
				*ep++ = c;
				cclcnt++;
			} while ((c = *sp++) != ']');
			lastep[1] = cclcnt;
			continue;

		defchar:
		default:
			*ep++ = CCHR;
			*ep++ = c;
		}
	}
   cerror:
	free(sep);
	return(0);
}
__size(strg) char *strg;
{
	int	i;

	i = 1;
	while(*strg++) i++;
	return(i);
}
__rpop() {
	return (*__sp_ == -1)?0:*__sp_--;
}
__rpush(ptr) char *ptr;
{
	if (++__sp_ > (int *)__stmax) return(0);
	*__sp_ = (int)ptr;
	return(1);
}

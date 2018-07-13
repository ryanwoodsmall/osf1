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
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
#if !defined(lint) && !defined(_NOIDENT)
static char rcsid[] = "@(#)$RCSfile: n8.c,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1993/10/14 04:17:43 $";
#endif
/*
 * HISTORY
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * n8.c	4.1 6/7/82
 *
 */

/*
 * Modification History:
 *
 * 001 21-May-91	gws
 *	this came from usr/local/nosupport/troff n8.c -r3.1
 *	cleaned up history comments; removed extraneous ifndef lint/endif
 *
 */

#include "tdef.h"

/*
troff8.c

hyphenation
*/

char hbuf[NHEX];
char *nexth = hbuf;
int *hyend;
extern int *wdstart, *wdend;
extern int *hyptr[];
extern int **hyp;
extern int hyoff;
extern int noscale;
extern int xxx;
/* +++ WW001 +++ */
extern nl_catd catd;
/* --- WW001 --- */
#define THRESH 160 /*digram goodness threshold*/
int thresh = THRESH;

hyphen(wp)
int *wp;
{
	register *i, j;

	i = wp;
	while(punct(*i++))
		;
	if (!alph(*--i))
		return;
	wdstart = i++;
	while(alph(*i++))
		;
	hyend = wdend = --i-1;
	while(punct(*i++))
		;
	if (*--i)
		return;
	if ((wdend-wdstart-4) < 0)
		return;
	hyp = hyptr;
	*hyp = 0;
	hyoff = 2;
	if (!exword() && !suffix())
		digram();
	*hyp++ = 0;
	if (*hyptr) for(j = 1; j;) {
		j = 0;
		for(hyp = hyptr+1; *hyp != 0; hyp++) {
			if (*(hyp-1) > *hyp) {
				j++;
				i = *hyp;
				*hyp = *(hyp-1);
				*(hyp-1) = i;
			}
		}
	}
}

punct(i)
int i;
{
	if (!i || alph(i))
		return(0);
	else
		return(1);
}

alph(i)
int i;
{
	register j;

	j = i & CMASK;
	if (((j >= 'A') && (j <= 'Z')) || ((j >= 'a') && (j <= 'z')))
		return(1);
	else
		return(0);
}

caseht()
{
	thresh = THRESH;
	if (skip())
		return;
	noscale++;
	thresh = atoi();
	noscale = 0;
}

casehw()
{
	register i, k;
	register char *j;

	k = 0;
	while(!skip()) {
		if ((j = nexth) >= (hbuf + NHEX - 2))
			goto full;
		for (;;) {
			if ((i = getch()) & MOT)
				continue;
/* +++ WL001 +++ */
			if (((i &= CMASK) == ' ') || (i == '\n') ||
			      IS_ENCODED_ACHAR(i)) {
/* --- WL001 --- */
				*j++ = 0;
				nexth = j;
				*j = 0;
/* +++ WL001 +++ */
				if ((i == ' ') || IS_ENCODED_ACHAR(i))
/* --- WL001 --- */
					break;
				else
					return;
			}
			if (i == '-') {
				k = 0200;
				continue;
			}
			*j++ = maplow(i) | k;
			k = 0;
			if (j >= (hbuf + NHEX - 2))
				goto full;
		}
	}
	return;
full:
	prstr(catgets(catd, 1, 26, "Exception word list full.\n"));
	*nexth = 0;
}

exword()
{
	register int *w;
	register char *e;
	char *save;

	e = hbuf;
	while(1) {
		save = e;
		if (*e == 0)return(0);
		w = wdstart;
		while((*e && (w <= hyend)) &&
		      ((*e & 0177) == maplow(*w & CMASK))) {e++; w++;};
		if (!*e) {
			if (((w-1) == hyend) ||
			   ((w == wdend) && (maplow(*w & CMASK) == 's'))) {
				w = wdstart;
				for(e = save; *e; e++) {
					if (*e & 0200)*hyp++ = w;
					if (hyp > (hyptr+NHYP-1))
						hyp = hyptr+NHYP-1;
					w++;
				}
				return(1);
			}else{e++; continue;}
		}else while(*e++);
	}
}

suffix()
{
	register int *w;
	register char *s, *s0;
	int i;
	extern char *suftab[];
	extern int *chkvow();

again:
	if (!alph(i = *hyend & CMASK))
		return(0);
	if (i < 'a')
		i -= 'A'-'a';
	if ((s0 = suftab[i-'a']) == 0)
		return(0);
	for (;;) {
		if ((i = *s0 & 017) == 0)
			return(0);
		s = s0 + i - 1;
		w = hyend - 1;
		while(((s > s0) && (w >= wdstart)) &&
		   ((*s & 0177) == maplow(*w))) {
			s--;
			w--;
		}
		if (s == s0)
			break;
		s0 += i;
	}
	s = s0 + i - 1;
	w = hyend;
	if (*s0 & 0200) goto mark;
	while(s > s0) {
		w--;
		if (*s-- & 0200) {
	mark:
			hyend = w - 1;
			if (*s0 & 0100)
				continue;
			if (!chkvow(w))
				return(0);
			*hyp++ = w;
		}
	}
	if (*s0 & 040)
		return(0);
	if (exword())
		return(1);
	goto again;
}

maplow(i)
int i;
{
	if ((i &= CMASK) < 'a')i += 'a' - 'A';
	return(i);
}

vowel(i)
int i;
{
	switch(maplow(i)) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case 'y':
			return(1);
		default:
			return(0);
	}
}

int *chkvow(w)
int *w;
{
	while(--w >= wdstart)if(vowel(*w & CMASK))return(w);
	return(0);
}

digram() {
	register *w, val;
	int *nhyend, *maxw, maxval;
	extern char bxh[26][13], bxxh[26][13], xxh[26][13], xhx[26][13], hxx[26][13];

again:
	if (!(w=chkvow(hyend+1)))return;
	hyend = w;
	if (!(w=chkvow(hyend)))return;
	nhyend = w;
	maxval = 0;
	w--;
	while((++w < hyend) && (w < (wdend-1))) {
		val = 1;
		if (w == wdstart)val *= dilook('a',*w,bxh);
		else if(w == wdstart+1)val *= dilook(*(w-1),*w,bxxh);
		else val *= dilook(*(w-1),*w,xxh);
		val *= dilook(*w, *(w+1), xhx);
		val *= dilook(*(w+1), *(w+2), hxx);
		if (val > maxval) {
			maxval = val;
			maxw = w + 1;
		}
	}
	hyend = nhyend;
	if (maxval > thresh)*hyp++ = maxw;
	goto again;
}

dilook(a,b,t)
int a, b;
char t[26][13];
{
	register i, j;

	i = t[maplow(a)-'a'][(j = maplow(b)-'a')/2];
	if (!(j & 01))i >>= 4;
	return(i & 017);
}
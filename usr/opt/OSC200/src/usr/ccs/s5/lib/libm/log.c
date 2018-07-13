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
static char	*sccsid = "@(#)$RCSfile: log.c,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 05:03:45 $";
#endif 
/*
 */
/*
 *	log returns the natural logarithm of its double-precision argument.
 *	log10 returns the base-10 logarithm of its double-precision argument.
 *	Returns EDOM error and value -HUGE if argument <= 0.
 *	Algorithm and coefficients from Cody and Waite (1980).
 *	Calls frexp.
 */

#include <math.h>
#include <errno.h>
#define C1	0.693359375
#define C2	-2.121944400546905827679e-4

static double log_error();

double
log(x)
register double x;
{
	static double p[] = {
		-0.78956112887491257267e0,
		 0.16383943563021534222e2,
		-0.64124943423745581147e2,
	}, q[] = {
		 1.0,
		-0.35667977739034646171e2,
		 0.31203222091924532844e3,
		-0.76949932108494879777e3,
	};
	register double y;
	int n; /* can't be in register because of frexp() below */

	if (x <= 0)
		return (log_error(x, "log", 3));
	y = 1.0;
	x = frexp(x, &n);
	if (x < M_SQRT1_2) {
		n--;
		y = 0.5;
	}
	x = (x - y)/(x + y);
	x += x;
	y = x * x;
	x += x * y * _POLY2(y, p)/_POLY3(y, q);
	y = (double)n;
	x += y * C2;
	return (x + y * C1);
}

double
log10(x)
register double x;
{
	return (x > 0 ? log(x) * M_LOG10E : log_error(x, "log10", 5));
}

static double
log_error(x, f_name, name_len)
double x;
char *f_name;
unsigned int name_len;
{
	register char *err_type;
	unsigned int mess_len;
	struct exception exc;

	exc.name = f_name;
	exc.retval = -HUGE;
	exc.arg1 = x;
	if (x) {
		exc.type = DOMAIN;
		err_type = ": DOMAIN error\n";
		mess_len = 15;
	} else {
		exc.type = SING;
		err_type = ": SING error\n";
		mess_len = 13;
	}
	if (!matherr(&exc)) {
		(void) write(2, f_name, name_len);
		(void) write(2, err_type, mess_len);
		errno = EDOM;
	}
	return (exc.retval);
}
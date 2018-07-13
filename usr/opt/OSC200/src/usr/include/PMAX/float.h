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
/*	
 *	@(#)$RCSfile: float.h,v $ $Revision: 4.2.3.4 $ (DEC) $Date: 1992/05/06 10:45:52 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * float.h
 *
 *	Modification History:
 * 
 * 03-Apr-92	David Metsky
 *  Change values of DBL_MIN, LDBL_MIN, FLT_MAX, FLT_MIN, and FLT_EPSILON to
 *  pass ANSI C test suite.
 *
 * 10-Dec-91	Fred Iannelli
 *  Change value for DBL_MAX to equal MAXDOUBLE
 *
 * 28-Apr-91	Fred Canter
 *	Change LANGUAGE_* to __LANGUAGE_*__ for MIPS ANSI C.
 *
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 

/*
 * COMPONENT_NAME: (float.h) floating point header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _FLOAT_H_
#define _FLOAT_H_
#include <standards.h>

/*
 *  Only a subset of the values in this header are required
 *  by the ANSI standard. The values not required will not be
 *  included if _ANSI_C_SOURCE is defined (for strict conformance).
 *
 *  ANSI required:
 *
 *      FLT_ROUNDS      Macro that returns current rounding mode value
 *      FLT_RADIX       Exponent radix
 *
 *               Values for "float" numbers
 *
 *      FLT_MANT_DIG    Number of bits in the significand
 *      FLT_EPSILON     1ulp when exponent = 0
 *      FLT_DIG         Number of decimal digits of precision
 *      FLT_MIN_EXP     Exponent of smallest NORMALIZED float number
 *      FLT_MIN         Smallest NORMALIZED float number
 *      FLT_MIN_10_EXP  Minimum base 10 exponent of NORMALIZED float
 *      FLT_MAX_EXP     Exponent of largest NORMALIZED float number
 *      FLT_MAX         Largest NORMALIZED float number
 *      FLT_MAX_10_EXP  Largest base 10 exponent of NORMALIZED float
 *
 *               Values for "double" numbers
 *
 *      DBL_MANT_DIG    Number of bits in the significand
 *      DBL_EPSILON     1ulp when exponent = 0
 *      DBL_DIG         Number of decimal digits of precision
 *      DBL_MIN_EXP     Exponent of smallest NORMALIZED double number
 *      DBL_MIN         Smallest NORMALIZED double number
 *      DBL_MIN_10_EXP  Minimum base 10 exponent of NORMALIZED double
 *      DBL_MAX_EXP     Exponent of largest NORMALIZED double number
 *      DBL_MAX         Largest NORMALIZED double number
 *      DBL_MAX_10_EXP  Largest base 10 exponent of NORMALIZED double
 *
 *                Values for "long double" numbers
 *
 *      LDBL_MANT_DIG   Number of bits in the significand
 *      LDBL_EPSILON    1ulp when unbiased exponent = 0
 *      LDBL_DIG        Number of decimal digits of precision
 *      LDBL_MIN_EXP    Exponent of smallest NORMALIZED long double number
 *      LDBL_MIN        Smallest NORMALIZED long double number
 *      LDBL_MIN_10_EX  Minimum base 10 exponent of NORMALIZED long double
 *      LDBL_MAX_EXP    Exponent of largest NORMALIZED long double number
 *      LDBL_MAX        Largest NORMALIZED long double number
 *      LDBL_MAX_10_EXP Largest base 10 exponent of NORMALIZED long double
 *
 *  Not required for ANSI compatibility:
 *
 *      FLT_INFINITY    Float Infinity
 *      DBL_INFINITY    Double Infinity
 *      LDBL_INFINITY   Long Double Infinity
 *      DBL_QNAN        Double QNaN
 *      FLT_QNAN        Float QNaN
 *      DBL_SNAN        Double SNaN
 *      FLT_SNAN        Float SNaN
 *      FP_RND_xx       Floating Point Rounding Mode Constants
 *      FP_xx           Floating Point Class Function Return Values
 *
 */

#ifdef _ANSI_C_SOURCE

/*
 *      General definitions
 */

#define FLT_ROUNDS         1
#define FLT_RADIX          2

/*
 *      Float definitions
 */

#define FLT_MANT_DIG       24
#define FLT_EPSILON        1.19209290e-07f
#define FLT_DIG            6
#define FLT_MIN_EXP        -125
#define FLT_MIN            1.17549435e-38f
#define FLT_MIN_10_EXP     -37
#define FLT_MAX_EXP        128
#define FLT_MAX            3.40282347e+38f
#define FLT_MAX_10_EXP     38

/*
 *      Double definitions
 */

#define DBL_MANT_DIG       53
#define DBL_EPSILON        2.2204460492503131e-16
#define DBL_DIG            15
#define DBL_MIN_EXP        -1021
#define DBL_MIN            2.2250738585072014e-308
#define DBL_MIN_10_EXP     -307
#define DBL_MAX_EXP        1024
#define DBL_MAX            1.79769313486231570e+308
#define DBL_MAX_10_EXP     308

/*
 *      Long Double definitions
 *
 *      For this implementation, long double is the same as double
 */

#define LDBL_MANT_DIG      DBL_MANT_DIG
#define LDBL_EPSILON       DBL_EPSILON
#define LDBL_DIG           DBL_DIG
#define LDBL_MIN_EXP       DBL_MIN_EXP
#define LDBL_MIN           DBL_MIN
#define LDBL_MIN_10_EXP    DBL_MIN_10_EXP
#define LDBL_MAX_EXP       DBL_MAX_EXP
#define LDBL_MAX           DBL_MAX
#define LDBL_MAX_10_EXP    DBL_MAX_10_EXP

#endif /* ANSI_C_SOURCE */

/* ******************************************************************
 *
 *      Non-ANSI definitions. The "old" definitions must be strict
 *      constants.
 */

#ifdef _OSF_SOURCE

#ifdef __LANGUAGE_C__
extern  unsigned   int SINFINITY;
extern  unsigned   int DINFINITY[2];
extern  unsigned   int SQNAN;
extern  unsigned   int DQNAN[2];
extern  unsigned   int SSNAN;
extern  unsigned   int DSNAN[2];
#endif

#define FLT_INFINITY  (*((float *) (&SINFINITY)))
#define DBL_INFINITY  (*((double *) (DINFINITY)))
#define LDBL_INFINITY DBL_INFINITY
#define FLT_QNAN (*((float *) (&SQNAN)))
#define DBL_QNAN (*((double *) (DQNAN)))
#define FLT_SNAN (*((float *) (&SSNAN)))
#define DBL_SNAN (*((double *) (DSNAN)))


/*
 *
 *      Values for the IEEE Rounding Modes (ANSI Encoding)
 *
 *      RZ = Round toward zero
 *      RN = Round toward nearest (default)
 *      RP = Round toward plus infinity
 *      RM = Round toward minus infinity
 *
 */
#define FP_RND_RZ       0
#define FP_RND_RN       1
#define FP_RND_RP       2
#define FP_RND_RM       3


/*
 *
 *      Floating Point Class Function Return Values
 *
 *      These are the values returned by the class function.
 *      The class function is one of the recommended functions in the
 *      IEEE standard. 
 * 
 *   NOTE: The values returned by fp_class[f/d]() are defined in 
 *		   fp_class.h. They are similarly named to those here, although
 *		   with DIFFERENT values.
 *		   For compatability assign the appropriate fp_plus_xxx
 *		   and fp_minus_xxx the corresponding values from fp_class.h.
 *		   
 *		   -Fred Iannelli 11/25/91 - 
 *
 */
#include <fp_class.h>
/* defined in fp_class.h 
   #define FP_SNAN           
   #define FP_QNAN     */
#define FP_PLUS_INF       FP_POS_INF
#define FP_MINUS_INF      FP_NEG_INF
#define FP_PLUS_NORM      FP_POS_NORM  
#define FP_MINUS_NORM     FP_NEG_NORM
#define FP_PLUS_DENORM    FP_POS_DENORM
#define FP_MINUS_DENORM   FP_NEG_DENORM
#define FP_PLUS_ZERO      FP_POS_ZERO
#define FP_MINUS_ZERO     FP_NEG_ZERO

#endif /* ALL_SOURCE */
#endif /* _FLOAT_H_ */


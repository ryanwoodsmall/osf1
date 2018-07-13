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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2.2
*/ 
/*   $RCSfile: TextDIconI.h,v $ $Revision: 1.1.4.3 $ $Date: 1993/07/15 17:17:32 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#ifndef _XmTextDIconP_h
#define _XmTextDIconP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************/
/* 16x16 drag icon */
/*******************/

#define XmTEXTUAL_DRAG_ICON_WIDTH_16 16
#define XmTEXTUAL_DRAG_ICON_HEIGHT_16 16
#define XmTEXTUAL_DRAG_ICON_X_HOT_16 7
#define XmTEXTUAL_DRAG_ICON_Y_HOT_16 0


static char XmTEXTUAL_DRAG_ICON_BITS_16[] = {
   0x00, 0x00, 0xfe, 0x0f, 0x02, 0x08, 0x02, 0x08, 0xfa, 0x0b, 0x02, 0x08,
   0xfa, 0x0b, 0x02, 0x08, 0x02, 0x08, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


static char XmTEXTUAL_DRAG_ICON_MASK_BITS_16[] = {
   0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f,
   0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*******************/
/* 32x32 drag icon */
/*******************/


#define XmTEXTUAL_DRAG_ICON_WIDTH_32 26
#define XmTEXTUAL_DRAG_ICON_HEIGHT_32 20
#define XmTEXTUAL_DRAG_ICON_X_HOT_32 26
#define XmTEXTUAL_DRAG_ICON_Y_HOT_32 4

static char XmTEXTUAL_DRAG_ICON_BITS_32[] = {
   0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x01, 0x02, 0x00, 0x00, 0x01,
   0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01,
   0x82, 0xff, 0x0f, 0x01, 0xc2, 0xff, 0x0f, 0x01, 0xc2, 0xff, 0x07, 0x01,
   0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x82, 0xff, 0x0f, 0x01,
   0xc2, 0xff, 0x0f, 0x01, 0xc2, 0xff, 0x07, 0x01, 0x02, 0x00, 0x00, 0x01,
   0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01,
   0xfe, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00};


static char XmTEXTUAL_DRAG_ICON_MASK_BITS_32[] = {
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03};

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmTextDIconP_h */

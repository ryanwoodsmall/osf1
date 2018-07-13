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
/*  DEC/CMS REPLACEMENT HISTORY, Element SMICONSTRAIN.H */
/*  *4    14-MAR-1990 17:31:50 WEBER "Change argument passing" */
/*  *3    13-MAR-1990 10:17:33 GREBUS "Fixed bug. Temp buffers must match drain datatype" */
/*  *2     9-MAR-1990 14:49:50 GREBUS "Change constrain context structure." */
/*  *1     8-MAR-1990 15:44:37 GREBUS "New element for constrains" */
/*  DEC/CMS REPLACEMENT HISTORY, Element SMICONSTRAIN.H */
/*******************************************************************************
**  Copyright 1989 by Digital Equipment Corporation, Maynard, Massachusetts,
**  and the Massachusetts Institute of Technology, Cambridge, Massachusetts.
**  
**                          All Rights Reserved
**  
**  Permission to use, copy, modify, and distribute this software and its 
**  documentation for any purpose and without fee is hereby granted, 
**  provided that the above copyright notice appear in all copies and that
**  both that copyright notice and this permission notice appear in 
**  supporting documentation, and that the names of Digital or MIT not be
**  used in advertising or publicity pertaining to distribution of the
**  software without specific, written prior permission.  
**  
**  DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
**  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
**  DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
**  ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
**  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
**  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
**  SOFTWARE.
**  
*******************************************************************************/

/*****************************************************************************
**
**  FACILITY:
**
**	X Imaging Extension
**      Sample Machine Independant DDX
**
**  ABSTRACT:
**
**      This is the header file for the CONSTRAIN pipeline element module.
**
**  ENVIRONMENT:
**
**      VAX/VMS V5.0
**	VAX ULTRIX V3.1
**	RISC ULTRIX V3.1
**
**  AUTHOR(S):
**
**      Gary Grebus
**
**  CREATION DATE:
**
**      Wed May  9 16:28:08 1990
**
**  MODIFICATION HISTORY:
**
*****************************************************************************/
#ifndef _SMICONSTRAIN
#define _SMICONSTRAIN

/*
**  Include files
*/
#include <SmiPipe.h>

/*	 
**  Function reference
*/	 
int     SmiConstrain();
int     SmiCreateConstrain();

/*
**  Structure definitions and Typedefs
*/

/*
**  Constrain pipeline context block.
*/
typedef struct _ConstrainPipeCtx {
    PipeElementCommonPart   common;
    struct _ConstrainPart {
	PipeSinkPtr	     src;
	PipeSinkPtr	     dst;
	PipeDrainPtr	     srcdrn;
	int                  model;
    } ConstrainPart;
} ConstrainPipeCtx, *ConstrainPipeCtxPtr;

/*
**  MACRO definitions
*/
    /*
    **  Constrain access macros
    */
#define ConSrcSnk_(ctx)   (((ConstrainPipeCtxPtr)(ctx))->ConstrainPart.src)
#define ConDstSnk_(ctx)   (((ConstrainPipeCtxPtr)(ctx))->ConstrainPart.dst)
#define ConSrcDrn_(ctx)	  (((ConstrainPipeCtxPtr)(ctx))->ConstrainPart.srcdrn)
#define ConModel_(ctx)	  (((ConstrainPipeCtxPtr)(ctx))->ConstrainPart.model)

#endif
/* _SMICONSTRAIN */

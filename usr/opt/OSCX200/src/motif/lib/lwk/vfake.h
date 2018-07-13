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
/* vfake.h - Include file for the VFake widget

*****************************************************************************
*									    *
*  COPYRIGHT (c) 1988, 1989, 1990  BY               			    *
*  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.		    *
*  ALL RIGHTS RESERVED.						    	    *
* 									    *
*  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND COPIED    *
*  ONLY IN  ACCORDANCE WITH  THE  TERMS  OF  SUCH  LICENSE  AND WITH THE    *
*  INCLUSION OF THE ABOVE COPYRIGHT NOTICE. THIS SOFTWARE OR  ANY  OTHER    *
*  COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY    *
*  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE IS  HEREBY    *
*  TRANSFERRED.							            * 
* 									    *
*  THE INFORMATION IN THIS SOFTWARE IS  SUBJECT TO CHANGE WITHOUT NOTICE    *
*  AND  SHOULD  NOT  BE  CONSTRUED AS  A COMMITMENT BY DIGITAL EQUIPMENT    *
*  CORPORATION.							            *
* 									    *
*  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE  OR  RELIABILITY OF ITS    *
*  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.		    *
* 									    *
*****************************************************************************

*****************************************************************************
*									    *
*		       DIGITAL INTERNAL USE ONLY			    *
*									    *
*      THIS SOFTWARE IS NOT FORMALLY SUPPORTED AND IS PROVIDED AS IS.       *
*  Do not distribute outside Digital without first contacting the author.   *
*									    *
*		Steve Klein, DECWIN::KLEIN, Digital ZKO			    *
*									    *
*****************************************************************************

This module contains C-language declarations needed to use the VFake widget.
Include this file into any C module that directly uses a VFake widget.

MODIFICATION HISTORY:

21-Feb-1990 (sjk) Initial release.
*/

/* Widget class */

external WidgetClass vfakewidgetclass;

/* Resource names */

#define VFakeNwindow			"window"

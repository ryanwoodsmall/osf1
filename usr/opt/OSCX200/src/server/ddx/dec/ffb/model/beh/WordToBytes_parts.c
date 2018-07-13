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
static char *rcsid = "@(#)$RCSfile: WordToBytes_parts.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/11/19 21:36:39 $";
#endif
wordtobytes_code( adr )
     Net_Entry **adr;
{
  extern void WordToBytes();
  int new_z [4];
  register Net_Entry *z;


  WordToBytes( (*(adr+4))->value, &new_z[0], &new_z[1], &new_z[2], &new_z[3] );
  z = (*(adr+3));
  assert_output( z, new_z[0] );
  z = (*(adr+2));
  assert_output( z, new_z[1] );
  z = (*(adr+1));
  assert_output( z, new_z[2] );
  z = (*(adr+0));
  assert_output( z, new_z[3] );
}

#
# *****************************************************************
# *                                                               *
# *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
# *                                                               *
# *   All Rights Reserved.  Unpublished rights  reserved  under   *
# *   the copyright laws of the United States.                    *
# *                                                               *
# *   The software contained on this media  is  proprietary  to   *
# *   and  embodies  the  confidential  technology  of  Digital   *
# *   Equipment Corporation.  Possession, use,  duplication  or   *
# *   dissemination of the software and media is authorized only  *
# *   pursuant to a valid written license from Digital Equipment  *
# *   Corporation.                                                *
# *                                                               *
# *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
# *   by the U.S. Government is subject to restrictions  as  set  *
# *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
# *   or  in  FAR 52.227-19, as applicable.                       *
# *                                                               *
# *****************************************************************
#
#
# HISTORY
#
#
#	@(#)$RCSfile: Makefile,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 05:37:11 $
#
# (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
# ALL RIGHTS RESERVED
#
#
# OSF/1 Release 1.0
#

DATAFILES		= br.tbl ndx.hdr ndx.mac \
			  toc.mac u.acc u.cov u.eqn u.ref u.ths u.toc

ILIST			= ${DATAFILES}
IDIR			= /usr/share/lib/mu/
IMODE			= 644

INOBJECTDIR_OPTIONS	= -e '/%beginstrip%/{' \
			  -e 'h' \
			  -e 's/.*/.\\" This version has had comments stripped; an unstripped version is available./p' \
			  -e 'g' \
			  -e '}' \
			  -e '/%beginstrip%/,$$s/[. 	][ 	]*\\".*//' \
			  -e '/^$$/d' \
			  -e '/\\n@/d'

include ${MAKEFILEPATH}/standard.mk
include ${MAKEFILEPATH}/datafiles.mk

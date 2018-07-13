
/***************************************************************************** 
**
**  Copyright (c) Digital Equipment Corporation, 1990 All Rights Reserved.
**  Unpublished rights reserved under the copyright laws of the United States.
**  
**  The software contained on this media is proprietary to and embodies the 
**  confidential technology of Digital Equipment Corporation. Possession, use,
**  duplication or dissemination of the software and media is authorized only 
**  pursuant to a valid written license from Digital Equipment Corporation.
**
**  RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure by the 
**  U.S. Government is subject to restrictions as set forth in 
**  Subparagraph (c)(1)(ii) of DFARS 252.227-7013, or in FAR 52.227-19, as
**  applicable.
**
*****************************************************************************/

/************************************************************************
**   IMG__ATTRIBUTE_ACCESS_UTILS
**
** FACILITY:                                                                
**   Image Services Library.
**
** ABSTRACT:
**
**   Access functions to get, put, and erase image attributes in the
**   ISL frame structure.
**
**   Data items are exchanged as copies of the items as they exist in	
**   the data structures.
**                                                                	
** ENVIRONMENT:
**
**   VAX/VMS, VAX/ULTRIX, RISC/ULTRIX, OSF1/RISC
**                                                                	
** AUTHOR:
**
**  Mark W. Sornson                                			
**                                                                	
** CREATION DATE: 
**
**   18-SEP-1989
**                                                                	
************************************************************************/

/*
** TABLE OF CONTENTS:
**
**  Global routines
*/
#ifdef NODAS_PROTO
struct FCT  *_ImgErase();
struct FCT  *_ImgGet();
void        _ImgLoadSelector();
struct FCT  *_ImgPut();
#endif


/*
** INCLUDE FILES:
*/
#include    <string.h>
#include    <stddef.h>

#include <img/ChfDef.h>
#include <img/ImgDef.h>
#include <ImgDefP.h>	    /* replaces img$internal_defs.h		    */
#include <ImgMacros.h>	    /* replaces img$ddifmacs.h and img$macros.h     */
#ifndef NODAS_PROTO
#include <imgprot.h>	    /* Img prototypes */
#endif

#if defined(__VMS) || defined(VMS)
#include <cda$def.h>
#include <cda$msg.h>
#include <cda$ptp.h>
#include <ddif$def.h>
#else
#if defined(NEW_CDA_CALLS)
#include <cdaptp.h>
#else
#include <cda_ptp.h>
#endif
#if defined(NEW_CDA_SYMBOLS)
#include <cdadef.h>
#include <cdamsg.h>
#include <ddifdef.h>
#else
#include <cda_def.h>
#include <cda_msg.h>
#include <ddif_def.h>
#endif
#endif

/*
** MACROS: (also see img$macros)
*/

/* macro to package status test from a CDA$LOCATE and copy to user item      */
/* if successful. If item is empty, item is zeroed.                          */

#ifdef NEW_CDA_SYMBOLS
#define TEST_AND_COPY_(status,item_size,item_addr) \
switch (status)\
    {\
    case CDA_INDEX:\
    case CDA_EMPTY:\
        ddif_item_size = 0;\
        /* NOTE: no break; fall through to zero out the empty item .... */\
    default:\
        if ((status & 1) == 1 || status == CDA_EMPTY)\
            {\
            if (item_size >= ddif_item_size)\
               {\
               /* move DDIF item to buffer. */\
               _IpsMovc5Long(ddif_item_size,(unsigned char *)ddif_item_addr,0,item_size,item_addr);\
               }\
            else\
               {\
               /* move what you can, signal possible truncation error              */\
               memcpy(bufptr,ddif_item_addr,item_size);\
               ChfSignal( 1,  ImgX_RVALTRUNC );\
               }\
            }\
        else\
            ChfSignal( 1,  status );\
        break;\
        }
#else
#define TEST_AND_COPY_(status,item_size,item_addr) \
switch (status)\
    {\
    case CDA$_INDEX:\
    case CDA$_EMPTY:\
        ddif_item_size = 0;\
        /* NOTE: no break; fall through to zero out the empty item .... */\
    default:\
        if ((status & 1) == 1 || status == CDA$_EMPTY)\
            {\
            if (item_size >= ddif_item_size)\
               {\
               /* move DDIF item to buffer. */\
               _IpsMovc5Long(ddif_item_size,(unsigned char *)ddif_item_addr,0,item_size,item_addr);\
               }\
            else\
               {\
               /* move what you can, signal possible truncation error              */\
               memcpy(bufptr,ddif_item_addr,item_size);\
               ChfSignal( 1,  ImgX_RVALTRUNC );\
               }\
            }\
        else\
            ChfSignal( 1,  status );\
        break;\
        }
#endif

/* macro to test CDA return status and signal if not NORMAL                  */

#define TEST_AND_SIGNAL_(stat) \
if ((stat & 1) != 1)\
   ChfSignal( 1, stat)

/*
** EQUATED SYMBOLS: none
*/

/* define SIZEOF_INT symbol, need for CDA rtn. calls, as &(sizeof(int))      */
/* was having trouble compiling                                              */

#define SIZEOF_INT sizeof(int)

/*
** OWN STORAGE: none
*/

/*
** EXTERNAL REFERENCES: 
**
**	From VAX RTL
*/
#ifdef NODAS_PROTO
void	ChfSignal();	/* Signal exception condition 		*/
void	ChfStop();	/* Stop execution and signal condition	*/

/*
**	From DDIF/CDA toolkit - are defined in <cdaptp.h> and <cda_ptp.h>
*/

/*
**      from ISL
*/
long	 ImgRestoreCtx();	    /* from module IMG$CONTEXT_SERVICES	*/
long	 ImgSaveCtx();		    /*	    "	    "			*/

long	 _ImgAttachDataPlane();	    /* from module IMG__DATA_PLANE_UTILS*/
void	 _ImgCfree();
long	 _ImgConvertLevelsToBits();      /* from module IMG__ATTRIBUTE_UTILS */
char	*_ImgRealloc();
long	 _ImgSetContentElement();
long	 _ImgSetDataPlane();	    /*	    "	    "			*/
void     _ImgSetFrameDataType();
long	 _ImgVerifyStandardFormat();	    /* from module IMG__VERIFY_UTILS */

unsigned long	_IpsGetUdpElementAlignment();	/* IPS__UDP_UTILS   */
unsigned long	_IpsGetUdpScanlineAlignment();	/* IPS__UDP_UTILS   */
unsigned long	_IpsGetUdpInfo();	        /* IPS__UDP_UTILS   */
void		_IpsMovc5Long();
void		_IpsSetUdpClassAndDType();	/* IPS__UDP_UTILS   */
#endif



/*
** Module local processing routines for dealing with
** item codes that require special processing to get or put.
*/
#ifdef NODAS_PROTO
static void	     Build_udp();
static void	     Erase_fct_item();
static struct FCT   *Erase_special_item();
static void	     Get_fct_item();
static void	     Get_quant_levels_per_comp();
static struct FCT   *Get_special_item();
static void	     Put_quant_levels_per_comp();
static struct FCT   *Put_special_item();
#else
PROTO(static void Build_udp, (struct FCT */*fct*/, long /*item_code*/, struct UDP */*dscptr*/, long /*index*/));
PROTO(static void Erase_fct_item, (struct FCT */*fct*/, unsigned long /*itemcode*/, unsigned long /*index*/));
PROTO(static struct FCT *Erase_special_item, (struct FCT */*fct*/, int /*itemcode*/, int /*index*/));
PROTO(static void Get_fct_item, (struct FCT */*fct*/, long /*itemcode*/, char **/*bufptr*/, long */*buflen*/));
PROTO(static void Get_quant_levels_per_comp, (struct FCT */*fct*/, long /*itemcode*/, char */*bufptr*/, long /*buflen*/, long */*retlen*/, long /*index*/));
PROTO(static struct FCT *Get_special_item, (struct FCT */*fct*/, long /*itemcode*/, char */*bufptr*/, long /*buflen*/, long */*retlen*/, long /*index*/));
PROTO(static void Put_quant_levels_per_comp, (struct FCT */*fct*/, long /*itemcode*/, char */*bufptr*/, long /*buflen*/, long /*index*/));
PROTO(static struct FCT *Put_special_item, (struct FCT */*fct*/, long /*itemcode*/, char */*bufptr*/, long /*buflen*/, long /*index*/));
#endif


/*
**  External symbol definitions (for status codes)
*/
#include <img/ImgStatusCodes.h>

/*
** DDIF codes lookup table.
*/
#if defined(__VAXC) || defined(VAXC)
globalref long int _ImgAL_DDIFAccessTable[];
#else
extern long int _ImgAL_DDIFAccessTable[];
#endif


/************************************************************************
** _ImgErase()
**
** FUNCTIONAL DESCRIPTION:                                		
**                                                                	
**	Deletes an item from the internal frame structures by calling
**      CDA_ERASE_ITEM_() to mark it "EMPTY".
**                                                                	
** FORMAL PARAMETERS:                                
**                                                                	
**	fct		= Address of Frame Context Block.  This is also 
**			  called the frame-id.
**
**	selector	= Item selector code.
**
**      index           = index value for items with "ARRAY_OF_xxxx" type
**			  This argument is optional.
**
** IMPLICIT INPUTS:                                			
**                                                                	
** IMPLICIT OUTPUTS:                                			
**                                                                	
**	NONE.                                                                
**                                                                	
** FUNCTION VALUE:
**
**	fct		address of frame context block (frame-id) passed in.
**
** SIGNAL CODES:
**
**	ImgX_ITMCODERR	Item code error (generic message)
**
** SIDE EFFECTS:                                			
**
**	none
**
*************************************************************************/

struct FCT *_ImgErase( fct, itemcode, index)
struct FCT 	*fct;
long             itemcode;
long		 index;
{
CDAconstant ddif_code;
int	idu_item_index;
int	index_ddif	= (int)index;
int	status;
struct ITEMCODE  selector;

_ImgLoadSelector(itemcode,&selector);
/* 
** Select action based on itemcode structure type.
*/
switch (selector.ItmV_StructType)
    {
    /*
    ** Erase items that are stored in DDIF data structures.
    */
    case ImgK_SegAggrItem:
        /*
        ** Using the ISL item code ItmW_Offset field as an index, get
        ** the actual DDIF item code that will be used for the erase
        ** operation.
        */
        ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
        status = CDA_ERASE_ITEM_( 
                &(fct->FctL_RootAggr),
                &(fct->FctL_SegAggr), 
                &ddif_code, 
                &index_ddif );  
#if defined(NEW_CDA_SYMBOLS)
	if ( status != CDA_NORMAL && status != CDA_EMPTY )
#else
        if ( status != CDA$_NORMAL && status != CDA$_EMPTY )
#endif
	    ChfStop( 1,  status );
        break;
    case ImgK_SgaAggrItem:
	switch ( itemcode )
	    {
	    /*
	    ** Items which have DDIF/CDA support
	    */
	    default:
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_ERASE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_SgaAggr),
		    &ddif_code,
                    &index_ddif );
#if defined(NEW_CDA_SYMBOLS)
	if ( status != CDA_NORMAL && status != CDA_EMPTY )
#else
        if ( status != CDA$_NORMAL && status != CDA$_EMPTY )
#endif
		    ChfStop( 1,  status );
		break;
	    }
	break;

    case ImgK_IduAggrItem:
	switch ( itemcode )
	    {
	    /*
	    ** Items which have DDIF/CDA support.
	    */
	    default:
/*		ImgSaveCtx( fct );
*/
		_ImgSetDataPlane( fct, (long)index_ddif );
		idu_item_index = 0;
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_ERASE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_IduAggr),
		    &ddif_code,
		    &idu_item_index );
#if defined(NEW_CDA_SYMBOLS)
	if ( status != CDA_NORMAL && status != CDA_EMPTY )
#else
        if ( status != CDA$_NORMAL && status != CDA$_EMPTY )
#endif
		    ChfStop( 1,  status );
/*		ImgRestoreCtx( fct );
*/
		break;
	    }
	break;

    case ImgK_SplProcItem:
	Erase_special_item( fct, itemcode, (long)index_ddif );
        break;

    case ImgK_FctItem:
	Erase_fct_item( fct, itemcode, (long)index_ddif );
	break;
    case ImgK_DscAggrItem:
    case ImgK_DhdAggrItem:
    default:
	ChfStop( 3,  ImgX_ITMCODERR, 1, selector );
	break;
    }   /* end of struct_type switch */

return fct;
} /* end of _ImgErase function */


/************************************************************************
** _ImgGet()
**
** FUNCTIONAL DESCRIPTION:
**
**	Get a data item from the internal frame data structures and
**	return it to the caller in the buffer passed in by reference.
**
** FORMAL PARAMETERS:
**
**	fct		= Address of Frame Context Block (frame-id)
**
**	selector	= ISL Item selector code
**
**	bufptr		= Address of the (receive) buffer into which
**			  the returned item is put.
**
**	buflen		= Length in bytes of the receive buffer.
**
**	retlen		= address of a word to receive the length
**			  in bytes of the returned data item.
**			  (Optional: not used if not present.)
**
**	index		= index value for an array-structured item.
**			  passed by value.
**			  optional (default = 0)
**
** IMPLICIT INPUTS:
**
**	None
**
** IMPLICIT OUTPUTS:
**
**	NONE.
**
** FUNCTION VALUE:
**
**	fct		address of context block passed in
**			(note: this is returned simply because
**			no other value is returned)
**
** SIGNAL CODES:
**
**	ImgX_ITMCODERR	Item code error.  Unrecognized item code or
**			unprocessable item code.
**	ImgX_RVALTRUNC	Return value truncation warning; return buffer was
**			shorter than the field from which the item was
**			extracted.  Truncation may have occurred.
**
** SIDE EFFECTS:
**
**	none
**
*************************************************************************/

struct FCT *_ImgGet( fct, itemcode, bufptr, buflen, retlen, index)
struct FCT	*fct;		/* required, frame context block */
long             itemcode;      /* required, longword itemcode */
void		*bufptr;	/* required, return buffer pointer */
long		 buflen;	/* required, retbuf len in bytes */
long		*retlen;	/* optional, return count in bytes */
long		 index;         /* index (required for ARRAY type items) */
{
CDAaddress ddif_item_addr;
long	 data_type;
CDAconstant ddif_code;
long	 ddif_item_size;
long	 dummy;
int	 idu_item_index;
int      index_ddif	= (int)index;
long	 itmlen;
char	*itmptr;
long	 parameter_count;
int	 status;
CDAconstant user_label_string_type;
short	 item_size_in_bytes;
short	 retbuflen;
struct ITEMCODE	 selector;	

_ImgLoadSelector(itemcode,&selector);

if ( retlen == 0 )
    retlen = &dummy;
/*
** Ok, let's be civilized and make a reasonable effort to blank out the
** buffer, in case the user wasn't sure of the size of the item they wanted.
*/
if (buflen == sizeof(long))
    *(long *)bufptr = (long)0;
else if (buflen == sizeof(int))
    *(int *)bufptr = (int)0;
else
    *(char *)bufptr = (char)0;
/*
** Figure out where to get the itemcode return value from.  Is it in the
** FCT or in a subordinate DDIF structure?
*/
switch (selector.ItmV_StructType)
    {
    case ImgK_FctItem:
	/*
        ** determine/set frame data type if the item is asked for...
        */
        if (itemcode == Img_ImageDataClass)
                _ImgSetFrameDataType( fct );
        /*
        ** Get the item from the frame context block (FCT).
	** FCT itemcodes don't work on alpha, so figure out the item
	** the hard way.
	*/
	Get_fct_item (fct, itemcode, &itmptr, &itmlen);
        if (buflen >= itmlen)
	    {
            *retlen = itmlen;
            /*
            ** Copy items that fit in the supplied buffer.
	    ** (Just assign longs; it's faster.)
            */
	    if (itmlen == sizeof(long))
        	*((long *)bufptr) = *((long *)itmptr);
	    else
		memcpy(bufptr,itmptr,itmlen);
            }
        else
            {
            /*
            ** Copy items that are larger than the supplied buffer.  Note that
            ** this will cause a truncation error to be signalled.
            */
            memcpy(bufptr,itmptr,buflen);
            *retlen = buflen;
            ChfSignal( 1,  ImgX_RVALTRUNC );
            }
        break;

    case ImgK_SegAggrItem:
        /*
        ** Get the item from DDIF segment aggregate structure.
        */
        ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
        status = CDA_LOCATE_ITEM_(
                &(fct->FctL_RootAggr),
                &(fct->FctL_SegAggr),
                &ddif_code,
                &ddif_item_addr,
                &ddif_item_size,
                &index_ddif,
                &user_label_string_type );
        TEST_AND_COPY_( status, buflen, bufptr);
        *retlen = (ddif_item_size > buflen) ? buflen : ddif_item_size;
        break;

    case ImgK_SgaAggrItem:
        /*
        ** Get SGA aggregate attributes 
        */
	switch ( itemcode )
	    {
	    /*
	    ** Items to temporarily process as special items
	    */
	    case Img_QuantLevelsPerComp:
		Get_quant_levels_per_comp( fct, itemcode, bufptr, buflen, 
					    retlen, (long)index_ddif );
		break;
	    /*
	    ** Items to regularly process as SGA items.
	    */
	    default:
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_LOCATE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_SgaAggr),
		    &ddif_code,
		    &ddif_item_addr,
		    &ddif_item_size,
		    &index_ddif, 0 );
		TEST_AND_COPY_( status, buflen, bufptr);
		*retlen = (ddif_item_size > buflen) ? buflen : ddif_item_size;
		break;
	    }
	break;

    /*
    ** Get image coding attributes.
    */
    case ImgK_IduAggrItem:
	switch ( itemcode )
	    {
	    /*
	    ** Items to be regularly processed as IDU items
	    */
	    default:
/*		ImgSaveCtx( fct );
*/
		_ImgSetDataPlane( fct, (long)index_ddif );
		idu_item_index = 0;
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_LOCATE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_IduAggr),
		    &ddif_code,
		    &ddif_item_addr,
		    &ddif_item_size,
		    &idu_item_index, 
		    0 );
		TEST_AND_COPY_( status, buflen, bufptr);
/*		ImgRestoreCtx( fct );
*/
		*retlen = (ddif_item_size > buflen) ? buflen : ddif_item_size;
		break;
	    }
	break;

    case ImgK_SplProcItem:
        Get_special_item( fct, itemcode, bufptr, buflen, retlen, (long)index_ddif );
        break;

    default:  /* default for switch (struct_type) */
        /*
        ** Unrecognized or invalid item codes.
        */
        ChfStop( 3,  ImgX_ITMCODERR, 1, itemcode );
        break;
    }    /* end of switch (struct_type)  */

return fct;
} /* end of _ImgGet function */


/******************************************************************************
**  _ImgLoadSelector()
**
**  FUNCTIONAL DESCRIPTION:
**
**      Take an itemcode and fill the parts of the selector (struct ITEMCODE).
**
**  FORMAL PARAMETERS:
**
**      itemcode - an integer representation of the ITEMCODE longword struct.
**     &selector - the address od the ITEMCODE structure to be loaded.
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**      None.
**
**  SIDE EFFECTS:
**
**	None.
**
******************************************************************************/
void _ImgLoadSelector( itemcode, selector )
unsigned int     itemcode;
struct ITEMCODE	*selector;
{
#ifndef sparc
  *selector = * ((struct ITEMCODE *) &itemcode);
#else
  unsigned int rc = 0;
  rc |= (itemcode & 0x0000FFFF) << 16;
  rc |= (itemcode & 0x00FF0000) >>  8;
  rc |= (itemcode & 0x0F000000) >> 20;
  rc |= (itemcode & 0x80000000) >> 31;
  rc |= (itemcode & 0x40000000) >> 29;
  rc |= (itemcode & 0x20000000) >> 27;
  rc |= (itemcode & 0x10000000) >> 25;

  *selector = * ((struct ITEMCODE *) &rc);
#endif

  return;
} /* end of _ImgLoadSelector */


/************************************************************************
** _ImgPut
**                                                                	
** FUNCTIONAL DESCRIPTION:                                		
**                                                                	
**	Put the contents of a buffer into the internal frame data	
**	structure.  
**                                                                	
** FORMAL PARAMETERS:                                			
**                                                                	
**	fct		= Address of Frame Context Block (frame-id)
**                                                                	
**	selector	= Item selector code                                
**                                                                	
**	bufptr		= Address of the (source) buffer from which 	
**			  the item to be stored is gotten.		
**                                                                	
**	buflen		= Length in bytes of the source buffer. (Required)
**
**	index		= Index value of an array-structured item.
**			  This argument is optional, default = 0.
**                                                                	
** IMPLICIT INPUTS:                                			
**                                                                	
**	None to speak of, although the addresses of the data blocks	
**	in the frame structure might be thought of as implicit.		
**	These addresses are accessable directly or indirectly via	
**	the FCT.                                			
**                                                                	
** IMPLICIT OUTPUTS:                                			
**                                                                	
**	NONE.                                                                
**                                                                	
** FUNCTION VALUE:	
**
**	fct		address of context block passed in
**			(note: this is returned simply because
**			no other value is returned)
**
** SIGNAL CODES:
**
**	ImgX_INVBUFLEN	The buffer length was shorter than required to
**			return the requested item code.
**	ImgX_ITMCODERR	Item code error.  Unrecognized item code or
**			unprocessable item code.
**	ImgX_NOWRTACC	Item code that disallows write access to the data
**			field was rejected.
**
** SIDE EFFECTS:                                			
**
**	none.
**
*************************************************************************/

struct FCT *_ImgPut( fct, itemcode, bufptr, buflen, index)
struct FCT	*fct;
long             itemcode;
void		*bufptr;
long		 buflen;
long		 index;
{
CDAconstant add_info;
int	cda_integer;
CDAconstant ddif_code;
int	idu_item_index;
int    index_ddif	= (int)index;
long	 itmlen;
char	*itmptr;
long	parameter_count;
int	status;
short	item_size_in_bits;
short	item_size_in_bytes;
short	srcbuflen;
struct  ITEMCODE selector;

_ImgLoadSelector(itemcode,&selector);

/*
** Reject any codes flagged as nowrite items
*/
if (selector.ItmV_Nowrite)
    ChfStop( 4,  ImgX_ITMCODERR, 1, itemcode, ImgX_NOWRTACC );

/*
** Figure out where to put the itemcode value into.  Does it go in the
** FCT or in a subordinate DDIF structure?
*/
switch (selector.ItmV_StructType)
    {
    case ImgK_FctItem:
	/*
        ** Put the item into the frame context block (FCT).
	** FCT itemcodes don't work on alpha, so figure out the offset
	** the hard way.
	*/
	Get_fct_item (fct, itemcode, &itmptr, &itmlen);
        if (selector.ItmB_DataType == ImgK_IntegerType)
            {
	    /*
	    ** FCT itemcodes CANNOT be larger than a long int, but allow
	    ** someone to pass in a shorter buffer (right, Mark?).
	    */
            srcbuflen = (buflen > sizeof(long)) ? sizeof(long) : buflen;
            memcpy(itmptr,bufptr,srcbuflen);
	    }
        else
            ChfStop( 3,  ImgX_ITMCODERR, 1, itemcode );
        break;

    case ImgK_SegAggrItem:  /* DDIF segment aggr. item               */
        /*
        ** Get the DDIF access code that corresponds to the ISL itemcode.
        */
        ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
#ifdef NEW_CDA_SYMBOLS
        add_info = CDA_K_ISO_LATIN1;
#else
        add_info = CDA$K_ISO_LATIN1;
#endif
        status = CDA_STORE_ITEM_(
                &(fct->FctL_RootAggr),
                &(fct->FctL_SegAggr),
                &ddif_code,
                &buflen,bufptr,
                &index_ddif, 
                &add_info );
        TEST_AND_SIGNAL_(status);
        break;

    case ImgK_SgaAggrItem:  /* DDIF SGA aggr item    */
	switch ( itemcode )
	    {
	    /*
	    ** Convert some buffers into int's for CDA
	    */
	    case Img_PrivateData:
	    case Img_LookupTables:
		break;
	    /*
	    ** Convert all other items into int's
	    */
	    default:
		if (buflen == sizeof (long))
		    cda_integer = (int) (*(long *)bufptr);
		else if (buflen == sizeof (int))
		    cda_integer = (int) (*(int *)bufptr);
		bufptr = (char *)&cda_integer;
		buflen = sizeof(cda_integer);
		break;
	    }
	switch ( itemcode )
	    {
	    case Img_QuantLevelsPerComp:
		Put_quant_levels_per_comp( fct, itemcode, bufptr, buflen, 
					    (long)index_ddif );
		break;
	    /*
	    ** Items which have DDIF/CDA support
	    */
	    default:
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_STORE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_SgaAggr),
		    &ddif_code,
		    &buflen,
		    bufptr,
		    &index_ddif,
		    0 );
		TEST_AND_SIGNAL_(status);
		break;
	    }
	break;

    case ImgK_IduAggrItem:   /* DDIF IDU aggregate item */
	switch ( itemcode )
	    {
	    /*
	    ** Convert some buffers into int's for CDA
	    */
	    case Img_PrivateCodingAttr:
	    case Img_PlaneData:
		break;
	    /*
	    ** Convert all other items into int's
	    */
	    default:
		if (buflen == sizeof (long))
		    cda_integer = (int) (*(long *)bufptr);
		else if (buflen == sizeof (int))
		    cda_integer = (int) (*(int *)bufptr);
		bufptr = (char *)&cda_integer;
		buflen = sizeof(cda_integer);
		break;
	    }
	switch ( itemcode )
	    {
	    /*
	    ** Items which have DDIF/CDA support.
	    */
	    default:
/*		ImgSaveCtx( fct );
*/
		_ImgSetDataPlane( fct, (long)index_ddif );
		idu_item_index = 0;
		ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
		status = CDA_STORE_ITEM_(
		    &(fct->FctL_RootAggr),
		    &(fct->FctL_IduAggr),
		    &ddif_code,
		    &buflen,
		    bufptr,
		    &idu_item_index,
		    0 );
		TEST_AND_SIGNAL_(status);
/*		ImgRestoreCtx( fct );
*/
		break;
	    }
	break;

    case ImgK_SplProcItem:
        Put_special_item( fct, itemcode, bufptr, buflen, (long)index_ddif );
        break;

    case ImgK_DscAggrItem:
    case ImgK_DhdAggrItem:
    default:  /* default for switch (struct_type) */
        ChfStop( 3, ImgX_ITMCODERR, 1, itemcode );
        break;
    }   /* end of switch (struct_type) */

return fct;
} /* end of _ImgPut */


/******************************************************************************
**  Build_udp()
**
**  FUNCTIONAL DESCRIPTION:
**
**	Build (or fill in) a UDP descriptor based on the attributes
**	of a specified frame.
**
**  FORMAL PARAMETERS:
**
**	fct	    Frame context block (fid) to get attributes from.
**
**	item_code   Item code to use when building UDP.  Descriminates
**		    UDPs from CDPs.
**
**	dscptr	    Address of a buffer that will contain the UDP info,
**		    which gets filled in by this function.
**
**	index	    IDU/data plane index to use in extracting attributes
**		    from the frame.
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**	none
**
**  SIDE EFFECTS:
**
**	none
**
******************************************************************************/
static void Build_udp( fct, item_code, dscptr, index )
struct FCT  *fct;
long	     item_code;
struct UDP  *dscptr;
long	     index;
{
char	    *data_plane_base    = 0;
long	     bits_per_pixel	= 0;
long	     comp_space_org	= 0;
long	     data_plane_size    = 0;
long	     data_offset	= 0;
long	     number_of_comp	= 0;
long	     number_of_lines    = 0;
long	     pixels_per_line    = 0;
long	     pixel_stride	= 0;
long	     quant_levels	= 0;
long	     scanline_stride    = 0;
long	     virtual_arsize	= 0;
struct UDP  *udp;
struct UDP  *cdp;

/*
** Get data items that are common to both UDPs and CDPs
*/
_ImgGet( fct, Img_BitsPerPixel,		&bits_per_pixel,    sizeof(bits_per_pixel), 0, index );
_ImgGet( fct, Img_CompSpaceOrg,		&comp_space_org,    sizeof(comp_space_org), 0, index );
_ImgGet( fct, Img_DataPlaneBase,	&data_plane_base,   sizeof(data_plane_base), 0, index );
_ImgGet( fct, Img_DataPlaneSize,	&data_plane_size,   sizeof(data_plane_size), 0, index );
_ImgGet( fct, Img_DataOffset,		&data_offset,	    sizeof(data_offset), 0, index );
_ImgGet( fct, Img_NumberOfComp,		&number_of_comp,    sizeof(number_of_comp), 0, index );
_ImgGet( fct, Img_NumberOfLines,	&number_of_lines,   sizeof(number_of_lines), 0, index );
_ImgGet( fct, Img_PixelStride,		&pixel_stride,	    sizeof(pixel_stride), 0, index );
_ImgGet( fct, Img_PixelsPerLine,	&pixels_per_line,   sizeof(pixels_per_line), 0, index );
_ImgGet( fct, Img_ScanlineStride,	&scanline_stride,   sizeof(scanline_stride), 0, index );
_ImgGet( fct, Img_VirtualArsize,	&virtual_arsize,    sizeof(virtual_arsize), 0, index );

/*
** Get quant levels for the data plane only if it's meaningful
** to do so, namely when the data plane data is monochromatic
** (or a single band of a multispectral image) and when the band
** is all in just the one plane.
*/
switch ( comp_space_org )
    {
    case ImgK_BandIntrlvdByPixel:
	if ( number_of_comp == 1 )
	    _ImgGet( fct, Img_QuantLevelsPerComp, &quant_levels, sizeof(quant_levels), 0, index );
	break;
    case ImgK_BandIntrlvdByPlane:
	_ImgGet( fct, Img_QuantLevelsPerComp, &quant_levels, sizeof(quant_levels), 0, index );
	break;
    default:
	break;
    }

/*
** Get data items that are descriptor specific.  (Assume that the
** descriptor structure address passed in actually points to the
** descriptor that corresponds to the item code.)
**
** After all items are fetched, fill in the descriptors.
*/
switch ( item_code )
    {
    case Img_Udp:
	udp = (struct UDP *) dscptr;
	udp->UdpW_PixelLength	= bits_per_pixel;
	udp->UdpB_DType		= UdpK_DTypeV;
	udp->UdpB_Class		= UdpK_ClassUBA;
	udp->UdpA_Base		= (unsigned char *)data_plane_base;
	udp->UdpL_ArSize	= virtual_arsize;
				  /* (data_plane_size * 8) + data_offset; */
	udp->UdpL_PxlStride	= pixel_stride;
	udp->UdpL_ScnStride	= scanline_stride;
	udp->UdpL_X1		= 0;
	udp->UdpL_X2		= pixels_per_line - 1;
	udp->UdpL_Y1		= 0;
	udp->UdpL_Y2		= number_of_lines - 1;
	udp->UdpL_PxlPerScn	= pixels_per_line;
	udp->UdpL_ScnCnt	= number_of_lines;
	udp->UdpL_Pos		= data_offset;
	udp->UdpL_CompIdx	= index;
	udp->UdpL_Levels	= quant_levels;

	break;

    case Img_Cdp:
	/*
	** NOTE that although PixelLength, PxlStride, ScnStride, 
	** X1, X2, Y1, & Y2 are theoretically undefined because the
	** data is compressed, the values are filled in according to
	** their frame attribute values to designate "intent" to
	** any decompression algorithm -- i.e., the decompression
	** algorithms should recognize these values as applicable to
	** the data once restored to PCM form.
	*/
	cdp = (struct UDP *) dscptr;
	cdp->UdpW_PixelLength	= bits_per_pixel;
	cdp->UdpB_DType		= UdpK_DTypeVU;
	cdp->UdpB_Class		= UdpK_ClassUBS;
	cdp->UdpA_Base		= (unsigned char *)data_plane_base;
	cdp->UdpL_ArSize	= (data_plane_size * 8) + data_offset;
	cdp->UdpL_PxlStride	= pixel_stride;
	cdp->UdpL_ScnStride	= scanline_stride;
	cdp->UdpL_X1		= 0;
	cdp->UdpL_X2		= pixels_per_line - 1;
	cdp->UdpL_Y1		= 0;
	cdp->UdpL_Y2		= number_of_lines - 1;
	cdp->UdpL_PxlPerScn	= pixels_per_line;
	cdp->UdpL_ScnCnt	= number_of_lines;
	cdp->UdpL_Pos		= data_offset;
	cdp->UdpL_CompIdx	= index;
	cdp->UdpL_Levels	= quant_levels;

    default:
	/*
	** Do nothing if the item isn't a descriptor.
	*/
	break;
    }

return;
} /* end of Build_udp */


/******************************************************************************
**  Erase_fct_item
**
**  FUNCTIONAL DESCRIPTION:
**
**	Erase attributes which are stored in the frame context block (fct).
**
**  FORMAL PARAMETERS:
**
**      fct             Address of FCT block belonging to frame to which
**			attributes must be inserted.
**	itemcode	Itemcode of item to erase.
**	index		Index of array structured item to erase.
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**	none
**
**  SIDE EFFECTS:
**
**	none
**
******************************************************************************/
static void Erase_fct_item( fct, itemcode, index )
struct FCT	*fct;
unsigned long	 itemcode;
unsigned long	 index;
{
unsigned long	 zero	    = 0;
struct UDP	*saved_udps;

switch( itemcode )
    {
    case Img_RectRoiInfo:
	_ImgGet( fct, Img_RectRoiInfo, &saved_udps, LONGSIZE, 0, 0 );
	if ( saved_udps != 0 )
	    {
	    _ImgCfree( (char *) saved_udps );
	    _ImgPut( fct, Img_RectRoiInfo, &zero, LONGSIZE, 0 );
	    }
	break;

    case Img_UserField:
	_ImgPut( fct, Img_UserField, &zero, LONGSIZE, 0 );
	break;
    /*
    ** If erase isn't supported for the itemcode, do nothing
    */
    default:
	break;
    } /* end of switch */

return;
} /* end of Erase_fct_item */

/************************************************************************
**  Erase_special_item() - Handle special case item code
**
**  FUNCTIONAL DESCRIPTION:
**
**      Erase image frame attributes which require special processing (i.e. can
**      not be directly inserted into the structures using _ImgPut).
**
**  FORMAL PARAMETERS:
**
**      fct             Address of FCT block belonging to frame to which
**			attributes must be inserted.
**	itemcode	Itemcode of item to erase.
**	index		Index of array structured item to erase.
**
**
**  IMPLICIT INPUTS:
**
**      none
**
**  IMPLICIT OUTPUTS:
**
**      none
**
**  FUNCTION VALUE:
**
**      fct		Pointer to FCT originally specified as input
**
**  SIGNAL CODES:
**
**	ImgX_NOSPCPRC	No special processing available for item code
**
**  SIDE EFFECTS:
**
**      none
**
************************************************************************/
static struct FCT *Erase_special_item( fct, itemcode, index )
struct FCT *fct;
int	    itemcode;
int	    index;
{
long	status;

/*
** Switch on each item code to perform the processing that is
** special to each item code.
*/
switch ( itemcode )
    {
    case Img_PxlAspectRatio:
	/*
	** Erase the pixel aspect ratio in the frame structure
	** as two separate item codes:  the first as the pixel
	** progression pixel distance, and the second as the 
	** line progression pixel distance.
	*/
	{
	_ImgErase( fct, Img_PPPixelDist, 0 );
	_ImgErase( fct, Img_LPPixelDist, 0 );
	break;
	}
    default:
        ChfStop( 3,  ImgX_NOSPCPRC, 1, itemcode );
    }

return (fct);
} /* end of Erase_special_item */


/******************************************************************************
**  Get_fct_item()
**
**  FUNCTIONAL DESCRIPTION:
**
**	[@tbs@]
**
**  FORMAL PARAMETERS:
**
**	[@description_or_none@]
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**	[@description_or_none@]
**
**  SIDE EFFECTS:
**
**	none
**
******************************************************************************/
static void Get_fct_item( fct, itemcode, bufptr, buflen )
struct FCT	 *fct;
long              itemcode;
char		**bufptr;
long		 *buflen;
{
char	*ptr	= NULL;
long	len	= 0;

/*
** Find the item value and length
*/

switch (itemcode)
    {
    case Img_RootAggr:
	ptr = (char *)&(fct->FctL_RootAggr);
	len = (long)sizeof(fct->FctL_RootAggr);
	break;
    case Img_SegAggr:
	ptr = (char *)&(fct->FctL_SegAggr);
	len = (long)sizeof(fct->FctL_SegAggr);
	break;
    case Img_SgaAggr:
	ptr = (char *)&(fct->FctL_SgaAggr);
	len = (long)sizeof(fct->FctL_SgaAggr);
	break;
    case Img_ImgAggr:
	ptr = (char *)&(fct->FctL_ImgAggr);
	len = (long)sizeof(fct->FctL_ImgAggr);
	break;
    case Img_IceCnt:
	ptr = (char *)&(fct->FctL_IceCnt);
	len = (long)sizeof(fct->FctL_IceCnt);
	break;
    case Img_IduAggr:
	ptr = (char *)&(fct->FctL_IduAggr);
	len = (long)sizeof(fct->FctL_IduAggr);
	break;
    case Img_UserField:
	ptr = (char *)&(fct->FctL_UserField);
	len = (long)sizeof(fct->FctL_UserField);
	break;
    case Img_SpectType:
	ptr = (char *)&(fct->FctL_SpectType);
	len = (long)sizeof(fct->FctL_SpectType);
	break;
    case Img_PageBreak:
	ptr = (char *)&(fct->FctL_PageBreak);
	len = (long)sizeof(fct->FctL_PageBreak);
	break;
    case Img_PvtQLevels:
	ptr = (char *)&(fct->FctA_PvtQLevels);
	len = (long)sizeof(fct->FctA_PvtQLevels);
	break;
    case Img_RectRoiInfo:
	ptr = (char *)&(fct->FctA_RectRoiInfo);
	len = (long)sizeof(fct->FctA_RectRoiInfo);
	break;
    default:
	ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );
	break;
    }

*bufptr = ptr;
*buflen = len;

return;
} /* end of Get_quant_levels_per_comp */


/******************************************************************************
**  Get_quant_levels_per_comp()
**
**  FUNCTIONAL DESCRIPTION:
**
**	[@tbs@]
**
**  FORMAL PARAMETERS:
**
**	[@description_or_none@]
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**	[@description_or_none@]
**
**  SIDE EFFECTS:
**
**	none
**
******************************************************************************/
static void Get_quant_levels_per_comp( fct, itemcode, bufptr, buflen, retlen, 
                                    index )
struct FCT	*fct;
long             itemcode;
char		*bufptr;
long		 buflen;
long		*retlen;
long		 index;
{
long	 bits_per_comp;
CDAconstant ddif_code;
CDAaddress ddif_item_addr;
long	 ddif_item_size;
long	 found			= FALSE;
int	 index_ddif	= (int)index;
long	 max_index;
long	 quant_levels_per_comp = 0;
long	*q_levels;
int	 status;
struct ITEMCODE  selector;

_ImgLoadSelector(itemcode,&selector);

/*
** Look for CDA item DDIF$_SGA_QUANT_LEVELS_PER_COMP.
** NOTE: for as long as the DDIF code is undefined, this
** procedure will fail, which means that private data
** may be present in the file.
*/
ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
status = CDA_LOCATE_ITEM_(
	    &(fct->FctL_RootAggr),
	    &(fct->FctL_SgaAggr),
	    &ddif_code,
	    &ddif_item_addr,
	    &ddif_item_size,
	    &index_ddif,
	    0 );
switch ( status )
    {
#ifdef NEW_CDA_SYMBOLS
    case CDA_NORMAL:
#else
    case CDA$_NORMAL:
#endif
	/*
	** Quantlevels is ALWAYS an int
	*/
	if (ddif_item_size == sizeof(int))
	    quant_levels_per_comp = *(int *)ddif_item_addr;
	else
	    quant_levels_per_comp = *(long *)ddif_item_addr;
	    
	found = TRUE;
    default:
	break;
    }

/*
** If not found, look for private data in the private FCT structure
*/
if ( !found )
    if ( fct->FctA_PvtQLevels != 0 )
        {
	max_index = *(fct->FctA_PvtQLevels);
	q_levels = fct->FctA_PvtQLevels + 1;
	if ( index_ddif <= max_index )
	    /*
	    ** Index is in range ...
	    */
	    {
	    quant_levels_per_comp = q_levels[index_ddif];
	    found = TRUE;
	    }
	else
	    /*
	    ** Index is out of range, therefore return nothing.
	    */
	    quant_levels_per_comp = 0;
	    found = TRUE;
	}

/*
** If not found anywhere in the frame (privately or via CDA), use 
** ImgX_BITS_PER_COMP attribute to supply a default value ...
*/
if ( !found )
    {
    _ImgGet( fct, Img_BitsPerComp, &bits_per_comp, LONGSIZE, 0, index_ddif );
    quant_levels_per_comp = (1 << bits_per_comp);
    }

/*
** Copy the value into the user return buffer
*/
*((int *)bufptr) = (int)quant_levels_per_comp;

if (*retlen != 0)
    *retlen = sizeof(int);

return;
} /* end of Get_quant_levels_per_comp */


/************************************************************************
**  Get_special_item() - Handle special case item code
**
**  FUNCTIONAL DESCRIPTION:
**
**      Get image frame attributes which require special processing (i.e. can
**	not be directly extracted from the structures using _ImgGet).
**
**  FORMAL PARAMETERS:
**
**      fct		Address of FCT block belonging to frame from which
**			attributes must be derived.
**	itemcode	Item code of data to put.
**	bufptr		Address of data to put.
**	buflen		Length in bytes of data to put.
**	retlen		Address of longword to receive 
**	index		Index of array-structured item to put.
**
**  IMPLICIT INPUTS:
**
**      none
**
**  IMPLICIT OUTPUTS:
**
**      none
**
**  FUNCTION VALUE:
**
**      fct		Pointer to FCT originally specified as input
**
**  SIGNAL CODES:
**
**	ImgX_INVITMBFL	Invalid item buffer length.
**	ImgX_NOIMGAGRP	No image content aggregate pointer if frame.
**	ImgX_NOSPCPRC	No special processing available for item code
**
**  SIDE EFFECTS:
**
**      none
**
************************************************************************/
static struct FCT *Get_special_item( fct, itemcode, bufptr, buflen, retlen, 
                                    index )
struct FCT  *fct;
long	     itemcode;
char	    *bufptr;
long	     buflen;
long	    *retlen;
long	     index;
{
CDAagghandle aggr;
CDAconstant aggregate_item;
long	 compression;
long	 count		= 0;
long	 data_type;
CDAconstant ddif_code;
CDAaddress ddif_item_addr;
long	 ddif_item_size;
CDAaddress	itemadr;
long	 itemlen	= 0;
long	 length;
CDArootagghandle root_aggr;
long	 size		= 0;
int	 status;

struct UDP  *udp;
struct UDP  *cdp;

/*
**	Process the item code according to what it is, since there
**	are no generized procedures for handling them.
*/
switch ( itemcode )
    {
    case Img_BPCListCnt:
	{
	/*
	** Get the number of elements in the bits per component list.
	*/
	if ( buflen < sizeof(int) )		/* must be a longword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );
	_ImgGet( fct, Img_SgaAggr, &aggr, sizeof(aggr), 0, 0 );
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_SGA_IMG_BITS_PER_COMP;
#else
        aggregate_item = DDIF$_SGA_IMG_BITS_PER_COMP;
#endif

	status = CDA_GET_ARRAY_SIZE_(
	    &aggr,
	    &aggregate_item,
	    &size );
#ifdef NEW_CDA_SYMBOLS
	if ( status != CDA_EMPTY )
#else
	if ( status != CDA$_EMPTY )
#endif
             LOWBIT_TEST_( status );
	/*
	** Return the element count in the user buffer.
	*/
	*((int *)bufptr) = (int)size;
	if ( retlen != NULL )
	    *retlen = sizeof(int);
	break;
	} /* end case Img_BPCListCnt */

    case Img_Cdp:
	{
        /*
        ** Construct a CDP for the user .....
        */
        if (buflen < sizeof(struct UDP))
            ChfStop( 1,  ImgX_INVBUFLEN );

/*	ImgSaveCtx( fct );
*/
	_ImgSetDataPlane( fct, index );
        cdp = (struct UDP*) bufptr;    /* copy the desc buffer pointer */
        Build_udp( fct, Img_Cdp, cdp, index);
	_ImgGet( fct, Img_Dtype, &data_type, sizeof(data_type), 0, index );
	_IpsSetUdpClassAndDType( cdp, data_type );
/*	ImgRestoreCtx( fct );
*/
        if ( retlen != 0)
            *retlen = sizeof(struct UDP);
        break;
	} /* end case Img_Cdp */

    case Img_CdpPrsnt:
    case Img_UdpPrsnt:
	{
	/*
	** Determine whether an uncompressed data plane (UDP) 
	** or a compressed data plane (CDP) is present.
	*/
	char	present_status  = FALSE;
	long	comp_type;
	if ( buflen < 1 )		/* must be a byte at least  */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );

/*	ImgSaveCtx( fct );
*/
	_ImgSetDataPlane( fct, index );
	_ImgGet( fct, Img_CompressionType, &comp_type, sizeof(comp_type), 0, 0 );
	_ImgGet( fct, Img_RootAggr, &root_aggr, sizeof(root_aggr), 0, 0 );
	_ImgGet( fct, Img_IduAggr, &aggr, sizeof(aggr), 0, 0 );
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_IDU_PLANE_DATA;
#else
        aggregate_item = DDIF$_IDU_PLANE_DATA;
#endif
	status = CDA_LOCATE_ITEM_(
	    &root_aggr,
	    &aggr,
	    &aggregate_item,
	    &itemadr,
	    &itemlen,
	    0,0 );
	switch ( status )
            {
#ifdef NEW_CDA_SYMBOLS
            case CDA_NORMAL:
#else
            case CDA$_NORMAL:
#endif
                switch ( (int)comp_type )
                    {
                    /*
                    ** Check for PCM as uncompressed.
                    */
#ifdef NEW_CDA_SYMBOLS
		    case DDIF_K_PCM_COMPRESSION:
#else
		    case DDIF$K_PCM_COMPRESSION:
#endif
                        if ( itemcode == Img_UdpPrsnt )
                            present_status = TRUE;
                        break;
                    /*
		    ** All other compression types are compressed.
		    */
		    default:
                        if ( itemcode == Img_CdpPrsnt )
                            present_status = TRUE;
         	    }
#ifdef NEW_CDA_SYMBOLS
            case CDA_EMPTY:
#else
            case CDA$_EMPTY:
#endif
                break;	    	/* FALSE already set	*/
	    default:
	        ChfStop( 1,  status );
	    } /* end switch */

/*	ImgRestoreCtx( fct );
*/
	/*
	** Return status, TRUE or FALSE, of whether the requested item
	** was there.
	*/
	_IpsMovc5Long(
    		sizeof(char),			/* srclen */
		(unsigned char *)&present_status,		/* srcadr */
		0,				/* fill   */
		buflen,                         /* dstlen */
		(unsigned char *)bufptr );			/* dstadr */
	if ( retlen != NULL )
	    *retlen = sizeof(char);
	break;
	} /* end case Img_CdpPrsnt, Img_UdpPrsnt */

    case Img_DataPlaneBase:
	{
        /*
        ** Return the ADDRESS of the plane_data.  Locate the data buffer
        ** address in the DDIF frame structure and then copy it into the
        ** return buffer.
        */
/*	ImgSaveCtx( fct );
*/
	_ImgSetDataPlane( fct, index );
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_IDU_PLANE_DATA;
#else
        aggregate_item = DDIF$_IDU_PLANE_DATA;
#endif
        status = CDA_LOCATE_ITEM_(
            &(fct->FctL_RootAggr),
            &(fct->FctL_IduAggr),
            &aggregate_item,
            &itemadr,
            &itemlen,
	    0,0 );
        switch ( status )
            {
#ifdef NEW_CDA_SYMBOLS
            case CDA_NORMAL:
#else
            case CDA$_NORMAL:
#endif
                memcpy(bufptr,&itemadr,sizeof(char *));
		if ( retlen != NULL )
                    *retlen = sizeof(char *);
                break;
#ifdef NEW_CDA_SYMBOLS
            case CDA_EMPTY:
#else
            case CDA$_EMPTY:
#endif
		*((int *)bufptr) = (int)0;
                if (retlen != NULL)
		    *retlen = 0;
                break;
            default:
                ChfStop( 1,  status );
                break;
            }   /* end switch (status) */

/*	ImgRestoreCtx( fct );
*/
        break;
	} /* end case Img_DataPlaneBase */

    case Img_DataPlaneBitSize:
	{
	long	bit_size    = 0;

	if ( buflen < sizeof(int) )		/* must be a longword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );

	_ImgGet( fct, Img_DataPlaneSize, &bit_size, LONGSIZE, 0, index );
	bit_size *= 8;

	*(int *)bufptr = (int)bit_size;
	if ( retlen != NULL )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_DataPlaneBitSize */

    case Img_DataPlaneSize:
	{
	if ( buflen < sizeof(int) )		/* must be a longword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );

/*	ImgSaveCtx( fct );
*/
	_ImgSetDataPlane( fct, index );
	_ImgGet( fct, Img_RootAggr, &root_aggr, sizeof(root_aggr), 0, 0 );
	_ImgGet( fct, Img_IduAggr, &aggr, sizeof(aggr), 0, 0 );
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_IDU_PLANE_DATA;
#else
        aggregate_item = DDIF$_IDU_PLANE_DATA;  
#endif
	status = CDA_LOCATE_ITEM_(
	    &root_aggr,
	    &aggr,
	    &aggregate_item,
	    &itemadr,
	    &itemlen,
	    0,0 );
	switch ( status )
	    {
#ifdef NEW_CDA_SYMBOLS
	    case CDA_NORMAL:
#else
	    case CDA$_NORMAL:
#endif
                *(int *)bufptr = (int)itemlen;
                if ( retlen != NULL )
                    *retlen = sizeof(int);
#ifdef NEW_CDA_SYMBOLS
	    case CDA_EMPTY:
#else
	    case CDA$_EMPTY:
#endif
                break;
	    default:
                ChfStop( 1,  status );
	    }

/*	ImgRestoreCtx( fct );
*/
	break;
	} /* end of case Img_DataPlaneSize */


    case Img_Dtype:
	{
	long	     compression_type;
	long	     udp_alignment;
	long	    *dtype = (long *)bufptr;
	struct UDP  udp;

	Build_udp( fct, Img_Udp, &udp, index );
	_ImgGet( fct, Img_CompressionType, &compression_type,LONGSIZE, 0,index);

	if ( compression_type != ImgK_PcmCompression )
	    /*
	    ** Data is compressed, therefore type is automatically bitstream.
	    */
	    *dtype = ImgK_DTypeBitstream;
	else
	    /*
	    ** Data is uncompressed, therefore class and type depend
	    ** upon data alignment and field length.
	    **
	    **	    NOTE: For this version, all data types are integer.
	    */
	    {
	    long    bitcnt;

	    udp_alignment = _IpsGetUdpInfo( &udp );
	    switch ( udp_alignment )
		{
		case BIT_ALIGNED_BITS:
		    if ( udp.UdpW_PixelLength == 1 )
			*dtype = ImgK_DTypeIntBit;
		    else
			*dtype = ImgK_DTypeIntBitsU;
		    break;

		case BYTE_ALIGNED_BYTE:
		case WORD_ALIGNED_BYTE:
		case LONG_ALIGNED_BYTE:
		    *dtype = ImgK_DTypeIntByteU;
		    break;

		case BYTE_ALIGNED_WORD:
		case WORD_ALIGNED_WORD:
		case LONG_ALIGNED_WORD:
		    *dtype = ImgK_DTypeIntWordU;
		    break;

		case BYTE_ALIGNED_LONG:
		case WORD_ALIGNED_LONG:
		case LONG_ALIGNED_LONG:
		    *dtype = ImgK_DTypeIntLongwordU;
		    break;

		case BIT_ALIGNED_BYTE:
		case BIT_ALIGNED_WORD:
		case BIT_ALIGNED_TRIPLE:
		case BIT_ALIGNED_LONG:
		case BYTE_ALIGNED_BITS:
		case BYTE_ALIGNED_TRIPLE:
		case WORD_ALIGNED_BITS:
		case WORD_ALIGNED_TRIPLE:
		case LONG_ALIGNED_BITS:
		case LONG_ALIGNED_TRIPLE:
		default:
		    *dtype = ImgK_DTypeIntBitsU;
		    break;
		} /* end switch */
	    } /* end else */

        if (*retlen != 0)
            *retlen = LONGSIZE;

	break;
	} /* end of case Img_Dtype */
    case Img_IduCnt:
	{
	/*
	** Get the number of data units in the current image content
	** element (i.e., attached to the current DDIF$_IMG aggregate).	*/
	CDAagghandle idu_aggr	= 0;
	CDAagghandle img_aggr	= 0;
	if ( buflen < sizeof(long) )		/* must be a longword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );

/*	ImgSaveCtx( fct );
*/
	_ImgSetContentElement( fct, index );
	_ImgGet( fct, Img_RootAggr, &root_aggr, sizeof(root_aggr), 0, 0 );
	_ImgGet( fct, Img_ImgAggr, &img_aggr, sizeof(img_aggr), 0, 0 );
	if ( img_aggr == (long) NULL )
	    ChfStop( 1,  ImgX_NOIMGAGRP );		/* No current img aggr	*/
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_IMG_CONTENT;
#else
        aggregate_item = DDIF$_IMG_CONTENT;
#endif
	/*
	 ** See if there is at least one IDU
	 */
	status = CDA_LOCATE_ITEM_(
	    &root_aggr,
	    &img_aggr,
	    &aggregate_item,
	    &itemadr,
	    &length,
	    0,0 );
	switch ( status )
            {
            /*
            ** If there is at least one idu, count it, and look for more.
            */
#ifdef NEW_CDA_SYMBOLS
	    case CDA_NORMAL:
#else
	    case CDA$_NORMAL:
#endif
                idu_aggr = *(CDAagghandle *)itemadr;
                do
                    {
                    ++count;
                   status = CDA_NEXT_AGGREGATE_( &idu_aggr, &idu_aggr );
#ifdef NEW_CDA_SYMBOLS
                    } while ( status == CDA_NORMAL );
#else
                    } while ( status == CDA$_NORMAL );
#endif
#ifdef NEW_CDA_SYMBOLS
            case CDA_EMPTY:
#else
            case CDA$_EMPTY:
#endif
                break;
            default:
                ChfStop( 1,  status );
                break;
            }
/*	ImgRestoreCtx( fct );
*/
	/*
	** Return the count in the user buffer.
	*/
	*((int *)bufptr) = (int)count;
	if ( retlen != NULL )
	    *retlen = sizeof(int);
	break;
	} /* end case Img_IduCnt */

    case Img_LutCnt:
	{
	/*
	** How many look up tables are there?
	*/
	if ( buflen < sizeof(int) )		/* must be a longword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );
	_ImgGet( fct, Img_SgaAggr, &aggr, sizeof(aggr), 0, 0 );
#ifdef NEW_CDA_SYMBOLS
        aggregate_item = DDIF_SGA_IMG_LOOKUP_TABLES;
#else
        aggregate_item = DDIF$_SGA_IMG_LOOKUP_TABLES;
#endif
	status = CDA_GET_ARRAY_SIZE_(
	    &aggr,
	    &aggregate_item,
	    &size );
#ifdef NEW_CDA_SYMBOLS
	if ( status != CDA_EMPTY )
#else
	if ( status != CDA$_EMPTY )
#endif
            LOWBIT_TEST_( status );
	/*
	** Return the array size in the user buffer.
	*/
	*(int *)bufptr = (int)size;
	if ( retlen != NULL )
	    *retlen = sizeof(int);
	break;
	} /* end case Img_LutCnt */

    case Img_PixelAlignment:
	{
	long	    pixel_alignment;
	struct UDP  udp;

	_ImgGet( fct, Img_Udp, &udp, sizeof( udp ), 0, index );
	pixel_alignment = _IpsGetUdpElementAlignment( &udp );
	switch ( pixel_alignment )
	    {
	    case BYTE_ALIGNED:
		pixel_alignment = ImgK_AlignByte;
		break;
	    case WORD_ALIGNED:
		pixel_alignment = ImgK_AlignWord;
		break;
	    case LONG_ALIGNED:
		pixel_alignment = ImgK_AlignLongword;
		break;
	    case BIT_ALIGNED:
	    default:
		pixel_alignment = ImgK_AlignBit;
		break;
	    } /* end switch on pixel_alignment */

	*((int *)bufptr) = (int)pixel_alignment;
	if (retlen != 0 )
	    *retlen = sizeof( int );

	break;
	} /* end of case Img_PixelAlignment */

    case Img_PxlAspectRatio:
	{
	/*
	** Set up the ratio pointer using the user return buffer address
	** and get the ratio one value at a time.
	*/
	long	*ratio = (long *)bufptr;
	if ( buflen < 8 )		/* must be a quadword   */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );

	_ImgGet( fct, Img_PPPixelDist, ratio++, sizeof(long), 0, 0 );
	_ImgGet( fct, Img_LPPixelDist, ratio, sizeof(long), 0, 0 );
	if ( retlen != NULL )
	    *retlen = 8;
	break;
	} /* end of case Img_PxlAspectRatio */

    case Img_ScanlineAlignment:
	{
	long	    scanline_alignment;
	struct UDP  udp;

	_ImgGet( fct, Img_Udp, &udp, sizeof( udp ), 0, index );
	scanline_alignment = _IpsGetUdpScanlineAlignment( &udp );
	switch ( scanline_alignment )
	    {
	    case BYTE_ALIGNED:
		scanline_alignment = ImgK_AlignByte;
		break;
	    case WORD_ALIGNED:
		scanline_alignment = ImgK_AlignWord;
		break;
	    case LONG_ALIGNED:
		scanline_alignment = ImgK_AlignLongword;
		break;
	    case BIT_ALIGNED:
	    default:
		scanline_alignment = ImgK_AlignBit;
		break;
	    } /* end switch on scanline_alignment */

	*((long*)bufptr) = scanline_alignment;
	if (retlen != 0 )
	    *retlen = sizeof( long );

	break;
	} /* end of case Img_ScanlineAlignment */

    case Img_QuantBitsPerComp:
	{
	long	levels;
	long	quant_bits;

	_ImgGet( fct, Img_QuantLevelsPerComp, &levels, LONGSIZE, 0, index );
	quant_bits = _ImgConvertLevelsToBits( levels );

	*((int *)(bufptr)) = (int)quant_bits;
	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_QuantBitsPerComp */


    /*
    ** Temporary processing of IDU item unsupported by DDIF/CDA
    */
    case Img_QuantLevelsPerComp:
        {
	  Get_quant_levels_per_comp( fct, itemcode, bufptr, buflen, retlen,
				    index );
	  break;
        } /* end case Img_QuantLevelsPerComp */

    case Img_StandardFormat:
	{
	long	std_format_flag;

	std_format_flag = _ImgVerifyStandardFormat( fct, ImgM_NoChf );

	/*
	** Since _ImgVerifyStandardFormat returns a status code, return
	** the low bit to the user to indicate TRUE or FALSE.
	*/
	*((int *)bufptr) = (std_format_flag & 1);

	if ( retlen != 0 )
	    *retlen = sizeof(int);
	break;
	} /* end case Img_StandardFormat */

    case Img_TotalBitsPerPixel:
	{
	long	bits_per_comp;
	long	comp_cnt;
	long	comp_idx;
	long	total_bits_per_pixel	= 0;

	_ImgGet( fct, Img_NumberOfComp, &comp_cnt, LONGSIZE, 0, 0 );
	for ( comp_idx = 0; comp_idx < comp_cnt; ++comp_idx )
	    {
	    _ImgGet( fct, Img_BitsPerComp, &bits_per_comp, LONGSIZE,0,comp_idx);
	    total_bits_per_pixel += bits_per_comp;
	    }

	*((int *)bufptr) = (int)total_bits_per_pixel;

	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_TotalBitsPerPixel */


    case Img_TotalQuantBitsPerPixel:
	{
	long	comp_cnt;
	long	comp_idx;
	long	quant_bits_per_comp;
	long	total_quant_bits_per_pixel	= 0;

	_ImgGet( fct, Img_NumberOfComp, &comp_cnt, LONGSIZE, 0, 0 );
	for ( comp_idx = 0; comp_idx < comp_cnt; ++comp_idx )
	    {
	    _ImgGet( fct, Img_QuantBitsPerComp, &quant_bits_per_comp, 
			LONGSIZE, 0, comp_idx );
	    total_quant_bits_per_pixel += quant_bits_per_comp;
	    }

	*((int *)bufptr) = (int)total_quant_bits_per_pixel;

	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_TotalQuantBitsPerPixel */

    case Img_Udp:
	{
        /*
        ** Construct a UDP for the user .....
        */
        if (buflen < sizeof(struct UDP))
            ChfStop( 1,  ImgX_INVBUFLEN );

	_ImgGet( fct, Img_CompressionType, &compression, sizeof(compression), 0, index );
	_ImgSetDataPlane( fct, index );
/*	ImgSaveCtx( fct );
*/
        udp = (struct UDP*) bufptr;    /* copy the desc buffer pointer */

	if ( compression == ImgK_PcmCompression )
	    Build_udp( fct, Img_Udp, udp, index );
	else
	    Build_udp( fct, Img_Cdp, udp, index );

	_ImgGet( fct, Img_Dtype, &data_type, sizeof(data_type), 0, index );
	_IpsSetUdpClassAndDType( udp, data_type );

/*	ImgRestoreCtx( fct );
*/
        if ( retlen != 0)
            *retlen = sizeof(struct UDP);
        break;
	} /* end case Img_Udp */


    case Img_UserLabelCnt:
	{
	CDAconstant             ddif_code;
	long            status;
	long            user_label_string_cnt;
	struct ITEMCODE itemcode;

	_ImgLoadSelector(Img_UserLabel,&itemcode);
        ddif_code = _ImgAL_DDIFAccessTable[ itemcode.ItmW_Offset ];

	status = CDA_GET_ARRAY_SIZE_( 
		    &(fct->FctL_SegAggr),
		    &ddif_code,
		    &user_label_string_cnt
		    );
	switch ( status )
	    {
#ifdef NEW_CDA_SYMBOLS
	    case CDA_NORMAL:
#else
	    case CDA$_NORMAL:
#endif
		break;
#ifdef NEW_CDA_SYMBOLS
	    case CDA_EMPTY:
#else
	    case CDA$_EMPTY:
#endif
		user_label_string_cnt = 0;
		break;
	    default:
		ChfSignal( 1, status );
	    } /* end switch */

	*((int *)bufptr) = (int)user_label_string_cnt;

	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_UserLabelCnt */


    case Img_UserLabelLen:
	{
	CDAconstant		ddif_code;
	CDAaddress		ddif_item_addr;
	long		ddif_item_size;
	int		index_ddif = (int)index;
	long		status;
	CDAconstant		user_label_string_type;
	struct ITEMCODE	itemcode;

	_ImgLoadSelector(Img_UserLabel, &itemcode);

        ddif_code = _ImgAL_DDIFAccessTable[ itemcode.ItmW_Offset ];
        status = CDA_LOCATE_ITEM_(
                &(fct->FctL_RootAggr),
                &(fct->FctL_SegAggr),
                &ddif_code,
                &ddif_item_addr,
                &ddif_item_size,
                &index_ddif,
                &user_label_string_type );
	switch ( status )
	    {
#ifdef NEW_CDA_SYMBOLS
	    case CDA_NORMAL:
#else
	    case CDA$_NORMAL:
#endif
		break;
#ifdef NEW_CDA_SYMBOLS
	    case CDA_EMPTY:
	    case CDA_INDEX:
#else
	    case CDA$_EMPTY:
	    case CDA$_INDEX:
#endif
		ddif_item_size = 0;
		break;
	    default:
		ChfSignal( 1, status );
	    } /* end switch */

	*((int *)bufptr) = (int)ddif_item_size;
	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_UserLabelLen */


    case Img_VirtualArsize:
	{
	long	pos;
	long	pixel_count;
	long	pixel_stride;
	long	scanline_count;
	long	scanline_stride;
	long	virtual_arsize;

	_ImgGet( fct, Img_DataOffset, &pos, LONGSIZE, 0, index );
	_ImgGet( fct, Img_PixelsPerLine, &pixel_count, LONGSIZE, 0, index );
	_ImgGet( fct, Img_PixelStride, &pixel_stride, LONGSIZE, 0, index );
	_ImgGet( fct, Img_NumberOfLines, &scanline_count, LONGSIZE, 0, index );
	_ImgGet( fct, Img_ScanlineStride, &scanline_stride, LONGSIZE, 0,index );

/*
**  NOTE that this is the *right* way to calculate it, but everyone else
**  only figures it as the scanline_stride * total_line_count ...
**
**	virtual_arsize = pos + (scanline_stride * (scanline_count-1)) +
**			    (pixel_stride * pixel_count);
*/
	virtual_arsize = pos + (scanline_stride * scanline_count);

	*((int *)bufptr) = (int)virtual_arsize;
	if ( retlen != 0 )
	    *retlen = sizeof(int);

	break;
	} /* end case Img_VirtualArsize */

    default:
        ChfSignal( 3,  ImgX_NOSPCPRC, 1, itemcode );
    } /* end of switch */

return fct;
} /* end of Get_special_item */


/******************************************************************************
**  Put_quant_levels_per_comp()
**
**  FUNCTIONAL DESCRIPTION:
**
**	[@tbs@]
**
**  FORMAL PARAMETERS:
**
**	[@description_or_none@]
**
**  IMPLICIT INPUTS:
**
**	none
**
**  IMPLICIT OUTPUTS:
**
**	none
**
**  FUNCTION VALUE:
**
**	void (none)
**
**  SIGNAL CODES:
**
**	[@description_or_none@]
**
**  SIDE EFFECTS:
**
**	none
**
******************************************************************************/
static void Put_quant_levels_per_comp( fct, itemcode, bufptr, buflen, index )
struct FCT	*fct;
long             itemcode;
char		*bufptr;
long		 buflen;
long		 index;
{
CDAconstant ddif_code;
int	index_ddif	= (int)index;
long	newsize;
int	status;
struct ITEMCODE	 selector;

_ImgLoadSelector(itemcode,&selector);

if ( fct->FctL_Flags.FctV_PvtQLevels )
    /*
    ** Put quant levels to private FCT structure ...
    */
    {
    if ( index_ddif <= *(fct->FctA_PvtQLevels) - 1 )
	/*
	** If the index falls within the size of the existing
	** quant levels list, store it immediately.
	*/
	(fct->FctA_PvtQLevels)[index_ddif+1] = *((long *)bufptr);
    else
	/*
	** Since the index is beyond the current list size,
	** add one more element to the list, and store the
	** put value as the last item in the list.
	*/
	{
	newsize = (*(fct->FctA_PvtQLevels) + 2) * LONGSIZE;
	fct->FctA_PvtQLevels = (long*)_ImgRealloc( (char *) fct->FctA_PvtQLevels,
						    newsize );
	*(fct->FctA_PvtQLevels) = *(fct->FctA_PvtQLevels) + 1;
	(fct->FctA_PvtQLevels)[*(fct->FctA_PvtQLevels)] = *((long *)bufptr);
	}
    }
else
    /*
    ** Put quant levels to CDA structure
    */
    {
    ddif_code = _ImgAL_DDIFAccessTable[selector.ItmW_Offset];
    status = CDA_STORE_ITEM_(
		&(fct->FctL_RootAggr),
		&(fct->FctL_SgaAggr),
		&ddif_code,
		&buflen,
		bufptr,
		&index_ddif,
		0 );
    TEST_AND_SIGNAL_(status);
    }

return;
} /* end of Put_quant_levels_per_comp */


/************************************************************************
**  Put_special_item() - Handle special case item code
**
**  FUNCTIONAL DESCRIPTION:
**
**      Put image frame attributes which require special processing (i.e. can
**	not be directly inserted into the structures using _ImgPut).
**
**
**  FORMAL PARAMETERS:
**
**      fct		Address of FCT block belonging to frame to which
**			attributes must be inserted.
**	itemcode	Item code of data to put.
**	bufptr		Address of data to put.
**	buflen		Length in bytes of data to put.
**	index		Index of array-structured item to put.
**
**  IMPLICIT INPUTS:
**
**      none
**
**  IMPLICIT OUTPUTS:
**
**      none
**
**  FUNCTION VALUE:
**
**      fct		Pointer to FCT originally specified as input
**
**  SIGNAL CODES:
**
**	ImgX_NOSPCPRC	No special processing available for item code
**
**  SIDE EFFECTS:
**
**      none
**
************************************************************************/
static struct FCT *Put_special_item( fct, itemcode, bufptr, buflen, index )
struct FCT  *fct;
long	     itemcode;
char	    *bufptr;
long	     buflen;
long	     index;
{
long	     aggregate_item;
long	     bits_per_pixel;
long	     comp_cnt;
long	     cs_org;
long	     item_size;
long	     number_of_lines;
long	     pixel_length;
long	     pixels_per_line;
long	     plane_data_size;
long	     status;

struct UDP  *cdp;
struct UDP  *udp;

/*
** Switch on each item code to perform the processing that is
** special to each item code.
*/
switch ( itemcode )
    {
    case Img_PxlAspectRatio:
	/*
        ** Put the pixel aspect ratio into the frame structure
        ** as two separate item codes:  the first as the pixel
        ** progression pixel distance, and the second as the 
        ** line progression pixel distance.
        */
        {
        long	*ratio  = (long *) bufptr;

        if ( buflen != 8 )/* must be a quadword */
	    ChfStop( 3,  ImgX_INVITMBFL, 1, itemcode );
        _ImgPut( fct, Img_PPPixelDist, ratio++, sizeof(long), 0 );
        _ImgPut( fct, Img_LPPixelDist, ratio, sizeof(long), 0 );
        break;
        } /* end of case Img_PxlAspectRatio */

    case Img_Udp:
    case Img_Cdp:
	/*
	** Store a UDP for the user .....
	*/
	{
	if (buflen < sizeof(struct UDP))
	    ChfStop( 1,  ImgX_INVBUFLEN );
	udp = (struct UDP *) bufptr;

	_ImgPut( fct, Img_NumberOfLines, &(udp->UdpL_ScnCnt), sizeof((udp->UdpL_ScnCnt)), index );
	_ImgPut( fct, Img_PixelsPerLine, &(udp->UdpL_PxlPerScn), sizeof((udp->UdpL_PxlPerScn)), index );
	_ImgPut( fct, Img_PixelStride, &(udp->UdpL_PxlStride), sizeof((udp->UdpL_PxlStride)), index );
	_ImgPut( fct, Img_ScanlineStride, &(udp->UdpL_ScnStride), sizeof((udp->UdpL_ScnStride)), index);
	_ImgPut( fct, Img_DataOffset, &(udp->UdpL_Pos), sizeof((udp->UdpL_Pos)), index );
	pixel_length = udp->UdpW_PixelLength;
	_ImgPut( fct, Img_PlaneBitsPerPixel, &pixel_length, sizeof(pixel_length), index );

	/*
	** If the image comp space org is band interleaved by plane,
	** store the quant levels, since the UDP index corresponds to
	** the component index.  If there is only one component in the
	** image, it's also OK to store the quant levels.
	*/
	_ImgGet( fct, Img_CompSpaceOrg, &cs_org, sizeof(cs_org), 0, 0 );
	_ImgGet( fct, Img_NumberOfComp, &comp_cnt, sizeof(comp_cnt), 0, 0 );
	if ( cs_org == ImgK_BandIntrlvdByPlane || comp_cnt == 1 )
	    _ImgPut( fct, Img_QuantLevelsPerComp, &(udp->UdpL_Levels), sizeof((udp->UdpL_Levels)), 
			index );

	/*
	/* Put data plane if it's there.
	*/
	if (udp->UdpA_Base != 0)
	    {
/*	    ImgSaveCtx( fct );
*/
	    _ImgSetDataPlane( fct, index );
	    _ImgAttachDataPlane( fct, (char *) udp->UdpA_Base, index );
/*	    ImgRestoreCtx( fct );
*/
	    }
    
        break;
	} /* end case Img_Udp */

    default:
	ChfStop( 3,  ImgX_NOSPCPRC, 1, itemcode );
    }
return fct;
} /* end of Put_special_item */

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
** Generated by ODL Version X0.1 on Tue Jul 14 18:32:18 1992
*/

/*
** COPYRIGHT (c) 1989 BY
** DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
** ALL RIGHTS RESERVED.
**
** THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND COPIED
** ONLY  IN  ACCORDANCE  OF  THE  TERMS  OF  SUCH  LICENSE  AND WITH THE
** INCLUSION OF THE ABOVE COPYRIGHT NOTICE. THIS SOFTWARE OR  ANY  OTHER
** COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
** OTHER PERSON.  NO TITLE TO AND  OWNERSHIP OF THE  SOFTWARE IS  HEREBY
** TRANSFERRED.
**
** THE INFORMATION IN THIS SOFTWARE IS  SUBJECT TO CHANGE WITHOUT NOTICE
** AND  SHOULD  NOT  BE  CONSTRUED  AS A COMMITMENT BY DIGITAL EQUIPMENT
** CORPORATION.
**
** DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE  OR  RELIABILITY OF ITS
** SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
*/

/*
** Private Type Definitions for the List Object
*/

/*
** Abstract Type Definitions for subtypes of Object
*/

typedef _Object _Set, _PtrTo _SetPtr;
typedef _Object _Property, _PtrTo _PropertyPtr;
typedef _Object _ObjectId, _PtrTo _ObjectIdPtr;
typedef _Object _ObjectDesc, _PtrTo _ObjectDescPtr;
typedef _Object _Ui, _PtrTo _UiPtr;
typedef _Object _DXmUi, _PtrTo _DXmUiPtr;
typedef _Object _DXmEnvState, _PtrTo _DXmEnvStatePtr;
typedef _Object _Persistent, _PtrTo _PersistentPtr;
typedef _Object _Surrogate, _PtrTo _SurrogatePtr;
typedef _Object _Link, _PtrTo _LinkPtr;
typedef _Object _Linknet, _PtrTo _LinknetPtr;
typedef _Object _CompLinknet, _PtrTo _CompLinknetPtr;
typedef _Object _Step, _PtrTo _StepPtr;
typedef _Object _Path, _PtrTo _PathPtr;
typedef _Object _CompPath, _PtrTo _CompPathPtr;
typedef _Object _Linkbase, _PtrTo _LinkbasePtr;

/*
** List Instance Structure Definition
*/

typedef struct __List {
        _Type type;
        _Domain domain;
        _Integer count;
        _Integer alloc;
        _AnyValuePtr elements;
    } _ListInstance, _PtrTo _List, _PtrTo _PtrTo _ListPtr;

/*
** List Property Name Table Index Definitions
*/

#define _DomainIndex 0
#define _ElementCountIndex 1
#define _P_ElementAlloc "$ElementAlloc"
#define _ElementAllocIndex 2
#define _P_Elements "$Elements"
#define _ElementsIndex 3

/*
** List Property Name Table Definition
*/

#define _ListPropertyNameTable \
    _PropertyNameTableEntry _Constant ListPropertyNameTable[] = { \
        {_P_Domain, _DomainIndex, _True}, \
        {_P_ElementCount, _ElementCountIndex, _True}, \
        {_P_ElementAlloc, _ElementAllocIndex, _False}, \
        {_P_Elements, _ElementsIndex, _False}, \
        {(_String) 0, 0, _False} \
    }

/*
** List Property Accessor Definitions
*/

#define _Domain_of(Obj) ((_List) _Reference(Obj))->domain
#define _ElementCount_of(Obj) ((_List) _Reference(Obj))->count
#define _ElementAlloc_of(Obj) ((_List) _Reference(Obj))->alloc
#define _Elements_of(Obj) ((_List) _Reference(Obj))->elements

/*
** Include Generic Operation Support
*/

#include "lwk_operation_prototypes.h"

/*
** List Method Declarations
*/

_DeclareFunction(void LwkOpListAddElement, (_inout _List list,
    _in _Domain domain, _in _AnyPtr element, _in _Boolean copy));
_DeclareFunction(void LwkOpListAppendElements, (_in _List list,
    _in _List append));
_DeclareFunction(void LwkOpObjIllOp, (_in _Object object));
_DeclareFunction(_List LwkOpObjCopy, (_in _List object, _in _Boolean aggreate));
_DeclareFunction(_List LwkOpObjCreate, (_in _Type type));
_DeclareFunction(_List LwkOpListCreate, (_in _Type type,
    _in _Domain domain, _in _Integer estimated_count));
_DeclareFunction(void LwkOpListDeleteElement, (_inout _List list,
    _in _Domain domain, _in _AnyPtr element));
_DeclareFunction(_Set LwkOpListEnumProps, (_in _List object));
_DeclareFunction(void LwkOpObjExpunge, (_inout _List object));
_DeclareFunction(void LwkOpListFree, (_inout _List object));
_DeclareFunction(_Domain LwkOpObjGetDomain, (_in _List object));
_DeclareFunction(void LwkOpListGetValue, (_in _List object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value));
_DeclareFunction(_Domain LwkOpListGetValueDomain, (_in _List object,
    _in _String property_name));
_DeclareFunction(_List LwkOpListGetValueList, (_in _List object,
    _in _String property_name));
_DeclareFunction(void LwkOpListInitialize, (_inout _List object,
    _in _List proto_object, _Boolean aggregate));
_DeclareFunction(_Boolean LwkOpListIsMultiValued, (_in _List object,
    _in _String property_name));
_DeclareFunction(_Boolean LwkOpObjIsType, (_in _List object,
    _in _Type type));
_DeclareFunction(_Termination LwkOpListIterate, (_in _List list,
    _in _Domain domain, _in _Closure closure,
    _in _Callback routine));
_DeclareFunction(void LwkOpListRemoveElement, (_inout _List list,
    _in _Domain domain, _in _AnyPtr element));
_DeclareFunction(void LwkOpListSelectElement, (_in _List list,
    _in _Integer index, _in _Domain domain, _out _AnyPtr element));
_DeclareFunction(void LwkOpListSetValue, (_inout _List object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value, _in _SetFlag flag));
_DeclareFunction(void LwkOpListSetValueList, (_inout _List object,
    _in _String property_name, _in _List_of(_Domain) value_list,
    _in _SetFlag flag));

/*
** List Type Instance Definition
*/

#define _ListTypeInstance \
    _TypeInstance _Constant LWK__ListTypeInstance = { \
        &LWK__ObjectTypeInstance, \
        sizeof(_ListInstance), \
        { \
        (_Method) LwkOpListAddElement, \
        (_Method) LwkOpListAppendElements, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjCopy, \
        (_Method) LwkOpObjCreate, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListCreate, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListDeleteElement, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListEnumProps, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjExpunge, \
        (_Method) LwkOpListFree, \
        (_Method) LwkOpObjGetDomain, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListGetValue, \
        (_Method) LwkOpListGetValueDomain, \
        (_Method) LwkOpListGetValueList, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListInitialize, \
        (_Method) LwkOpListIsMultiValued, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIsType, \
        (_Method) LwkOpListIterate, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListRemoveElement, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListSelectElement, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpListSetValue, \
        (_Method) LwkOpListSetValueList, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp \
        } \
    }

#define _ListType \
    _Type _Constant LWK__ListType = &LWK__ListTypeInstance

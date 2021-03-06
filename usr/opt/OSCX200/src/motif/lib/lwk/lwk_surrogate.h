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
** Generated by ODL Version X0.1 on Tue Jul 14 18:32:25 1992
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
** Private Type Definitions for the Surrogate Object
*/

/*
** Abstract Type Definitions for subtypes of Object
*/

typedef _Object _List, _PtrTo _ListPtr;
typedef _Object _Set, _PtrTo _SetPtr;
typedef _Object _Property, _PtrTo _PropertyPtr;
typedef _Object _ObjectId, _PtrTo _ObjectIdPtr;
typedef _Object _ObjectDesc, _PtrTo _ObjectDescPtr;
typedef _Object _Ui, _PtrTo _UiPtr;
typedef _Object _DXmUi, _PtrTo _DXmUiPtr;
typedef _Object _DXmEnvState, _PtrTo _DXmEnvStatePtr;
typedef _Object _Persistent, _PtrTo _PersistentPtr;
typedef _Object _Link, _PtrTo _LinkPtr;
typedef _Object _Linknet, _PtrTo _LinknetPtr;
typedef _Object _CompLinknet, _PtrTo _CompLinknetPtr;
typedef _Object _Step, _PtrTo _StepPtr;
typedef _Object _Path, _PtrTo _PathPtr;
typedef _Object _CompPath, _PtrTo _CompPathPtr;
typedef _Object _Linkbase, _PtrTo _LinkbasePtr;

/*
** Surrogate Instance Structure Definition
*/

typedef struct __Surrogate {
        _Type type;
        _Linkbase linkbase;
        _Integer identifier;
        _DDIFString description;
        _DDIFString author;
        _Date creation_date;
        _Set_of(_DDIFString) keywords;
        _Set_of(_Property) properties;
        _StateFlags flags;
        _Persistent container;
        _Set_of(_Persistent) inter_links;
        _String surrogate_subtype;
    } _SurrogateInstance, _PtrTo _Surrogate, _PtrTo _PtrTo _SurrogatePtr;

/*
** Surrogate Property Name Table Index Definitions
*/

#define _ContainerIndex 0
#define _InterLinksIndex 1
#define _SurrogateSubTypeIndex 2

/*
** Surrogate Property Name Table Definition
*/

#define _SurrogatePropertyNameTable \
    _PropertyNameTableEntry _Constant SurrogatePropertyNameTable[] = { \
        {_P_Container, _ContainerIndex, _True}, \
        {_P_InterLinks, _InterLinksIndex, _True}, \
        {_P_SurrogateSubType, _SurrogateSubTypeIndex, _True}, \
        {(_String) 0, 0, _False} \
    }

/*
** Surrogate Property Accessor Definitions
*/

#define _Container_of(Obj) ((_Surrogate) _Reference(Obj))->container
#define _InterLinks_of(Obj) ((_Surrogate) _Reference(Obj))->inter_links
#define _SurrogateSubType_of(Obj) ((_Surrogate) _Reference(Obj))->surrogate_subtype

/*
** Include Generic Operation Support
*/

#include "lwk_operation_prototypes.h"

/*
** Surrogate Method Declarations
*/

_DeclareFunction(void LwkOpObjIllOp, (_in _Object object));
_DeclareFunction(_Surrogate LwkOpObjCopy, (_in _Surrogate object, _in _Boolean aggreate));
_DeclareFunction(_Surrogate LwkOpObjCreate, (_in _Type type));
_DeclareFunction(void LwkOpSurrDecode, (_inout _Surrogate persistent,
    _in _DDIShandle handle, _in _Boolean keys_only,
    _inout _SetPtr properties));
_DeclareFunction(void LwkOpSurrEncode, (_in _Surrogate persistent,
    _in _Boolean aggregate, _in _DDIShandle handle));
_DeclareFunction(_Set LwkOpSurrEnumProps, (_in _Surrogate object));
_DeclareFunction(_Integer LwkOpPersistExport, (_in _Surrogate persistent,
    _in _Boolean aggregate, _out _VaryingStringPtr encoding));
_DeclareFunction(void LwkOpSurrExpunge, (_inout _Surrogate object));
_DeclareFunction(void LwkOpSurrFree, (_inout _Surrogate object));
_DeclareFunction(_Domain LwkOpObjGetDomain, (_in _Surrogate object));
_DeclareFunction(_ObjectDesc LwkOpPersistGetObjectDesc, (
    _in _Surrogate persistent));
_DeclareFunction(_ObjectId LwkOpSurrGetObjectId, (
    _in _Surrogate persistent));
_DeclareFunction(void LwkOpSurrGetValue, (_in _Surrogate object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value));
_DeclareFunction(_Domain LwkOpSurrGetValueDomain, (_in _Surrogate object,
    _in _String property_name));
_DeclareFunction(_List LwkOpSurrGetValueList, (_in _Surrogate object,
    _in _String property_name));
_DeclareFunction(_Surrogate LwkOpPersistImport, (_in _Type type,
    _in _VaryingString encoding));
_DeclareFunction(void LwkOpPersistImportKeyProperties, (
    _in _Type type, _in _VaryingString encoding,
    _inout _SetPtr properties));
_DeclareFunction(void LwkOpSurrInitialize, (_inout _Surrogate object,
    _in _Surrogate proto_object, _Boolean aggregate));
_DeclareFunction(_Boolean LwkOpSurrIsMultiValued, (_in _Surrogate object,
    _in _String property_name));
_DeclareFunction(_Boolean LwkOpObjIsType, (_in _Surrogate object,
    _in _Type type));
_DeclareFunction(_Boolean LwkOpSurrSelected, (_in _Surrogate surrogate,
    _in _QueryExpression expression));
_DeclareFunction(_Boolean LwkOpPersistSetState, (_inout _Surrogate persistent,
    _in _PersistentState state, _in _StateOperation operation));
_DeclareFunction(void LwkOpSurrSetValue, (_inout _Surrogate object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value, _in _SetFlag flag));
_DeclareFunction(void LwkOpSurrSetValueList, (_inout _Surrogate object,
    _in _String property_name, _in _List_of(_Domain) value_list,
    _in _SetFlag flag));

/*
** Surrogate Type Instance Definition
*/

#define _SurrogateTypeInstance \
    _TypeInstance _Constant LWK__SurrogateTypeInstance = { \
        &LWK__PersistentTypeInstance, \
        sizeof(_SurrogateInstance), \
        { \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjCopy, \
        (_Method) LwkOpObjCreate, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpSurrDecode, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpSurrEncode, \
        (_Method) LwkOpSurrEnumProps, \
        (_Method) LwkOpPersistExport, \
        (_Method) LwkOpSurrExpunge, \
        (_Method) LwkOpSurrFree, \
        (_Method) LwkOpObjGetDomain, \
        (_Method) LwkOpPersistGetObjectDesc, \
        (_Method) LwkOpSurrGetObjectId, \
        (_Method) LwkOpSurrGetValue, \
        (_Method) LwkOpSurrGetValueDomain, \
        (_Method) LwkOpSurrGetValueList, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpPersistImport, \
        (_Method) LwkOpPersistImportKeyProperties, \
        (_Method) LwkOpSurrInitialize, \
        (_Method) LwkOpSurrIsMultiValued, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIsType, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpSurrSelected, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpPersistSetState, \
        (_Method) LwkOpSurrSetValue, \
        (_Method) LwkOpSurrSetValueList, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp, \
        (_Method) LwkOpObjIllOp \
        } \
    }

#define _SurrogateType \
    _Type _Constant LWK__SurrogateType = &LWK__SurrogateTypeInstance

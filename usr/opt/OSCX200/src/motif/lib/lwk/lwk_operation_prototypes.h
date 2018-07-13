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
** Generated by ODL Version X0.1 on Tue Jul 14 18:32:35 1992
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
** Operation Prototype Definitions
*/

#ifdef _Prototypes
typedef void (*_AddElement_P)(_inout _Object list,
    _in _Domain domain, _in _AnyPtr element, _in _Boolean copy);
typedef void (*_AppendElements_P)(_in _Object list,
    _in _Object append);
typedef void (*_Apply_P)(_in _Object ui, _in _String operation,
    _in _Surrogate surrogate);
typedef void (*_Close_P)(_inout _Object linkbase);
typedef void (*_CompleteLink_P)(_inout _Object dxmui,
    _in _Link link, _in _Boolean iff_visible,
    _Closure closure);
typedef void (*_ConfirmApply_P)(
    _in _Object ui, _in _Surrogate surrogate);
typedef void (*_ConfirmLink_P)(
    _in _Object ui, _in _Boolean confirmed,
    _in _Boolean retain_source, _in _Boolean retain_target);
typedef _Object (*_Copy_P)(_in _Object object, _in _Boolean aggreate);
typedef _Object (*_Create_P)(_in _Type type);
typedef _Object (*_CreateDXmUi_P)(_in _Type type,
    _in _CString appl_name, _in _Boolean create_menu,
    _in _Boolean default_accelerators, _in _Widget main_window,
    _in _Widget link_menu);
typedef _Object (*_CreateList_P)(_in _Type type,
    _in _Domain domain, _in _Integer estimated_count);
typedef _Object (*_CreateSet_P)(_in _Type type,
    _in _Domain element_type, _in _Integer estimated_count);
typedef void (*_Decode_P)(_inout _Object prop,
    _in _DDIShandle handle, _in _Boolean keys_only,
    _inout _SetPtr properties);
typedef void (*_DeleteElement_P)(_inout _Object list,
    _in _Domain domain, _in _AnyPtr element);
typedef void (*_DisplayMessage_P)(_in _Object dxmui,
    _in _StatusPtr status, _in _Integer count);
typedef void (*_Drop_P)(_inout _Object linknet);
typedef void (*_Encode_P)(_in _Object prop,
    _in _Boolean aggregate, _in _DDIShandle handle);
typedef _Set (*_EnumerateProperties_P)(_in _Object object);
typedef _Integer (*_Export_P)(_in _Object prop,
    _in _Boolean aggregate, _out _VaryingStringPtr encoding);
typedef void (*_Expunge_P)(_inout _Object object);
typedef void (*_Free_P)(_inout _Object object);
typedef _Domain (*_GetDomain_P)(_in _Object object);
typedef _ObjectDesc (*_GetObjectDesc_P)(
    _in _Object persistent);
typedef _ObjectId (*_GetObjectId_P)(
    _in _Object persistent);
typedef void (*_GetValue_P)(_in _Object object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value);
typedef _Domain (*_GetValueDomain_P)(_in _Object object,
    _in _String property_name);
typedef _List (*_GetValueList_P)(_in _Object object,
    _in _String property_name);
typedef void (*_Highlight_P)(_inout _Object dxmui);
typedef _Object (*_Import_P)(_in _Type type,
    _in _VaryingString encoding);
typedef void (*_ImportKeyProperties_P)(
    _in _Type type, _in _VaryingString encoding,
    _inout _SetPtr properties);
typedef void (*_Initialize_P)(_inout _Object object,
    _in _Object proto_object, _Boolean aggregate);
typedef _Boolean (*_IsMultiValued_P)(_in _Object object,
    _in _String property_name);
typedef _Boolean (*_IsNamed_P)(_in _Object object,
    _in _String property_name);
typedef _Boolean (*_IsType_P)(_in _Object object,
    _in _Type type);
typedef _Termination (*_Iterate_P)(_in _Object list,
    _in _Domain domain, _in _Closure closure,
    _in _Callback routine);
typedef void (*_Navigate_P)(_in _Object ui,
    _in _Link link, _in _Surrogate origin,
    _in _Surrogate destination, _in _String Operation,
    _in _FollowType follow_type);
typedef _Object (*_Open_P)(_in _Type type, _in _String identifier,
    _Boolean create);
typedef _Termination (*_Query_P)(_in _Object linknet,
    _in _Domain domain, _in _QueryExpression expression,
    _in _Closure closure, _in _Callback routine);
typedef void (*_RemoveElement_P)(_inout _Object list,
    _in _Domain domain, _in _AnyPtr element);
typedef _Persistent (*_Retrieve_P)(_in _Object id);
typedef void (*_SelectElement_P)(_in _Object list,
    _in _Integer index, _in _Domain domain, _out _AnyPtr element);
typedef void (*_SelectMenu_P)(_inout _Object ui,
    _in _Menu menu, _in _Closure closure);
typedef _Boolean (*_Selected_P)(_in _Object surrogate,
    _in _QueryExpression expression);
typedef void (*_SendMessage_P)(_in _Object object,
    _in _Integer address, _in _Integer size, _in _AnyPtr message);
typedef _Boolean (*_SetState_P)(_inout _Object persistent,
    _in _PersistentState state, _in _StateOperation operation);
typedef void (*_SetValue_P)(_inout _Object object,
    _in _String property_name, _in _Domain domain,
    _in _AnyPtr value, _in _SetFlag flag);
typedef void (*_SetValueList_P)(_inout _Object object,
    _in _String property_name, _in _List_of(_Domain) value_list,
    _in _SetFlag flag);
typedef void (*_ShowHistory_P)(_inout _Object dxmui,
    _in _List_of(_Step) steps,
    _in _List_of(_List_of(_String)) origin_opr_ids,
    _in _List_of(_List_of(_DDIFString)) origin_opr_names,
    _in _List_of(_List_of(_String)) dest_opr_ids,
    _in _List_of(_List_of(_DDIFString)) dest_opr_names,
    _in _Boolean iff_visible, _Closure closure);
typedef void (*_ShowLinks_P)(_inout _Object dxmui,
    _in _List_of(_Link) links,
    _in _List_of(_List_of(_String)) opr_ids,
    _in _List_of(_List_of(_DDIFString)) opr_names,
    _in _List_of(_Boolean) outgoing, _in _FollowType follow_type,
    _in _Boolean iff_visible, _in _Boolean update, 
    _in _Closure closure);
typedef void (*_Store_P)(_inout _Object linknet,
    _inout _Linkbase linkbase);
typedef _Boolean (*_SurrogateIsHighlighted_P)(
    _in _Object ui, _in _Surrogate surrogate);
typedef _Transaction (*_Transact_P)(_inout _Object object,
    _in _Transaction transaction);
typedef _Boolean (*_Verify_P)(_inout _Object linkbase,
    _in _Integer flags, _in _OSFile file);
#else /* !_Prototypes */
typedef _Method _AddElement_P;
typedef _Method _AppendElements_P;
typedef _Method _Apply_P;
typedef _Method _Close_P;
typedef _Method _CompleteLink_P;
typedef _Method _ConfirmApply_P;
typedef _Method _ConfirmLink_P;
typedef _Method _Copy_P;
typedef _Method _Create_P;
typedef _Method _CreateDXmUi_P;
typedef _Method _CreateList_P;
typedef _Method _CreateSet_P;
typedef _Method _Decode_P;
typedef _Method _DeleteElement_P;
typedef _Method _DisplayMessage_P;
typedef _Method _Drop_P;
typedef _Method _Encode_P;
typedef _Method _EnumerateProperties_P;
typedef _Method _Export_P;
typedef _Method _Expunge_P;
typedef _Method _Free_P;
typedef _Method _GetDomain_P;
typedef _Method _GetObjectDesc_P;
typedef _Method _GetObjectId_P;
typedef _Method _GetValue_P;
typedef _Method _GetValueDomain_P;
typedef _Method _GetValueList_P;
typedef _Method _Highlight_P;
typedef _Method _Import_P;
typedef _Method _ImportKeyProperties_P;
typedef _Method _Initialize_P;
typedef _Method _IsMultiValued_P;
typedef _Method _IsNamed_P;
typedef _Method _IsType_P;
typedef _Method _Iterate_P;
typedef _Method _Navigate_P;
typedef _Method _Open_P;
typedef _Method _Query_P;
typedef _Method _RemoveElement_P;
typedef _Method _Retrieve_P;
typedef _Method _SelectElement_P;
typedef _Method _SelectMenu_P;
typedef _Method _Selected_P;
typedef _Method _SendMessage_P;
typedef _Method _SetState_P;
typedef _Method _SetValue_P;
typedef _Method _SetValueList_P;
typedef _Method _ShowHistory_P;
typedef _Method _ShowLinks_P;
typedef _Method _Store_P;
typedef _Method _SurrogateIsHighlighted_P;
typedef _Method _Transact_P;
typedef _Method _Verify_P;
#endif /* _Prototypes */

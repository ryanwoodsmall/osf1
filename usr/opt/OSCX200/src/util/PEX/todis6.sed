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
# HISTORY
# 
# $XConsortium: todis6.sed,v 1.1 91/02/16 09:51:49 rws Exp $
#  Copyright (c) 1990 by Sun Microsystems, Inc.
#  A Sed script for converting to the PHIGS DIS C binding
#  This file should each be kept sorted in inverse order, so
#  that substitutions don't interfere with each other.
#
s/Pfn_writemf/Pfn_write_item/g
s/Pfn_updatews/Pfn_upd_ws/g
s/Pfn_unpoststruct/Pfn_unpost_struct/g
s/Pfn_unpostallstruct/Pfn_unpost_all_structs/g
s/Pfn_tri3_data/Pfn_tri_strip3_data/g
s/Pfn_setwswindow3/Pfn_set_ws_win3/g
s/Pfn_setwswindow/Pfn_set_ws_win/g
s/Pfn_setwsviewport3/Pfn_set_ws_vp3/g
s/Pfn_setwsviewport/Pfn_set_ws_vp/g
s/Pfn_setviewtraninputpri/Pfn_set_view_tran_in_pri/g
s/Pfn_setviewrep3/Pfn_set_view_rep3/g
s/Pfn_setviewrep/Pfn_set_view_rep/g
s/Pfn_setviewind/Pfn_set_view_ind/g
s/Pfn_setvalmode/Pfn_set_val_mode/g
s/Pfn_settextrep/Pfn_set_text_rep/g
s/Pfn_settextprec/Pfn_set_text_prec/g
s/Pfn_settextpath/Pfn_set_text_path/g
s/Pfn_settextind/Pfn_set_text_ind/g
s/Pfn_settextfont/Pfn_set_text_font/g
s/Pfn_settextcolourind/Pfn_set_text_colr_ind/g
s/Pfn_settextalign/Pfn_set_text_align/g
s/Pfn_setstrokemode/Pfn_set_stroke_mode/g
s/Pfn_setstringmode/Pfn_set_string_mode/g
s/Pfn_setpickmode/Pfn_set_pick_mode/g
s/Pfn_setpickid/Pfn_set_pick_id/g
s/Pfn_setpickfilter/Pfn_set_pick_filter/g
s/Pfn_setpatsize/Pfn_set_pat_size/g
s/Pfn_setpatrep/Pfn_set_pat_rep/g
s/Pfn_setpatrefptvectors/Pfn_set_pat_ref_point_vecs/g
s/Pfn_setpatrefpt/Pfn_set_pat_ref_point/g
s/Pfn_setmodelclipvolume3/Pfn_set_model_clip_vol3/g
s/Pfn_setmodelclipvolume/Pfn_set_model_clip_vol/g
s/Pfn_setmodelclipindicator/Pfn_set_model_clip_ind/g
s/Pfn_setmarkertype/Pfn_set_marker_type/g
s/Pfn_setmarkersize/Pfn_set_marker_size/g
s/Pfn_setmarkerrep/Pfn_set_marker_rep/g
s/Pfn_setmarkerind/Pfn_set_marker_ind/g
s/Pfn_setmarkercolourind/Pfn_set_marker_colr_ind/g
s/Pfn_setlocmode/Pfn_set_loc_mode/g
s/Pfn_setlocaltran3/Pfn_set_local_tran3/g
s/Pfn_setlocaltran/Pfn_set_local_tran/g
s/Pfn_setlinewidth/Pfn_set_linewidth/g
s/Pfn_setlinetype/Pfn_set_linetype/g
s/Pfn_setlinerep/Pfn_set_line_rep/g
s/Pfn_setlineind/Pfn_set_line_ind/g
s/Pfn_setlinecolourind/Pfn_set_line_colr_ind/g
s/Pfn_setinvisfilter/Pfn_set_invis_filter/g
s/Pfn_setintstyleind/Pfn_set_int_style_ind/g
s/Pfn_setintstyle/Pfn_set_int_style/g
s/Pfn_setintrep/Pfn_set_int_rep/g
s/Pfn_setintind/Pfn_set_int_ind/g
s/Pfn_setintcolourind/Pfn_set_int_colr_ind/g
s/Pfn_setindivasf/Pfn_set_indiv_asf/g
s/Pfn_sethlhsrmode/Pfn_set_hlhsr_mode/g
s/Pfn_sethlhsrid/Pfn_set_hlhsr_id/g
s/Pfn_sethilightfilter/Pfn_set_highl_filter/g
s/Pfn_setglobaltran3/Pfn_set_global_tran3/g
s/Pfn_setglobaltran/Pfn_set_global_tran/g
s/Pfn_seterrorhandmode/Pfn_set_err_hand_mode/g
s/Pfn_setelemptrlabel/Pfn_set_elem_ptr_label/g
s/Pfn_setelemptr/Pfn_set_elem_ptr/g
s/Pfn_seteditmode/Pfn_set_edit_mode/g
s/Pfn_setedgewidth/Pfn_set_edgewidth/g
s/Pfn_setedgetype/Pfn_set_edgetype/g
s/Pfn_setedgerep/Pfn_set_edge_rep/g
s/Pfn_setedgeind/Pfn_set_edge_ind/g
s/Pfn_setedgeflag/Pfn_set_edge_flag/g
s/Pfn_setedgecolourind/Pfn_set_edge_colr_ind/g
s/Pfn_setdisplayupdatest/Pfn_set_disp_upd_st/g
s/Pfn_setconfres/Pfn_set_conf_res/g
s/Pfn_setcolourrep/Pfn_set_colr_rep/g
s/Pfn_setcolourmodel/Pfn_set_colr_model/g
s/Pfn_setchoicemode/Pfn_set_choice_mode/g
s/Pfn_setcharup/Pfn_char_up_vec/g
s/Pfn_setcharspace/Pfn_set_char_space/g
s/Pfn_setcharheight/Pfn_char_ht/g
s/Pfn_setcharexpan/Pfn_set_char_expan/g
s/Pfn_setannotationstyle/Pfn_set_anno_style/g
s/Pfn_setannotationpath/Pfn_set_anno_path/g
s/Pfn_setannotationcharup/Pfn_set_anno_char_up_vec/g
s/Pfn_setannotationcharheight/Pfn_set_anno_char_ht/g
s/Pfn_setannotationalign/Pfn_set_anno_align/g
s/Pfn_set_para_surf_charac/Pfn_set_para_surf_characs/g
s/Pfn_set_line_shade_method/Pfn_set_line_shad_meth/g
s/Pfn_set_int_shad_meth/Pfn_set_int_shad_meth/g
s/Pfn_set_int_reflect_eq/Pfn_set_refl_eqn/g
s/Pfn_set_face_distg_mode/Pfn_set_face_disting_mode/g
s/Pfn_set_ext_text_rep/Pfn_set_text_rep_plus/g
s/Pfn_set_ext_pat_rep/Pfn_set_pat_rep_plus/g
s/Pfn_set_ext_marker_rep/Pfn_set_marker_rep_plus/g
s/Pfn_set_ext_line_rep/Pfn_set_line_rep_plus/g
s/Pfn_set_ext_int_rep/Pfn_set_int_rep_plus/g
s/Pfn_set_ext_edge_rep/Pfn_set_edge_rep_plus/g
s/Pfn_set_back_int_shade_method/Pfn_set_back_int_shad_meth/g
s/Pfn_set_back_int_reflect_eq/Pfn_set_back_refl_eqn/g
s/Pfn_sampleval/Pfn_sample_val/g
s/Pfn_samplestroke3/Pfn_sample_stroke3/g
s/Pfn_samplestroke/Pfn_sample_stroke/g
s/Pfn_samplestring/Pfn_sample_string/g
s/Pfn_samplepick/Pfn_sample_pick/g
s/Pfn_sampleloc3/Pfn_sample_loc3/g
s/Pfn_sampleloc/Pfn_sample_loc/g
s/Pfn_samplechoice/Pfn_sample_choice/g
s/Pfn_retrievestructnet/Pfn_ret_struct_nets/g
s/Pfn_retrievestructids/Pfn_ret_struct_ids/g
s/Pfn_retrievestruct/Pfn_ret_structs/g
s/Pfn_retrievedescstruct/Pfn_ret_paths_descs/g
s/Pfn_retrieveancesstruct/Pfn_ret_paths_ancest/g
s/Pfn_retrieveallstruct/Pfn_ret_all_structs/g
s/Pfn_restoremodelclipvolume/Pfn_restore_model_clip_vol/g
s/Pfn_reqval/Pfn_req_val/g
s/Pfn_reqstroke3/Pfn_req_stroke3/g
s/Pfn_reqstroke/Pfn_req_stroke/g
s/Pfn_reqstring/Pfn_req_string/g
s/Pfn_reqpick/Pfn_req_pick/g
s/Pfn_reqloc3/Pfn_req_loc3/g
s/Pfn_reqloc/Pfn_req_loc/g
s/Pfn_reqchoice/Pfn_req_choice/g
s/Pfn_removenameset/Pfn_remove_names_set/g
s/Pfn_redrawallstruct/Pfn_redraw_all_structs/g
s/Pfn_readmf/Pfn_read_item/g
s/Pfn_quad3_data/Pfn_quad_mesh3_data/g
s/Pfn_poststruct/Pfn_post_struct/g
s/Pfn_openws/Pfn_open_ws/g
s/Pfn_openstruct/Pfn_open_struct/g
s/Pfn_openphigs/Pfn_open_phigs/g
s/Pfn_openarfile/Pfn_open_ar_file/g
s/Pfn_offsetelemptr/Pfn_offset_elem_ptr/g
s/Pfn_interpret/Pfn_interpret_item/g
s/Pfn_initval3/Pfn_init_val3/g
s/Pfn_initval/Pfn_init_val/g
s/Pfn_initstroke3/Pfn_init_stroke3/g
s/Pfn_initstroke/Pfn_init_stroke/g
s/Pfn_initstring3/Pfn_init_string3/g
s/Pfn_initstring/Pfn_init_string/g
s/Pfn_initpick3/Pfn_init_pick3/g
s/Pfn_initpick/Pfn_init_pick/g
s/Pfn_initloc3/Pfn_init_loc3/g
s/Pfn_initloc/Pfn_init_loc/g
s/Pfn_initchoice3/Pfn_init_choice3/g
s/Pfn_initchoice/Pfn_init_choice/g
s/Pfn_getval/Pfn_get_val/g
s/Pfn_gettypemf/Pfn_get_item_type/g
s/Pfn_getstroke3/Pfn_get_stroke3/g
s/Pfn_getstroke/Pfn_get_stroke/g
s/Pfn_getstring/Pfn_get_string/g
s/Pfn_getpick/Pfn_get_pick/g
s/Pfn_getloc3/Pfn_get_loc3/g
s/Pfn_getloc/Pfn_get_loc/g
s/Pfn_getchoice/Pfn_get_choice/g
s/Pfn_flushevents/Pfn_flush_events/g
s/Pfn_fillareaset3/Pfn_fill_area_set3/g
s/Pfn_fillareaset/Pfn_fill_area_set/g
s/Pfn_fillarea3/Pfn_fill_area3/g
s/Pfn_fillarea/Pfn_fill_area/g
s/Pfn_ext_cell_array3/Pfn_cell_array3_plus/g
s/Pfn_executestruct/Pfn_exec_struct/g
s/Pfn_emptystruct/Pfn_empty_struct/g
s/Pfn_delstructnetar/Pfn_del_struct_nets_ar/g
s/Pfn_delstructnet/Pfn_del_struct_net/g
s/Pfn_delstructar/Pfn_del_structs_ar/g
s/Pfn_delstruct/Pfn_del_struct/g
s/Pfn_delelemslabels/Pfn_del_elems_labels/g
s/Pfn_delelemrange/Pfn_del_elem_range/g
s/Pfn_delelem/Pfn_del_elem/g
s/Pfn_delallstructar/Pfn_del_all_structs_ar/g
s/Pfn_delallstruct/Pfn_del_all_struct/g
s/Pfn_copyallelemsstruct/Pfn_copy_all_elems_struct/g
s/Pfn_closews/Pfn_close_ws/g
s/Pfn_closestruct/Pfn_close_struct/g
s/Pfn_closephigs/Pfn_close_phigs/g
s/Pfn_closearfile/Pfn_close_ar_file/g
s/Pfn_changestructref/Pfn_change_struct_refs/g
s/Pfn_changestructidref/Pfn_change_struct_id_refs/g
s/Pfn_changestructid/Pfn_change_struct_id/g
s/Pfn_cellarray3/Pfn_cell_array3/g
s/Pfn_cellarray/Pfn_cell_array/g
s/Pfn_awaitevent/Pfn_await_event/g
s/Pfn_arstructnet/Pfn_ar_struct_nets/g
s/Pfn_arstruct/Pfn_ar_structs/g
s/Pfn_arallstruct/Pfn_ar_all_structs/g
s/Pfn_applicationdata/Pfn_appl_data/g
s/Pfn_annotationtextrelative3/Pfn_anno_text_rel3/g
s/Pfn_annotationtextrelative/Pfn_anno_text_rel/g
s/Pfn_addnameset/Pfn_add_names_set/g

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
 * @(#)$RCSfile: spain.h,v $ $Revision: 1.1.4.5 $ (DEC) $Date: 1994/01/24 19:20:58 $
 */
/* xkeycaps, Copyright (c) 1991 Jamie Zawinski <jwz@lucid.com>
 *
 * This file describes the 102-key DEC PC keyboard.
 * By Steven W. Orr <steveo@world.std.com>.
 */

static struct key spain_row1 [] = {
 {8,	"Esc",	0,		8, 8,	0,	XK_Escape},
 {0,	0,	0,			8, 8},
 {9,	"F1",	0,		8, 8,	0,	XK_F1},
 {0xf,	"F2",	0,		8, 8,	0,	XK_F2},
 {0x17,	"F3",	0,		8, 8,	0,	XK_F3},
 {0x1f,	"F4",	0,		8, 8,	0,	XK_F4},
 {0,	0,	0,			4, 8},
 {0x27,	"F5",	0,		8, 8,	0,	XK_F5},
 {0x2f,	"F6",	0,		8, 8,	0,	XK_F6},
 {0x37,	"F7",	0,		8, 8,	0,	XK_F7},
 {0x3f,	"F8",	0,		8, 8,	0,	XK_F8},
 {0,	0,	0,			4, 8},
 {0x47,	"F9",	0,		8, 8,	0,	XK_F9},
 {0x4f,	"F10",	0,		8, 8,	0,	XK_F10},
 {0x56,	"F11",	0,		8, 8,	0,	XK_F11},
 {0x5e,	"F12",	0,		8, 8,	0,	XK_F12},
 {0,	0,	0,			4, 8},
 {0x57,"Print", "Scrn",8, 8,	0,	XK_Print},
 {0x5f,	"Scroll","Lock",8, 8,	0,	XK_Cancel},
 {0x62,"Pause", "Break",8, 8,	0,	XK_Pause},
};

static struct key spain_row2 [] = {
 {0xe, StrXK_ordfeminine, StrXK_masculine, 8, 8,	0,	XK_masculine, XK_ordfeminine},
 {0x16, "!", "1", 8, 8,	0,	XK_1, XK_exclam, XK_bar},
 {0x1e, "\"", "2", 8, 8,	0,	XK_2, XK_quotedbl, XK_at},
 {0x26, StrXK_periodcentered, "3", 8, 8,	0,	XK_3, XK_periodcentered, XK_numbersign},
 {0x25, "$", "4", 8, 8,	0,	XK_4, XK_dollar},
 {0x2e, "", "5", 8, 8,	0,	XK_5, XK_percent},
 {0x36, "&", "6", 8, 8,	0,	XK_6, XK_ampersand, XK_notsign},
 {0x3d, "/", "7", 8, 8,	0,	XK_7, XK_slash},
 {0x3e, "(", "8", 8, 8,	0,	XK_8, XK_parenleft},
 {0x46, ")", "9", 8, 8,	0,	XK_9, XK_parenright},
 {0x45, "=", "0", 8, 8,	0,	XK_0, XK_equal},
 {0x4e, "?", "'", 8, 8,	0,	XK_apostrophe, XK_question},
 {0x55, StrXK_questiondown, StrXK_exclamdown, 8, 8,	0,	XK_exclamdown, XK_questiondown},
 {0x66,	"Backspace", 0,		16, 8,	0,	XK_BackSpace},
 {0,	0,	0,				4, 8},
 {0x67,	"Insert", 0,		8, 8,	0,	XK_Insert},
 {0x6e,	"Home",	0,			8, 8,	0,	XK_Home},
 {0x6f,   "Page","up",		8, 8,	0,	XK_Prior},
 {0,	0,	0,				4, 8},
 {0x76,	"Num",	"Lock",		8, 8,	0,	XK_Num_Lock,	XK_Num_Lock},
 {0x77,	"/",	0,			8, 8,	0,	XK_KP_Divide},
 {0x7e,	"*",	0,			8, 8,	0,	XK_KP_Multiply},
 {0x84,	"-",	0,			8, 8,	0,	XK_KP_Subtract}
};

static struct key spain_row3 [] = {
 {0x0d,	"Tab",	0,		12, 8,	0,	XK_Tab},
 {0x15, 0, "Q", 8, 8,	0,	XK_Q},
 {0x1d, 0, "W", 8, 8,	0,	XK_W},
 {0x24, 0, "E", 8, 8,	0,	XK_E},
 {0x2d, 0, "R", 8, 8,	0,	XK_R},
 {0x2c, 0, "T", 8, 8,	0,	XK_T},
 {0x35, 0, "Y", 8, 8,	0,	XK_Y},
 {0x3c, 0, "U", 8, 8,	0,	XK_U},
 {0x43, 0, "I", 8, 8,	0,	XK_I},
 {0x44, 0, "O", 8, 8,	0,	XK_O},
 {0x4d, 0, "P", 8, 8,	0,	XK_P},
 {0x54, "^", "`", 8, 8,	0,	XK_grave, XK_asciicircum, XK_bracketleft},
 {0x5b, "*", "+", 8, 8,	0,	XK_plus, XK_asterisk, XK_bracketright},
 {0,    0,  0,      	2, 7},
 {0x5a,	"Return", 0,	10, 16,	0,	XK_Return},
 {0,	0,	0,			4, 7},
 {0x64,	"Delete", 0,	8, 8,	0,	XK_Delete},
 {0x65,	"End",	0,		8, 8,	0,	XK_End},
 {0x6d, "Page","down",	8, 8,	0,	XK_Next},
 {0,	0,	0,			4, 8},
 {0x6c,	"7","Home",		8, 8,	0,	XK_KP_7},
 {0x75,	"8","UpArrow",	8, 8,	0,	XK_KP_8},
 {0x7d,	"9","PgUp",		8, 8,	0,	XK_KP_9},
 {0x7c,	"+",0,			8, 16,	0,	XK_KP_Add}
};

static struct key spain_row4 [] = {
 {0x14, "Caps",	"Lock",	14, 8,	LockMask,	XK_Caps_Lock},
 {0x1c, 0, "A", 8, 8,	0,	XK_A},
 {0x1b, 0, "S", 8, 8,	0,	XK_S},
 {0x23, 0, "D", 8, 8,	0,	XK_D},
 {0x2b, 0, "F", 8, 8,	0,	XK_F},
 {0x34, 0, "G", 8, 8,	0,	XK_G},
 {0x33, 0, "H", 8, 8,	0,	XK_H},
 {0x3b, 0, "J", 8, 8,	0,	XK_J},
 {0x42, 0, "K", 8, 8,	0,	XK_K},
 {0x4b, 0, "L", 8, 8,	0,	XK_L},
 {0x4c, StrXK_Ntilde, StrXK_ntilde, 8, 8,	0,	XK_ntilde, XK_Ntilde},
 {0x52, StrXK_diaeresis, StrXK_acute, 8, 8,	0,	XK_acute, XK_diaeresis, XK_braceleft},
 {0x53, StrXK_Ccedilla, StrXK_ccedilla, 8, 8,	0,	XK_ccedilla, XK_Ccedilla, XK_braceright},
 {0,	0,	0,			42,7},
 {0x6b,	"4","LeftArrow",8, 8,	0,	XK_KP_4},
 {0x73,	"5",0,			8, 8,	0,	XK_KP_5},
 {0x74,"6","RightArrow",8, 8,	0,	XK_KP_6}
};

static struct key spain_row5 [] = {
 {0x12,	"Shift",0,		10, 8,	ShiftMask,	XK_Shift_L},
 {0x13, ">", "<", 8, 8,	0,		XK_less, XK_greater},
 {0x1a, 0, "Z", 8, 8,	0,		XK_Z},
 {0x22, 0, "X", 8, 8,	0,		XK_X},
 {0x21, 0, "C", 8, 8,	0,		XK_C},
 {0x2a, 0, "V", 8, 8,	0,		XK_V},
 {0x32, 0, "B", 8, 8,	0,		XK_B},
 {0x31, 0, "N", 8, 8,	0,		XK_N},
 {0x3a, 0, "M", 8, 8,	0,		XK_M},
 {0x41, ";", ",", 8, 8,	0,		XK_comma, XK_semicolon},
 {0x49, ":", ".", 8, 8,	0,		XK_period, XK_colon},
 {0x4a, "_", "-", 8, 8,	0,		XK_minus, XK_underscore},
 {0x59,	"Shift",0,		22, 8,	ShiftMask,	XK_Shift_R},
 {0,	0,	0,			12, 8},
 {0x63,	"UpArrow",0,	8, 8,	0,		XK_Up},
 {0,	0,	0,			12, 8},
 {0x69,   "1",	"End",	8, 8,	0,		XK_KP_1},
 {0x72,   "2",	"DownArrow",	8, 8,	0,		XK_KP_2},
 {0x7a,   "3",	"PgDn",	8, 8,	0,		XK_KP_3},
 {0x79,	"Enter",0,		8, 16,	0,		XK_KP_Enter}
};

static struct key spain_row6 [] = {
 {0x11,	"Ctrl",		0,	12, 8,	ControlMask,	XK_Control_L},
 {0,	0,		0,		8, 8},
 {0x19,	"Alt",		0,	12, 8,	Mod1Mask,	XK_Alt_L},
 {0x29,	" ",		0,	57, 8,	0,		XK_space},
 {0x39,	"Alt",	"gr",	12, 8,	Mod3Mask,	XK_Mode_switch},
 {0,	0,		0,		7, 8},
 {0x58,	"Ctrl",		0,	12, 8,	ControlMask,	XK_Control_R},
 {0,	0,		0,		4, 8},
 {0x61,	"LeftArrow",	0,	8, 8,	0,		XK_Left},
 {0x60,	"DownArrow",	0,	8, 8,	0,		XK_Down},
 {0x6a,	"RightArrow",	0,	8, 8,	0,		XK_Right},
 {0,	0,		0,		4, 8},
 {0x70,	"0",	"Ins",	16, 8,	0,		XK_KP_0},
 {0x71,	".",	"Del",	8, 8,	0,		XK_KP_Decimal}
};

static struct row spain_rows [] = {
  { sizeof (spain_row1) / sizeof (struct key), 8, spain_row1 },
  { 0, 8, 0 },
  { sizeof (spain_row2) / sizeof (struct key), 8, spain_row2 },
  { sizeof (spain_row3) / sizeof (struct key), 8, spain_row3 },
  { sizeof (spain_row4) / sizeof (struct key), 8, spain_row4 },
  { sizeof (spain_row5) / sizeof (struct key), 8, spain_row5 },
  { sizeof (spain_row6) / sizeof (struct key), 8, spain_row6 },
};

static struct keyboard spain = {
  "PCXAL (Espanol)",
  sizeof (spain_rows) / sizeof (struct row),
  spain_rows,
  6, 3, 3
};

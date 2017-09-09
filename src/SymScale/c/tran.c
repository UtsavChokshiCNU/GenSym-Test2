/* tran.c
 * Input file:  translate.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "tran.h"


DEFINE_VARIABLE_WITH_SYMBOL(Modules_to_translate_verbosely, Qmodules_to_translate_verbosely);

DEFINE_VARIABLE_WITH_SYMBOL(Dummy_place_for_chestnut_internals, Qdummy_place_for_chestnut_internals);

Object The_standard_mnemonics = UNBOUND;

void translate_INIT()
{
    Object list_constant_48, list_constant_47, list_constant_46;
    Object list_constant_45, list_constant_44, list_constant_43;
    Object list_constant_42, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_38, list_constant_37;
    Object list_constant_36, list_constant_35, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object list_constant_30, list_constant_29, list_constant_28;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_18, list_constant_17, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_9, list_constant_8, list_constant_7, list_constant_6;
    Object list_constant_5, list_constant_4, list_constant_3, list_constant_2;
    Object list_constant_1, list_constant, string_constant_93;
    Object string_constant_92, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object string_constant_2, string_constant_1, string_constant;

    x_note_fn_call(253,0);
    SET_PACKAGE("AB");
    if (Modules_to_translate_verbosely == UNBOUND)
	Modules_to_translate_verbosely = Qnil;
    if (Dummy_place_for_chestnut_internals == UNBOUND)
	Dummy_place_for_chestnut_internals = Nil;
    string_constant = STATIC_STRING("area");
    string_constant_1 = STATIC_STRING("a");
    list_constant_16 = STATIC_LIST((SI_Long)2L,string_constant,
	    string_constant_1);
    string_constant_2 = STATIC_STRING("attr-export");
    string_constant_3 = STATIC_STRING("atrxpt");
    list_constant_17 = STATIC_LIST((SI_Long)2L,string_constant_2,
	    string_constant_3);
    string_constant_4 = STATIC_STRING("attribute");
    string_constant_5 = STATIC_STRING("attr");
    list_constant_18 = STATIC_LIST((SI_Long)2L,string_constant_4,
	    string_constant_5);
    string_constant_6 = STATIC_STRING("change-log");
    string_constant_7 = STATIC_STRING("chglog");
    list_constant_19 = STATIC_LIST((SI_Long)2L,string_constant_6,
	    string_constant_7);
    string_constant_8 = STATIC_STRING("character");
    string_constant_9 = STATIC_STRING("char");
    list_constant_20 = STATIC_LIST((SI_Long)2L,string_constant_8,
	    string_constant_9);
    string_constant_10 = STATIC_STRING("check");
    string_constant_11 = STATIC_STRING("chk");
    list_constant_21 = STATIC_LIST((SI_Long)2L,string_constant_10,
	    string_constant_11);
    string_constant_12 = STATIC_STRING("codes");
    string_constant_13 = STATIC_STRING("cds");
    list_constant_22 = STATIC_LIST((SI_Long)2L,string_constant_12,
	    string_constant_13);
    string_constant_14 = STATIC_STRING("ctest");
    string_constant_15 = STATIC_STRING("ct");
    list_constant_23 = STATIC_LIST((SI_Long)2L,string_constant_14,
	    string_constant_15);
    string_constant_16 = STATIC_STRING("command");
    string_constant_17 = STATIC_STRING("cmd");
    list_constant_24 = STATIC_LIST((SI_Long)2L,string_constant_16,
	    string_constant_17);
    string_constant_18 = STATIC_STRING("rpc-common");
    string_constant_19 = STATIC_STRING("rpcmn");
    list_constant_25 = STATIC_LIST((SI_Long)2L,string_constant_18,
	    string_constant_19);
    string_constant_20 = STATIC_STRING("common");
    string_constant_21 = STATIC_STRING("cmn");
    list_constant_26 = STATIC_LIST((SI_Long)2L,string_constant_20,
	    string_constant_21);
    string_constant_22 = STATIC_STRING("connect");
    string_constant_23 = STATIC_STRING("cnct");
    list_constant_27 = STATIC_LIST((SI_Long)2L,string_constant_22,
	    string_constant_23);
    string_constant_24 = STATIC_STRING("dialogs");
    string_constant_25 = STATIC_STRING("dlogs");
    list_constant_28 = STATIC_LIST((SI_Long)2L,string_constant_24,
	    string_constant_25);
    string_constant_26 = STATIC_STRING("events");
    string_constant_27 = STATIC_STRING("evt");
    list_constant_29 = STATIC_LIST((SI_Long)2L,string_constant_26,
	    string_constant_27);
    string_constant_28 = STATIC_STRING("grammar");
    string_constant_29 = STATIC_STRING("gram");
    list_constant_30 = STATIC_LIST((SI_Long)2L,string_constant_28,
	    string_constant_29);
    string_constant_30 = STATIC_STRING("hash-tables");
    string_constant_31 = STATIC_STRING("hshtbl");
    list_constant_31 = STATIC_LIST((SI_Long)2L,string_constant_30,
	    string_constant_31);
    string_constant_32 = STATIC_STRING("images");
    string_constant_33 = STATIC_STRING("lspimg");
    list_constant_32 = STATIC_LIST((SI_Long)2L,string_constant_32,
	    string_constant_33);
    string_constant_34 = STATIC_STRING("interface");
    string_constant_35 = STATIC_STRING("if");
    list_constant_33 = STATIC_LIST((SI_Long)2L,string_constant_34,
	    string_constant_35);
    string_constant_36 = STATIC_STRING("licensing-users");
    string_constant_37 = STATIC_STRING("lsusr");
    list_constant_34 = STATIC_LIST((SI_Long)2L,string_constant_36,
	    string_constant_37);
    string_constant_38 = STATIC_STRING("lucid-server");
    string_constant_39 = STATIC_STRING("lsrvr");
    list_constant_35 = STATIC_LIST((SI_Long)2L,string_constant_38,
	    string_constant_39);
    string_constant_40 = STATIC_STRING("memory");
    string_constant_41 = STATIC_STRING("mem");
    list_constant_36 = STATIC_LIST((SI_Long)2L,string_constant_40,
	    string_constant_41);
    string_constant_42 = STATIC_STRING("module");
    string_constant_43 = STATIC_STRING("mod");
    list_constant_37 = STATIC_LIST((SI_Long)2L,string_constant_42,
	    string_constant_43);
    string_constant_44 = STATIC_STRING("native-");
    string_constant_45 = STATIC_STRING("natv");
    list_constant_38 = STATIC_LIST((SI_Long)2L,string_constant_44,
	    string_constant_45);
    string_constant_46 = STATIC_STRING("nupec");
    string_constant_47 = STATIC_STRING("np");
    list_constant_39 = STATIC_LIST((SI_Long)2L,string_constant_46,
	    string_constant_47);
    string_constant_48 = STATIC_STRING("patch");
    string_constant_49 = STATIC_STRING("pat");
    list_constant_40 = STATIC_LIST((SI_Long)2L,string_constant_48,
	    string_constant_49);
    string_constant_50 = STATIC_STRING("platform");
    string_constant_51 = STATIC_STRING("ptfm");
    list_constant_41 = STATIC_LIST((SI_Long)2L,string_constant_50,
	    string_constant_51);
    string_constant_52 = STATIC_STRING("portable");
    string_constant_53 = STATIC_STRING("p");
    list_constant_42 = STATIC_LIST((SI_Long)2L,string_constant_52,
	    string_constant_53);
    string_constant_54 = STATIC_STRING("postscript");
    string_constant_55 = STATIC_STRING("ps");
    list_constant_43 = STATIC_LIST((SI_Long)2L,string_constant_54,
	    string_constant_55);
    string_constant_56 = STATIC_STRING("priority-queues");
    string_constant_57 = STATIC_STRING("priqus");
    list_constant_44 = STATIC_LIST((SI_Long)2L,string_constant_56,
	    string_constant_57);
    string_constant_58 = STATIC_STRING("sysproc");
    string_constant_59 = STATIC_STRING("sp");
    list_constant_45 = STATIC_LIST((SI_Long)2L,string_constant_58,
	    string_constant_59);
    string_constant_60 = STATIC_STRING("proc");
    string_constant_61 = STATIC_STRING("pc");
    list_constant_46 = STATIC_LIST((SI_Long)2L,string_constant_60,
	    string_constant_61);
    string_constant_62 = STATIC_STRING("resources");
    string_constant_63 = STATIC_STRING("rsrcs");
    list_constant = STATIC_LIST((SI_Long)2L,string_constant_62,
	    string_constant_63);
    string_constant_64 = STATIC_STRING("socket");
    string_constant_65 = STATIC_STRING("sock");
    list_constant_1 = STATIC_LIST((SI_Long)2L,string_constant_64,
	    string_constant_65);
    string_constant_66 = STATIC_STRING("service");
    string_constant_67 = STATIC_STRING("svc");
    list_constant_2 = STATIC_LIST((SI_Long)2L,string_constant_66,
	    string_constant_67);
    string_constant_68 = STATIC_STRING("settings");
    string_constant_69 = STATIC_STRING("set");
    list_constant_3 = STATIC_LIST((SI_Long)2L,string_constant_68,
	    string_constant_69);
    string_constant_70 = STATIC_STRING("smbx");
    string_constant_71 = STATIC_STRING("sm");
    list_constant_4 = STATIC_LIST((SI_Long)2L,string_constant_70,
	    string_constant_71);
    string_constant_72 = STATIC_STRING("stack");
    string_constant_73 = STATIC_STRING("stk");
    list_constant_5 = STATIC_LIST((SI_Long)2L,string_constant_72,
	    string_constant_73);
    string_constant_74 = STATIC_STRING("stubs");
    string_constant_75 = STATIC_STRING("sb");
    list_constant_6 = STATIC_LIST((SI_Long)2L,string_constant_74,
	    string_constant_75);
    string_constant_76 = STATIC_STRING("systems");
    string_constant_77 = STATIC_STRING("systm");
    list_constant_7 = STATIC_LIST((SI_Long)2L,string_constant_76,
	    string_constant_77);
    string_constant_78 = STATIC_STRING("transcode");
    string_constant_79 = STATIC_STRING("trnscd");
    list_constant_8 = STATIC_LIST((SI_Long)2L,string_constant_78,
	    string_constant_79);
    string_constant_80 = STATIC_STRING("translate");
    string_constant_81 = STATIC_STRING("tran");
    list_constant_9 = STATIC_LIST((SI_Long)2L,string_constant_80,
	    string_constant_81);
    string_constant_82 = STATIC_STRING("traversal");
    string_constant_83 = STATIC_STRING("trv");
    list_constant_10 = STATIC_LIST((SI_Long)2L,string_constant_82,
	    string_constant_83);
    string_constant_84 = STATIC_STRING("version");
    string_constant_85 = STATIC_STRING("vrn");
    list_constant_11 = STATIC_LIST((SI_Long)2L,string_constant_84,
	    string_constant_85);
    string_constant_86 = STATIC_STRING("view");
    string_constant_87 = STATIC_STRING("vw");
    list_constant_12 = STATIC_LIST((SI_Long)2L,string_constant_86,
	    string_constant_87);
    string_constant_88 = STATIC_STRING("win32");
    string_constant_89 = STATIC_STRING("w32");
    list_constant_13 = STATIC_LIST((SI_Long)2L,string_constant_88,
	    string_constant_89);
    string_constant_90 = STATIC_STRING("windows");
    string_constant_91 = STATIC_STRING("win");
    list_constant_14 = STATIC_LIST((SI_Long)2L,string_constant_90,
	    string_constant_91);
    string_constant_92 = STATIC_STRING("workstation");
    string_constant_93 = STATIC_STRING("wrkstn");
    list_constant_15 = STATIC_LIST((SI_Long)2L,string_constant_92,
	    string_constant_93);
    list_constant_47 = STATIC_LIST((SI_Long)16L,list_constant,
	    list_constant_1,list_constant_2,list_constant_3,
	    list_constant_4,list_constant_5,list_constant_6,
	    list_constant_7,list_constant_8,list_constant_9,
	    list_constant_10,list_constant_11,list_constant_12,
	    list_constant_13,list_constant_14,list_constant_15);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)32L,list_constant_16,
	    list_constant_17,list_constant_18,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23,list_constant_24,list_constant_25,
	    list_constant_26,list_constant_27,list_constant_28,
	    list_constant_29,list_constant_30,list_constant_31,
	    list_constant_32,list_constant_33,list_constant_34,
	    list_constant_35,list_constant_36,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44,list_constant_45,list_constant_46,
	    list_constant_47);
    The_standard_mnemonics = list_constant_48;
}

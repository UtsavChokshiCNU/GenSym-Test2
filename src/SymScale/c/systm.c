/* systm.c
 * Input file:  systems.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "systm.h"


DEFINE_VARIABLE_WITH_SYMBOL(Development_world_save_p, Qdevelopment_world_save_p);

static Object Qab;                 /* ab */

/* LAUNCH-G2-IMAGE */
Object launch_g2_image()
{
    x_note_fn_call(2,0);
    return launch_system(Qab);
}

static Object Qtelewindows;        /* telewindows */

/* LAUNCH-TELEWINDOWS-IMAGE */
Object launch_telewindows_image()
{
    x_note_fn_call(2,1);
    return launch_system(Qtelewindows);
}

void systems_INIT()
{
    Object temp, temp_1, symbol_from_ab_package, package_of_symbol;
    Object list_constant_51, list_constant_50, Qls, Qdeclare_system_1;
    Object list_constant_10, Qproducts_uninterested_in_this_system;
    Object Qlicensing_server, Qalias, AB_package, Qlicense, Qintegrals;
    Object Qnumbers, list_constant_44, list_constant_6, Qglbasics, Qab_loop;
    Object Qg2_config, list_constant_5, Qdelta, Qportable_threads, Qsystems;
    Object list_constant_4, Qsystem_binary_pathname_qm, string_constant_1;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object Qsystems_to_share_binary_files_with, Qsystem_is_windowless_p;
    Object list_constant_46, Qnicknames, Qg2, Qgensym_site, list_constant_45;
    Object Qtranscode, Qiso2022, Qunicode, Qletters, Qutilities2, Qutilities1;
    Object Qutilities0, Qkeydefs, Qkeyboards, Qcharacters2, Qgbmapr, Qgbmap;
    Object Qksmap2, Qjismap, Qcharacters, Qprimitives, Qos_memory;
    Object Qos_settings, Qos_time, Qbasics, Qos_foreign, Qg2_patches;
    Object list_constant_43, Qwindows4, Qwindows3a, Qwindows3, Qwindows2;
    Object Qwindows1, Qgsi_common, Qint4, Qint3b, Qint3a, Qint2, Qnetevent;
    Object Qneterror, Qint1, Qint0, Qnetworks, Qclocks, Qschedule, Qpostscript;
    Object Qstreams, Qfile_parse, Qpathnames, Qlaunch, Qplatforms, Qos_error;
    Object Qf_keys, Qtimes, Qutilities4, Qutilities3, Qtoken, Qalphabet;
    Object Qiso8859, list_constant_42, Qpanes, Qframes5, Qframes4, Qframes3;
    Object Qframes2b, Qframes2a, Qslots, Qframes2, Qtypes, Qframes1, Qparse2;
    Object Qparse, list_constant_41, list_constant_40, Qthai24, Qthai18;
    Object Qthai14, Qhebrew24, Qhebrew18, Qhebrew14, Qslavic24, Qslavic18;
    Object Qslavic14, Qhm24, Qhm18, Qhm14, Qhb72, Qicons, Qmice, Qimages;
    Object list_constant_39, Qfacilities, Qnew_menus, Qmenus, Qbooks;
    Object Qworkstation, Qnative_tw, Qdialogs, Qtelestubs, Qtables, Qlanguage;
    Object Qboxes, Qsequences3, Qsequences2, Qsequences1, Qformats, Qrelations;
    Object Qdefinitions, Qconnect5, Qconnect4, Qconnect3a, Qconnect3;
    Object Qconnect2, Qconnect1, Qprinting, Qps_header, Qab_debug, Qab_modules;
    Object Qview_def, Qplaces, Qentities, Qdraw, list_constant_38, Qroles;
    Object Qhistories, Qvariables, Qpriority_queues, Qhash_tables, Qarrays;
    Object Qlists, Qsets, Qcompile2, Qcompile1, Qcomp_utils, list_constant_37;
    Object Qfont_files, Qwarmboot, Qkb_save4, Qkb_save3, Qkb_save2, Qkb_save1;
    Object Qkb_load2, Qkb_load1, Qkb_merge, Qrun, Qmoves, Qrings, Qedit2;
    Object Qedit1, Qhfep2, Qhfep1, Qkfep3, Qkfep2, Qkfep1, list_constant_36;
    Object Qfilters, Qinstall, Qnew_tables, Qcharts1, Qgraphs, Qgraph_def;
    Object Qgraph_util, Qgraphs2, Qgraphs1, Qdisplays, Qparts, Qexplain;
    Object Qg2_rpc3, Qg2_rpc2, Qg2_rpc1, Qmem_sysproc, Qfile_sysproc;
    Object Qchange_log, Qproc_debug, Qproc_comp, Qproc_utils, Qrpc_common3;
    Object Qrpc_common2, Qrpc_common1, Qproc_gram, Qcells, Qfunctions;
    Object Qchaining, Qnew_rules, Qrules, list_constant_35, Qproc_inst;
    Object Qstack_kern, Qstack_acts, Qstack_eval2, Qstack_eval1, Qstack_comp;
    Object Qstack_inst, Qstack_utils, Qgrammar7, Qgrammar6c, Qgrammar6b;
    Object Qgrammar6a, Qgrammar5, Qgrammar4a, Qgrammar4, Qgrammar3, Qgrammar2;
    Object Qgrammar1a, Qgrammar1, Qgrammar0, Qconclude, Qdom, Qsax, Qlexer;
    Object Qsimulate5, Qsimulate3, Qsimulate2, Qsimulate1, Qcycles;
    Object Qattr_export, Qactivate, list_constant_34, Qweb_services, Qsocket2;
    Object Qsocket1, Qsmartsignalextension, Qcontinentalextension, Qinterop;
    Object Qicons5, Qicons4, Qicons3, Qicons2, Qicons1, Qteleserver;
    Object Qtraversals, Qmedia, Qview_g2, Qview_msg1, Qcommands2, Qcommands1;
    Object Qcommands0, Qcontrols, Qviews, Qg2ds_nupec, Qg2ds, list_constant_33;
    Object list_constant_32, list_constant_31, Qattributes, Qgfi_stubs;
    Object Qg2_foreign, Qqueries, Qproc_inst2, Qg2_final, Qtranslate;
    Object list_constant_30, Qsysicons, Qjava3, Qjava2, Qjava1, Qevents_g2;
    Object Qevents, Qresources, Qg2_meters, list_constant_29, Qplayer;
    Object Qg2_bpel, list_constant_28, Koverriding_include_test, Qcheckmemory;
    Object Kno_macros, Kdevelopment, Qrg_report, list_constant_25, Qgspan;
    Object Qg2_gsi, Qgfi, list_constant_27, Qcheck_kbs, Qno_macros;
    Object list_constant_26, Qdoc, Qsite, list_constant_24, Koptional_module_p;
    Object list_constant_1, Qlisp_server, list_constant_23, list_constant_22;
    Object Qgw, list_constant_19, list_constant_21, Qweblink, list_constant_20;
    Object Qgsi_patches, list_constant_16, Qweb_gsi, Qserver, Qweb, Qbridge;
    Object Qhtmlgen, Qgthread, Qbuffer, Qgwutil_1, Qgsi_rpc2, Qgsi_rpc1, Qgsi;
    Object Qfixed_system_key, Qgsi_extension, list_constant_18;
    Object list_constant_17, list_constant_15, list_constant_14;
    Object list_constant_13, Qsystem_c_files, list_constant_12;
    Object list_constant_11, Qtw, list_constant_9, string_constant;
    Object Klocal_directory_namestring, list_constant_8, Qtwmain, Qchestnut_3;
    Object Qchestnut, Qab_or, list_constant_7, Qtw_patches, list_constant_3;
    Object list_constant_2, Qgldebug, Qab_features, Qdevelopment;
    Object Qupdate_bootstrap_and_reupdate_all_modules, Klisp_update_function;
    Object Qcompile_bootstrap_and_reboot_all_modules, Klisp_compile_function;
    Object list_constant, Kinclude_test_for_load, Qbootstrap;
    Object Kdo_not_load_bootstrap;

    x_note_fn_call(2,2);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qsystem_binary_pathname_qm = STATIC_SYMBOL("SYSTEM-BINARY-PATHNAME\?",
	    AB_package);
    if ( !TRUEP(get(Qtelewindows,Qsystem_binary_pathname_qm,_))) {
	temp = SEVENTH(Bootstrap_information);
	set_get(Qtelewindows,Qsystem_binary_pathname_qm,temp);
    }
    temp = adjoin(2,Qtelewindows,All_systems);
    All_systems = temp;
    Qdeclare_system_1 = STATIC_SYMBOL("DECLARE-SYSTEM-1",AB_package);
    SET_SYMBOL_FUNCTION(Qdeclare_system_1,STATIC_FUNCTION(declare_system_1,
	    NIL,TRUE,2,2));
    Qbootstrap = STATIC_SYMBOL("BOOTSTRAP",AB_package);
    Kinclude_test_for_load = STATIC_SYMBOL("INCLUDE-TEST-FOR-LOAD",Pkeyword);
    Kdo_not_load_bootstrap = STATIC_SYMBOL("DO-NOT-LOAD-BOOTSTRAP",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,Qnot,Kdo_not_load_bootstrap);
    Klisp_compile_function = STATIC_SYMBOL("LISP-COMPILE-FUNCTION",Pkeyword);
    Qcompile_bootstrap_and_reboot_all_modules = 
	    STATIC_SYMBOL("COMPILE-BOOTSTRAP-AND-REBOOT-ALL-MODULES",
	    AB_package);
    Klisp_update_function = STATIC_SYMBOL("LISP-UPDATE-FUNCTION",Pkeyword);
    Qupdate_bootstrap_and_reupdate_all_modules = 
	    STATIC_SYMBOL("UPDATE-BOOTSTRAP-AND-REUPDATE-ALL-MODULES",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)7L,Qbootstrap,
	    Kinclude_test_for_load,list_constant,Klisp_compile_function,
	    Qcompile_bootstrap_and_reboot_all_modules,
	    Klisp_update_function,Qupdate_bootstrap_and_reupdate_all_modules);
    Qsystems = STATIC_SYMBOL("SYSTEMS",AB_package);
    Qdelta = STATIC_SYMBOL("DELTA",AB_package);
    Qab_features = STATIC_SYMBOL("FEATURES",AB_package);
    Koverriding_include_test = STATIC_SYMBOL("OVERRIDING-INCLUDE-TEST",
	    Pkeyword);
    Qdevelopment = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Koverriding_include_test,
	    Qdevelopment);
    list_constant_5 = STATIC_CONS(Qab_features,list_constant_1);
    Qg2_config = STATIC_SYMBOL("G2-CONFIG",AB_package);
    Qtw_patches = STATIC_SYMBOL("TW-PATCHES",AB_package);
    Qab_loop = STATIC_SYMBOL("LOOP",AB_package);
    Qglbasics = STATIC_SYMBOL("GLBASICS",AB_package);
    Qgldebug = STATIC_SYMBOL("GLDEBUG",AB_package);
    list_constant_6 = STATIC_CONS(Qgldebug,list_constant_1);
    Qos_foreign = STATIC_SYMBOL("OS-FOREIGN",AB_package);
    Qbasics = STATIC_SYMBOL("BASICS",AB_package);
    Qos_time = STATIC_SYMBOL("OS-TIME",AB_package);
    Qos_settings = STATIC_SYMBOL("OS-SETTINGS",AB_package);
    Qos_memory = STATIC_SYMBOL("OS-MEMORY",AB_package);
    Qprimitives = STATIC_SYMBOL("PRIMITIVES",AB_package);
    Qcharacters = STATIC_SYMBOL("CHARACTERS",AB_package);
    Qjismap = STATIC_SYMBOL("JISMAP",AB_package);
    Qksmap2 = STATIC_SYMBOL("KSMAP2",AB_package);
    Qgbmap = STATIC_SYMBOL("GBMAP",AB_package);
    Qgbmapr = STATIC_SYMBOL("GBMAPR",AB_package);
    Qcharacters2 = STATIC_SYMBOL("CHARACTERS2",AB_package);
    Qkeyboards = STATIC_SYMBOL("KEYBOARDS",AB_package);
    Qkeydefs = STATIC_SYMBOL("KEYDEFS",AB_package);
    Qutilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    Qletters = STATIC_SYMBOL("LETTERS",AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    Qiso2022 = STATIC_SYMBOL("ISO2022",AB_package);
    Qtranscode = STATIC_SYMBOL("TRANSCODE",AB_package);
    Qiso8859 = STATIC_SYMBOL("ISO8859",AB_package);
    Qutilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Qtimes = STATIC_SYMBOL("TIMES",AB_package);
    Qf_keys = STATIC_SYMBOL("F-KEYS",AB_package);
    Qos_error = STATIC_SYMBOL("OS-ERROR",AB_package);
    Qplatforms = STATIC_SYMBOL("PLATFORMS",AB_package);
    Qlaunch = STATIC_SYMBOL("LAUNCH",AB_package);
    Qpathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Qfile_parse = STATIC_SYMBOL("FILE-PARSE",AB_package);
    Qstreams = STATIC_SYMBOL("STREAMS",AB_package);
    Qschedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    Qclocks = STATIC_SYMBOL("CLOCKS",AB_package);
    Qnetworks = STATIC_SYMBOL("NETWORKS",AB_package);
    Qint0 = STATIC_SYMBOL("INT0",AB_package);
    Qint1 = STATIC_SYMBOL("INT1",AB_package);
    Qneterror = STATIC_SYMBOL("NETERROR",AB_package);
    Qnetevent = STATIC_SYMBOL("NETEVENT",AB_package);
    Qint2 = STATIC_SYMBOL("INT2",AB_package);
    Qint3a = STATIC_SYMBOL("INT3A",AB_package);
    Qint3b = STATIC_SYMBOL("INT3B",AB_package);
    Qint4 = STATIC_SYMBOL("INT4",AB_package);
    Qwindows1 = STATIC_SYMBOL("WINDOWS1",AB_package);
    Qwindows2 = STATIC_SYMBOL("WINDOWS2",AB_package);
    Qwindows3 = STATIC_SYMBOL("WINDOWS3",AB_package);
    Qwindows3a = STATIC_SYMBOL("WINDOWS3A",AB_package);
    Qwindows4 = STATIC_SYMBOL("WINDOWS4",AB_package);
    Qimages = STATIC_SYMBOL("IMAGES",AB_package);
    Qfonts = STATIC_SYMBOL("FONTS",AB_package);
    Qhb72 = STATIC_SYMBOL("HB72",AB_package);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    Qhm18 = STATIC_SYMBOL("HM18",AB_package);
    Qhm24 = STATIC_SYMBOL("HM24",AB_package);
    Qslavic14 = STATIC_SYMBOL("SLAVIC14",AB_package);
    Qslavic18 = STATIC_SYMBOL("SLAVIC18",AB_package);
    Qslavic24 = STATIC_SYMBOL("SLAVIC24",AB_package);
    Qhebrew14 = STATIC_SYMBOL("HEBREW14",AB_package);
    Qhebrew18 = STATIC_SYMBOL("HEBREW18",AB_package);
    Qhebrew24 = STATIC_SYMBOL("HEBREW24",AB_package);
    Qthai14 = STATIC_SYMBOL("THAI14",AB_package);
    Qthai18 = STATIC_SYMBOL("THAI18",AB_package);
    Qthai24 = STATIC_SYMBOL("THAI24",AB_package);
    Qsequences1 = STATIC_SYMBOL("SEQUENCES1",AB_package);
    Qtelestubs = STATIC_SYMBOL("TELESTUBS",AB_package);
    Qdialogs = STATIC_SYMBOL("DIALOGS",AB_package);
    Qnative_tw = STATIC_SYMBOL("NATIVE-TW",AB_package);
    Qrings = STATIC_SYMBOL("RINGS",AB_package);
    Qfont_files = STATIC_SYMBOL("FONT-FILES",AB_package);
    Qcheckmemory = STATIC_SYMBOL("CHECKMEMORY",AB_package);
    list_constant_2 = STATIC_CONS(Qcheckmemory,list_constant_1);
    Qtranslate = STATIC_SYMBOL("TRANSLATE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)18L,Qslavic14,Qslavic18,
	    Qslavic24,Qhebrew14,Qhebrew18,Qhebrew24,Qthai14,Qthai18,
	    Qthai24,Qsequences1,Qtelestubs,Qdialogs,Qnative_tw,Qrings,
	    Qfont_files,Qtelewindows,list_constant_2,Qtranslate);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)32L,Qutilities3,Qtimes,
	    Qf_keys,Qos_error,Qplatforms,Qlaunch,Qpathnames,Qfile_parse,
	    Qstreams,Qschedule,Qclocks,Qnetworks,Qint0,Qint1,Qneterror,
	    Qnetevent,Qint2,Qint3a,Qint3b,Qint4,Qwindows1,Qwindows2,
	    Qwindows3,Qwindows3a,Qwindows4,Qimages,Qfonts,Qhb72,Qhm14,
	    Qhm18,Qhm24,list_constant_3);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)32L,list_constant_4,
	    Qsystems,Qdelta,list_constant_5,Qg2_config,Qtw_patches,
	    Qab_loop,Qglbasics,list_constant_6,Qos_foreign,Qbasics,
	    Qos_time,Qos_settings,Qos_memory,Qprimitives,Qcharacters,
	    Qjismap,Qksmap2,Qgbmap,Qgbmapr,Qcharacters2,Qkeyboards,
	    Qkeydefs,Qutilities0,Qutilities1,Qutilities2,Qletters,Qunicode,
	    Qiso2022,Qtranscode,Qiso8859,list_constant_7);
    Qproducts_uninterested_in_this_system = 
	    STATIC_SYMBOL("PRODUCTS-UNINTERESTED-IN-THIS-SYSTEM",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    list_constant_10 = STATIC_CONS(Qgsi,Qnil);
    Qalias = STATIC_SYMBOL("ALIAS",AB_package);
    Qtw = STATIC_SYMBOL("TW",AB_package);
    Qnicknames = STATIC_SYMBOL("NICKNAMES",AB_package);
    list_constant_11 = STATIC_CONS(Qtw,Qnil);
    Qsystems_to_share_binary_files_with = 
	    STATIC_SYMBOL("SYSTEMS-TO-SHARE-BINARY-FILES-WITH",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qgensym_site = STATIC_SYMBOL("GENSYM-SITE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab,Qgensym_site);
    Qsystem_c_files = STATIC_SYMBOL("SYSTEM-C-FILES",AB_package);
    Qtwmain = STATIC_SYMBOL("TWMAIN",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qchestnut = STATIC_SYMBOL("CHESTNUT",AB_package);
    Qchestnut_3 = STATIC_SYMBOL("CHESTNUT-3",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_or,Qchestnut,Qchestnut_3);
    Klocal_directory_namestring = 
	    STATIC_SYMBOL("LOCAL-DIRECTORY-NAMESTRING",Pkeyword);
    string_constant = STATIC_STRING("system-c-local-directory-namestring");
    list_constant_9 = STATIC_LIST((SI_Long)5L,Qtwmain,
	    Koverriding_include_test,list_constant_8,
	    Klocal_directory_namestring,string_constant);
    list_constant_13 = STATIC_CONS(list_constant_9,Qnil);
    list_constant_15 = STATIC_LIST((SI_Long)10L,
	    Qproducts_uninterested_in_this_system,list_constant_10,Qalias,
	    Qtw,Qnicknames,list_constant_11,
	    Qsystems_to_share_binary_files_with,list_constant_12,
	    Qsystem_c_files,list_constant_13);
    temp_1 = SYMBOL_FUNCTION(Qdeclare_system_1);
    APPLY_3(temp_1,Qtelewindows,list_constant_14,list_constant_15);
    if ( !TRUEP(get(Qgsi,Qsystem_binary_pathname_qm,_))) {
	temp = SEVENTH(Bootstrap_information);
	set_get(Qgsi,Qsystem_binary_pathname_qm,temp);
    }
    temp = adjoin(2,Qgsi,All_systems);
    All_systems = temp;
    Qgsi_patches = STATIC_SYMBOL("GSI-PATCHES",AB_package);
    Qgsi_common = STATIC_SYMBOL("GSI-COMMON",AB_package);
    Qrpc_common1 = STATIC_SYMBOL("RPC-COMMON1",AB_package);
    Qrpc_common2 = STATIC_SYMBOL("RPC-COMMON2",AB_package);
    Qrpc_common3 = STATIC_SYMBOL("RPC-COMMON3",AB_package);
    Qgsi_rpc1 = STATIC_SYMBOL("GSI-RPC1",AB_package);
    Qgsi_rpc2 = STATIC_SYMBOL("GSI-RPC2",AB_package);
    list_constant_16 = STATIC_CONS(Qtranslate,Qnil);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)21L,Qos_error,Qlaunch,
	    Qpathnames,Qschedule,Qclocks,Qnetworks,Qint1,Qneterror,
	    Qnetevent,Qint2,Qint3a,Qint3b,Qint4,Qgsi_common,Qrpc_common1,
	    Qrpc_common2,Qrpc_common3,Qgsi,Qgsi_rpc1,Qgsi_rpc2,
	    list_constant_16);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)32L,list_constant_4,
	    Qsystems,Qdelta,list_constant_5,Qg2_config,Qgsi_patches,
	    Qab_loop,Qglbasics,list_constant_6,Qos_foreign,Qbasics,
	    Qos_time,Qos_settings,Qos_memory,Qprimitives,Qcharacters,
	    Qjismap,Qksmap2,Qgbmap,Qgbmapr,Qcharacters2,Qutilities0,
	    Qutilities1,Qutilities2,Qletters,Qunicode,Qiso2022,Qtranscode,
	    Qiso8859,Qutilities3,Qtimes,list_constant_17);
    Qsystem_is_windowless_p = STATIC_SYMBOL("SYSTEM-IS-WINDOWLESS-P",
	    AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qsystem_is_windowless_p,Qt);
    temp_1 = SYMBOL_FUNCTION(Qdeclare_system_1);
    APPLY_3(temp_1,Qgsi,list_constant_18,list_constant_19);
    Qgsi_extension = STATIC_SYMBOL("GSI-EXTENSION",AB_package);
    set_system_version(Qgsi_extension,LIST_2(FIX((SI_Long)2L),
	    FIX((SI_Long)0L)));
    Qfixed_system_key = STATIC_SYMBOL("FIXED-SYSTEM-KEY",AB_package);
    set_get(Qgsi_extension,Qfixed_system_key,CHR('x'));
    Qgw = STATIC_SYMBOL("GW",AB_package);
    if ( !TRUEP(get(Qgw,Qsystem_binary_pathname_qm,_))) {
	temp = SEVENTH(Bootstrap_information);
	set_get(Qgw,Qsystem_binary_pathname_qm,temp);
    }
    temp = adjoin(2,Qgw,All_systems);
    All_systems = temp;
    Qgwutil_1 = STATIC_SYMBOL("GWUTIL-1",AB_package);
    Qbuffer = STATIC_SYMBOL("BUFFER",AB_package);
    Qgthread = STATIC_SYMBOL("GTHREAD",AB_package);
    Qhtmlgen = STATIC_SYMBOL("HTMLGEN",AB_package);
    Qbridge = STATIC_SYMBOL("BRIDGE",AB_package);
    Qweb = STATIC_SYMBOL("WEB",AB_package);
    Qserver = STATIC_SYMBOL("SERVER",AB_package);
    Qweb_gsi = STATIC_SYMBOL("WEB-GSI",AB_package);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)29L,Qpathnames,
	    Qfile_parse,Qstreams,Qschedule,Qclocks,Qnetworks,Qint1,
	    Qneterror,Qnetevent,Qint2,Qint3a,Qint3b,Qint4,Qgsi_common,
	    Qrpc_common1,Qrpc_common2,Qrpc_common3,Qgsi,Qgsi_rpc1,
	    Qgsi_rpc2,Qgwutil_1,Qbuffer,Qgthread,Qhtmlgen,Qbridge,Qweb,
	    Qserver,Qweb_gsi,list_constant_16);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)32L,list_constant_4,
	    Qsystems,Qdelta,Qgsi_patches,Qab_loop,Qglbasics,
	    list_constant_6,Qos_foreign,Qbasics,Qos_time,Qos_settings,
	    Qos_memory,Qprimitives,Qcharacters,Qjismap,Qksmap2,Qgbmap,
	    Qgbmapr,Qcharacters2,Qutilities0,Qutilities1,Qutilities2,
	    Qletters,Qunicode,Qiso2022,Qtranscode,Qiso8859,Qutilities3,
	    Qtimes,Qos_error,Qlaunch,list_constant_20);
    Qweblink = STATIC_SYMBOL("WEBLINK",AB_package);
    list_constant_21 = STATIC_CONS(Qweblink,Qnil);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)5L,Qalias,Qweblink,
	    Qnicknames,list_constant_21,list_constant_19);
    temp_1 = SYMBOL_FUNCTION(Qdeclare_system_1);
    APPLY_3(temp_1,Qgw,list_constant_22,list_constant_23);
    if ( !TRUEP(get(Qab,Qsystem_binary_pathname_qm,_))) {
	temp = SEVENTH(Bootstrap_information);
	set_get(Qab,Qsystem_binary_pathname_qm,temp);
    }
    temp = adjoin(2,Qab,All_systems);
    All_systems = temp;
    Qg2_patches = STATIC_SYMBOL("G2-PATCHES",AB_package);
    Qlisp_server = STATIC_SYMBOL("LISP-SERVER",AB_package);
    list_constant_44 = STATIC_CONS(Qlisp_server,list_constant_1);
    Qalphabet = STATIC_SYMBOL("ALPHABET",AB_package);
    Qtoken = STATIC_SYMBOL("TOKEN",AB_package);
    Qutilities4 = STATIC_SYMBOL("UTILITIES4",AB_package);
    Qpostscript = STATIC_SYMBOL("POSTSCRIPT",AB_package);
    Qmice = STATIC_SYMBOL("MICE",AB_package);
    Qicons = STATIC_SYMBOL("ICONS",AB_package);
    Qsite = STATIC_SYMBOL("SITE",AB_package);
    Kdevelopment = STATIC_SYMBOL("DEVELOPMENT",Pkeyword);
    Koptional_module_p = STATIC_SYMBOL("OPTIONAL-MODULE-P",Pkeyword);
    list_constant_24 = STATIC_CONS(Qt,Qnil);
    list_constant_25 = STATIC_CONS(Koptional_module_p,list_constant_24);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,
	    Koverriding_include_test,Kdevelopment,list_constant_25);
    list_constant_40 = STATIC_CONS(Qsite,list_constant_26);
    Qdoc = STATIC_SYMBOL("DOC",AB_package);
    list_constant_41 = STATIC_CONS(Qdoc,list_constant_26);
    Qparse = STATIC_SYMBOL("PARSE",AB_package);
    Qparse2 = STATIC_SYMBOL("PARSE2",AB_package);
    Qframes1 = STATIC_SYMBOL("FRAMES1",AB_package);
    Qtypes = STATIC_SYMBOL("TYPES",AB_package);
    Qframes2 = STATIC_SYMBOL("FRAMES2",AB_package);
    Qslots = STATIC_SYMBOL("SLOTS",AB_package);
    Qframes2a = STATIC_SYMBOL("FRAMES2A",AB_package);
    Qframes2b = STATIC_SYMBOL("FRAMES2B",AB_package);
    Qframes3 = STATIC_SYMBOL("FRAMES3",AB_package);
    Qframes4 = STATIC_SYMBOL("FRAMES4",AB_package);
    Qframes5 = STATIC_SYMBOL("FRAMES5",AB_package);
    Qpanes = STATIC_SYMBOL("PANES",AB_package);
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    Qentities = STATIC_SYMBOL("ENTITIES",AB_package);
    Qplaces = STATIC_SYMBOL("PLACES",AB_package);
    Qview_def = STATIC_SYMBOL("VIEW-DEF",AB_package);
    Qab_modules = STATIC_SYMBOL("MODULES",AB_package);
    Qab_debug = STATIC_SYMBOL("DEBUG",AB_package);
    Qps_header = STATIC_SYMBOL("PS-HEADER",AB_package);
    Qprinting = STATIC_SYMBOL("PRINTING",AB_package);
    Qconnect1 = STATIC_SYMBOL("CONNECT1",AB_package);
    Qconnect2 = STATIC_SYMBOL("CONNECT2",AB_package);
    Qconnect3 = STATIC_SYMBOL("CONNECT3",AB_package);
    Qconnect3a = STATIC_SYMBOL("CONNECT3A",AB_package);
    Qconnect4 = STATIC_SYMBOL("CONNECT4",AB_package);
    Qconnect5 = STATIC_SYMBOL("CONNECT5",AB_package);
    Qdefinitions = STATIC_SYMBOL("DEFINITIONS",AB_package);
    Qrelations = STATIC_SYMBOL("RELATIONS",AB_package);
    Qformats = STATIC_SYMBOL("FORMATS",AB_package);
    Qsequences2 = STATIC_SYMBOL("SEQUENCES2",AB_package);
    Qsequences3 = STATIC_SYMBOL("SEQUENCES3",AB_package);
    Qboxes = STATIC_SYMBOL("BOXES",AB_package);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Qtables = STATIC_SYMBOL("TABLES",AB_package);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    Qbooks = STATIC_SYMBOL("BOOKS",AB_package);
    Qmenus = STATIC_SYMBOL("MENUS",AB_package);
    Qnew_menus = STATIC_SYMBOL("NEW-MENUS",AB_package);
    Qfacilities = STATIC_SYMBOL("FACILITIES",AB_package);
    Qkfep1 = STATIC_SYMBOL("KFEP1",AB_package);
    Qkfep2 = STATIC_SYMBOL("KFEP2",AB_package);
    Qkfep3 = STATIC_SYMBOL("KFEP3",AB_package);
    Qhfep1 = STATIC_SYMBOL("HFEP1",AB_package);
    Qhfep2 = STATIC_SYMBOL("HFEP2",AB_package);
    Qedit1 = STATIC_SYMBOL("EDIT1",AB_package);
    Qedit2 = STATIC_SYMBOL("EDIT2",AB_package);
    Qmoves = STATIC_SYMBOL("MOVES",AB_package);
    Qrun = STATIC_SYMBOL("RUN",AB_package);
    Qkb_merge = STATIC_SYMBOL("KB-MERGE",AB_package);
    Qkb_load1 = STATIC_SYMBOL("KB-LOAD1",AB_package);
    Qkb_load2 = STATIC_SYMBOL("KB-LOAD2",AB_package);
    Qkb_save1 = STATIC_SYMBOL("KB-SAVE1",AB_package);
    Qkb_save2 = STATIC_SYMBOL("KB-SAVE2",AB_package);
    Qkb_save3 = STATIC_SYMBOL("KB-SAVE3",AB_package);
    Qkb_save4 = STATIC_SYMBOL("KB-SAVE4",AB_package);
    Qwarmboot = STATIC_SYMBOL("WARMBOOT",AB_package);
    Qcheck_kbs = STATIC_SYMBOL("CHECK-KBS",AB_package);
    Qno_macros = STATIC_SYMBOL("NO-MACROS",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qnot,Qno_macros);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qcheck_kbs,
	    Koverriding_include_test,list_constant_27);
    Qcomp_utils = STATIC_SYMBOL("COMP-UTILS",AB_package);
    Qcompile1 = STATIC_SYMBOL("COMPILE1",AB_package);
    Qcompile2 = STATIC_SYMBOL("COMPILE2",AB_package);
    Qsets = STATIC_SYMBOL("SETS",AB_package);
    Qlists = STATIC_SYMBOL("LISTS",AB_package);
    Qarrays = STATIC_SYMBOL("ARRAYS",AB_package);
    Qhash_tables = STATIC_SYMBOL("HASH-TABLES",AB_package);
    Qpriority_queues = STATIC_SYMBOL("PRIORITY-QUEUES",AB_package);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qhistories = STATIC_SYMBOL("HISTORIES",AB_package);
    Qroles = STATIC_SYMBOL("ROLES",AB_package);
    Qrules = STATIC_SYMBOL("RULES",AB_package);
    Qnew_rules = STATIC_SYMBOL("NEW-RULES",AB_package);
    Qchaining = STATIC_SYMBOL("CHAINING",AB_package);
    Qfunctions = STATIC_SYMBOL("FUNCTIONS",AB_package);
    Qcells = STATIC_SYMBOL("CELLS",AB_package);
    Qproc_gram = STATIC_SYMBOL("PROC-GRAM",AB_package);
    Qproc_utils = STATIC_SYMBOL("PROC-UTILS",AB_package);
    Qproc_comp = STATIC_SYMBOL("PROC-COMP",AB_package);
    Qproc_debug = STATIC_SYMBOL("PROC-DEBUG",AB_package);
    Qchange_log = STATIC_SYMBOL("CHANGE-LOG",AB_package);
    Qfile_sysproc = STATIC_SYMBOL("FILE-SYSPROC",AB_package);
    Qmem_sysproc = STATIC_SYMBOL("MEM-SYSPROC",AB_package);
    Qg2_rpc1 = STATIC_SYMBOL("G2-RPC1",AB_package);
    Qg2_rpc2 = STATIC_SYMBOL("G2-RPC2",AB_package);
    Qg2_rpc3 = STATIC_SYMBOL("G2-RPC3",AB_package);
    Qexplain = STATIC_SYMBOL("EXPLAIN",AB_package);
    Qparts = STATIC_SYMBOL("PARTS",AB_package);
    Qdisplays = STATIC_SYMBOL("DISPLAYS",AB_package);
    Qgraphs1 = STATIC_SYMBOL("GRAPHS1",AB_package);
    Qgraphs2 = STATIC_SYMBOL("GRAPHS2",AB_package);
    Qgraph_util = STATIC_SYMBOL("GRAPH-UTIL",AB_package);
    Qgraph_def = STATIC_SYMBOL("GRAPH-DEF",AB_package);
    Qgraphs = STATIC_SYMBOL("GRAPHS",AB_package);
    Qcharts1 = STATIC_SYMBOL("CHARTS1",AB_package);
    Qnew_tables = STATIC_SYMBOL("NEW-TABLES",AB_package);
    Qinstall = STATIC_SYMBOL("INSTALL",AB_package);
    Qfilters = STATIC_SYMBOL("FILTERS",AB_package);
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    Qattr_export = STATIC_SYMBOL("ATTR-EXPORT",AB_package);
    Qcycles = STATIC_SYMBOL("CYCLES",AB_package);
    Qsimulate1 = STATIC_SYMBOL("SIMULATE1",AB_package);
    Qsimulate2 = STATIC_SYMBOL("SIMULATE2",AB_package);
    Qsimulate3 = STATIC_SYMBOL("SIMULATE3",AB_package);
    Qsimulate5 = STATIC_SYMBOL("SIMULATE5",AB_package);
    Qlexer = STATIC_SYMBOL("LEXER",AB_package);
    Qsax = STATIC_SYMBOL("SAX",AB_package);
    Qdom = STATIC_SYMBOL("DOM",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qgrammar0 = STATIC_SYMBOL("GRAMMAR0",AB_package);
    Qgrammar1 = STATIC_SYMBOL("GRAMMAR1",AB_package);
    Qgrammar1a = STATIC_SYMBOL("GRAMMAR1A",AB_package);
    Qgrammar2 = STATIC_SYMBOL("GRAMMAR2",AB_package);
    Qgrammar3 = STATIC_SYMBOL("GRAMMAR3",AB_package);
    Qgrammar4 = STATIC_SYMBOL("GRAMMAR4",AB_package);
    Qgrammar4a = STATIC_SYMBOL("GRAMMAR4A",AB_package);
    Qgrammar5 = STATIC_SYMBOL("GRAMMAR5",AB_package);
    Qgrammar6a = STATIC_SYMBOL("GRAMMAR6A",AB_package);
    Qgrammar6b = STATIC_SYMBOL("GRAMMAR6B",AB_package);
    Qgrammar6c = STATIC_SYMBOL("GRAMMAR6C",AB_package);
    Qgrammar7 = STATIC_SYMBOL("GRAMMAR7",AB_package);
    Qstack_utils = STATIC_SYMBOL("STACK-UTILS",AB_package);
    Qstack_inst = STATIC_SYMBOL("STACK-INST",AB_package);
    Qstack_comp = STATIC_SYMBOL("STACK-COMP",AB_package);
    Qstack_eval1 = STATIC_SYMBOL("STACK-EVAL1",AB_package);
    Qstack_eval2 = STATIC_SYMBOL("STACK-EVAL2",AB_package);
    Qstack_acts = STATIC_SYMBOL("STACK-ACTS",AB_package);
    Qstack_kern = STATIC_SYMBOL("STACK-KERN",AB_package);
    Qproc_inst = STATIC_SYMBOL("PROC-INST",AB_package);
    Qproc_inst2 = STATIC_SYMBOL("PROC-INST2",AB_package);
    Qqueries = STATIC_SYMBOL("QUERIES",AB_package);
    Qg2_foreign = STATIC_SYMBOL("G2-FOREIGN",AB_package);
    Qgfi_stubs = STATIC_SYMBOL("GFI-STUBS",AB_package);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    list_constant_31 = STATIC_CONS(Qgfi,list_constant_25);
    Qg2_gsi = STATIC_SYMBOL("G2-GSI",AB_package);
    list_constant_32 = STATIC_CONS(Qg2_gsi,list_constant_25);
    Qgspan = STATIC_SYMBOL("GSPAN",AB_package);
    list_constant_33 = STATIC_CONS(Qgspan,list_constant_25);
    Qg2ds = STATIC_SYMBOL("G2DS",AB_package);
    Qg2ds_nupec = STATIC_SYMBOL("G2DS-NUPEC",AB_package);
    Qviews = STATIC_SYMBOL("VIEWS",AB_package);
    Qcontrols = STATIC_SYMBOL("CONTROLS",AB_package);
    Qcommands0 = STATIC_SYMBOL("COMMANDS0",AB_package);
    Qcommands1 = STATIC_SYMBOL("COMMANDS1",AB_package);
    Qcommands2 = STATIC_SYMBOL("COMMANDS2",AB_package);
    Qview_msg1 = STATIC_SYMBOL("VIEW-MSG1",AB_package);
    Qview_g2 = STATIC_SYMBOL("VIEW-G2",AB_package);
    Qmedia = STATIC_SYMBOL("MEDIA",AB_package);
    Qtraversals = STATIC_SYMBOL("TRAVERSALS",AB_package);
    Qteleserver = STATIC_SYMBOL("TELESERVER",AB_package);
    Qicons1 = STATIC_SYMBOL("ICONS1",AB_package);
    Qicons2 = STATIC_SYMBOL("ICONS2",AB_package);
    Qicons3 = STATIC_SYMBOL("ICONS3",AB_package);
    Qicons4 = STATIC_SYMBOL("ICONS4",AB_package);
    Qicons5 = STATIC_SYMBOL("ICONS5",AB_package);
    Qinterop = STATIC_SYMBOL("INTEROP",AB_package);
    Qcontinentalextension = STATIC_SYMBOL("CONTINENTALEXTENSION",AB_package);
    Qsmartsignalextension = STATIC_SYMBOL("SMARTSIGNALEXTENSION",AB_package);
    Qsocket1 = STATIC_SYMBOL("SOCKET1",AB_package);
    Qsocket2 = STATIC_SYMBOL("SOCKET2",AB_package);
    Qweb_services = STATIC_SYMBOL("WEB-SERVICES",AB_package);
    Qg2_bpel = STATIC_SYMBOL("G2-BPEL",AB_package);
    Qplayer = STATIC_SYMBOL("PLAYER",AB_package);
    Qrg_report = STATIC_SYMBOL("RG-REPORT",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qrg_report,
	    Koverriding_include_test,Kdevelopment);
    Qg2_meters = STATIC_SYMBOL("G2-METERS",AB_package);
    Qresources = STATIC_SYMBOL("RESOURCES",AB_package);
    Qevents = STATIC_SYMBOL("EVENTS",AB_package);
    Qevents_g2 = STATIC_SYMBOL("EVENTS-G2",AB_package);
    Qjava1 = STATIC_SYMBOL("JAVA1",AB_package);
    Qjava2 = STATIC_SYMBOL("JAVA2",AB_package);
    Qjava3 = STATIC_SYMBOL("JAVA3",AB_package);
    Qsysicons = STATIC_SYMBOL("SYSICONS",AB_package);
    Kno_macros = STATIC_SYMBOL("NO-MACROS",Pkeyword);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnot,Kno_macros);
    list_constant_30 = STATIC_LIST((SI_Long)3L,Qcheckmemory,
	    Koverriding_include_test,list_constant_28);
    Qg2_final = STATIC_SYMBOL("G2-FINAL",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)14L,Qg2_bpel,Qplayer,
	    list_constant_29,Qg2_meters,Qresources,Qevents,Qevents_g2,
	    Qjava1,Qjava2,Qjava3,Qsysicons,list_constant_30,Qtranslate,
	    Qg2_final);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)32L,Qproc_inst2,Qqueries,
	    Qg2_foreign,Qgfi_stubs,Qattributes,list_constant_31,
	    list_constant_32,list_constant_33,Qg2ds,Qg2ds_nupec,Qviews,
	    Qcontrols,Qcommands0,Qcommands1,Qcommands2,Qview_msg1,Qview_g2,
	    Qmedia,Qtraversals,Qteleserver,Qicons1,Qicons2,Qicons3,Qicons4,
	    Qicons5,Qinterop,Qcontinentalextension,Qsmartsignalextension,
	    Qsocket1,Qsocket2,Qweb_services,list_constant_34);
    list_constant_36 = STATIC_LIST_STAR((SI_Long)32L,Qactivate,
	    Qattr_export,Qcycles,Qsimulate1,Qsimulate2,Qsimulate3,
	    Qsimulate5,Qlexer,Qsax,Qdom,Qconclude,Qgrammar0,Qgrammar1,
	    Qgrammar1a,Qgrammar2,Qgrammar3,Qgrammar4,Qgrammar4a,Qgrammar5,
	    Qgrammar6a,Qgrammar6b,Qgrammar6c,Qgrammar7,Qstack_utils,
	    Qstack_inst,Qstack_comp,Qstack_eval1,Qstack_eval2,Qstack_acts,
	    Qstack_kern,Qproc_inst,list_constant_35);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)32L,Qeval,Qrules,
	    Qnew_rules,Qchaining,Qfunctions,Qcells,Qproc_gram,Qrpc_common1,
	    Qrpc_common2,Qrpc_common3,Qproc_utils,Qproc_comp,Qproc_debug,
	    Qchange_log,Qfile_sysproc,Qmem_sysproc,Qg2_rpc1,Qg2_rpc2,
	    Qg2_rpc3,Qexplain,Qparts,Qdisplays,Qgraphs1,Qgraphs2,
	    Qgraph_util,Qgraph_def,Qgraphs,Qcharts1,Qnew_tables,Qinstall,
	    Qfilters,list_constant_36);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)32L,Qkfep1,Qkfep2,Qkfep3,
	    Qhfep1,Qhfep2,Qedit1,Qedit2,Qrings,Qmoves,Qrun,Qkb_merge,
	    Qkb_load1,Qkb_load2,Qkb_save1,Qkb_save2,Qkb_save3,Qkb_save4,
	    Qwarmboot,Qfont_files,list_constant_37,Qcomp_utils,Qcompile1,
	    Qcompile2,Qsets,Qlists,Qarrays,Qhash_tables,Qpriority_queues,
	    Qvariables,Qhistories,Qroles,list_constant_38);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)32L,Qdraw,Qentities,
	    Qplaces,Qview_def,Qab_modules,Qab_debug,Qps_header,Qprinting,
	    Qconnect1,Qconnect2,Qconnect3,Qconnect3a,Qconnect4,Qconnect5,
	    Qdefinitions,Qrelations,Qformats,Qsequences1,Qsequences2,
	    Qsequences3,Qboxes,Qlanguage,Qtables,Qtelestubs,Qdialogs,
	    Qnative_tw,Qworkstation,Qbooks,Qmenus,Qnew_menus,Qfacilities,
	    list_constant_39);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)32L,Qimages,Qmice,Qfonts,
	    Qicons,Qhb72,Qhm14,Qhm18,Qhm24,Qslavic14,Qslavic18,Qslavic24,
	    Qhebrew14,Qhebrew18,Qhebrew24,Qthai14,Qthai18,Qthai24,
	    list_constant_40,list_constant_41,Qparse,Qparse2,Qframes1,
	    Qtypes,Qframes2,Qslots,Qframes2a,Qframes2b,Qframes3,Qframes4,
	    Qframes5,Qpanes,list_constant_42);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)32L,Qiso8859,Qalphabet,
	    Qtoken,Qutilities3,Qutilities4,Qtimes,Qf_keys,Qos_error,
	    Qplatforms,Qlaunch,Qpathnames,Qfile_parse,Qstreams,Qpostscript,
	    Qschedule,Qclocks,Qnetworks,Qint0,Qint1,Qneterror,Qnetevent,
	    Qint2,Qint3a,Qint3b,Qint4,Qgsi_common,Qwindows1,Qwindows2,
	    Qwindows3,Qwindows3a,Qwindows4,list_constant_43);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)32L,list_constant_4,
	    Qsystems,Qdelta,list_constant_5,Qg2_config,Qg2_patches,
	    Qab_loop,Qglbasics,list_constant_6,list_constant_44,
	    Qos_foreign,Qbasics,Qos_time,Qos_settings,Qos_memory,
	    Qprimitives,Qcharacters,Qjismap,Qksmap2,Qgbmap,Qgbmapr,
	    Qcharacters2,Qkeyboards,Qkeydefs,Qutilities0,Qutilities1,
	    Qutilities2,Qletters,Qunicode,Qiso2022,Qtranscode,
	    list_constant_45);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    list_constant_46 = STATIC_CONS(Qg2,Qnil);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)3L,Qtelewindows,
	    Qgensym_site,list_constant_10);
    list_constant_49 = STATIC_LIST((SI_Long)10L,Qalias,Qg2,Qnicknames,
	    list_constant_46,Qsystem_is_windowless_p,Qnil,
	    Qproducts_uninterested_in_this_system,list_constant_10,
	    Qsystems_to_share_binary_files_with,list_constant_47);
    temp_1 = SYMBOL_FUNCTION(Qdeclare_system_1);
    APPLY_3(temp_1,Qab,list_constant_48,list_constant_49);
    if (Development_world_save_p == UNBOUND)
	Development_world_save_p = Nil;
    Qdevelopment_world_save_p = STATIC_SYMBOL("DEVELOPMENT-WORLD-SAVE-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdevelopment_world_save_p,
	    Development_world_save_p);
    string_constant_1 = STATIC_STRING("AB");
    symbol_from_ab_package = Qdevelopment_world_save_p;
    package_of_symbol = SYMBOL_PACKAGE(symbol_from_ab_package);
    if ( !EQ(find_package(string_constant_1),package_of_symbol))
	error((SI_Long)3L,
		"IMPORT-INTO-USER-PACKAGE:\n                      can only import from AB package, but symbol ~s is in the ~s package.",
		symbol_from_ab_package,package_name(package_of_symbol));
    Qls = STATIC_SYMBOL("LS",AB_package);
    if ( !TRUEP(get(Qls,Qsystem_binary_pathname_qm,_))) {
	temp = SEVENTH(Bootstrap_information);
	set_get(Qls,Qsystem_binary_pathname_qm,temp);
    }
    temp = adjoin(2,Qls,All_systems);
    All_systems = temp;
    Qportable_threads = STATIC_SYMBOL("PORTABLE-THREADS",AB_package);
    Qnumbers = STATIC_SYMBOL("NUMBERS",AB_package);
    Qintegrals = STATIC_SYMBOL("INTEGRALS",AB_package);
    Qlicense = STATIC_SYMBOL("LICENSE",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)13L,list_constant_4,Qsystems,
	    Qportable_threads,Qdelta,list_constant_5,Qg2_config,Qab_loop,
	    Qglbasics,list_constant_6,list_constant_44,Qnumbers,Qintegrals,
	    Qlicense);
    Qlicensing_server = STATIC_SYMBOL("LICENSING-SERVER",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)4L,Qalias,Qlicensing_server,
	    Qproducts_uninterested_in_this_system,list_constant_10);
    temp_1 = SYMBOL_FUNCTION(Qdeclare_system_1);
    APPLY_3(temp_1,Qls,list_constant_50,list_constant_51);
}

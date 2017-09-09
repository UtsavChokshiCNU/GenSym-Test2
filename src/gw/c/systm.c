/* systm.c
 * Input file:  systems.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "systm.h"


Object G2int_development_world_save_p = UNBOUND;

static Object Qg2int_ab;           /* ab */

/* LAUNCH-G2-IMAGE */
Object g2int_launch_g2_image()
{
    x_note_fn_call(2,0);
    return g2int_launch_system(Qg2int_ab);
}

static Object Qg2int_telewindows;  /* telewindows */

/* LAUNCH-TELEWINDOWS-IMAGE */
Object g2int_launch_telewindows_image()
{
    x_note_fn_call(2,1);
    return g2int_launch_system(Qg2int_telewindows);
}

void systems_INIT()
{
    Object temp, temp_1;
    Object AB_package, list_constant_14, list_constant_13, Qg2int_gw;
    Object Qg2int_declare_system_1, list_constant_12, list_constant_11;
    Object Qg2int_nicknames, Qg2int_weblink, Qg2int_alias;
    Object Qg2int_system_is_windowless_p, list_constant_10, Qg2int_launch;
    Object Qg2int_os_error, Qg2int_times, Qg2int_utilities3, Qg2int_iso8859;
    Object Qg2int_transcode, Qg2int_iso2022, Qg2int_unicode, Qg2int_letters;
    Object Qg2int_utilities2, Qg2int_utilities1, Qg2int_utilities0;
    Object Qg2int_characters2, Qg2int_gbmapr, Qg2int_gbmap, Qg2int_ksmap2;
    Object Qg2int_jismap, Qg2int_characters, Qg2int_primitives;
    Object Qg2int_os_memory, Qg2int_os_settings, Qg2int_os_time, Qg2int_basics;
    Object Qg2int_os_foreign, list_constant_5, Qg2int_glbasics, Qg2int_loop;
    Object Qg2int_gsi_patches, Qg2int_delta, Qg2int_systems, list_constant_3;
    Object list_constant_9, Qg2int_gsi_rpc2, Qg2int_gsi_rpc1, Qg2int_gsi;
    Object Qg2int_rpc_common3, Qg2int_rpc_common2, Qg2int_rpc_common1;
    Object Qg2int_gsi_common, Qg2int_int4, Qg2int_int3b, Qg2int_int3a;
    Object Qg2int_int2, Qg2int_netevent, Qg2int_neterror, Qg2int_int1;
    Object Qg2int_networks, Qg2int_clocks, Qg2int_schedule, Qg2int_streams;
    Object Qg2int_file_parse, Qg2int_pathnames, list_constant_2;
    Object Qg2int_web_gsi, Qg2int_server, Qg2int_web, Qg2int_bridge;
    Object Qg2int_htmlgen, Qg2int_gthread, Qg2int_buffer, Qg2int_gwutil_1;
    Object Qg2int_system_binary_pathnameqm, Qg2int_fixed_system_key;
    Object Qg2int_gsi_extension, list_constant_8, list_constant_7;
    Object list_constant_6, Qg2int_g2_config, list_constant_4, Qg2int_socket1;
    Object Qg2int_translate, list_constant_1, Qg2int_gldebug, Qg2int_features;
    Object Qg2int_development, Koverriding_include_test;
    Object Qg2int_update_bootstrap_and_reupdate_all_modules;
    Object Klisp_update_function;
    Object Qg2int_compile_bootstrap_and_reboot_all_modules;
    Object Klisp_compile_function, list_constant, Kinclude_test_for_load;
    Object Qg2int_bootstrap, Kdo_not_load_bootstrap;

    x_note_fn_call(2,2);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_system_binary_pathnameqm = 
	    STATIC_SYMBOL("SYSTEM-BINARY-PATHNAME\?",AB_package);
    if ( !TRUEP(get(Qg2int_gsi,Qg2int_system_binary_pathnameqm,_))) {
	temp = SEVENTH(G2int_bootstrap_information);
	set_get(Qg2int_gsi,Qg2int_system_binary_pathnameqm,temp);
    }
    temp = adjoin(2,Qg2int_gsi,G2int_all_systems);
    G2int_all_systems = temp;
    Qg2int_declare_system_1 = STATIC_SYMBOL("DECLARE-SYSTEM-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_declare_system_1,
	    STATIC_FUNCTION(g2int_declare_system_1,NIL,TRUE,2,2));
    Qg2int_bootstrap = STATIC_SYMBOL("BOOTSTRAP",AB_package);
    Kinclude_test_for_load = STATIC_SYMBOL("INCLUDE-TEST-FOR-LOAD",Pkeyword);
    Kdo_not_load_bootstrap = STATIC_SYMBOL("DO-NOT-LOAD-BOOTSTRAP",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,Qnot,Kdo_not_load_bootstrap);
    Klisp_compile_function = STATIC_SYMBOL("LISP-COMPILE-FUNCTION",Pkeyword);
    Qg2int_compile_bootstrap_and_reboot_all_modules = 
	    STATIC_SYMBOL("COMPILE-BOOTSTRAP-AND-REBOOT-ALL-MODULES",
	    AB_package);
    Klisp_update_function = STATIC_SYMBOL("LISP-UPDATE-FUNCTION",Pkeyword);
    Qg2int_update_bootstrap_and_reupdate_all_modules = 
	    STATIC_SYMBOL("UPDATE-BOOTSTRAP-AND-REUPDATE-ALL-MODULES",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)7L,Qg2int_bootstrap,
	    Kinclude_test_for_load,list_constant,Klisp_compile_function,
	    Qg2int_compile_bootstrap_and_reboot_all_modules,
	    Klisp_update_function,
	    Qg2int_update_bootstrap_and_reupdate_all_modules);
    Qg2int_systems = STATIC_SYMBOL("SYSTEMS",AB_package);
    Qg2int_delta = STATIC_SYMBOL("DELTA",AB_package);
    Qg2int_features = STATIC_SYMBOL("FEATURES",AB_package);
    Koverriding_include_test = STATIC_SYMBOL("OVERRIDING-INCLUDE-TEST",
	    Pkeyword);
    Qg2int_development = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Koverriding_include_test,
	    Qg2int_development);
    list_constant_4 = STATIC_CONS(Qg2int_features,list_constant_1);
    Qg2int_g2_config = STATIC_SYMBOL("G2-CONFIG",AB_package);
    Qg2int_gsi_patches = STATIC_SYMBOL("GSI-PATCHES",AB_package);
    Qg2int_loop = STATIC_SYMBOL("LOOP",AB_package);
    Qg2int_glbasics = STATIC_SYMBOL("GLBASICS",AB_package);
    Qg2int_gldebug = STATIC_SYMBOL("GLDEBUG",AB_package);
    list_constant_5 = STATIC_CONS(Qg2int_gldebug,list_constant_1);
    Qg2int_os_foreign = STATIC_SYMBOL("OS-FOREIGN",AB_package);
    Qg2int_basics = STATIC_SYMBOL("BASICS",AB_package);
    Qg2int_os_time = STATIC_SYMBOL("OS-TIME",AB_package);
    Qg2int_os_settings = STATIC_SYMBOL("OS-SETTINGS",AB_package);
    Qg2int_os_memory = STATIC_SYMBOL("OS-MEMORY",AB_package);
    Qg2int_primitives = STATIC_SYMBOL("PRIMITIVES",AB_package);
    Qg2int_characters = STATIC_SYMBOL("CHARACTERS",AB_package);
    Qg2int_jismap = STATIC_SYMBOL("JISMAP",AB_package);
    Qg2int_ksmap2 = STATIC_SYMBOL("KSMAP2",AB_package);
    Qg2int_gbmap = STATIC_SYMBOL("GBMAP",AB_package);
    Qg2int_gbmapr = STATIC_SYMBOL("GBMAPR",AB_package);
    Qg2int_characters2 = STATIC_SYMBOL("CHARACTERS2",AB_package);
    Qg2int_utilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    Qg2int_utilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    Qg2int_letters = STATIC_SYMBOL("LETTERS",AB_package);
    Qg2int_unicode = STATIC_SYMBOL("UNICODE",AB_package);
    Qg2int_iso2022 = STATIC_SYMBOL("ISO2022",AB_package);
    Qg2int_transcode = STATIC_SYMBOL("TRANSCODE",AB_package);
    Qg2int_iso8859 = STATIC_SYMBOL("ISO8859",AB_package);
    Qg2int_utilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Qg2int_times = STATIC_SYMBOL("TIMES",AB_package);
    Qg2int_os_error = STATIC_SYMBOL("OS-ERROR",AB_package);
    Qg2int_launch = STATIC_SYMBOL("LAUNCH",AB_package);
    Qg2int_pathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Qg2int_file_parse = STATIC_SYMBOL("FILE-PARSE",AB_package);
    Qg2int_streams = STATIC_SYMBOL("STREAMS",AB_package);
    Qg2int_schedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    Qg2int_clocks = STATIC_SYMBOL("CLOCKS",AB_package);
    Qg2int_networks = STATIC_SYMBOL("NETWORKS",AB_package);
    Qg2int_int1 = STATIC_SYMBOL("INT1",AB_package);
    Qg2int_neterror = STATIC_SYMBOL("NETERROR",AB_package);
    Qg2int_netevent = STATIC_SYMBOL("NETEVENT",AB_package);
    Qg2int_int2 = STATIC_SYMBOL("INT2",AB_package);
    Qg2int_int3a = STATIC_SYMBOL("INT3A",AB_package);
    Qg2int_int3b = STATIC_SYMBOL("INT3B",AB_package);
    Qg2int_int4 = STATIC_SYMBOL("INT4",AB_package);
    Qg2int_gsi_common = STATIC_SYMBOL("GSI-COMMON",AB_package);
    Qg2int_rpc_common1 = STATIC_SYMBOL("RPC-COMMON1",AB_package);
    Qg2int_rpc_common2 = STATIC_SYMBOL("RPC-COMMON2",AB_package);
    Qg2int_rpc_common3 = STATIC_SYMBOL("RPC-COMMON3",AB_package);
    Qg2int_gsi_rpc1 = STATIC_SYMBOL("GSI-RPC1",AB_package);
    Qg2int_gsi_rpc2 = STATIC_SYMBOL("GSI-RPC2",AB_package);
    Qg2int_socket1 = STATIC_SYMBOL("SOCKET1",AB_package);
    Qg2int_gwutil_1 = STATIC_SYMBOL("GWUTIL-1",AB_package);
    Qg2int_buffer = STATIC_SYMBOL("BUFFER",AB_package);
    Qg2int_gthread = STATIC_SYMBOL("GTHREAD",AB_package);
    Qg2int_htmlgen = STATIC_SYMBOL("HTMLGEN",AB_package);
    Qg2int_bridge = STATIC_SYMBOL("BRIDGE",AB_package);
    Qg2int_web = STATIC_SYMBOL("WEB",AB_package);
    Qg2int_server = STATIC_SYMBOL("SERVER",AB_package);
    Qg2int_web_gsi = STATIC_SYMBOL("WEB-GSI",AB_package);
    Qg2int_translate = STATIC_SYMBOL("TRANSLATE",AB_package);
    list_constant_2 = STATIC_CONS(Qg2int_translate,Qnil);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)32L,Qg2int_os_error,
	    Qg2int_launch,Qg2int_pathnames,Qg2int_file_parse,
	    Qg2int_streams,Qg2int_schedule,Qg2int_clocks,Qg2int_networks,
	    Qg2int_int1,Qg2int_neterror,Qg2int_netevent,Qg2int_int2,
	    Qg2int_int3a,Qg2int_int3b,Qg2int_int4,Qg2int_gsi_common,
	    Qg2int_rpc_common1,Qg2int_rpc_common2,Qg2int_rpc_common3,
	    Qg2int_gsi,Qg2int_gsi_rpc1,Qg2int_gsi_rpc2,Qg2int_socket1,
	    Qg2int_gwutil_1,Qg2int_buffer,Qg2int_gthread,Qg2int_htmlgen,
	    Qg2int_bridge,Qg2int_web,Qg2int_server,Qg2int_web_gsi,
	    list_constant_2);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)32L,list_constant_3,
	    Qg2int_systems,Qg2int_delta,list_constant_4,Qg2int_g2_config,
	    Qg2int_gsi_patches,Qg2int_loop,Qg2int_glbasics,list_constant_5,
	    Qg2int_os_foreign,Qg2int_basics,Qg2int_os_time,
	    Qg2int_os_settings,Qg2int_os_memory,Qg2int_primitives,
	    Qg2int_characters,Qg2int_jismap,Qg2int_ksmap2,Qg2int_gbmap,
	    Qg2int_gbmapr,Qg2int_characters2,Qg2int_utilities0,
	    Qg2int_utilities1,Qg2int_utilities2,Qg2int_letters,
	    Qg2int_unicode,Qg2int_iso2022,Qg2int_transcode,Qg2int_iso8859,
	    Qg2int_utilities3,Qg2int_times,list_constant_6);
    Qg2int_alias = STATIC_SYMBOL("ALIAS",AB_package);
    Qg2int_gw = STATIC_SYMBOL("GW",AB_package);
    Qg2int_system_is_windowless_p = STATIC_SYMBOL("SYSTEM-IS-WINDOWLESS-P",
	    AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)4L,Qg2int_alias,Qg2int_gw,
	    Qg2int_system_is_windowless_p,Qt);
    temp_1 = SYMBOL_FUNCTION(Qg2int_declare_system_1);
    APPLY_3(temp_1,Qg2int_gsi,list_constant_7,list_constant_8);
    Qg2int_gsi_extension = STATIC_SYMBOL("GSI-EXTENSION",AB_package);
    g2int_set_system_version(Qg2int_gsi_extension,LIST_2(FIX((SI_Long)2L),
	    FIX((SI_Long)0L)));
    Qg2int_fixed_system_key = STATIC_SYMBOL("FIXED-SYSTEM-KEY",AB_package);
    set_get(Qg2int_gsi_extension,Qg2int_fixed_system_key,CHR('x'));
    if ( !TRUEP(get(Qg2int_gw,Qg2int_system_binary_pathnameqm,_))) {
	temp = SEVENTH(G2int_bootstrap_information);
	set_get(Qg2int_gw,Qg2int_system_binary_pathnameqm,temp);
    }
    temp = adjoin(2,Qg2int_gw,G2int_all_systems);
    G2int_all_systems = temp;
    list_constant_9 = STATIC_LIST_STAR((SI_Long)9L,Qg2int_gwutil_1,
	    Qg2int_buffer,Qg2int_gthread,Qg2int_htmlgen,Qg2int_bridge,
	    Qg2int_web,Qg2int_server,Qg2int_web_gsi,list_constant_2);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)21L,Qg2int_pathnames,
	    Qg2int_file_parse,Qg2int_streams,Qg2int_schedule,Qg2int_clocks,
	    Qg2int_networks,Qg2int_int1,Qg2int_neterror,Qg2int_netevent,
	    Qg2int_int2,Qg2int_int3a,Qg2int_int3b,Qg2int_int4,
	    Qg2int_gsi_common,Qg2int_rpc_common1,Qg2int_rpc_common2,
	    Qg2int_rpc_common3,Qg2int_gsi,Qg2int_gsi_rpc1,Qg2int_gsi_rpc2,
	    list_constant_9);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)32L,list_constant_3,
	    Qg2int_systems,Qg2int_delta,Qg2int_gsi_patches,Qg2int_loop,
	    Qg2int_glbasics,list_constant_5,Qg2int_os_foreign,
	    Qg2int_basics,Qg2int_os_time,Qg2int_os_settings,
	    Qg2int_os_memory,Qg2int_primitives,Qg2int_characters,
	    Qg2int_jismap,Qg2int_ksmap2,Qg2int_gbmap,Qg2int_gbmapr,
	    Qg2int_characters2,Qg2int_utilities0,Qg2int_utilities1,
	    Qg2int_utilities2,Qg2int_letters,Qg2int_unicode,Qg2int_iso2022,
	    Qg2int_transcode,Qg2int_iso8859,Qg2int_utilities3,Qg2int_times,
	    Qg2int_os_error,Qg2int_launch,list_constant_10);
    Qg2int_weblink = STATIC_SYMBOL("WEBLINK",AB_package);
    Qg2int_nicknames = STATIC_SYMBOL("NICKNAMES",AB_package);
    list_constant_11 = STATIC_CONS(Qg2int_weblink,Qnil);
    list_constant_12 = STATIC_LIST((SI_Long)2L,
	    Qg2int_system_is_windowless_p,Qt);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)5L,Qg2int_alias,
	    Qg2int_weblink,Qg2int_nicknames,list_constant_11,list_constant_12);
    temp_1 = SYMBOL_FUNCTION(Qg2int_declare_system_1);
    APPLY_3(temp_1,Qg2int_gw,list_constant_13,list_constant_14);
    if (G2int_development_world_save_p == UNBOUND)
	G2int_development_world_save_p = Nil;
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
}

/* userinit.c -- Lisp-to-C Translator Top-Level Forms
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"


INCLUDE_LISP_PACKAGE_SELECTIVELY

void userinit()
{
    extern void load_INIT();
    extern void bootstrap_INIT();
    extern void systems_INIT();
    extern void delta_INIT();
    extern void g2_config_INIT();
    extern void gsi_patches_INIT();
    extern void loop_INIT();
    extern void glbasics_INIT();
    extern void os_foreign_INIT();
    extern void basics_INIT();
    extern void os_time_INIT();
    extern void os_settings_INIT();
    extern void os_memory_INIT();
    extern void primitives_INIT();
    extern void characters_INIT();
    extern void jismap_INIT();
    extern void ksmap2_INIT();
    extern void gbmap_INIT();
    extern void gbmapr_INIT();
    extern void characters2_INIT();
    extern void utilities0_INIT();
    extern void utilities1_INIT();
    extern void utilities2_INIT();
    extern void letters_INIT();
    extern void unicode_INIT();
    extern void iso2022_INIT();
    extern void transcode_INIT();
    extern void iso8859_INIT();
    extern void utilities3_INIT();
    extern void times_INIT();
    extern void os_error_INIT();
    extern void launch_INIT();
    extern void pathnames_INIT();
    extern void file_parse_INIT();
    extern void streams_INIT();
    extern void schedule_INIT();
    extern void clocks_INIT();
    extern void networks_INIT();
    extern void int1_INIT();
    extern void neterror_INIT();
    extern void netevent_INIT();
    extern void int2_INIT();
    extern void int3a_INIT();
    extern void int3b_INIT();
    extern void int4_INIT();
    extern void gsi_common_INIT();
    extern void rpc_common1_INIT();
    extern void rpc_common2_INIT();
    extern void rpc_common3_INIT();
    extern void gsi_INIT();
    extern void gsi_rpc1_INIT();
    extern void gsi_rpc2_INIT();
    extern void socket1_INIT();
    extern void gwutil_1_INIT();
    extern void buffer_INIT();
    extern void gthread_INIT();
    extern void htmlgen_INIT();
    extern void bridge_INIT();
    extern void web_INIT();
    extern void server_INIT();
    extern void web_gsi_INIT();
    extern void translate_INIT();

    INIT_names(3878);
    load_INIT();
    bootstrap_INIT();
    systems_INIT();
    delta_INIT();
    g2_config_INIT();
    gsi_patches_INIT();
    loop_INIT();
    glbasics_INIT();
    os_foreign_INIT();
    basics_INIT();
    os_time_INIT();
    os_settings_INIT();
    os_memory_INIT();
    primitives_INIT();
    characters_INIT();
    jismap_INIT();
    ksmap2_INIT();
    gbmap_INIT();
    gbmapr_INIT();
    characters2_INIT();
    utilities0_INIT();
    utilities1_INIT();
    utilities2_INIT();
    letters_INIT();
    unicode_INIT();
    iso2022_INIT();
    transcode_INIT();
    iso8859_INIT();
    utilities3_INIT();
    times_INIT();
    os_error_INIT();
    launch_INIT();
    pathnames_INIT();
    file_parse_INIT();
    streams_INIT();
    schedule_INIT();
    clocks_INIT();
    networks_INIT();
    int1_INIT();
    neterror_INIT();
    netevent_INIT();
    int2_INIT();
    int3a_INIT();
    int3b_INIT();
    int4_INIT();
    gsi_common_INIT();
    rpc_common1_INIT();
    rpc_common2_INIT();
    rpc_common3_INIT();
    gsi_INIT();
    gsi_rpc1_INIT();
    gsi_rpc2_INIT();
    socket1_INIT();
    gwutil_1_INIT();
    buffer_INIT();
    gthread_INIT();
    htmlgen_INIT();
    bridge_INIT();
    web_INIT();
    server_INIT();
    web_gsi_INIT();
    translate_INIT();
}


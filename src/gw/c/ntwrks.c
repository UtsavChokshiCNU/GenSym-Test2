/* ntwrks.c
 * Input file:  networks.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntwrks.h"


/* C-NETWORK-CONNECT */
Object g2int_c_network_connect(network_pathname,host,port,secure_p)
    Object network_pathname, host, port, secure_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(37,0);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(network_pathname);
    gensymed_symbol_1 = g2int_copy_foreign_string_arg_if_appropriate(host);
    gensymed_symbol_2 = g2int_copy_foreign_string_arg_if_appropriate(port);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = network_pathname;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = host;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = port;
    temp = FIX(g2ext_network_connect(temp_1,temp_2,ISTRING(temp),
	    IFIX(secure_p)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	g2int_reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* NETWORK-CONNECT */
Object g2int_network_connect varargs_1(int, n)
{
    Object pathname_1, host, port;
    Object secure_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(37,1);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    port = REQUIRED_ARG_nonrelocating();
    secure_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : G2int_secure_icp_default_p;
    END_ARGS_nonrelocating();
    if (secure_qm &&  !TRUEP(G2int_secure_icp_initialized_p))
	g2int_set_up_secure_icp(0);
    return g2int_c_network_connect(pathname_1,host,port,secure_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

/* C-GET-CONNECTION-PATHNAME */
Object g2int_c_get_connection_pathname(handle,buffer,buffer_size)
    Object handle, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,2);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_connection_pathname(IFIX(handle),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-SET-CONNECTION-PATHNAME */
Object g2int_c_set_connection_pathname(handle,buffer)
    Object handle, buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,3);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_set_connection_pathname(IFIX(handle),ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-GET-NETWORK-LISTENER */
Object g2int_c_get_network_listener(position_1,buffer,buffer_size)
    Object position_1, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,4);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_network_listener(IFIX(position_1),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GETHOSTNAME-1 */
Object g2int_gethostname_1(name,namelen)
    Object name, namelen;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,5);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp = FIX(g2ext_g2_gethostname(ISTRING(temp),IFIX(namelen)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GET-NTH-NETWORK-ADDRESS */
Object g2int_get_nth_network_address(n_1,buffer,buffer_size)
    Object n_1, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(37,6);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_nth_network_address(IFIX(n_1),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object G2int_fixnum_time_units_of_sleep_this_clock_tick = UNBOUND;

Object G2int_record_fixnum_time_units_of_sleep_this_clock_tickqm = UNBOUND;

Object G2int_profiling_enabledqm = UNBOUND;

void networks_INIT()
{
    Object Qg2int_networks, Qg2int_fixnum_time_units_of_sleep_this_clock_tick;
    Object AB_package;

    x_note_fn_call(37,7);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_fixnum_time_units_of_sleep_this_clock_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNITS-OF-SLEEP-THIS-CLOCK-TICK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fixnum_time_units_of_sleep_this_clock_tick,
	    G2int_fixnum_time_units_of_sleep_this_clock_tick);
    Qg2int_networks = STATIC_SYMBOL("NETWORKS",AB_package);
    g2int_record_system_variable(Qg2int_fixnum_time_units_of_sleep_this_clock_tick,
	    Qg2int_networks,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (G2int_record_fixnum_time_units_of_sleep_this_clock_tickqm == UNBOUND)
	G2int_record_fixnum_time_units_of_sleep_this_clock_tickqm = Nil;
    if (G2int_profiling_enabledqm == UNBOUND)
	G2int_profiling_enabledqm = Nil;
}

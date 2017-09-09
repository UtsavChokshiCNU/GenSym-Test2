/* ntwrks.c
 * Input file:  networks.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntwrks.h"


/* C-NETWORK-CONNECT */
Object c_network_connect(network_pathname,host,port,secure_p)
    Object network_pathname, host, port, secure_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(45,0);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(network_pathname);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(host);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(port);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* NETWORK-CONNECT */
Object network_connect varargs_1(int, n)
{
    Object pathname_1, host, port;
    Object secure_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(45,1);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    port = REQUIRED_ARG_nonrelocating();
    secure_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Secure_icp_default_p;
    END_ARGS_nonrelocating();
    if (secure_qm &&  !TRUEP(Secure_icp_initialized_p))
	set_up_secure_icp(0);
    return c_network_connect(pathname_1,host,port,secure_qm ? 
	    FIX((SI_Long)1L) : FIX((SI_Long)0L));
}

/* C-GET-CONNECTION-PATHNAME */
Object c_get_connection_pathname(handle,buffer,buffer_size)
    Object handle, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(45,2);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_connection_pathname(IFIX(handle),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-SET-CONNECTION-PATHNAME */
Object c_set_connection_pathname(handle,buffer)
    Object handle, buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(45,3);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_set_connection_pathname(IFIX(handle),ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-GET-NETWORK-LISTENER */
Object c_get_network_listener(position_1,buffer,buffer_size)
    Object position_1, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(45,4);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_network_listener(IFIX(position_1),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GETHOSTNAME-1 */
Object gethostname_1(name,namelen)
    Object name, namelen;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(45,5);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp = FIX(g2ext_g2_gethostname(ISTRING(temp),IFIX(namelen)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GET-NTH-NETWORK-ADDRESS */
Object get_nth_network_address(n_1,buffer,buffer_size)
    Object n_1, buffer, buffer_size;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(45,6);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_nth_network_address(IFIX(n_1),ISTRING(temp),
	    IFIX(buffer_size)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_units_of_sleep_this_clock_tick, Qfixnum_time_units_of_sleep_this_clock_tick);

DEFINE_VARIABLE_WITH_SYMBOL(Record_fixnum_time_units_of_sleep_this_clock_tick_qm, Qrecord_fixnum_time_units_of_sleep_this_clock_tick_qm);

void networks_INIT()
{
    Object Qnetworks, AB_package;

    x_note_fn_call(45,7);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qfixnum_time_units_of_sleep_this_clock_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNITS-OF-SLEEP-THIS-CLOCK-TICK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfixnum_time_units_of_sleep_this_clock_tick,
	    Fixnum_time_units_of_sleep_this_clock_tick);
    Qnetworks = STATIC_SYMBOL("NETWORKS",AB_package);
    record_system_variable(Qfixnum_time_units_of_sleep_this_clock_tick,
	    Qnetworks,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (Record_fixnum_time_units_of_sleep_this_clock_tick_qm == UNBOUND)
	Record_fixnum_time_units_of_sleep_this_clock_tick_qm = Nil;
    if (Profiling_enabled_qm == UNBOUND)
	Profiling_enabled_qm = Nil;
}

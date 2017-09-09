/* tlsrvr.c
 * Input file:  teleserver.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "tlsrvr.h"


void teleserver_INIT()
{
    Object temp, temp_1;
    Object string_constant_5, string_constant_4, list_constant, Qwindow;
    Object Qcreate_icon_description, string_constant_3, string_constant_2;
    Object string_constant_1, string_constant, AB_package, Qentity;

    x_note_fn_call(231,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qwindow,list_constant);
    string_constant = STATIC_STRING("1l1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_1 = 
	    STATIC_STRING("1l4z8r8u8u834ry834ry01p8w9k3-2y3py1n1p83Jy1mpk1m3--yk1m3--y3ay1mp3ay1p83Oy1mp3ay1mk3py1m3-2y3py1m3--y3ay1x83Jy1mux1m83*Hy1mwr1m3");
    string_constant_2 = 
	    STATIC_STRING("Eyp1m3myp1m83*Hy1m3syr1m3uyx1m3uy3Ny1m83*Hy1m3sy3Ty1m3my3Vy1m3Ey3Vy1m83*Hy1mw3Ty1mu3Ny001o1l8l1l8o1l8z1m83Dy53YySee comment on E");
    string_constant_3 = STATIC_STRING("NTITY class definition00000");
    string_constant_4 = 
	    STATIC_STRING("1n8q1n834ry1l83-+y8t1m8u1p8w9k3-2y3py1n1p83Jy1mpk1m3--yk1m3--y3ay1mp3ay1p83Oy1mp3ay1mk3py1m3-2y3py1m3--y3ay1x83Jy1mux1m83*Hy1mwr");
    string_constant_5 = 
	    STATIC_STRING("1m3Eyp1m3myp1m83*Hy1m3syr1m3uyx1m3uy3Ny1m83*Hy1m3sy3Ty1m3my3Vy1m3Ey3Vy1m83*Hy1mw3Ty1mu3Ny");
    temp = regenerate_optimized_constant(string_constant);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_1,
	    string_constant_2,string_constant_3));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qwindow,list_constant,Nil,temp,Nil,temp_1,
	    list_constant,
	    regenerate_optimized_constant(LIST_2(string_constant_4,
	    string_constant_5)),Nil);
}

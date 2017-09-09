/*
 * stdpkgs.c - Standard Package system initialization
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "kernel.h"
#include "sdefs.h"


/*  Create standard packages.
 *  SI_bind_symbols() binds and inserts only those symbols RTL needs.
 *  When CLOS is ON, SI_initsyms() inserts all symbols specified 
 *  in the translator database.
 */
void SI_INIT_standard_packages()
{
    Pclos = NEW_PACKAGE("CLOS");
    ADD_PACKAGE_NICKNAME(Pclos,"TCLOS");
    ADD_PACKAGE_NICKNAME(Pclos,"TRANSLATOR-CLOS");
    Pcl = NEW_PACKAGE("COMMON-LISP");
    ADD_PACKAGE_NICKNAME(Pcl,"CL");
    ADD_PACKAGE_NICKNAME(Pcl,"LISP");
    ADD_PACKAGE_NICKNAME(Pcl,"TCL");
    ADD_PACKAGE_NICKNAME(Pcl,"TRANSLATOR-COMMON-LISP");
    Ptx = NEW_PACKAGE("TX");
    ADD_PACKAGE_NICKNAME(Ptx,"TRANSLATOR-EXTENSIONS");
    Ptrun = NEW_PACKAGE("TRUN");
    ADD_PACKAGE_NICKNAME(Ptrun,"TRANSLATOR-RUNTIME");
    Pclos_run = NEW_PACKAGE("CLOS-RUN");
    ADD_PACKAGE_NICKNAME(Pclos_run,"TCLOS-RUN");
    ADD_PACKAGE_NICKNAME(Pclos_run,"TRANSLATOR-CLOS-RUNTIME");
    Pclosx = NEW_PACKAGE("CLOSX");
    ADD_PACKAGE_NICKNAME(Pclosx,"CLOS-EXTENSIONS");
    ADD_PACKAGE_NICKNAME(Pclosx,"TCLOSX");
    ADD_PACKAGE_NICKNAME(Pclosx,"TRANSLATOR-CLOS-EXTENSIONS");
    Pkeyword = NEW_PACKAGE("KEYWORD");
    Pcl_user = NEW_PACKAGE("COMMON-LISP-USER");
    ADD_PACKAGE_NICKNAME(Pcl_user,"USER");
    ADD_PACKAGE_NICKNAME(Pcl_user,"CL-USER");
    ADD_PACKAGE_NICKNAME(Pcl_user,"TCL-USER");
    ADD_PACKAGE_USE(Pcl_user,Pcl);
}


/* main.c -- Main file
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


#include "user.h"
main(argc, argv)
    int argc;
    char **argv;
{
    extern Object launch_ab();

    /* Process command line arguments */
    heap_command_line(argc, argv);

    /* Set up Lisp system internals */
    init_top_level();

    /* Application specific initialization */
    userinit();

    /* Calling User Toplevel Function */
    launch_ab();

    lexit(FIX(0));
    /* NOTREACHED */
}

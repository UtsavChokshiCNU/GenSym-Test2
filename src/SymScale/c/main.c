/* main.c -- Main file
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


#include "user.h"
main(argc, argv)
    int argc;
    char **argv;
{
    extern Object launch_ab();

#ifdef PTW32_STATIC_LIB
    pthread_win32_process_attach_np();
#endif

    /* Process command line arguments */
    heap_command_line(argc, argv);

    /* Set up Lisp system internals */
    init_top_level();

    /* Application specific initialization */
    userinit();

    /* Calling User Toplevel Function */
    launch_ab();

#ifdef PTW32_STATIC_LIB
    pthread_win32_process_detach_np();
#endif

    lexit(FIX(0));
    /* NOTREACHED */
}

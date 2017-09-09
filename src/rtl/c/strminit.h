/*
 * strminit.h - the stream system include file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

extern long SI_init_streams_flag;

#define INIT_STREAMS() \
      if (!SI_init_streams_flag) { \
          SI_init_streams_flag = TRUE; \
          SI_INIT_streams(); \
      } else SI_init_streams_flag = SI_init_streams_flag

extern Object *SI_Stream_etypes[];

#if  SI_SUPPORT_CLOS 
#define SI_MAKE_STREAM(stype, dir, etype, closed_p, obj, wrapper) \
    SI_make_stream(stype, dir, etype, closed_p, obj, wrapper)
#else
/* Ignore wrapper arg and pass dummy value to make_stream, which will
 * be ignored.
 */
#define SI_MAKE_STREAM(stype, dir, etype, closed_p, obj, wrapper) \
    SI_make_stream(stype, dir, etype, closed_p, obj, FIX(0))
#endif

/* when CLOS is off, preprocessor eliminates "wrapper" */
#define SI_ALLOC_STREAM(x, stype, dir, etype, closed_p, obj, wrapper)\
    /*short stype, dir, etype, closed_p;*/\
    /*Object obj, wrapper;*/\
\
    x = SI_ALLOC(SI_Stream, STREAM_TYPE, SI_INSTANCE_TAG, SI_UGLY);\
    SI_SET_WRAPPER(x, wrapper);\
    STREAM_INFO(x) = (stype | dir | etype | closed_p);\
    STREAM_CURRPOS(x) = 0;\
    STREAM_OBJ(x) = obj

#define SI_ALLOC_FILE_OBJECT(fobj, file, name)\
    fobj = SI_ALLOC(SI_Cobject, COBJECT_TYPE, SI_INSTANCE_TAG, SI_UGLY);\
    SI_SET_WRAPPER(fobj, SI_WRAPPER_cobject);\
    COBJECT_NAME(fobj) = name;\
    COBJECT_OBJ(fobj) = (char *)file



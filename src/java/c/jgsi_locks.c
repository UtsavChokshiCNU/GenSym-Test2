

#define __GENSYM_NOALIAS__

#include "gsi_main.h"
#include "com_gensym_jgsi_GsiInterface.h"

#ifdef MSVM
extern struct Hcom_gensym_jgsi_GsiInterface* registeredGsiInterface;
#define return_from_call_within_lock(fn_call_with_args)\
        ObjectMonitorEnter(UNHAND_GLOBAL(registeredGsiInterface));\
	retn = fn_call_with_args;\
	ObjectMonitorExit(UNHAND_GLOBAL(registeredGsiInterface));\
	return retn
#define call_within_lock(fn_call_with_args)\
        ObjectMonitorEnter(UNHAND_GLOBAL(registeredGsiInterface));\
	fn_call_with_args;\
	ObjectMonitorExit(UNHAND_GLOBAL(registeredGsiInterface))
#else
extern Classcom_gensym_jgsi_GsiInterface* gsiInterface;
#define return_from_call_within_lock(fn_call_with_args)\
        monitorEnter (obj_monitor(gsiInterface));\
        retn = fn_call_with_args;\
        monitorExit (obj_monitor(gsiInterface));\
        return retn
#define call_within_lock(fn_call_with_args)\
        monitorEnter (obj_monitor(gsiInterface));\
        fn_call_with_args;\
        monitorExit (obj_monitor(gsiInterface))
#endif

#define fn_with_no_arg_returning_value(return_type,new_fn_name,fn_name)\
      return_type new_fn_name() {\
      return_type retn;\
      return_from_call_within_lock(fn_name());\
      }
#define fn_with_one_arg_returning_value(return_type,arg_type0,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0));\
      }

#define fn_with_two_args_returning_value(return_type,arg_type0,arg_type1,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1));\
      }

#define fn_with_three_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1, arg_type2 v2) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1,v2));\
      }

#define fn_with_four_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1,v2,v3));\
      }

#define fn_with_six_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3, arg_type4 v4, arg_type5 v5) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1,v2,v3,v4,v5));\
      }

#define fn_with_seven_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3, arg_type4 v4, arg_type5 v5,arg_type6 v6) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1,v2,v3,v4,v5,v6));\
      }

#define fn_with_eight_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7,new_fn_name,fn_name)\
      return_type new_fn_name(arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3, arg_type4 v4, arg_type5 v5,arg_type6 v6,arg_type v7) {\
      return_type retn;\
      return_from_call_within_lock(fn_name(v0,v1,v2,v3,v4,v5,v6,v7));\
      }

#define void_fn_with_no_arg(new_fn_name,fn_name)\
      void new_fn_name () {\
      call_within_lock(fn_name());\
      }

#define void_fn_with_one_arg(arg_type0,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0) {\
      call_within_lock(fn_name(v0));\
      }

#define void_fn_with_two_args(arg_type0,arg_type1,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1) {\
      call_within_lock(fn_name(v0,v1));\
      }

#define void_fn_with_three_args(arg_type0,arg_type1,arg_type2,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2) {\
      call_within_lock(fn_name(v0,v1,v2));\
      }

#define void_fn_with_four_args(arg_type0,arg_type1,arg_type2,arg_type3,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3) {\
      call_within_lock(fn_name(v0,v1,v2,v3));\
      }

#define void_fn_with_five_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3,arg_type4 v4) {\
      call_within_lock(fn_name(v0,v1,v2,v3,v4));\
      }

#define void_fn_with_six_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3,arg_type4 v4,arg_type5 v5) {\
      call_within_lock(fn_name(v0,v1,v2,v3,v4,v5));\
      }

#define void_fn_with_seven_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3,arg_type4 v4,arg_type5 v5,arg_type6 v6) {\
      call_within_lock(fn_name(v0,v1,v2,v3,v4,v5,v6));\
      }

#define void_fn_with_eight_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7,new_fn_name,fn_name)\
      void new_fn_name (arg_type0 v0, arg_type1 v1, arg_type2 v2, arg_type3 v3,arg_type4 v4,arg_type5 v5,arg_type6 v6,arg_type7 v7) {\
      call_within_lock(fn_name(v0,v1,v2,v3,v4,v5,v6,v7));\
      }

#include "jgsi_locks_generate.h"

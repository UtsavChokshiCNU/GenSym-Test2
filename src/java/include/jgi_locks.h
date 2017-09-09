/**
 *
 * Include this file if you will be using any of the GSI API
 * in a multi-threaded environment
 *
 */


#define fn_with_no_arg_returning_value(return_type,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *);

#define fn_with_one_arg_returning_value(return_type,arg_type0,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0);

#define fn_with_two_args_returning_value(return_type,arg_type0,arg_type1,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1);

#define fn_with_three_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2);

#define fn_with_four_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3);

#define fn_with_five_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3, arg_type4);

#define fn_with_six_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3, arg_type4, arg_type5);

#define fn_with_seven_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3, arg_type4, arg_type5,arg_type6);

#define fn_with_eight_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3, arg_type4, arg_type5,arg_type6,arg_type7);

#define fn_with_nine_args_returning_value(return_type,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7,arg_type8,new_fn_name,fn_name)\
extern return_type new_fn_name(JNIEnv *,arg_type0, arg_type1, arg_type2, arg_type3, arg_type4, arg_type5,arg_type6,arg_type7, arg_type8);


#define void_fn_with_no_arg(new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *);

#define void_fn_with_one_arg(arg_type0,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0);

#define void_fn_with_two_args(arg_type0,arg_type1,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1);

#define void_fn_with_two_args_fn(arg_type0,arg_type1,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,void (*)(),arg_type1);

#define void_fn_with_three_args(arg_type0,arg_type1,arg_type2,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2);

#define void_fn_with_three_args_fn(arg_type0,arg_type1,arg_type2,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,void (*)(),arg_type1,arg_type2);

#define void_fn_with_four_args(arg_type0,arg_type1,arg_type2,arg_type3,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2,arg_type3);

#define void_fn_with_five_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4);

#define void_fn_with_six_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5);

#define void_fn_with_seven_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6);

#define void_fn_with_eight_args(arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7,new_fn_name,fn_name)\
extern void new_fn_name(JNIEnv *,arg_type0,arg_type1,arg_type2,arg_type3,arg_type4,arg_type5,arg_type6,arg_type7);

#include "jgi_locks_generate.h"

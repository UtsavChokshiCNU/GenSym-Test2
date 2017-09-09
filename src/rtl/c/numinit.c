/*
 * numinit.c globals, externals and initializer for numeric functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object STATIC_FLOAT(DOUBLE d);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object STATIC_FLOAT();

#endif


#if defined (__ZTC__)
#include "time.h"
#else
#include "ltime.h"
#endif


Object Most_positive_fixnum = MOST_POSITIVE_FIXNUM;
Object Most_negative_fixnum = MOST_NEGATIVE_FIXNUM;

Object Pi;

Object Most_positive_short_float;
Object Least_positive_normalized_short_float;
Object Least_positive_short_float;
Object Least_negative_short_float;
Object Least_negative_normalized_short_float;
Object Most_negative_short_float;
Object Short_float_epsilon;
Object Short_float_negative_epsilon;

Object Most_positive_single_float;
Object Least_positive_normalized_single_float;
Object Least_positive_single_float;
Object Least_negative_single_float;
Object Least_negative_normalized_single_float;
Object Most_negative_single_float;
Object Single_float_epsilon;
Object Single_float_negative_epsilon;

Object Most_positive_double_float;
Object Least_positive_normalized_double_float;
Object Least_positive_double_float;
Object Least_negative_double_float;
Object Least_negative_normalized_double_float;
Object Most_negative_double_float;
Object Double_float_epsilon;
Object Double_float_negative_epsilon;

Object Most_positive_long_float;
Object Least_positive_normalized_long_float;
Object Least_positive_long_float;
Object Least_negative_long_float;
Object Least_negative_normalized_long_float;
Object Most_negative_long_float;
Object Long_float_epsilon;
Object Long_float_negative_epsilon;

Object Random_state = UNBOUND;

long SI_gc_unsafe = 0;
jmp_buf SI_restart_unsafe;

Object SI_Float_zero;
Object SI_Float_one;
Object SI_Float_negative_one;

void SI_INIT_numbers()
{

#ifdef SUN386i  /* ?? */
  Pi = STATIC_FLOAT(3.141592653589793);
#else
  Pi = STATIC_FLOAT(3.1415926535897932385);
#endif

  SI_Float_zero = STATIC_FLOAT(0.0);
  SI_Float_one = STATIC_FLOAT(1.0);
  SI_Float_negative_one = STATIC_FLOAT(-1.0);


  Most_positive_double_float = STATIC_FLOAT(SI_FLOAT_MAX);


  Least_positive_normalized_double_float = STATIC_FLOAT(SI_FLOAT_NMIN);


  Least_positive_double_float = STATIC_FLOAT(SI_FLOAT_MIN);


  Least_negative_double_float = STATIC_FLOAT(SI_FLOAT_NEG_MIN);


  Least_negative_normalized_double_float = STATIC_FLOAT(SI_FLOAT_NEG_NMIN);


  Most_negative_double_float = STATIC_FLOAT(SI_FLOAT_NEG_MAX);


  Double_float_epsilon = STATIC_FLOAT(SI_FLOAT_EPSILON);


  Double_float_negative_epsilon = STATIC_FLOAT(SI_FLOAT_NEG_EPSILON);


  /* Since we currently only provide one type of float, all the other float
   * constants are just equivalent to the corresponding constants for doubles.
   */


  Most_positive_short_float = Most_positive_double_float;


  Least_positive_normalized_short_float =
    Least_positive_normalized_double_float;


  Least_positive_short_float = Least_positive_double_float;


  Least_negative_short_float = Least_negative_double_float;


  Least_negative_normalized_short_float =
    Least_negative_normalized_double_float;


  Most_negative_short_float = Most_negative_double_float;


  Short_float_epsilon = Double_float_epsilon;


  Short_float_negative_epsilon = Double_float_negative_epsilon;



  Most_positive_single_float = Most_positive_double_float;


  Least_positive_normalized_single_float =
    Least_positive_normalized_double_float;


  Least_positive_single_float = Least_positive_double_float;


  Least_negative_single_float = Least_negative_double_float;


  Least_negative_normalized_single_float =
    Least_negative_normalized_double_float;


  Most_negative_single_float = Most_negative_double_float;


  Single_float_epsilon = Double_float_epsilon;


  Single_float_negative_epsilon = Double_float_negative_epsilon;



  Most_positive_long_float = Most_positive_double_float;


  Least_positive_normalized_long_float =
    Least_positive_normalized_double_float;


  Least_positive_long_float = Least_positive_double_float;


  Least_negative_long_float = Least_negative_double_float;


  Least_negative_normalized_long_float =




    Least_negative_normalized_double_float;


  Most_negative_long_float = Most_negative_double_float;


  Long_float_epsilon = Double_float_epsilon;


  Long_float_negative_epsilon = Double_float_negative_epsilon;
}

static time_t make_random_seed()
{
#ifdef USE_GETTIMEOFDAY
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec;
#else
#ifdef __ZTC__
     time_t ntime;
     time(&ntime);
     return ntime;
#else
    struct timeb tp;  /* time_t time;  unsigned short millitm; */
    ftime(&tp);  /* returns status only on some systems */
    return tp.time;
#endif
#endif
}

unsigned long SI_get_internal_msec()
{
#ifdef USE_GETTIMEOFDAY
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_usec/ (1000000L / IINTERNAL_TIME_UNITS_PER_SECOND);
#else
#ifdef __ZTC__
     time_t ntime;
     time(&ntime);
     return ntime;
#else
    struct timeb tp;  /* time_t time;  unsigned short millitm; */
    ftime(&tp);  /* returns status only on some systems */
    return tp.millitm * (IINTERNAL_TIME_UNITS_PER_SECOND / 1000L);
#endif
#endif
}

Object make_random_state(state)
    Object state;
{
    Declare_local_temp;
    Object newstate = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(state, newstate);

    newstate =
	SI_ALLOC(SI_Random_state, RANDOM_STATE_TYPE, SI_INSTANCE_TAG, SI_UGLY);
    SI_SET_WRAPPER(newstate, SI_WRAPPER_random_state);

    if (!SUPPLIEDP(state) || state == NIL) {
	if (Random_state == UNBOUND)
	    RANDOM_SEED(newstate) = 123; /* Pretty random, huh */
	else
	    RANDOM_SEED(newstate) = RANDOM_SEED(Random_state);
    } else if (RANDOM_STATE_P(state))
	RANDOM_SEED(newstate) = RANDOM_SEED(state);
    else   if (state == T) {
	RANDOM_SEED(newstate) = (unsigned)make_random_seed;
    }
    else{
	error(2, "make_random_state: invalid or unimplemented argument - ~s",
	      state);
	/*NOTREACHED*/
    }
    RESTORE_STACK();
    return VALUES_1(newstate);
}
    

SI_Long SI_igcd (n1, n2)
    SI_Long n1, n2;
{
    SI_Long temp, r;

    if (n1 < 0) n1 = -n1;
    if (n2 < 0) n2 = -n2;
    if (n1<n2) {
	temp = n1;
	n1 = n2;
	n2 = temp;
    }
    if (n2 == 0) return n1;
    while (r = n1%n2) {
        n1 = n2;
        n2 = r;
    }
    return n2;
}





#include "svargs.h"

/***************************************************************************
 *
 * Macro definitions for do_format_1 function
 * 
 * do_format_1 is a format string parser
 *
 * Control flow: case dispatch with recursion on nested
 * control expressions
 * 
 * State of computation:
 *   do_format_1 (lstr, args_ptr, arg_n, arg_i) 
 * assumes that arg_n variables always are placed somewhere
 * onto the stack starting from args_ptr; actual processing should
 * starts from variable number arg_i;
 * lstr is a control string that should be GC-nonmovable;
 *
 *
 * do_format_1 uses global variable Work that is an output buffer.
 *
 * Control state continuation: do_format_1 can pass all or several
 * state items recursively [example: FA_WITH_CONTROL() ]. Also
 * it returns the number of 'next' argument, which can be used
 * to continue
 *
 *
 * Shortcomings: the correct way to parse  control strings is not
 * implemented yet. The current approach is an approximation and
 * can give wrong results in specific nested situations
 *
 *
 **************************************************************************/


#define Declare_fa_frame  Declare_stack_pointer

/* spread list onto the stack and put  the number of arguments
   and initial index value (zero) onto the top */
#define FA_SPREAD_ARG(arg) \
    M_BEGIN { \
	Object a; long i = 0;\
	a = arg; \
	     for (; TRUEP(a); a = M_CDR(a), i++)\
		  STACK_PUSH(M_CAR(a)); \
	          STACK_PUSH(FIX(i)); \
		  STACK_PUSH(FIX(0)); \
   } M_END
    
#define OLD_STACK()  SI_old_stack_marker
    
#define FA_INITIAL_SIZE_OF_FRAME_COVER  2
#define FA_RETURNED_SIZE_OF_FRAME_COVER 2
    
#define FLUSH_FRAME()
#define FA_ARG_NUMBER() IFIX(STACK_REF(- FA_INITIAL_SIZE_OF_FRAME_COVER))
#define FA_ARG_INDEX() \
    IFIX(STACK_REF(1 - FA_INITIAL_SIZE_OF_FRAME_COVER))    

#define FA_NEXT()  (args_ptr[arg_i++].object)
#define FA_THIS()  (args_ptr[arg_i-1].object)
#define FA_UNGET()  (arg_i--)
    
#define FA_ARG() \
    ((arg_i < arg_n) \
     ? FA_NEXT() \
     : FA_ERROR(), FA_THIS())

#define FA_ERROR()  error(1, "format: not enough arguments")

#define FA_USING_CONTROL(str) do_format_1(str, args_ptr, arg_n, arg_i)

#define FA_MORE_ARGS_P() (STACK_REF(-1L) < STACK_REF(-2L))

/***************************************************************************
 *
 *  Prefix Parameters
 *
 ***************************************************************************/

#define PREFIX_DEFAULT   -1L
#define NUMBER_OF_PREFIXES  8L

#define INIT_PREFIXES(tabl) \
{long i=NUMBER_OF_PREFIXES;while(i--)tabl[i]=PREFIX_DEFAULT;}

#define SET_DEFAULT(p,dflt)\
(p = ( p == PREFIX_DEFAULT) ? dflt : p)

/* the following macro names have meaning <directive>_<prefix> */

#define T_COLNUM         pp[0]
#define T_COLREL         pp[0]
#define T_COLINC         pp[1]

/* for bith ~A and ~S */
#define S_MINCOL         pp[0]
#define S_COLINC         pp[1]
#define S_MINPAD         pp[2]
#define S_PADCHAR        pp[3]

#define D_MINCOL         pp[0]
#define D_PADCHAR        pp[1]
#define D_COMMACHAR      pp[1]
#define D_COMMAINTERVAL  pp[1]

#define R_RADIX          pp[0]
#define R_MINCOL         pp[1]
#define R_PADCHAR        pp[2]
#define R_COMMACHAR      pp[3]

#define B_MINCOL         pp[0]
#define B_PADCHAR        pp[1]
#define B_COMMACHAR      pp[1]

#define O_MINCOL         pp[0]
#define O_PADCHAR        pp[1]
#define O_COMMACHAR      pp[1]

#define F_W              pp[0]
#define F_D              pp[1]
#define F_K              pp[2]
#define F_OVERFLOWCHAR   pp[3]
#define F_PADCHAR        pp[4]

/* for both ~E and ~G */
#define E_W              pp[0]
#define E_D              pp[1]
#define E_K              pp[2]
#define E_E              pp[3]
#define E_OVERFLOWCHAR   pp[4]
#define E_PADCHAR        pp[5]
#define E_EXPONENTCHAR   pp[6]

#define DLR_D            pp[0]
#define DLR_N            pp[1]
#define DLR_W            pp[2]
#define DLR_PADCHAR      pp[3]

/***************************************************************************
 *
 * format() invocation
 *
 ***************************************************************************/

#define FA_PARSE(str, arg_ptr, arg_n) \
    M_BEGIN \
    FA_COVER(arg_n); \
    do_format_1(str,  arg_ptr); \
    FA_UNCOVER(); \
    M_END
    
#define BEGIN_FA_LIST(list) \
    SAVE_STACK(); \
    FA_SPREAD_ARG(list)

#define END_FA_LIST()  RESTORE_STACK()
#define FA_ARGS()      OLD_STACK()

/***************************************************************************
 *
 * misc
 * 
 ***************************************************************************/

/*
 do not checks nesting; broken in the following situations:
(1)  nested ~[... ~], each with ~; and argth are > 0
(2)  if ~~; situation occures during the search
*/
#define SKIP_OVER(sptr, ch) \
    while (*sptr) \
      if (*sptr++ == '~') \
        if (*sptr++  == ch) \
             break

#define FA_CONTROL_ARG(buff) \
    strcpy(buff, ISTRING(FA_ARG()))








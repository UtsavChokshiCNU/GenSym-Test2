

/****************************************************************************
 *
 *   This set of macros provides simulation of
 *   the standard varargs protocol by means of the Lisp stack.
 *
 *   The advantage is that arguments are GC safe
 *
 *   EXAMPLE:

Object foo (n, va_alist)
    int n;
    va_dcl
{
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object str;

    VA_SIZE(n);
    VA_START(ap);
    str = VA_ARG(ap, Object);
    VA_END(ap);

    return VALUES_1(FIX(1L)); 
}

 *
 ****************************************************************************/

typedef char * CH_PTR;
typedef SI_Stack_item * Stack_item_ptr;


#define M_BEGIN if (TRUE) 
#define M_END  else FALSE

/* essentially va_stack bottom pointer */
#define Declare_va_stack_pointer    SI_Stack_item *SI_Va_stack_marker
#define VA_LIST                 Stack_item_ptr

/*  ap:  lisp stack pointer 
 *  assumes that n is the name of the first argument of the vararg function */
#define VA_START(ap,last) \
  M_BEGIN \
    { \
    VA_SAVE_STACK(ap); \
    SPREAD_VA(n, (ap), last); \
    } \
  M_END

#define VA_SAVE_STACK(ap) \
    SI_Va_stack_marker = Stack; \
    ap = Stack

#define VA_END(ap)      (Stack = SI_Va_stack_marker)

/* !! */
#define VA_ARG(ap, t)  (*(t *)(ap)++)

#define VA_UNGET(ap)   (ap--)

#define VA_SIZE(number) (SI_Va_stack_frame_size = (number))

#define SPREAD_VA(nargs, rest, last)  \
    {long _nargs = (nargs);                 \
        long _rest_index;                      \
        va_list _ap;                          \
        SI_va_start(_ap,last);                        \
        rest = Stack;               \
        Stack += _nargs;                      \
        for(_rest_index = 0; _rest_index < _nargs; ++_rest_index) \
            rest[_rest_index].object                 \
                =  va_arg(_ap, Object);        \
        va_end(_ap);                          \
    }










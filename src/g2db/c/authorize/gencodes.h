#ifndef __GENCODES_H
#define __GENCODES_H

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#define OK 1L
#define NOT_OK -1L

/* prototypes to avoid build warnings */
extern void  gb_raise_to_uppercase ();
extern void  remove_whitespace();
extern short verify_char_dates();
extern short calc_universal_dates();
extern void  major_version();
extern long  weighted_value();
extern void  f();
extern void  g();

#endif



/***************************************************************************
 *
 * Multiple values
 *
 **************************************************************************/

extern TLS int Values_count;


#ifdef SI_SUPPORT_MF
#define valuesr values_list
#define valuesn values
#endif

#define VALUES_0()		(Values_count=0, NIL)
#define VALUES_1(a)		(Values_count=1, (a))
#define VALUES_2(a,b)		(Values_count=2, Values[0]=(b), (a))
#define VALUES_3(a,b,c)		(Values_count=3, Values[0]=(b), \
				 Values[1]=(c), (a))
#define VALUES_4(a,b,c,d)	(Values_count=4, Values[0]=(b), \
				 Values[1]=(c), Values[2]=(d), (a))
#define VALUES_5(a,b,c,d,e)	(Values_count=5, Values[0]=(b), \
				 Values[1]=(c), Values[2]=(d), \
				 Values[3]=(e), (a))
#define VALUES_6(a,b,c,d,e,f)	(Values_count=6, Values[0]=(b), \
				 Values[1]=(c), Values[2]=(d), \
				 Values[3]=(e), Values[4]=(f), (a))
#define VALUES_7(a,b,c,d,e,f,g)	(Values_count=7, Values[0]=(b), \
				 Values[1]=(c), Values[2]=(d), \
				 Values[3]=(e), Values[4]=(f), \
				 Values[5]=(g), (a))
#define VALUES_8(a,b,c,d,e,f,g,h) (Values_count=8, Values[0]=(b), \
				   Values[1]=(c), Values[2]=(d), \
				   Values[3]=(e), Values[4]=(f), \
				   Values[5]=(g), Values[6]=(h), (a))
#define VALUES_9(a,b,c,d,e,f,g,h,i) (Values_count=9, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), (a))
#define VALUES_10(a,b,c,d,e,f,g,h,i,j) (Values_count=10, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), (a))
#define VALUES_11(a,b,c,d,e,f,g,h,i,j,k) (Values_count=11, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), \
				     Values[9]=(k), (a))
#define VALUES_12(a,b,c,d,e,f,g,h,i,j,k,l) (Values_count=12, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), \
				     Values[9]=(k), Values[10]=(l), (a))
#define VALUES_13(a,b,c,d,e,f,g,h,i,j,k,l,m) (Values_count=13, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), \
				     Values[9]=(k), Values[10]=(l), \
				     Values[11]=(m), (a))
#define VALUES_14(a,b,c,d,e,f,g,h,i,j,k,l,m,n) \
                                    (Values_count=14, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), \
				     Values[9]=(k), Values[10]=(l), \
				     Values[11]=(m), Values[12]=(n), (a))
#define VALUES_15(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) \
                                    (Values_count=15, Values[0]=(b), \
				     Values[1]=(c), Values[2]=(d), \
				     Values[3]=(e), Values[4]=(f), \
				     Values[5]=(g), Values[6]=(h), \
				     Values[7]=(i), Values[8]=(j), \
				     Values[9]=(k), Values[10]=(l), \
				     Values[11]=(m), Values[12]=(n), \
				     Values[13]=(o), (a))
#define LIST_VALUES(a)           (Values_count > 0 ? list_values(a) : NIL)


#if SI_SUPPORT_SF

/* Get a specific value from the buffer, testing to see whether there are
 * enough values and returning NIL if not.
 */

#define NTH_VALUE(n, firstval) \
    ((Values_count > (n)) \
     ? ((n) == 0 ? firstval : Values[(n) - 1]) : NIL)

#define MV_LIST(e)	list_values(e)

#endif /* SI_SUPPORT_SF */

/* MULTIPLE-VALUE-SETQ */

/*
 * MF translator requires MVS_n macros to return a value.
 * SF translator does not. we define a new symbol here to conditionalize
 * this on, since SI_SUPPORT_SF and SI_SUPPORT_MF must currently both be 1.
 */

#ifdef SI_OLD_MVS

#ifdef RETURN_MULTIPLE_VALUES

#define MVS_0(r)		(SI_First_value=(r))
#define MVS_1(r,a)		((a)=SI_First_value=(r))
#define MVS_2(r,a,b)		((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 SI_First_value)
#define MVS_3(r,a,b,c)		((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 SI_First_value)
#define MVS_4(r,a,b,c,d)	((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 SI_First_value)
#define MVS_5(r,a,b,c,d,e)	((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 ((e)=Values_count > 4 ? Values[3] : NIL), \
				 SI_First_value)
#define MVS_6(r,a,b,c,d,e,f)	((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 ((e)=Values_count > 4 ? Values[3] : NIL), \
				 ((f)=Values_count > 5 ? Values[4] : NIL), \
				 SI_First_value)
#define MVS_7(r,a,b,c,d,e,f,g)	((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 ((e)=Values_count > 4 ? Values[3] : NIL), \
				 ((f)=Values_count > 5 ? Values[4] : NIL), \
				 ((g)=Values_count > 6 ? Values[5] : NIL), \
				 SI_First_value)
#define MVS_8(r,a,b,c,d,e,f,g,h) ((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 ((e)=Values_count > 4 ? Values[3] : NIL), \
				 ((f)=Values_count > 5 ? Values[4] : NIL), \
				 ((g)=Values_count > 6 ? Values[5] : NIL), \
				 ((h)=Values_count > 7 ? Values[6] : NIL), \
				  SI_First_value)
#define MVS_9(r,a,b,c,d,e,f,g,h,i) ((a)=SI_First_value=(r), \
				 ((b)=Values_count > 1 ? Values[0] : NIL), \
				 ((c)=Values_count > 2 ? Values[1] : NIL), \
				 ((d)=Values_count > 3 ? Values[2] : NIL), \
				 ((e)=Values_count > 4 ? Values[3] : NIL), \
				 ((f)=Values_count > 5 ? Values[4] : NIL), \
				 ((g)=Values_count > 6 ? Values[5] : NIL), \
				 ((h)=Values_count > 7 ? Values[6] : NIL), \
				 ((i)=Values_count > 8 ? Values[7] : NIL), \
				    SI_First_value)
#else
#define MVS_0(r)		(r)
#define MVS_1(r,a)		((a)=(r))
#define MVS_2(r,a,b)		((a)=(r), (b)=Values[0], a)
#define MVS_3(r,a,b,c)		((a)=(r), (b)=Values[0], (c)=Values[1], a)
#define MVS_4(r,a,b,c,d)	((a)=(r), \
				 (b)=Values[0], (c)=Values[1], \
				 (d)=Values[2], a)
#define MVS_5(r,a,b,c,d,e)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 a)
#define MVS_6(r,a,b,c,d,e,f)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 a)
#define MVS_7(r,a,b,c,d,e,f,g)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 a)
#define MVS_8(r,a,b,c,d,e,f,g,h) ((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 (h)=Values[6], \
				  a)
#define MVS_9(r,a,b,c,d,e,f,g,h,i) ((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 (h)=Values[6], \
				 (i)=Values[7], \
				    a)
#endif /* RETURN_MULTIPLE_VALUES */

#else

#ifdef RETURN_MULTIPLE_VALUES
#define MVS_0(r)	((void)(r))
#define MVS_1(r,a)	((void)((a)=(r)))

#define MVS_2(r,a,b)	((void)((a)=(r), \
				((b) = Values_count > 1 ? Values[0] : NIL)))

/* For more than two values, dispatch on the values count to set any unsupplied
 * entries in the values buffer that are needed to NIL.
 */

//#define MVS_3(r,a,b,c) \
//    do { \
//      (a) = (r); \
//      switch (Values_count) { \
//	case 0: case 1: Values[0] = NIL; \
//	case 2: Values[1] = NIL; \
//      } \
//      (b) = Values[0]; (c) = Values[1]; \
//    } while (0)

#define MVS_3(r,a,b,c)						\
    do {									\
		(a) = (r);							\
		if( Values_count >= 3 ) {			\
			(c) = Values[1];				\
			(b) = Values[0];				\
		} else if( Values_count == 2 ) {	\
			(c) = NIL;						\
			(b) = Values[0];				\
		} else {							\
			(c) = NIL;						\
			(b) = NIL;						\
		}									\
    } while (0)
      
#define MVS_4(r,a,b,c,d)					\
    do {									\
		(a) = (r);							\
		if( Values_count >= 4 ) {			\
			(d) = Values[2];				\
			(c) = Values[1];				\
			(b) = Values[0];				\
		} else if( Values_count >= 2 ) {	\
			if( Values_count == 3 ) {		\
				(d) = NIL;					\
				(c) = Values[1];			\
				(b) = Values[0];			\
			} else {						\
				(d) = NIL;					\
				(c) = NIL;					\
				(b) = Values[0];			\
			}								\
		} else {							\
			(d) = NIL;						\
			(c) = NIL;						\
			(b) = NIL;						\
		}									\
    } while (0)
      
#define MVS_5(r,a,b,c,d,e)					\
    do {									\
		(a) = (r);							\
		if( Values_count >= 5 ) {			\
			(e) = Values[3];				\
			(d) = Values[2];				\
			(c) = Values[1];				\
			(b) = Values[0];				\
		} else if( Values_count >= 3 ) {	\
			if( Values_count == 4 ) {		\
				(e) = NIL;					\
				(d) = Values[2];			\
				(c) = Values[1];			\
				(b) = Values[0];			\
			} else {						\
				(e) = NIL;					\
				(d) = NIL;					\
				(c) = Values[1];			\
				(b) = Values[0];			\
			}								\
		} else if( Values_count == 2 ) {	\
			(e) = NIL;						\
			(d) = NIL;						\
			(c) = NIL;						\
			(b) = Values[0];				\
		} else {							\
			(e) = NIL;						\
			(d) = NIL;						\
			(c) = NIL;						\
			(b) = NIL;						\
		}									\
    } while (0)

#define MVS_6(r,a,b,c,d,e,f)			\
    do {								\
		(a) = (r);						\
		if( Values_count >= 6 ) {		\
			(f) = Values[4];			\
			(e) = Values[3];			\
			(d) = Values[2];			\
			(c) = Values[1];			\
			(b) = Values[0];			\
			break;						\
		}								\
		(f) = NIL;						\
		if( Values_count >= 4 ) {		\
			(d) = Values[2];			\
			(c) = Values[1];			\
			(b) = Values[0];			\
			if( Values_count == 5 ) {	\
				(e) = Values[3];		\
			} else {					\
				(e) = NIL;				\
			}							\
			break;						\
		}								\
		(e) = NIL;						\
		(d) = NIL;						\
		if( Values_count >= 2 ) {		\
			(b) = Values[0];			\
			if( Values_count == 3 ) {	\
				(c) = Values[1];		\
			} else {					\
				(c) = NIL;				\
			}							\
			break;						\
		}								\
		(c) = NIL;						\
		(b) = NIL;						\
    } while (0)

#define MVS_7(r,a,b,c,d,e,f,g) \
    do { \
      (a) = (r); \
      switch (Values_count) { \
	case 0: case 1: Values[0] = NIL; \
	case 2: Values[1] = NIL; \
	case 3: Values[2] = NIL; \
	case 4: Values[3] = NIL; \
	case 5: Values[4] = NIL; \
	case 6: Values[5] = NIL; \
      } \
      (b) = Values[0]; (c) = Values[1]; (d) = Values[2]; \
      (e) = Values[3]; (f) = Values[4]; (g) = Values[5]; \
    } while (0)

#define MVS_8(r,a,b,c,d,e,f,g,h) \
    do { \
      (a) = (r); \
      switch (Values_count) { \
	case 0: case 1: Values[0] = NIL; \
	case 2: Values[1] = NIL; \
	case 3: Values[2] = NIL; \
	case 4: Values[3] = NIL; \
	case 5: Values[4] = NIL; \
	case 6: Values[5] = NIL; \
	case 7: Values[6] = NIL; \
      } \
      (b) = Values[0]; (c) = Values[1]; (d) = Values[2]; \
      (e) = Values[3]; (f) = Values[4]; (g) = Values[5]; \
      (h) = Values[6]; \
    } while (0)
      
#define MVS_9(r,a,b,c,d,e,f,g,h,i) \
    do { \
      (a) = (r); \
      switch (Values_count) { \
	case 0: case 1: Values[0] = NIL; \
	case 2: Values[1] = NIL; \
	case 3: Values[2] = NIL; \
	case 4: Values[3] = NIL; \
	case 5: Values[4] = NIL; \
	case 6: Values[5] = NIL; \
	case 7: Values[6] = NIL; \
	case 8: Values[7] = NIL; \
      } \
      (b) = Values[0]; (c) = Values[1]; (d) = Values[2]; \
      (e) = Values[3]; (f) = Values[4]; (g) = Values[5]; \
      (h) = Values[6]; (i) = Values[7]; \
    } while (0)

#define MVS_10(r,a,b,c,d,e,f,g,h,i,j) \
    do { \
      (a) = (r); \
      switch (Values_count) { \
	case 0: case 1: Values[0] = NIL; \
	case 2: Values[1] = NIL; \
	case 3: Values[2] = NIL; \
	case 4: Values[3] = NIL; \
	case 5: Values[4] = NIL; \
	case 6: Values[5] = NIL; \
	case 7: Values[6] = NIL; \
	case 8: Values[7] = NIL; \
	case 9: Values[8] = NIL; \
      } \
      (b) = Values[0]; (c) = Values[1]; (d) = Values[2]; \
      (e) = Values[3]; (f) = Values[4]; (g) = Values[5]; \
      (h) = Values[6]; (i) = Values[7]; (j) = Values[8]; \
    } while (0)

#define MVSR(n,a,b,c,d,e,f,g,h,i,j) \
    do { \
      switch (Values_count < (n) ? 0 : Values_count-(n)) { \
	case 0: Values[n-1] = NIL; \
	case 1: Values[n+0] = NIL; \
	case 2: Values[n+1] = NIL; \
	case 3: Values[n+2] = NIL; \
	case 4: Values[n+3] = NIL; \
	case 5: Values[n+4] = NIL; \
	case 6: Values[n+5] = NIL; \
	case 7: Values[n+6] = NIL; \
	case 8: Values[n+7] = NIL; \
	case 9: Values[n+8] = NIL; \
      } \
      (a) = Values[n-1]; (b) = Values[n+0]; (c) = Values[n+1]; \
      (d) = Values[n+2]; (e) = Values[n+3]; (f) = Values[n+4]; \
      (g) = Values[n+5]; (h) = Values[n+6]; (i) = Values[n+7]; \
      (j) = Values[n+8]; \
    } while (0)

#else
#define MVS_0(r)		(r)
#define MVS_1(r,a)		((a)=(r))
#define MVS_2(r,a,b)		((a)=(r), (b)=Values[0])
#define MVS_3(r,a,b,c)		((a)=(r), (b)=Values[0], (c)=Values[1])
#define MVS_4(r,a,b,c,d)	((a)=(r), \
				 (b)=Values[0], (c)=Values[1], \
				 (d)=Values[2])
#define MVS_5(r,a,b,c,d,e)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3])
#define MVS_6(r,a,b,c,d,e,f)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4])
#define MVS_7(r,a,b,c,d,e,f,g)	((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5])
#define MVS_8(r,a,b,c,d,e,f,g,h) ((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 (h)=Values[6])
#define MVS_9(r,a,b,c,d,e,f,g,h,i) ((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 (h)=Values[6], \
				 (i)=Values[7])
#define MVS_10(r,a,b,c,d,e,f,g,h,i,j) ((a)=(r), \
				 (b)=Values[0], \
				 (c)=Values[1], \
				 (d)=Values[2], \
				 (e)=Values[3], \
				 (f)=Values[4], \
				 (g)=Values[5], \
				 (h)=Values[6], \
				 (i)=Values[7], \
				 (j)=Values[8])
#define MVSR(n,a,b,c,d,e,f,g,h,i,j) ((a)=Values[n-1], \
				 (b)=Values[n], \
				 (c)=Values[n+1], \
				 (d)=Values[n+2], \
				 (e)=Values[n+3], \
				 (f)=Values[n+4], \
				 (g)=Values[n+5], \
				 (h)=Values[n+6], \
				 (i)=Values[n+7], \
				 (j)=Values[n+8])
#endif /* RETURN_MULTIPLE_VALUES */

#endif /* SI_OLD_MVS */

/* These are used by catch/throw */

#ifdef RETURN_MULTIPLE_VALUES
#define SAVE_VALUES(form) \
    (STACK_PUSH(form), \
     (Values_count == 1L ? \
      (STACK_PUSH(FIX(1)), 0) : \
      (SI_save_values(), 0)))

#define POP_VALUES()  (Stack -= IFIX(STACK_REF(-1L)) + 1L)

#if SI_SUPPORT_SF
#define SAVE_MORE_VALUES(form)		SI_save_more_values(form)
#endif

#define RESTORE_VALUES() \
    (STACK_REF(-1L) == FIX(1L) ? \
     (Values_count = 1L, Stack -= 2L, STACK_REF(0)) : \
     SI_restore_values())
#else
#define SAVE_VALUES(form) STACK_PUSH(form) /* ? */
#define RESTORE_VALUES()  STACK_POP()
#endif

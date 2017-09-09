
extern Object (*SI_long_to_bignum)(/*SI_Long l*/);
extern enum bignum_comparison
    (*SI_bignum_compare)(/*bignum_type x, bignum_type y*/);

extern void SI_INIT_new_bignums();

#ifdef __STDC__

typedef void * bignum_procedure_context;
extern bignum_type bignum_make_zero (void);
extern bignum_type bignum_make_one (int negative_p);
extern int bignum_equal_p (bignum_type, bignum_type);
extern enum bignum_comparison bignum_test (bignum_type);
extern enum bignum_comparison bignum_compare (bignum_type, bignum_type);
extern bignum_type bignum_add (bignum_type, bignum_type);
extern bignum_type bignum_subtract (bignum_type, bignum_type);
extern bignum_type bignum_negate (bignum_type);
extern bignum_type bignum_multiply (bignum_type, bignum_type);
extern int bignum_divide
  (bignum_type numerator, bignum_type denominator,
   bignum_type * quotient, bignum_type * remainder);
extern bignum_type bignum_quotient (bignum_type, bignum_type);
extern bignum_type bignum_remainder (bignum_type, bignum_type);
#ifndef BIGNUM_NO_ULONG
extern bignum_type long_to_bignum (SI_Long);
extern SI_Long bignum_to_long (bignum_type);
extern bignum_type unsigned_long_to_bignum (SI_Ulong);
extern SI_Ulong bignum_to_unsigned_long (bignum_type);
#endif /* not BIGNUM_NO_ULONG */
extern bignum_type double_to_bignum (double);
extern double bignum_to_double (bignum_type);
extern int bignum_fits_in_word_p
  (bignum_type, long word_length, int twos_complement_p);
#ifdef CHESTNUT
extern SI_Long bignum_length_in_bits (bignum_type);
#else
extern bignum_type bignum_length_in_bits (bignum_type);
#endif
extern bignum_type bignum_length_upper_limit (void);
extern bignum_type digit_stream_to_bignum
  (unsigned int n_digits,
   unsigned int (*producer) (), bignum_procedure_context context,
   unsigned int radix, int negative_p);
extern void bignum_to_digit_stream
  (bignum_type, unsigned int radix,
   void (*consumer) (), bignum_procedure_context context);
extern long bignum_max_digit_stream_radix (void);

/* Added these for Chestnut */
extern int bignum_oddp (bignum_type);
extern bignum_type bignum_ash (bignum_type, Object);
extern bignum_type bignum_lognot (bignum_type);
extern bignum_type bignum_logand (bignum_type, bignum_type);
extern bignum_type bignum_logior (bignum_type, bignum_type);
extern bignum_type bignum_logxor (bignum_type, bignum_type);
extern bignum_type bignum_logeqv (bignum_type, bignum_type);
extern Object bignum_logcount (bignum_type);
extern SI_Long bignum_integer_length (bignum_type);


#else /* not __STDC__ */

typedef char * bignum_procedure_context;
extern bignum_type bignum_make_zero ();
extern bignum_type bignum_make_one ();
extern int bignum_equal_p ();
extern enum bignum_comparison bignum_test ();
extern enum bignum_comparison bignum_compare ();
extern bignum_type bignum_add ();
extern bignum_type bignum_subtract ();
extern bignum_type bignum_negate ();
extern bignum_type bignum_multiply ();
extern int bignum_divide ();
extern bignum_type bignum_quotient ();
extern bignum_type bignum_remainder ();
#ifndef BIGNUM_NO_ULONG
extern bignum_type long_to_bignum ();
extern SI_Long bignum_to_long ();
extern bignum_type unsigned_long_to_bignum ();
extern SI_Ulong bignum_to_unsigned_long ();
#endif /* not BIGNUM_NO_ULONG */
extern bignum_type double_to_bignum ();
extern double bignum_to_double ();
extern int bignum_fits_in_word_p ();
#ifdef CHESTNUT
extern SI_Long bignum_length_in_bits ();
#else
extern bignum_type bignum_length_in_bits ();
#endif
extern bignum_type bignum_length_upper_limit ();
extern bignum_type digit_stream_to_bignum ();
extern void bignum_to_digit_stream ();
extern long bignum_max_digit_stream_radix ();

/* Added these for Chestnut */
extern int bignum_oddp ();
extern bignum_type bignum_ash ();
extern bignum_type bignum_lognot ();
extern bignum_type bignum_logand ();
extern bignum_type bignum_logior ();
extern bignum_type bignum_logxor ();
extern bignum_type bignum_logeqv ();
extern Object bignum_logcount ();
extern SI_Long bignum_integer_length ();

#endif /* __STDC__ */

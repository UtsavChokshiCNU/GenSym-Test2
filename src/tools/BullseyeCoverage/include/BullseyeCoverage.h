/* $Id: BullseyeCoverage.h.in 9843 2009-03-26 22:13:53Z Steve Cornett $
 * Copyright (c) Bullseye Testing Technology
 */
#undef _BullseyeCoverage
#define _BullseyeCoverage 71338

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define _Linkage __cdecl
#else
	#define _Linkage
#endif

int _Linkage cov_check(void);
unsigned _Linkage cov_eventCount(void);
int _Linkage cov_file(const char*);
int _Linkage cov_reset(void);
void _Linkage cov_term(void);
int _Linkage cov_write(void);

#undef _Linkage

#if defined(__cplusplus)
}
#endif

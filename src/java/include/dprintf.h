#include "shared.h"

#ifndef __DPRINTF__
#define __DPRINTF__


#ifdef WIN32

#define ASSERT(exp) ((exp) ? (void)0 : __AssertMsg((LPSTR)(#exp), (LPSTR)__FILE__, __LINE__))

#define OLEDBGASSERTDATA
#define OLEDBGDATA_MAIN(szPrefix)
#define OLEDBGDATA
#define OLEDBG_BEGIN2(lpsz)
#define OLEDBG_END2

#define ALWAYS    0
#define DERROR   10
#define PROGRESS 20
#define DETAIL   30
#define DUMP     40
#define TOFILE   50


CONTAINAPI void cdecl jprintf(JNIEnv *, short, LPSTR lpFormat, ...);
CONTAINAPI void cdecl dprintf(short, LPSTR lpFormat, ...);
CONTAINAPI void print_iid_info(JNIEnv *, short, char *, const struct _GUID *);
CONTAINAPI void ClearDebugHistory();
CONTAINAPI short DebugLevel();

void __AssertMsg(LPSTR exp ,LPSTR file, int line);


#endif /* WIN32 */

#endif


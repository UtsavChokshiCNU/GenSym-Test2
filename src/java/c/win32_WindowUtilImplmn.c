
#include <windows.h>
#include <stdio.h>

void com_gensym_util_WindowUtil_pRaise0(struct Hcom_gensym_util_WindowUtil *pT,
				       long hWnd) {

  BOOL res =BringWindowToTop ((HWND)hWnd);
  printf (" --> BringWindowToTop returned %d\n", res);
  fflush (stdout);
}


extern void com_gensym_util_WindowUtil_pRaise(struct Hcom_gensym_util_WindowUtil *pT,struct Hjava_lang_Object *obj) {}

extern void com_gensym_util_WindowUtil_psetSaveUnder(struct Hcom_gensym_util_WindowUtil *pT,struct Hjava_lang_Object *obj) {}

extern void com_gensym_util_WindowUtil_pMove(struct Hcom_gensym_util_WindowUtil *pT,struct Hjava_lang_Object *obj,long x,long y) {}

extern void com_gensym_util_WindowUtil_pUpdateCoordinates(struct Hcom_gensym_util_WindowUtil *pT,struct Hjava_awt_Component *obj,long x,long y) {}

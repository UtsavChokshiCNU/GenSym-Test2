
#include <X11/Intrinsic.h>
#include "com_gensym_ntw_util_WindowUtil.h"
#include "sun_awt_motif_MComponentPeer.h"
#include "java_awt_Component.h"


struct ComponentData {
    Widget	widget;
    int 	repaintPending;
    int		x1, y1, x2, y2;
};

#define PDATA(T, x) ((struct T *)(unhand(x)->pData))

void awt_winutil_raise (Widget);
void awt_winutil_move (Widget, long, long);

void com_gensym_ntw_util_WindowUtil_pRaise (struct Hcom_gensym_ntw_util_WindowUtil *null,
					    struct Hjava_lang_Object *hObj)
{
  struct Hsun_awt_motif_MComponentPeer* hthis = (struct Hsun_awt_motif_MComponentPeer*)hObj;
  struct ComponentData *cdata;
  
  cdata = PDATA(ComponentData, hthis);
  awt_winutil_raise (cdata->widget);
}

void awt_winutil_raise (Widget w)
{
  Display *display;
  Window window;
  
  if (w == 0) {
    SignalError(0, JAVAPKG "NullPointerException", 0);
    return;
  }
  display = XtDisplay (w);
  window  = XtWindow  (w);
  XRaiseWindow (display, window);
}

void com_gensym_ntw_util_WindowUtil_pMove (struct Hcom_gensym_ntw_util_WindowUtil *null,
					   struct Hjava_lang_Object *hObj,
					   long newX, long newY)
{
  struct Hsun_awt_motif_MComponentPeer* hthis = (struct Hsun_awt_motif_MComponentPeer*)hObj;
  struct ComponentData *cdata;
  
  cdata = PDATA(ComponentData, hthis);
  awt_winutil_move (cdata->widget, newX, newY);
}

void awt_winutil_move (Widget w, long newX, long newY)
{
  Display *display;
  Window window;
  
  if (w == 0) {
    SignalError(0, JAVAPKG "NullPointerException", 0);
    return;
  }
  display = XtDisplay (w);
  window  = XtWindow  (w);
  XMoveWindow (display, window, newX, newY);
}

void com_gensym_ntw_util_WindowUtil_pUpdateCoordinates (struct Hcom_gensym_ntw_util_WindowUtil *null,
							struct Hjava_awt_Component* hthis,
							long newX, long newY)
{
  Classjava_awt_Component* this = unhand(hthis);
  this->x = newX;
  this->y = newY;
}

void awt_util_save_under (Widget w)
{
  Display *display;
  Window window;
  XSetWindowAttributes setwinattr;
  unsigned long valuemask;
  
  if (w == 0) {
    SignalError(0, JAVAPKG "NullPointerException", 0);
    return;
  }
  display = XtDisplay (w);
  window  = XtWindow  (w);
  setwinattr.save_under = 1;
  valuemask = CWSaveUnder;
  XChangeWindowAttributes (display, window, valuemask, &setwinattr);
}

void com_gensym_ntw_util_WindowUtil_psetSaveUnder (struct Hcom_gensym_ntw_util_WindowUtil *null,
						   struct Hjava_lang_Object* hObj)
{
  struct Hsun_awt_motif_MComponentPeer* hthis = (struct Hsun_awt_motif_MComponentPeer*)hObj;
  struct ComponentData *cdata;
  
  cdata = PDATA(ComponentData, hthis);
  awt_util_save_under (cdata->widget);
}

void com_gensym_ntw_util_WindowUtil_pRaise0 (struct Hcom_gensym_ntw_util_WindowUtil *null,
					     long x)
{
  /* Do nothing */
}

#include "dialogs.h"

/*  */
/*  Menu ids */
/*  */

#define IDM_OPEN            0x0100
#define IDM_SAVE            0x0101
#define IDM_SAVEAS          0x0102
#define IDM_PRINT           0x0103
#define IDM_PRINTSETUP      0x0104
#define IDM_EXIT            0x0105
#define IDM_NEW             0x0106

#define IDM_CUT             0x0200
#define IDM_COPY            0x0201
#define IDM_PASTE           0x0203
#define IDM_INSERT_OBJECT   0x0204
#define IDM_BROWSE_LIBRARY  0x0205
#define IDM_DISPATCH_METHOD 0x0206
#define IDM_DELETE          0x0207
#define IDM_DISPATCH_DLL    0x0208

#define IDM_DEBUG0          0x0800
#define IDM_DEBUG1          (IDM_DEBUG0+1)
#define IDM_DEBUG2          (IDM_DEBUG0+2)
#define IDM_DEBUG3          (IDM_DEBUG0+3)
#define IDM_DEBUG4          (IDM_DEBUG0+4)
#define IDM_DEBUGCLEAR      (IDM_DEBUG0+5)

#define IDM_HELPCONTENTS    0x0900
#define IDM_ABOUT           0x0901

#define SB_WIDTH            5       /*  width of size border */

#define SB_HIT_NONE         0
#define SB_HIT_TOP          1
#define SB_HIT_LEFT         2
#define SB_HIT_BOTTOM       3
#define SB_HIT_RIGHT        4


#define OLEUI_SHADE_FULLRECT        1
#define OLEUI_SHADE_BORDERIN        2
#define OLEUI_SHADE_BORDEROUT       3


#ifdef WIN32
typedef struct _NTWOBJECT *PNTWOBJ;

typedef struct _NTWOBJECT {
  DWORD dwMagic;                  /*  magic number */
  PNTWOBJ pNext;                  /*  pointer to the next one */
  RECT rc;                        /*  container rectangle */
  TRUTH_VALUE bObjOpenInWindow;          /*  TRUE if open in server window */
  PCOMOBJ comObj;
} NTWOBJ;
#endif

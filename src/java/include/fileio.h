#ifdef WIN32

#include <windows.h>
#include <shellapi.h>   /*  needed for HKEY */
#include <commdlg.h>    /*  needed for LPPRINTDLG */

#ifndef RC_INVOKED /*  OLE headers nuke the resource compiler */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#include <ole2.h>
#include <oledlg.h>
#endif /*  RC_INVOKED */

#include <string.h>
#include <dlgs.h>           /* For fileopen dlg; standard include */
#include <docobj.h>
#include <olectl.h>

#if DBG
#include <assert.h>
#endif

#ifndef RC_INVOKED
#include <dos.h>        /*  needed for filetime */
#endif  /* RC_INVOKED */

/*  */
/*  Structure used in the INFO stream */
/*  */

typedef struct _FILEHEADER {
    DWORD dwMagic;              /*  magic number */
    int iWidth;                 /*  width of the window */
    int iHeight;                /*  height of the window */
    DWORD dwNextObject;         /*  next object number */
} FILEHEADER, FAR *PFILEHEADER;



/*  */
/*  Names of streams in the OLE2 structured storage model we use */
/*  Note the leading '\3' character which marks them as private */
/*  so they won't be touched by any object handler if we use them */
/*  in a sub-storage used to save an object's data. */
/*  */

#define INFO_STREAM     "\3INFO"
#define OBJLIST_STREAM  "\3OBJLIST"

/*  <dwFlags> for PromptForFileName() */
#define PFFN_OPENFILE        0x0001    /*  prompt to open a file */
#define PFFN_SAVEFILE        0x0002    /*  prompt to save a file */
#define PFFN_SHOWDEFAULT     0x0004    /*  init. show what's in <achFileName> */
#define PFFN_OVERWRITEPROMPT 0x0008    /*  prompt the user about overwriting */
#define PFFN_UPPERCASE       0x0010    /*  make the name uppercase */

#define FILEMAGIC MAKEFOURCC('B','U','K','T')
#define FILEEXT "BKT"

/*  Create Obj flags */

#define AS_TEMPORARY        0x00000001
#define FROM_STORAGE        0x00000002
#define FROM_DATA           0x00000004
#define FROM_CLASSID        0x00000008


#endif /* WIN32 */

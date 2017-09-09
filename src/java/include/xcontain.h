#ifdef WIN32

#include <windows.h>
#include <windowsx.h>
#include <stdarg.h>  
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

#if DBG
#include <assert.h>
#endif

#ifndef RC_INVOKED
#include <dos.h>        /*  needed for filetime */
#endif  /* RC_INVOKED */

#define AXB_TITLEBAR_HEIGHT 15
#define AXB_BORDER_HEIGHT 5
#define AXB_BORDER_WIDTH  5


#if !defined(__cplusplus) && !defined( __TURBOC__)
#define NONAMELESSUNION     /*  use strict ANSI standard (for DVOBJ.H) */
#endif

#define UNICODEOLE32


#define UtDupStringA2W       UtDupString


#define MAXFORMATS 10       /*  max number of formats */

/*  String table defines... */
#define  IDS_OLESTDNOCREATEFILE   700
#define  IDS_OLESTDNOOPENFILE     701
#define  IDS_OLESTDDISKFULL       702



#ifdef WIN32S
#if !defined(UNICODEOLE32)
#pragma message("Compiling for 32bit ANSI Ole!\n");
#endif
#endif



#ifndef UNICODEOLE32

#define OLESTRCPY                lstrcpy
#define OLESTRCAT                lstrcat
#define OLESTRLEN                lstrlen
#define OLESTRCMP                lstrcmp
#define OLESTRCMPI               lstrcmpi
#define DeleteFile_AW            DeleteFile
#define _lopen_AW                _lopen
#define _lcreat_AW               _lcreat
#define GlobalAddAtom_AW         GlobalAddAtom
#define GlobalGetAtomName_AW     GlobalGetAtomName
#define RegOpenKey_AW            RegOpenKey

#define W2A(w, a, cb)     lstrcpy (a, w)
#define A2W(a, w, cb)     lstrcpy (w, a)

#define FREELOCALSTRING(p)
#define MAKE_STR_LOCAL_COPYW2A(s, l)  l = s
#define MAKE_STR_LOCAL_COPYA2W(s, l)  l = s

/*  IPersistFile ansi translation */

#define IPersistFile_LoadA(pf, file, mode) (pf)->Load(file, mode)

/*  IMoniker ansi translation */

#define IMoniker_GetDisplayNameA(pm, p1, p2, p3) (pm)->GetDisplayName(p1,p2,p3)

#define CreateFileMonikerA   CreateFileMoniker

#else  /*  UNICODEOLE32 */


#define OLESTRCAT                lstrcatW
#define OLESTRCMP                lstrcmpW
#define OLESTRCMPI               lstrcmpiW
#define DeleteFile_AW            DeleteFileW
#define _lopen_AW                _lopenW
#define _lcreat_AW               _lcreatW
#define GlobalAddAtom_AW         GlobalAddAtomW
#define GlobalGetAtomName_AW     GlobalGetAtomNameW
#define RegOpenKey_AW            RegOpenKeyW


#define StringFromCLSID2A(rclsid, lpsz, cbMax) \
    StringFromGUID2A(rclsid, lpsz, cbMax)

#define StringFromIID2A(riid, lpsz, cbMax) \
    StringFromGUID2A(riid, lpsz, cbMax)

#endif /*  !UNICODEOLE32 */


/*************************************************************************
** DEBUG ASSERTION ROUTINES
*************************************************************************/

#if DBG
#define FnAssert(lpstrExpr, lpstrMsg, lpstrFileName, iLine)     \
        (_assert(lpstrMsg ? lpstrMsg : lpstrExpr,               \
                 lpstrFileName,                                 \
                 iLine), NOERROR)
#endif /* DBG */

/*  BEGINING OF OLD OLESTD.H FILE */
#if defined( __TURBOC__ ) || defined( WIN32 )
#define _based(a)
#endif



/*
 * Some C interface declaration stuff
 */

#if ! defined(__cplusplus)
typedef struct tagINTERFACEIMPL {
      IUnknownVtbl FAR*       lpVtbl;
      LPVOID                  lpBack;
      int                     cRef;   /*  interface specific ref count. */
} INTERFACEIMPL, FAR* LPINTERFACEIMPL;

#define INIT_INTERFACEIMPL(lpIFace, pVtbl, pBack)   \
      ((lpIFace)->lpVtbl = pVtbl, \
         ((LPINTERFACEIMPL)(lpIFace))->lpBack = (LPVOID)pBack,   \
         ((LPINTERFACEIMPL)(lpIFace))->cRef = 0  \
      )

#if defined( _DEBUG )
#define OleDbgQueryInterfaceMethod(lpUnk)   \
      ((lpUnk) != NULL ? ((LPINTERFACEIMPL)(lpUnk))->cRef++ : 0)
#define OleDbgAddRefMethod(lpThis, iface)   \
      ((LPINTERFACEIMPL)(lpThis))->cRef++

#if _DEBUGLEVEL >= 2
#define OleDbgReleaseMethod(lpThis, iface) \
      (--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
         OleDbgOut("\t" iface "* RELEASED (cRef == 0)\r\n"),1 : \
          (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
            ( \
               DebugBreak(), \
               OleDbgOut(  \
                  "\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
            ),1 : \
            1)

#else       /*  if _DEBUGLEVEL < 2 */
#define OleDbgReleaseMethod(lpThis, iface) \
      (--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
         1 : \
          (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
            ( \
               OleDbgOut(  \
                  "\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
      ),1 : \
            1)

#endif      /*  if _DEBUGLEVEL < 2 */

#else       /*  ! defined (_DEBUG) */

#define OleDbgQueryInterfaceMethod(lpUnk)
#define OleDbgAddRefMethod(lpThis, iface)
#define OleDbgReleaseMethod(lpThis, iface)

#endif      /*  if defined( _DEBUG ) */

#endif      /*  ! defined(__cplusplus) */

/*
 * Some docfiles stuff
 */

#define STGM_DFRALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_DENY_WRITE)
#define STGM_DFALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE)
#define STGM_SALL (STGM_READWRITE | STGM_SHARE_EXCLUSIVE)

/*
 * Some Concurrency stuff
 */

/* standard Delay (in msec) to wait before retrying an LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDRETRYDELAY    (DWORD)5000

/* Cancel the pending outgoing LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDCANCELRETRY   (DWORD)-1

/*
 * Some Icon support stuff.
 *
 * The following API's are now OBSOLETE because equivalent API's have been
 * added to the OLE2.DLL library
 *      GetIconOfFile       superceeded by OleGetIconOfFile
 *      GetIconOfClass      superceeded by OleGetIconOfClass
 *
 * The following macros are defined for backward compatibility with previous
 * versions of the OLE2UI library. It is recommended that the new Ole* API's
 * should be used instead.
 */
#define GetIconOfFile(hInst, lpszFileName, fUseFileAsLabel) \
   OleGetIconOfFile(lpszFileName, fUseFileAsLabel)

#define GetIconOfClass(hInst, rclsid, lpszLabel, fUseTypeAsLabel) \
   OleGetIconOfClass(rclsid, lpszLabel, fUseTypeAsLabel)

/*
 * Some Clipboard Copy/Paste & Drag/Drop support stuff
 */

/* Macro to set all FormatEtc fields */
#define SETFORMATETC(fe, cf, asp, td, med, li)   \
   ((fe).cfFormat=cf, \
    (fe).dwAspect=asp, \
    (fe).ptd=td, \
    (fe).tymed=med, \
    (fe).lindex=li)

/* Macro to set interesting FormatEtc fields defaulting the others. */
#define SETDEFAULTFORMATETC(fe, cf, med)  \
   ((fe).cfFormat=cf, \
    (fe).dwAspect=DVASPECT_CONTENT, \
    (fe).ptd=NULL, \
    (fe).tymed=med, \
    (fe).lindex=-1)

/*  Macro to test if two FormatEtc structures are an exact match */
#define IsEqualFORMATETC(fe1, fe2)  \
   (OleStdCompareFormatEtc(&(fe1), &(fe2))==0)

/*  REVIEW: these need to be added to OLE2.H */
#if !defined( DD_DEFSCROLLINTERVAL )
#define DD_DEFSCROLLINTERVAL    50
#endif

#if !defined( DD_DEFDRAGDELAY )
#define DD_DEFDRAGDELAY         200
#endif

#if !defined( DD_DEFDRAGMINDIST )
#define DD_DEFDRAGMINDIST       2
#endif


/* OleStdGetDropEffect
** -------------------
**
** Convert a keyboard state into a DROPEFFECT.
**
** returns the DROPEFFECT value derived from the key state.
**    the following is the standard interpretation:
**          no modifier -- Default Drop     (NULL is returned)
**          CTRL        -- DROPEFFECT_COPY
**          SHIFT       -- DROPEFFECT_MOVE
**          CTRL-SHIFT  -- DROPEFFECT_LINK
**
**    Default Drop: this depends on the type of the target application.
**    this is re-interpretable by each target application. a typical
**    interpretation is if the drag is local to the same document
**    (which is source of the drag) then a MOVE operation is
**    performed. if the drag is not local, then a COPY operation is
**    performed.
*/
#define OleStdGetDropEffect(grfKeyState)    \
   ( (grfKeyState & MK_CONTROL) ?          \
      ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_LINK : DROPEFFECT_COPY ) :  \
      ( (grfKeyState & MK_SHIFT) ? DROPEFFECT_MOVE : 0 ) )


#define OLESTDDROP_NONE         0
#define OLESTDDROP_DEFAULT      1
#define OLESTDDROP_NONDEFAULT   2


/*
 * Some misc stuff
 */

#define EMBEDDINGFLAG "Embedding"     /*  Cmd line switch for launching a srvr */

#define HIMETRIC_PER_INCH   2540      /*  number HIMETRIC units per inch */
#define PTS_PER_INCH        72        /*  number points (font size) per inch */

#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)

/*  Returns TRUE if all fields of the two Rect's are equal, else FALSE. */
#define AreRectsEqual(lprc1, lprc2)     \
   (((lprc1->top == lprc2->top) &&     \
     (lprc1->left == lprc2->left) &&   \
     (lprc1->right == lprc2->right) && \
     (lprc1->bottom == lprc2->bottom)) ? TRUE : FALSE)

#define LSTRCPYN(lpdst, lpsrc, cch) \
(\
   (lpdst)[(cch)-1] = '\0', \
   ((cch)>1 ? _fstrncpy(lpdst, lpsrc, (cch)-1) : 0)\
)





#define UPDATELINKS_STARTDELAY 2000 /*  delay before first link */

#ifdef __TURBOC__
#define _getcwd getcwd
#define _itoa   itoa
#define __max   max
#define _find_t find_t
#endif /*  __TURBOC__ */

#ifdef WIN32
#define _fmemset memset
#define _fmemcpy memcpy
#define _fmemcmp memcmp
#define _fstrcpy strcpy
#define _fstrncpy strncpy
#define _fstrlen strlen
#define _fstrrchr strrchr
#define _fstrtok strtok

/*  BUGBUG32: isspace function does not seem to work properly */
#undef isspace
#define isspace(j) (j==' ' || j=='\t' || j=='\n')
#endif  /*  WIN32 */

#if !defined( EXPORT )
#ifdef WIN32
#define EXPORT
#else
#define EXPORT  __export
#endif  /*  WIN32 */
#endif  /*  !EXPORT */

/*
 * Initialization / Uninitialization routines.  OleStdInitialize
 * must be called prior to using any functions in OLESTD.LIB.
 */




/* Dialog Identifiers as passed in Help messages to identify the source. */
#define IDD_FILEOPEN            32253

#define IDS_FILTERS             32320
#define IDS_ICONFILTERS         32321
#define IDS_BROWSE              32322

/* Resource identifiers for bitmaps */
#define IDB_RESULTSEGA                  32325
#define IDB_RESULTSVGA                  32326
#define IDB_RESULTSHIRESVGA             32327


/* Missing from windows.h */
#ifndef PVOID
typedef VOID *PVOID;
#endif


/* Hook type used in all structures. */
typedef UINT (CALLBACK *LPFNOLEUIHOOK)(HWND, UINT, WPARAM, LPARAM);


/* Strings for registered messages */
#define SZOLEUI_MSG_FILEOKSTRING        "OLEUI_MSG_FILEOKSTRING"


/* Help Button Identifier */
#define ID_OLEUIHELP                    99

/*  Static text control (use this instead of -1 so things work correctly for */
/*  localization */
#define  ID_STATIC                      98







/*************************************************************************
** INSERT OBJECT DIALOG
*************************************************************************/

/* Maximum key size we read from the RegDB. */
#define OLEUI_CCHKEYMAX                 256  /*  make any changes to this in geticon.c too */

/* Maximum verb length and length of Object menu */
#define OLEUI_CCHVERBMAX                32
#define OLEUI_OBJECTMENUMAX             256


/* Icon label length */
#define OLEUI_CCHLABELMAX               40  /*  make any changes to this in geticon.c too */

/* Length of the CLSID string */
#define OLEUI_CCHCLSIDSTRING            39


/* Maximum MS-DOS pathname. */
/* See OLEUI_CCHPATHMAX in shared.h */

#define OLEUI_CCHFILEMAX                13



/* Insert Object Dialog identifiers */
#define ID_IO_CREATENEW                 2100
#define ID_IO_CREATEFROMFILE            2101
#define ID_IO_LINKFILE                  2102
#define ID_IO_OBJECTTYPELIST            2103
#define ID_IO_DISPLAYASICON             2104
#define ID_IO_CHANGEICON                2105
#define ID_IO_FILE                      2106
#define ID_IO_FILEDISPLAY               2107
#define ID_IO_RESULTIMAGE               2108
#define ID_IO_RESULTTEXT                2109
#define ID_IO_ICONDISPLAY               2110
#define ID_IO_OBJECTTYPETEXT            2111
#define ID_IO_FILETEXT                  2112
#define ID_IO_FILETYPE                  2113

/*  Strings in OLE2UI resources */
#define IDS_IORESULTNEW                 32400
#define IDS_IORESULTNEWICON             32401
#define IDS_IORESULTFROMFILE1           32402
#define IDS_IORESULTFROMFILE2           32403
#define IDS_IORESULTFROMFILEICON2       32404
#define IDS_IORESULTLINKFILE1           32405
#define IDS_IORESULTLINKFILE2           32406
#define IDS_IORESULTLINKFILEICON1       32407
#define IDS_IORESULTLINKFILEICON2       32408



/* inside ole2ui.c */
#ifdef __cplusplus
extern "C"
#endif


STDAPI_(BOOL)         OleStdCopyFormatEtc(LPFORMATETC petcDest, LPFORMATETC petcSrc);
STDMETHODIMP_(ULONG)  OleStdEnumFmtEtc_AddRef(LPENUMFORMATETC lpThis);

#define OLESTRCPY                lstrcpyW
#define OLESTRLEN                lstrlenW



#define W2A(w, a, cb)     WideCharToMultiByte(                              \
                                               CP_ACP,                      \
                                               0,                           \
                                               w,                           \
                                               -1,                          \
                                               a,                           \
                                               cb,                          \
                                               NULL,                        \
                                               NULL)

#define A2W(a, w, cb)     MultiByteToWideChar(                              \
                                               CP_ACP,                      \
                                               0,                           \
                                               a,                           \
                                               -1,                          \
                                               w,                           \
                                               cb)


#define FREELOCALSTRING(p)      delete (p)
#define MAKE_STR_LOCAL_COPYW2A(s, l)  {                                   \
                                      l = UtDupStringW2A(s);              \
                                      if (!l) {                           \
                                         return ResultFromScode(S_OOM);   \
                                      }                                   \
                                   }

#define MAKE_STR_LOCAL_COPYA2W(s, l)  {                                   \
                                      l = UtDupStringA2W(s);              \
                                      if (!l) {                           \
                                         return ResultFromScode(S_OOM);   \
                                      }                                   \
                                   }


/*************************************************************************
** The following API's have been converted into macros:
**          OleStdQueryOleObjectData
**          OleStdQueryLinkSourceData
**          OleStdQueryObjectDescriptorData
**          OleStdQueryFormatMedium
**          OleStdCopyMetafilePict
*************************************************************************/

#define OleStdQueryOleObjectData(lpformatetc)   \
   (((lpformatetc)->tymed & TYMED_ISTORAGE) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryLinkSourceData(lpformatetc)   \
   (((lpformatetc)->tymed & TYMED_ISTREAM) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryObjectDescriptorData(lpformatetc)    \
   (((lpformatetc)->tymed & TYMED_HGLOBAL) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

#define OleStdQueryFormatMedium(lpformatetc, tymd)  \
   (((lpformatetc)->tymed & tymd) ?    \
         NOERROR : ResultFromScode(DV_E_FORMATETC))

/*  Make an independent copy of a MetafilePict */
#define OleStdCopyMetafilePict(hpictin, phpictout)  \
   (*(phpictout) = OleDuplicateData(hpictin,CF_METAFILEPICT,GHND|GMEM_SHARE))





/*  Clipboard format strings */
#define CF_EMBEDSOURCE      TEXT("Embed Source")
#define CF_EMBEDDEDOBJECT   TEXT("Embedded Object")
#define CF_LINKSOURCE       TEXT("Link Source")
#define CF_CUSTOMLINKSOURCE TEXT("Custom Link Source")
#define CF_OBJECTDESCRIPTOR TEXT("Object Descriptor")
#define CF_LINKSRCDESCRIPTOR TEXT("Link Source Descriptor")
#define CF_OWNERLINK        TEXT("OwnerLink")
#define CF_FILENAME         TEXT("FileName")

/*  */
/*  Structure used to describe an object */
/*  */





#define STRICT  1

#define IDS_OLE2UIPASTELINKEDTYPE  32311


typedef struct tagOleStdEnumFmtEtc {
  IEnumFORMATETCVtbl FAR* lpVtbl;
  ULONG m_dwRefs;       /* reference count */
  ULONG m_nIndex;       /* current index in list */
  ULONG m_nCount;       /* how many items in list */
  LPFORMATETC m_lpEtc;  /* list of formatetc */
} OLESTDENUMFMTETC, FAR* LPOLESTDENUMFMTETC;


typedef struct _ERRINFO {
    SCODE scode;
    LPSTR szDescription;
} ERRINFO, FAR *PERRINFO;


static GUID that_1b_thing = { 0x1b, 0, 0, 0xc0, 0, 0, 0, 0, 0, 0, 0x46 };
static ERRINFO errinfo[] = {
  E_UNEXPECTED,                   "relatively catastrophic failure",
  E_NOTIMPL,                      "not implemented",
  E_OUTOFMEMORY,                  "ran out of memory",
  E_INVALIDARG,                   "one or more arguments are invalid",
  E_NOINTERFACE,                  "no such interface supported",
  E_POINTER,                      "invalid pointer",
  E_HANDLE,                       "invalid handle",
  E_ABORT,                        "operation aborted",
  E_FAIL,                         "unspecified error",
  E_ACCESSDENIED,                 "general access denied error",

  CLIPBRD_E_CANT_OPEN,            "CLIPBRD_E_CANT_OPEN", 
  CLIPBRD_E_CANT_EMPTY,           "CLIPBRD_E_CANT_EMPTY",
  CLIPBRD_E_CANT_SET,             "CLIPBRD_E_CANT_SET",  
  CLIPBRD_E_BAD_DATA,             "CLIPBRD_E_BAD_DATA",  
  CLIPBRD_E_CANT_CLOSE,           "CLIPBRD_E_CANT_CLOSE",

  OLE_E_OLEVERB,                  "invalid OLEVERB structure  ",
  OLE_E_ADVF,                     "invalid advise flags",
  OLE_E_ENUM_NOMORE,              "you cannot enuemrate any more, because the associated data is missing",
  OLE_E_ADVISENOTSUPPORTED,       "this implementation does not take advises",
  OLE_E_NOCONNECTION,             "there is no connection for this connection id",
  OLE_E_NOTRUNNING,               "need run the COMOBJ to perform this operation",
  OLE_E_NOCACHE,                  "there is no cache to operate on",
  OLE_E_BLANK,                    "Uninitialized COMOBJ",
  OLE_E_CLASSDIFF,                "linked COMOBJ's source class has changed ",
  OLE_E_CANT_GETMONIKER,          "not able to get the moniker of the COMOBJ",
  OLE_E_CANT_BINDTOSOURCE,        "not able to bind to the source",
  OLE_E_STATIC,                   "COMOBJ is static, operation not allowed",
  OLE_E_PROMPTSAVECANCELLED,      "user cancelled out of save dialog",
  OLE_E_INVALIDRECT,              "invalid rectangle ",
  OLE_E_WRONGCOMPOBJ,             "compobj.dll is too old for the ole2.dll initialized",
  OLE_E_INVALIDHWND,              "invalid window handle",
  OLE_E_NOT_INPLACEACTIVE,        "COMOBJ is not in any of the inplace active states  ",
  DV_E_FORMATETC,                 "invalid FORMATETC structure",
  DV_E_DVTARGETDEVICE,            "invalid DVTARGETDEVICE structure",
  DV_E_STGMEDIUM,                 "invalid STDGMEDIUM structure",
  DV_E_STATDATA,                  "invalid STATDATA structure",
  DV_E_LINDEX,                    "invalid lindex",
  DV_E_TYMED,                     "invalid tymed",
  DV_E_CLIPFORMAT,                "invalid clipboard format",
  DV_E_DVASPECT,                  "invalid aspect(s) ",
  DV_E_DVTARGETDEVICE_SIZE,       "tdSize paramter of the DVTARGETDEVICE structure is invalid",
  DV_E_NOIVIEWOBJECT,             "COMOBJ does not support IViewCOMOBJ interface",

  STG_E_INVALIDFUNCTION,          "INVALIDFUNCTION",    
  STG_E_FILENOTFOUND,             "FILENOTFOUND",        
  STG_E_PATHNOTFOUND,             "PATHNOTFOUND",
  STG_E_TOOMANYOPENFILES,         "TOOMANYOPENFILES",
  STG_E_ACCESSDENIED,             "ACCESSDENIED",
  STG_E_INVALIDHANDLE,            "INVALIDHANDLE",
  STG_E_INSUFFICIENTMEMORY,       "INSUFFICIENTMEMORY",
  STG_E_INVALIDPOINTER,           "INVALIDPOINTER",
  STG_E_NOMOREFILES,              "NOMOREFILES",
  STG_E_DISKISWRITEPROTECTED,     "DISKISWRITEPROTECTED",
  STG_E_SEEKERROR,                "SEEKERROR",
  STG_E_WRITEFAULT,               "WRITEFAULT",
  STG_E_READFAULT,                "READFAULT",
  STG_E_LOCKVIOLATION,            "LOCKVIOLATION",
  STG_E_FILEALREADYEXISTS,        "FILEALREADYEXISTS",
  STG_E_INVALIDPARAMETER,         "INVALIDPARAMETER",
  STG_E_MEDIUMFULL,               "MEDIUMFULL",
  STG_E_ABNORMALAPIEXIT,          "ABNORMALAPIEXIT",
  STG_E_INVALIDHEADER,            "INVALIDHEADER",
  STG_E_INVALIDNAME,              "INVALIDNAME",
  STG_E_UNKNOWN,                  "UNKNOWN",
  STG_E_UNIMPLEMENTEDFUNCTION,    "UNIMPLEMENTEDFUNCTION",
  STG_E_INVALIDFLAG,              "INVALIDFLAG",          
  STG_E_INUSE,                    "INUSE",
  STG_E_NOTCURRENT,               "NOTCURRENT",
  STG_E_REVERTED,                 "REVERTED",
  STG_E_CANTSAVE,                 "CANTSAVE",
  STG_E_OLDFORMAT,                "OLDFORMAT",
  STG_E_OLDDLL,                   "OLDDLL",
  STG_E_SHAREREQUIRED,            "SHAREREQUIRED",
  STG_S_CONVERTED,                "CONVERTED",
  /*  STG_S_BUFFEROVERFLOW,           "BUFFEROVERFLOW", */
  /*  STG_S_TRYOVERWRITE,             "TRYOVERWRITE", */
  (long) NULL, NULL};





/*  */
/*  Function prototypes */
/*  */


STDAPI_(LPENUMFORMATETC) OleStdEnumFmtEtc_Create(ULONG nCount, LPFORMATETC lpEtc);

extern void start_up_debug_window(HANDLE);

extern void client_set_open_in_window(PCOMOBJ, short);
extern void client_force_redraw(PCOMOBJ);

extern void InitInterfaces();
extern void initialize_object(PCOMOBJ);

#endif  /* WIN32 */

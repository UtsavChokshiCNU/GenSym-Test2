#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <commctrl.h>

#define BUFFER_SIZE 128

unsigned int styles [] =
{
  WS_OVERLAPPED,   /* WS == Window Styles */
  WS_POPUP,
  WS_CHILD,
  WS_MINIMIZE,
  WS_VISIBLE ,
  WS_DISABLED,
  WS_CLIPSIBLINGS,
  WS_CLIPCHILDREN,
  WS_MAXIMIZE,
  WS_CAPTION,
  WS_BORDER,
  WS_DLGFRAME,
  WS_VSCROLL,
  WS_HSCROLL,
  WS_SYSMENU,
  WS_THICKFRAME,
  WS_GROUP,
  WS_TABSTOP,
  WS_MINIMIZEBOX,
  WS_MAXIMIZEBOX,
  WS_EX_MDICHILD,  /* WINVER >= 0x0400 */
  WS_EX_TOOLWINDOW,
  WS_EX_WINDOWEDGE,
  WS_EX_CLIENTEDGE,
  WS_EX_CONTEXTHELP,
  WS_EX_RIGHT,
  WS_EX_LEFT,
  WS_EX_RTLREADING,
  WS_EX_LTRREADING,
  WS_EX_LEFTSCROLLBAR,
  WS_EX_RIGHTSCROLLBAR,
  WS_EX_CONTROLPARENT,
  WS_EX_STATICEDGE,
  WS_EX_APPWINDOW,
  WS_EX_OVERLAPPEDWINDOW,
  WS_EX_PALETTEWINDOW,
  BS_PUSHBUTTON,  /* BS == Button styles */
  BS_DEFPUSHBUTTON,
  BS_CHECKBOX,
  BS_AUTOCHECKBOX,
  BS_RADIOBUTTON,
  BS_3STATE,
  BS_AUTO3STATE,
  BS_GROUPBOX,
  BS_USERBUTTON,
  BS_AUTORADIOBUTTON,
  BS_OWNERDRAW,
  BS_LEFTTEXT,
  BS_TEXT, /* WINVER >= 0x0400 */
  BS_ICON,
  BS_BITMAP,
  BS_LEFT,
  BS_RIGHT,
  BS_CENTER,
  BS_TOP,
  BS_BOTTOM,
  BS_VCENTER,
  BS_PUSHLIKE,
  BS_MULTILINE,
  BS_NOTIFY,
  BS_FLAT,
  BS_RIGHTBUTTON,
  ES_LEFT,  /* ES == Edit styles */
  ES_CENTER,
  ES_RIGHT,
  ES_MULTILINE,
  ES_UPPERCASE,
  ES_LOWERCASE,
  ES_PASSWORD,
  ES_AUTOVSCROLL,
  ES_AUTOHSCROLL,
  ES_NOHIDESEL,
  ES_OEMCONVERT,
  ES_READONLY,
  ES_WANTRETURN,
  ES_NUMBER, /* WINVER >= 0x0400 */
  SS_LEFT, /* SS == Static control constants */
  SS_CENTER,
  SS_RIGHT,
  SS_ICON,
  SS_BLACKRECT,
  SS_GRAYRECT,
  SS_WHITERECT,
  SS_BLACKFRAME,
  SS_GRAYFRAME,
  SS_WHITEFRAME,
  SS_USERITEM,
  SS_SIMPLE,
  SS_LEFTNOWORDWRAP,
  SS_OWNERDRAW, /* WINVER >= 0x0400 */
  SS_BITMAP,
  SS_ENHMETAFILE,
  SS_ETCHEDHORZ,
  SS_ETCHEDVERT,
  SS_ETCHEDFRAME,
  SS_TYPEMASK,
  SS_NOPREFIX, /* Don't do "&" character translation */
  SS_NOTIFY, /* WINVER >= 0x0400 */
  SS_CENTERIMAGE,
  SS_RIGHTJUST,
  SS_REALSIZEIMAGE,
  SS_SUNKEN,
  SS_ENDELLIPSIS,
  SS_PATHELLIPSIS,
  SS_WORDELLIPSIS,
  SS_ELLIPSISMASK,
  PBS_SMOOTH,
  PBS_VERTICAL,
  TBS_AUTOTICKS,
  TBS_VERT,
  TBS_HORZ,
  TBS_TOP,
  TBS_BOTTOM,
  TBS_LEFT,
  TBS_RIGHT,
  TBS_BOTH,
  TBS_NOTICKS,
  TBS_ENABLESELRANGE,
  TBS_FIXEDLENGTH,
  TBS_NOTHUMB,
  TBS_TOOLTIPS,
  DTS_UPDOWN,
  DTS_SHOWNONE,
  DTS_SHORTDATEFORMAT,
  DTS_LONGDATEFORMAT,
  DTS_TIMEFORMAT,
  DTS_APPCANPARSE,
  DTS_RIGHTALIGN,
  UDS_WRAP, /* UDS == COM control constants */
  /* UDS_SETBUDDYINT, -- breaks increments in spinners!!! */
  UDS_ALIGNRIGHT,
  UDS_ALIGNLEFT,
  UDS_AUTOBUDDY,
  UDS_ARROWKEYS,
  UDS_HORZ,
  UDS_NOTHOUSANDS,
  UDS_HOTTRACK, /* _WIN32_IE >= 0x0300 */
  LBS_NOTIFY,
  LBS_SORT,
  LBS_NOREDRAW,
  LBS_MULTIPLESEL,
  LBS_OWNERDRAWFIXED,
  LBS_OWNERDRAWVARIABLE,
  LBS_HASSTRINGS,
  LBS_USETABSTOPS,
  LBS_NOINTEGRALHEIGHT,
  LBS_MULTICOLUMN,
  LBS_WANTKEYBOARDINPUT,
  LBS_EXTENDEDSEL,
  LBS_DISABLENOSCROLL,
  LBS_NODATA,
  LBS_NOSEL,  /* WINVER >= 0x0400 */
  CBS_SIMPLE, /* CBS == Combo box styles */
  CBS_DROPDOWN,
  CBS_DROPDOWNLIST,
  CBS_OWNERDRAWFIXED,
  CBS_OWNERDRAWVARIABLE,
  CBS_AUTOHSCROLL,
  CBS_OEMCONVERT,
  CBS_SORT,
  CBS_HASSTRINGS,
  CBS_NOINTEGRALHEIGHT,
  CBS_DISABLENOSCROLL,
  CBS_UPPERCASE, /* WINVER >= 0x0400 */
  CBS_LOWERCASE,
  LVS_ICON, /* LVS == List view styles */
  LVS_REPORT,
  LVS_SMALLICON,
  LVS_LIST,
  LVS_TYPEMASK,
  LVS_SINGLESEL,
  LVS_SHOWSELALWAYS,
  LVS_SORTASCENDING,
  LVS_SORTDESCENDING,
  LVS_SHAREIMAGELISTS,
  LVS_NOLABELWRAP,
  LVS_AUTOARRANGE,
  LVS_EDITLABELS,
  LVS_OWNERDATA,
  LVS_NOSCROLL,
  LVS_TYPESTYLEMASK,
  LVS_ALIGNTOP,
  LVS_ALIGNLEFT,
  LVS_ALIGNMASK,
  LVS_OWNERDRAWFIXED,
  LVS_NOCOLUMNHEADER,
  LVS_NOSORTHEADER
};

char *styles_name [] =
{
  "ws-overlapped",    /* ws == Window Styles */
  "ws-popup",
  "ws-child",
  "ws-minimize",
  "ws-visible",
  "ws-disabled",
  "ws-clipsiblings",
  "ws-clipchildren",
  "ws-maximize",
  "ws-caption",
  "ws-border",
  "ws-dlgframe",
  "ws-vscroll",
  "ws-hscroll",
  "ws-sysmenu",
  "ws-thickframe",
  "ws-group",
  "ws-tabstop",
  "ws-minimizebox",
  "ws-maximizebox",
  "ws-ex-mdichild",  /* WINVER >= 0x0400 */
  "ws-ex-toolwindow",
  "ws-ex-windowedge",
  "ws-ex-clientedge",
  "ws-ex-contexthelp",
  "ws-ex-right",
  "ws-ex-left",
  "ws_ex-rtlreading",
  "ws-ex-ltrreading",
  "ws-ex-leftscrollbar",
  "ws-ex-rightscrollbar",
  "ws-ex-controlparent",
  "ws-ex-staticedge",
  "ws-ex-appwindow",
  "ws-ex-overlappedwindow",
  "ws-ex-pallettewindow",
  "bs-pushbutton",  /* bs == Button styles */
  "bs-defpushbutton",
  "bs-checkbox",
  "bs-autocheckbox",
  "bs-radiobutton",
  "bs-3state",
  "bs-auto3state",
  "bs-groupbox",
  "bs-userbutton",
  "bs-autoradiobutton",
  "bs-ownerdraw",
  "bs-lefttext",
  "bs-text", /* WINVER >= 0x0400 */
  "bs-icon",
  "bs-bitmap",
  "bs-left",
  "bs-right",
  "bs-center",
  "bs-top",
  "bs-bottom",
  "bs-vcenter",
  "bs-pushlike",
  "bs-multiline",
  "bs-notify",
  "bs-flat",
  "bs-rightbutton",
  "es-left",      /* es == Edit styles */
  "es-center",
  "es-right",
  "es-multiline",
  "es-uppercase",
  "es-lowercase",
  "es-password",
  "es-autovscroll",
  "es-autohscroll",
  "es-nohidesel",
  "es-oemconvert",
  "es-readonly",
  "es-wantreturn",
  "es-number", /* WINVER >= 0x0400 */
  "ss-left",   /* ss = Static control constants */
  "ss-center",
  "ss-right",
  "ss-icon",
  "ss-blackrect",
  "ss-grayrect",
  "ss-whiterect",
  "ss-blackframe",
  "ss-grayframe",
  "ss-whiteframe",
  "ss-useritem",
  "ss-simple",
  "ss-leftnowordwrap",
  "ss-ownerdraw", /* WINVER >= 0x0400 */
  "ss-bitmap",
  "ss-enhmetafile",
  "ss-etchedhorz",
  "ss-etchedvert",
  "ss-etchedframe",
  "ss-typemask",
  "ss-noprefix", /* Don't do "&" character translation */
  "ss-notify", /* WINVER >= 0x0400 */
  "ss-centerimage",
  "ss-rightjust",
  "ss-realsizeimage",
  "ss-sunken",
  "ss-endellipsis",
  "ss-pathellipsis",
  "ss-wordellipsis",
  "ss-ellipsismask",
  "pbs-smooth",
  "pbs-vertical",
  "tbs-autoticks",
  "tbs-vert",
  "tbs-horz",
  "tbs-top",
  "tbs-bottom",
  "tbs-left",
  "tbs-right",
  "tbs-both",
  "tbs-noticks",
  "tbs-enableselrange",
  "tbs-fixedlength",
  "tbs-nothumb",
  "tbs-tooltips",
  "dts-updown",
  "dts-shownone",
  "dts-shortdateformat",
  "dts-longdateformat",
  "dts-timeformat",
  "dts-appcanparse",
  "dts-rightalign",
  "uds-wrap",    /* uds = COM control constants */
  /* "uds-setbuddyint", -- breaks increments in spinners!!! */
  "uds-alignright",
  "uds-alignleft",
  "uds-autobuddy",
  "uds-arrowkeys",
  "uds-horz",
  "uds-nothousands",
  "uds-hottrack", /* _WIN32_IE >= 0x0300 */
  "lbs-notify", /* LBS == List box styles */
  "lbs-sort",
  "lbs-noredraw",
  "lbs-multiplesel",
  "lbs-ownerdrawfixed",
  "lbs-ownerdrawvariable",
  "lbs-hasstrings",
  "lbs-usetabstops",
  "lbs-nointegralheight",
  "lbs-multicolumn",
  "lbs-wantkeyboardinput",
  "lbs-extendedsel",
  "lbs-disablenoscroll",
  "lbs-nodata",
  "lbs-nosel",  /* WINVER >= 0x0400 */
  "cbs-simple", /* cbs == Combo box styles */
  "cbs-dropdown",
  "cbs-dropdownlist",
  "cbs-ownerdrawfixed",
  "cbs-ownerdrawvariable",
  "cbs-autohscroll",
  "cbs-oemconver",
  "cbs-sort",
  "cbs-hasstrings",
  "cbs-nointegralheight",
  "cbs-disablenoscroll",
  "cbs-uppercase", /* WINVER >= 0x0400 */
  "cbs-lowercase",
  "lvs-icon", /* LVS == List view styles */
  "lvs-report",
  "lvs-smallicon",
  "lvs-list",
  "lvs-typemask",
  "lvs-singlesel",
  "lvs-showselalways",
  "lvs-sortascending",
  "lvs-sortdescending",
  "lvs-shareimagelists",
  "lvs-nolabelwrap",
  "lvs-autoarrange",
  "lvs-editlabels",
  "lvs-ownerdata",
  "lvs-noscroll",
  "lvs-typestylemask",
  "lvs-aligntop",
  "lvs-alignleft",
  "lvs-alignmask",
  "lvs-ownerdrawfixed",
  "lvs-nocolumnheader",
  "lvs-nosortheader"
};


/*****************************************************************************
 * void gprintf (char *pFormatString, ...)
 *
 *   Description:
 *   Input Arguments:
 *   Return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void gprintf (char *pFormatString, ...)
{
  static char buf[BUFFER_SIZE];
  size_t ret = -1;

  /*  format the string */
  ret = _vsnprintf(buf, BUFFER_SIZE, pFormatString,
                   (va_list)(&pFormatString+1));
  if ((ret >= BUFFER_SIZE) || (ret == -1) && (buf != NULL)) {
    buf[BUFFER_SIZE - 1] = '\0';
    /* ensure null terminated string in error case */
  }

  fprintf(stdout, "%s", buf);
#ifdef _DEBUG
  OutputDebugString(buf);
#endif
}


void print_lisp_form(char *name, unsigned int x)
{
  unsigned int low_bits;
  unsigned int high_bits;

  low_bits = (x & 0xFFFFL);
  high_bits = ((x >>16) & 0xFFFFL);

  gprintf("(def-32bit-constant %-22s '( %5u . %5u))\n",
          name, high_bits, low_bits);
}


int main(int argc, char *argv[])
{
  int i, styles_count;

  styles_count = sizeof(styles)/sizeof(int);

  gprintf(";;; BEGIN:  Autogenerated section\n");
  gprintf(";;; Warning:  Do not edit this section!\n");
  gprintf(";;; This section is generated by winuser_constants.exe\n");

  for(i=0; i<styles_count; i++) {
    print_lisp_form(styles_name[i], styles[i]);
  }
  gprintf(";;; END:  Autogenerated section\n");
}

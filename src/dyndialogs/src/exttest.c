/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      exttest.c
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2004 -       jv, lkaspar
+
+ Description:  function calls to test the C interface to dialogs
+
+
+ Key:
+   (obsolete)
+
+ File Organization:
+   Section:      INCLUDE FILES
+   Section:      DEFINES
+   Section:      GLOBALS
+   Section:      FUNCTION GROUP
+
+ External Interface:
+
+ Dependencies:
+
+ Notes:
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+   03/12/04,  jv: created
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define UNICODE
#define _UNICODE

#include <windows.h>
#include <commctrl.h>

#include "testharness.h"
#include "dyndlgs.h"
#include "ddrsc.h"


extern long g2ext_start_dialog (long guess_ncontrols, long width, long height, long type, LPWSTR title);
extern long g2ext_add_to_dialog (long pDialogId, long pControlId,
                                 long parentControlId, LPWSTR pParentControlText,
                                 long pHeight, long pWidth, long pLeft, long pTop,
                                 long pType, LPWSTR pText,
                                 long pStylesHi, long pStylesLo, 
                                 long pG2Styles, long bResponse);
extern long g2ext_add_grid_column(long dialog, long controlid, long index, long width, LPWSTR name);
extern long g2ext_start_add_grid_row(int dlgid, int ctrlid, long key, long bgcolor, long textcolor);
extern long g2ext_start_add_grid (long dialogid, long controlid, long textcolor, long bgcolor, long rowheight);
extern long g2ext_add_grid_cell(long dlgid, long ctrlid, long key, long index,
                                    long textcolor, long bgcolor, LPWSTR text);
extern long g2ext_end_add_grid_row(long dialogid, long controlid, long key);



// c_add_to_dialog... unfortunately, Lisp doesn't do 32-bit integers.  We are
// limited to passing 29 bits in a "long".  For most integer arguments, that's
// ok, but the "styles" of a Windows control often has the 2^32 bit set.  So,
// we have to pass it in two words, rather than in one.
//
// For calling directly from C, however, that's pretty inconvenient, so we
// add this little wrapper that takes a "real" long, as a single argument,
// and breaks it up the way Lisp will have to.

long c_add_to_dialog (long pDialogId, long pControlId,
                      long parentControlId, LPWSTR pParentControlText,
                      long pHeight, long pWidth, long pLeft, long pTop,
                      long pType, LPWSTR pText, long pStyles, long pG2Styles, BOOL bResponse)
{
  return g2ext_add_to_dialog(pDialogId, pControlId, parentControlId, 
    pParentControlText, pHeight, pWidth,
    pLeft, pTop, pType, pText,
    pStyles >> 16, pStyles & 65535, pG2Styles, bResponse);
}

/*long new_stuff_g2ext_build_dynamic_dialog_1()
{
  long hdialog;
  
  hdialog = g2ext_start_dialog(28, 304, 366, MODELESS, _T(" Main Dialog Masked Edit Example "));
  
 // multiline edit box or single line edit box in the case of a password
  c_add_to_dialog(hdialog, IDC_EDIT1, PARENT_IS_ENTIRE_DIALOG, _T(""),
    27, 114, 105, 10, ctMaskedTextBx, _T("Upper Case Example"),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
   G2_CVT_TO_UPPER,  // G2styles
   DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles

// multiline edit box or single line edit box in the case of a password
  c_add_to_dialog(hdialog, IDC_EDIT3, PARENT_IS_ENTIRE_DIALOG, _T(""),
    27, 114, 105, 10+30, ctMaskedTextBx, _T("Lower Case Example"),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
   G2_CVT_TO_LOWER,  // G2styles
   DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles

 // multiline edit box or single line edit box in the case of a password
  c_add_to_dialog(hdialog, IDC_EDIT2, PARENT_IS_ENTIRE_DIALOG, _T(""),
   //* h, w, l, t 
    27, 114, 105, 10+60, ctMaskedTextBx, _T("Masked Edit Password Example"),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
    G2_PASSWORD_TEXT_BOX,  // G2styles
   DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles

 // MASKED SPEC multiline edit box or single line edit box in the case of a password
  c_add_to_dialog(hdialog, IDC_EDIT4, PARENT_IS_ENTIRE_DIALOG, _T(""),
    // h, w, l, t 
    22, 114, 105, 10+90, ctMaskedTextBx, _T("Masked Edit Password Example"),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
    G2_MASK_SPEC,  // G2styles
    DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles
 
// TRACK BAR 
  c_add_to_dialog(hdialog, IDC_TRACKBAR, PARENT_IS_ENTIRE_DIALOG, _T(""),
    // h, w, l, t 
    22, 114, 105, 10+130, ctTrackBar,
    
       _T("0.0|0.8|2.0|.1|%0.1f"), // default is 0.0, min is .08, max is 2.0, increment is 0.1 

    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
    0,  // G2styles
    DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles
// TRACK BAR 

  c_add_to_dialog(hdialog, IDC_PROGRESSBAR, PARENT_IS_ENTIRE_DIALOG, _T(""),
    // h, w, l, t 
    22, 114, 105, 10+160, ctProgressBar, _T("ProgressBar control"),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN | WS_VISIBLE | WS_TABSTOP, 
    0,  // G2styles
    DLG_JUST_RESPOND); // hjg changed NOREPOSE to JUST_RESPOND and now using G2 styles


  // OK button
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 93, 326, ctPushBtn, _T("OK"),
    BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_RESPOND_ALL_OK); //DLG_RESPOND_OK);
  
  
  return hdialog; 
} */


long g2ext_build_dynamic_dialog_1 ()
{
  long hdialog;
  
  hdialog = g2ext_start_dialog(28, 304, 366, MODELESS, _T("Financial Table"));
  
  // tabs across the top
  c_add_to_dialog(hdialog, IDC_TAB1, PARENT_IS_ENTIRE_DIALOG, _T(""), 310, 290, 7, 7, ctTabs,
    _T("Role\\Financial\\Assets\\Cost"),
    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // OK button
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 93, 326, ctPushBtn, _T("OK"),
    BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_RESPOND_ALL_OK); //DLG_RESPOND_OK);
  
  // Cancel button
  c_add_to_dialog(hdialog, IDCANCEL, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 155, 326, ctPushBtn,
    _T("Cancel"), BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_RESPOND_OK);
  
  // General group box
  c_add_to_dialog(hdialog, IDC_STATIC_GENERAL, IDC_TAB1, _T("Role"), 87, 228, 27, 29, ctGroup,
    _T("General"), BS_GROUPBOX | WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Role Label: label
  c_add_to_dialog(hdialog, IDC_STATIC_ROLE, IDC_TAB1, _T("Role"), 8, 37, 37, 55, ctStatic,
    _T("Role Label:"), SS_LEFT | WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Role Label: multiline edit box
  c_add_to_dialog(hdialog, IDC_EDIT1, IDC_TAB1, _T("Role"), 27, 114, 105, 41, ctTextBx, _T(""),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Sequence Number: label
  c_add_to_dialog(hdialog, IDC_STATIC_SEQ_NUM, IDC_TAB1, _T("Role"), 8, 62, 37, 76, ctStatic,
    _T("Sequence Number:"), WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Sequence Number: edit box
  c_add_to_dialog(hdialog, IDC_EDIT2, IDC_TAB1, _T("Role"), 14, 104, 105, 73, ctTextBx, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_JUST_RESPOND); //DLG_NO_RESPONSE);
  
// hjg original  // Sequence Number: spinner
// hjg original  c_add_to_dialog(hdialog, IDC_SPIN1, IDC_TAB1, _T("Role"), 14, 10, 209, 73, ctSpin,
// hjg original     _T("0|0|50|.5|%0.1f"),
// hjg original     WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_AUTOBUDDY | WS_TABSTOP,
// hjg original     0, DLG_NO_RESPONSE);
// hjg another test  _T("0.0|0.8|2.0|.1|%0.1f")
 // Sequence Number: spinner
  c_add_to_dialog(hdialog, IDC_SPIN1, IDC_TAB1, _T("Role"), 14, 10, 209, 73, ctSpin,
   _T("0.0|-0.8|2.0|.1|%0.1f"), /* default is 0.0, min is .8, max is 2.0, increment is 0.1 */
   WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_AUTOBUDDY | WS_TABSTOP,
     0, DLG_NO_RESPONSE);


  // _T("0|0|50",
  // _T("350|0|500|5",
  // _T("0|0|50|.5|%g"),
  
  
  // Upgrade checkbox
  c_add_to_dialog(hdialog, IDC_CHECK1, IDC_TAB1, _T("Role"), 10, 43, 120, 99, ctCheck,
    _T("Upgrade"),
    WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Order Method groupbox
  c_add_to_dialog(hdialog, IDC_STATIC_ORDER_METHOD, IDC_TAB1, _T("Role"), 48, 228, 26, 129, ctGroup,
    _T("Order Method:"), BS_GROUPBOX | WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Source type: label
  c_add_to_dialog(hdialog, IDC_STATIC_SOURCE_TYPE, IDC_TAB1, _T("Role"), 8, 44, 63, 145, ctStatic,
    _T("Source Type:"), WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Source type Push radiobutton
  c_add_to_dialog(hdialog, IDC_RADIO1, IDC_TAB1, _T("Role"), 10, 32, 114, 145, ctRadio,
    _T("Push"), BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Source type Pull radiobutton
  c_add_to_dialog(hdialog, IDC_RADIO2, IDC_TAB1, _T("Role"), 10, 27, 152, 145, ctRadio,
    _T("Pull"), BS_AUTORADIOBUTTON | WS_CHILD
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Delivery type: label
  c_add_to_dialog(hdialog, IDC_STATIC_DELIVERY_TYPE, IDC_TAB1, _T("Role"), 8, 46, 61, 158, ctStatic,
    _T("Delivery Type:"), WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Delivery type Push radiobutton
  c_add_to_dialog(hdialog, IDC_RADIO3, IDC_TAB1, _T("Role"), 10, 32, 113, 158, ctRadio,
    _T("Push"), BS_AUTORADIOBUTTON | WS_GROUP | WS_CHILD
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Delivery type Pull radiobutton
  c_add_to_dialog(hdialog, IDC_RADIO3, IDC_TAB1, _T("Role"), 10, 27, 152, 158, ctRadio,
    _T("Pull"), BS_AUTORADIOBUTTON | WS_CHILD
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Metrics groupbox
  c_add_to_dialog(hdialog, IDC_STATIC_METRICS, IDC_TAB1, _T("Role"), 48, 228, 26, 191, ctGroup,
    _T("Metrics"), BS_GROUPBOX | WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Number of End Products: label
  c_add_to_dialog(hdialog, IDC_STATIC_END_PRODUCTS, IDC_TAB1, _T("Role"), 8, 80, 53, 208, ctStatic,
    _T("Number of End Products:"), WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Number of End Products: editbox
  c_add_to_dialog(hdialog, IDC_EDIT3, IDC_TAB1, _T("Role"), 12, 80, 136, 203, ctTextBx, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_JUST_RESPOND);
  
  // Logging groupbox
  c_add_to_dialog(hdialog, IDC_STATIC_LOGGING_GB, IDC_TAB1, _T("Role"), 48, 229, 25, 248, ctGroup,
    _T("Logging"), BS_GROUPBOX | WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // Logging checkbox
  c_add_to_dialog(hdialog, IDC_CHECK2, IDC_TAB1, _T("Role"), 10, 41, 124, 258, ctCheck,
    _T("Logging"),
    WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // Logging checkbox
  c_add_to_dialog(hdialog, IDC_STATIC_LOGGING, IDC_TAB1, _T("Role"), 8, 34, 34, 274, ctStatic,
    _T("File Name:"), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // File name editbox
  c_add_to_dialog(hdialog, IDC_EDIT4, IDC_TAB1, _T("Role"), 12, 127, 71, 271, ctTextBx, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // File name browse button
  c_add_to_dialog(hdialog, IDC_BUTTON1, IDC_TAB1, _T("Role"), 14, 16, 201, 270, ctPushBtn,
    _T("..."), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // first control of second tab
  c_add_to_dialog(hdialog, IDC_BUTTON2, IDC_TAB1, _T("Financial"), 14, 50, 20, 145, ctPushBtn,
    _T("Financial"), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // second control of second tab
  c_add_to_dialog(hdialog, IDC_EDIT1, IDC_TAB1, _T("Financial"), 150, 150, 100, 40, ctTextBx,
    _T("The quick brown fox jumps over the lazy dog."),
    ES_MULTILINE | WS_VSCROLL | WS_CHILD | ES_WANTRETURN
    | WS_VISIBLE | WS_TABSTOP, 0, DLG_NO_RESPONSE);
  
  // first control of third tab
  c_add_to_dialog(hdialog, IDC_BUTTON3, IDC_TAB1, _T("Assets"), 8, 34, 34, 274, ctStatic,
    _T("An asset:"), WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // second control of third tab
  c_add_to_dialog(hdialog, IDC_EDIT5, IDC_TAB1, _T("Assets"), 12, 127, 71, 271, ctTextBx, _T(""),
    WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  return hdialog;
}


long g2ext_build_dynamic_dialog_2 ()
{
  long hdialog;
  
  hdialog = g2ext_start_dialog(19, 295, 327, MODELESS, _T("Dialog 2"));
  // TODO:  update the input param with actual number of controls to be added to the dialog
  
  // inner tabs
  c_add_to_dialog(hdialog, IDC_TAB4, IDC_TAB5, _T("Build Orders"), 121, 236, 29, 98,
    ctTabs, _T("First\\Second\\Third\\Fourth"),
    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, FALSE);
  
  // tabs across the top
  c_add_to_dialog(hdialog, IDC_TAB5, PARENT_IS_ENTIRE_DIALOG, _T(""), 281, 272, 7, 7,
    ctTabs, _T("Build Orders\\Manufacturer\\Build\\Cost"),
    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, FALSE);
  
  // OK button        
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 41, 286,
    ctPushBtn, _T("OK"),
    BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_RESPOND_OK);
  
  // Cancel button
  c_add_to_dialog(hdialog, IDCANCEL, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 201, 286,
    ctPushBtn, _T("Cancel"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_RESPOND_OK);
  
  // Apply button
  c_add_to_dialog(hdialog, IDC_BUTTON1, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 95, 286,
    ctPushBtn, _T("Apply"), 
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, DLG_JUST_RESPOND);
  
  // Update button
  c_add_to_dialog(hdialog, IDC_BUTTON2, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 147, 286,
    ctPushBtn, _T("Update"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, TRUE);
  
  // Groupbox
  c_add_to_dialog(hdialog, IDC_STATIC, IDC_TAB5, _T("Build Orders"), 139, 241, 27, 86,
    ctGroup, _T("Build Selection"),
    WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, FALSE);
  
  // Groupbox
  c_add_to_dialog(hdialog, IDC_STATIC, IDC_TAB5, _T("Manufacturer"), 139, 241, 27, 86,
    ctGroup, _T("Manufacturer"),
    WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, FALSE);
  
  // Sort Direction:
  c_add_to_dialog(hdialog, IDC_STATIC_SORTDIR, IDC_TAB4, _T("First"), 8, 46, 33, 138,
    ctStatic, _T("Sort Direction:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // Sort By:
  c_add_to_dialog(hdialog, IDC_STATIC_SORTBY, IDC_TAB4, _T("First"), 8, 26, 34, 154,
    ctStatic, _T("Sort By:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // Cutoff:
  c_add_to_dialog(hdialog, IDC_STATIC_CUTOFF, IDC_TAB4, _T("First"), 8, 22, 34, 170,
    ctStatic, _T("Cutoff:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // Cutoff Value:
  c_add_to_dialog(hdialog, IDC_STATIC_CUTOFFVAL, IDC_TAB4, _T("First"), 8, 42, 34, 185,
    ctStatic, _T("Cutoff Value:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // Cutoff Duration
  c_add_to_dialog(hdialog, IDC_STATIC_CUTOFFDUR, IDC_TAB4, _T("First"), 8, 50, 33, 201,
    ctStatic, _T("Cutoff Duration:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // Sort direction combobox
  c_add_to_dialog(hdialog, IDC_COMBO1, IDC_TAB4, _T("First"), 30, 144, 94, 132,
    ctComboBox, _T("Biggest\001Smallest"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWN | CBS_SORT, 0, DLG_JUST_RESPOND);
  
  // Sort by combobox
  c_add_to_dialog(hdialog, IDC_COMBO2, IDC_TAB4, _T("First"), 30, 144, 94, 148,
    ctComboBox, _T("Order Size\001Order Amount"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_SORT, 0, FALSE);
  
  // Cutoff combobox
  c_add_to_dialog(hdialog, IDC_COMBO3, IDC_TAB4, _T("First"), 30, 144, 94, 163,
    ctComboBox, _T("Minimum Acceptable"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP  | CBS_DROPDOWNLIST | CBS_SORT, 0, FALSE);
  
  // Sequence Number: edit box
  c_add_to_dialog(hdialog, IDC_EDIT2, IDC_TAB4, _T("First"), 12, 125, 93, 178,
    ctTextBx, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, TRUE);
  
  // Cutoff Value: spinner
  c_add_to_dialog(hdialog, IDC_SPIN1, IDC_TAB4, _T("First"), 10, 14, 226, 177,
    ctSpin, _T("350,0,500,5"),
    WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_ARROWKEYS 
    | UDS_SETBUDDYINT | UDS_AUTOBUDDY | WS_TABSTOP, 0, FALSE);
  
  // Cutoff duration edit box
  c_add_to_dialog(hdialog, IDC_EDIT1, IDC_TAB4, _T("First"), 14, 92, 92, 194,
    ctTextBx, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, FALSE);
  
  // Cutoff duration combobox
  c_add_to_dialog(hdialog, IDC_COMBO4, IDC_TAB4, _T("First"), 30, 48, 189, 194,
    ctComboBox, _T("Minutes\001Hours\001Seconds"),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_SORT, 0, FALSE);
  
  return hdialog;
}

long g2ext_build_dynamic_dialog_3 ()
{
  long hdialog;
  
  int i = 0;
  
  const TCHAR sz11[] = _T("Edwin Land");
  const TCHAR sz12[] = _T("13 Old Milford Road");
  const TCHAR sz13[] = _T("Hooksett");
  
  const TCHAR sz21[] = _T("Victor Steele");
  const TCHAR sz22[] = _T("28 Windsong Lane");
  const TCHAR sz23[] = _T("Friendswood");
  
  const TCHAR sz31[] = _T("Pete Paplaskas");
  const TCHAR sz32[] = _T("1564 Wilton Rd.");
  const TCHAR sz33[] = _T("Alton");
  
  // allocate and populate an array of strings
  TCHAR ** ppvals = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  TCHAR ** ppvals2 = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  TCHAR ** ppvals3 = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  
  ZeroMemory((LPVOID)ppvals, 3*sizeof(TCHAR*));
  
  ppvals[0] = (TCHAR*)malloc(sizeof(sz11));
  _tcscpy(ppvals[0], sz11);
  
  ppvals[1] = (TCHAR*)malloc(sizeof(sz12));
  _tcscpy(ppvals[1], sz12);
  
  ppvals[2] = (TCHAR*)malloc(sizeof(sz13));
  _tcscpy(ppvals[2], sz13);
  
  ZeroMemory((LPVOID)ppvals2, 3*sizeof(TCHAR*));
  
  ppvals2[0] = (TCHAR*)malloc(sizeof(sz21));
  _tcscpy(ppvals2[0], sz21);
  
  ppvals2[1] = (TCHAR*)malloc(sizeof(sz22));
  _tcscpy(ppvals2[1], sz22);
  
  ppvals2[2] = (TCHAR*)malloc(sizeof(sz23));
  _tcscpy(ppvals2[2], sz23);
  
  ZeroMemory((LPVOID)ppvals3, 3*sizeof(TCHAR*));
  
  ppvals3[0] = (TCHAR*)malloc(sizeof(sz31));
  _tcscpy(ppvals3[0], sz31);
  
  ppvals3[1] = (TCHAR*)malloc(sizeof(sz32));
  _tcscpy(ppvals3[1], sz32);
  
  ppvals3[2] = (TCHAR*)malloc(sizeof(sz33));
  _tcscpy(ppvals3[2], sz33);
  
  hdialog = g2ext_start_dialog(4, 295, 327, MODELESS, _T("Dialog 3"));
  
  /*
  // Sequence Number: edit box
  c_add_to_dialog(hdialog, IDC_EDIT2, PARENT_IS_ENTIRE_DIALOG, _T(""), 
  14, 104, 105, 73, ctTextBx, _T("",
  WS_CHILD | WS_VISIBLE | WS_TABSTOP, DLG_NO_RESPONSE);
  
    // Cutoff Value: spinner
    c_add_to_dialog(hdialog, 8, PARENT_IS_ENTIRE_DIALOG, _T(""), 
    14, 10, 209, 73, ctSpin, _T("20.0|0.0|100.0|5.0|%g",
    WS_CHILD | WS_VISIBLE | UDS_ALIGNRIGHT | UDS_ARROWKEYS | 
    UDS_AUTOBUDDY | WS_TABSTOP, DLG_NO_RESPONSE);
  */
  
  // ok button
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 57, 142, ctPushBtn, _T("&OK"),
    WS_CHILD | WS_VISIBLE|BS_DEFPUSHBUTTON, 0, DLG_RESPOND_OK);
  
  // cancel button
  c_add_to_dialog(hdialog, IDCANCEL, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 111, 142,
    ctPushBtn, _T("Ca&ncel"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_OK);
  
  // listview        
  c_add_to_dialog(hdialog, IDC_LISTVIEW, PARENT_IS_ENTIRE_DIALOG, _T(""),
    100/*75*/, 200/*161*/, 20, 36, ctTabularView, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | LVS_SINGLESEL /*| WS_BORDER*/, 0, DLG_JUST_RESPOND); 
  
  // listview static
  c_add_to_dialog(hdialog, IDC_LISTVIEW_STATIC, PARENT_IS_ENTIRE_DIALOG, _T(""),
    8, 28, 15, 19, ctStatic, _T("Listview:"),
    WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  // now fill in the listview
  g2ext_start_add_grid(hdialog, IDC_LISTVIEW, -1, -1, 30);
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 0, TVIEW_DEFAULT_COL_WIDTH_HEADER, _T("Name"));
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 1, TVIEW_DEFAULT_COL_WIDTH_HEADER, _T("Address"));
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 2, TVIEW_DEFAULT_COL_WIDTH_HEADER, _T("City"));
  
  // row 1
  g2ext_start_add_grid_row(hdialog,              // dialog id
    IDC_LISTVIEW,                            // control id
    0,                                       // key
    RGB(225, 250, 250),                      // row background color
    RGB(255, 0, 0));                         // row text color
  
  for (i = 0; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 0, 0, RGB(200, 150, 200),
      RGB(255, 255, 255), (TCHAR*)ppvals[i]);
  }
  
  g2ext_end_add_grid_row(hdialog, IDC_LISTVIEW, 0);
  
  // row 2
  g2ext_start_add_grid_row(hdialog,              // dialog id
    IDC_LISTVIEW,                            // control id
    1,                                       // key
    RGB(255, 255, 255),                      // row background color
    RGB(0, 0, 0));                           // row text color
  
  for (i = 0; i < 2; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 1, 0, RGB(225, 115, 100),
      RGB(255, 255, 255), (TCHAR*)ppvals2[i]);
  }
  g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 1, 0,
    RGB(150, 225, 100), RGB(0, 0, 0), (TCHAR*)ppvals2[2]);
  
  g2ext_end_add_grid_row(hdialog, IDC_LISTVIEW, 1);
  
  // row 3
  g2ext_start_add_grid_row(hdialog,              // dialog id
    IDC_LISTVIEW,                            // control id
    2,                                       // key
    RGB(0, 100, 250),                        // row background color
    RGB(255, 255, 255));                     // row text color
  
  for (i = 0; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 2, 0,
      RGB(200, 100, 200), RGB(255, 255, 255), (TCHAR*)ppvals3[i]);
  }
  
  g2ext_end_add_grid_row(hdialog, IDC_LISTVIEW, 2);
  
  return hdialog;
}

// simulate a grid control
long g2ext_build_dynamic_dialog_4 ()
{
  long hdialog;
  int i = 0;
  
  const TCHAR sz11[] = _T("1");
  const TCHAR sz12[] = _T("Open");
  const TCHAR sz13[] = _T("ACK");
  
  const TCHAR sz21[] = _T("2");
  const TCHAR sz22[] = _T("Closed");
  const TCHAR sz23[] = _T("DLG_NO_RESPONSE");
  
  // allocate and populate an array of strings
  TCHAR ** ppvals = (TCHAR**)malloc(3 * sizeof(TCHAR));
  TCHAR ** ppvals2 = (TCHAR**)malloc(3 * sizeof(TCHAR));
  
  ZeroMemory((LPVOID)ppvals, 3*sizeof(TCHAR*));
  
  ppvals[0] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[0], sz11);
  
  ppvals[1] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[1], sz12);
  
  ppvals[2] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[2], sz13);
  
  ZeroMemory((LPVOID)ppvals2, 3*sizeof(TCHAR*));
  
  ppvals2[0] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[0], sz21);
  
  ppvals2[1] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[1], sz22);
  
  ppvals2[2] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[2], sz23);
  
  hdialog = g2ext_start_dialog(4, 206, 195, MODAL, _T("Dialog 4"));
  // TODO:  update the input param with actual number of controls to be added to the dialog
  
  // ok button
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 57, 142,
    ctPushBtn, _T("&OK"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_OK);
  
  // cancel button
  c_add_to_dialog(hdialog, IDCANCEL, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 111, 142,
    ctPushBtn, _T("Ca&ncel"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_OK);
  
  // grid        
  c_add_to_dialog(hdialog, IDC_LISTVIEW, PARENT_IS_ENTIRE_DIALOG, _T(""), 75, 161, 20, 36,
    ctTabularView, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 0, DLG_JUST_RESPOND); 
  
  // listview static
  c_add_to_dialog(hdialog, IDC_LISTVIEW_STATIC, PARENT_IS_ENTIRE_DIALOG, _T(""), 8, 28, 15, 19,
    ctStatic, _T("The grid:"),
    WS_CHILD | WS_VISIBLE, 0, FALSE);
  
  // now fill in the grid
  g2ext_start_add_grid(hdialog, IDC_LISTVIEW, -1, -1, 100);
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 0, 5, _T("Message Id"));
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 1, 15, _T("Message Status"));
  g2ext_add_grid_column(hdialog, IDC_LISTVIEW, 2, 20, _T("Message Response"));
  
  
  // row 1
  g2ext_start_add_grid_row(hdialog, IDC_LISTVIEW, 0, RGB(125, 150, 50), RGB(255, 255, 255));
  
  for (i = 0; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 0, 0, RGB(150, 150, 150),
      RGB(255, 255, 255), (TCHAR*)ppvals[i]);
  }
  
  // row 2
  g2ext_start_add_grid_row(hdialog,          // dialog id
    IDC_LIST_MSG_BROWSE,                 // control id
    9,                                   // key
    RGB(150, 150, 150),                  // row background color
    RGB(255, 255, 255));                 // row text color
  
  for (i = 0; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LISTVIEW, 1, 0, RGB(100, 100, 100),
      RGB(255, 255, 255), (TCHAR*)ppvals2[i]);
  }
  
  return hdialog;
}

// demo message browser
long g2ext_build_message_browser ()
{
  long hdialog;
  int i = 0;
  
  const TCHAR sz11[] = _T("1");
  const TCHAR sz12[] = _T("Open");
  const TCHAR sz13[] = _T("ACK");
  
  const TCHAR sz21[] = _T("2");
  const TCHAR sz22[] = _T("Closed");
  const TCHAR sz23[] = _T("DLG_NO_RESPONSE");
  
  const TCHAR sz31[] = _T("3");
  const TCHAR sz32[] = _T("Pending");
  const TCHAR sz33[] = _T("DLG_NO_RESPONSE");
  
  // allocate and populate an array of strings
  TCHAR ** ppvals = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  TCHAR ** ppvals2 = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  TCHAR ** ppvals3 = (TCHAR**)malloc(3 * sizeof(TCHAR *));
  
  ZeroMemory((LPVOID)ppvals, 3*sizeof(TCHAR*));
  
  ppvals[0] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[0], sz11);
  
  ppvals[1] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[1], sz12);
  
  ppvals[2] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals[2], sz13);
  
  ZeroMemory((LPVOID)ppvals2, 3*sizeof(TCHAR*));
  
  ppvals2[0] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[0], sz21);
  
  ppvals2[1] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[1], sz22);
  
  ppvals2[2] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals2[2], sz23);
  
  ZeroMemory((LPVOID)ppvals3, 3*sizeof(TCHAR*));
  
  ppvals3[0] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals3[0], sz31);
  
  ppvals3[1] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals3[1], sz32);
  
  ppvals3[2] = (TCHAR*)malloc(3 * sizeof(TCHAR));
  _tcscpy(ppvals3[2], sz33);
  
  hdialog = g2ext_start_dialog(8, 390, 270, MODELESS, _T("Message Browser"));
  // TODO:  update the input param with actual number of controls to be added to the dialog
  
  // ok button
  c_add_to_dialog(hdialog, IDOK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 145, 235, ctPushBtn, _T("&OK"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_ALL_OK);
  
  // cancel button
  c_add_to_dialog(hdialog, IDCANCEL, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 201, 235,
    ctPushBtn, _T("Ca&ncel"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_OK);
  
  // Columns button
  c_add_to_dialog(hdialog, IDC_BTN_COLUMNS, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 83, 9,
    ctPushBtn, _T("Columns..."),
    WS_CHILD | WS_VISIBLE, 0, DLG_JUST_RESPOND);
  
  // Filters button
  c_add_to_dialog(hdialog, IDC_BTN_FILTERS, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 134, 9,
    ctPushBtn, _T("Filters..."),
    WS_CHILD | WS_VISIBLE, 0, DLG_JUST_RESPOND);
  
  // Delete button
  c_add_to_dialog(hdialog, IDC_BTN_DELETE, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 280, 9,
    ctPushBtn, _T("Delete"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_ALL);
  
  // Acknowledge button
  c_add_to_dialog(hdialog, IDC_BTN_ACK, PARENT_IS_ENTIRE_DIALOG, _T(""), 14, 50, 332, 9,
    ctPushBtn, _T("Acknowledge"),
    WS_CHILD | WS_VISIBLE, 0, DLG_RESPOND_ALL);
  
  // grid        
  c_add_to_dialog(hdialog, IDC_LIST_MSG_BROWSE, PARENT_IS_ENTIRE_DIALOG, _T(""), 200, 376, 7, 24, 
    ctTabularView, _T(""),
    WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | /*LVS_SINGLESEL | */LVS_SHOWSELALWAYS | WS_BORDER, 
    G2_LVS_GRIDLINES|G2_LVS_SORT, DLG_JUST_RESPOND); 
  
  // message browser static
  c_add_to_dialog(hdialog, IDC_STATIC_MSG_BROWSE, PARENT_IS_ENTIRE_DIALOG, _T(""), 8, 57, 9, 9,
    ctStatic, _T("Message Browser"),
    WS_CHILD | WS_VISIBLE, 0, DLG_NO_RESPONSE);
  
  
  // now fill in the grid
  g2ext_start_add_grid(hdialog, IDC_LIST_MSG_BROWSE, -1, -1, TVIEW_DEFAULT_ROW_HEIGHT);
  g2ext_add_grid_column(hdialog, IDC_LIST_MSG_BROWSE, 0, 20, _T("Message Id"));
  g2ext_add_grid_column(hdialog, IDC_LIST_MSG_BROWSE, 1,
    TVIEW_DEFAULT_COL_WIDTH_TEXT, _T("Message Status"));
  g2ext_add_grid_column(hdialog, IDC_LIST_MSG_BROWSE, 2,
    TVIEW_DEFAULT_COL_WIDTH_HEADER, _T("Message Response"));
  
  // row 1
  g2ext_start_add_grid_row(hdialog,          // dialog id
    IDC_LIST_MSG_BROWSE,                 // control id
    9,                                   // key
    RGB(100, 200, 150),                  // row background color
    RGB(255, 255, 255));                 // row text color
  
  g2ext_add_grid_cell(hdialog, IDC_LIST_MSG_BROWSE, 9, 0,
    RGB(60, 175, 200), RGB(255, 255, 255), ppvals[0]);

  for (i = 1; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LIST_MSG_BROWSE, 9, 0,
      RGB(114, 100, 200), RGB(255, 255, 255), ppvals[i]);
  }
  
  g2ext_end_add_grid_row(hdialog, IDC_LIST_MSG_BROWSE, 9);
  
  // row 2
  g2ext_start_add_grid_row(hdialog,          // dialog id
    IDC_LIST_MSG_BROWSE,                 // control id
    10,                                  // key
    RGB(200, 200, 200),                  // row background color
    RGB(0, 0, 0));                       // row text color
  
  // row 2
  for (i = 0; i < 2; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LIST_MSG_BROWSE, 10, 0,
      RGB(100, 20, 200), RGB(255, 255, 255), ppvals2[i]);
  }
  g2ext_add_grid_cell(hdialog, IDC_LIST_MSG_BROWSE, 10, 0,
    RGB(20, 100, 200), RGB(0, 0, 0), ppvals2[2]);
  
  g2ext_end_add_grid_row(hdialog, IDC_LIST_MSG_BROWSE, 10);
  
  // row 3
  g2ext_start_add_grid_row(hdialog,          // dialog id
    IDC_LIST_MSG_BROWSE,                 // control id
    2,                                   // key
    RGB(200, 200, 200),                  // row background color
    RGB(255, 255, 255));                 // row text color
  
  for (i = 0; i < 3; i++) {
    g2ext_add_grid_cell(hdialog, IDC_LIST_MSG_BROWSE, 2, 0,
      RGB(200, 200, 200), RGB(255, 255, 255), ppvals3[i]);
  }
  
  g2ext_end_add_grid_row(hdialog, IDC_LIST_MSG_BROWSE, 2);
  
  return hdialog;
}

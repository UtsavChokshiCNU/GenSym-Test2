#include <stdio.h>
#include "shared.h"
#include "fileio.h"
#include "bucket.h"
#include "dprintf.h"
#include "javaString.h"
#include <string.h>

#ifdef WIN32

#include <windows.h>
#include <oledlg.h>

#define CONTAINER_TYPE short
#define CONTAINER_TYPE_NOT_DEFINED 1
#define C_CONTAINER                2
#define JAVA_CONTAINER             4


/***********************************************************************
 * Visual Basic code which "does stuff"
 *
 * Dim Value As Integer
 * Set Chart = CreateObject("Excel.Chart")
 * Set Obj = Chart.Application
 * Obj.Visible = True
 * Set Books = Obj.Workbooks
 * Set Book = Books(1)
 * Set Sheets = Book.Worksheets
 * Set Sheet = Sheets(1)
 * Set Cells = Sheet.Cells
 * Set Cell = Cells(2, 2)
 * Value = Cell.Value
 * Cell.Value = 100
 * Set Range = Sheet.Range("A1:D8")
 * Chart.SetSourceData Source:=Range, PlotBy:=xlRows
 * MsgBox "Click to end"
 * Obj.Quit
 *
 * ActiveChart.SetSourceData Source:=Sheets("Sheet1").Range("A1:D8"), PlotBy:= _
        xlRows
 PTR to USERDEFINED Range(
    IN Variant Cell1,
    <error!> Variant Cell2
    )
 ***********************************************************************/

static PNTWOBJ (*ntw_Redraw_pointer)() = NULL;
static PNTWOBJ (*ntw_SetOpen_pointer)() = NULL;
static PNTWOBJ (*ntw_ClearOpen_pointer)() = NULL;


static HWND  ghwndMain;
static char *gszAppName;
static CONTAINER_TYPE container_type = CONTAINER_TYPE_NOT_DEFINED;
static jclass nativeMethodInterfacePointer = NULL;


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jint bucket_GetDC(jint hWnd_address)
{
    return (jint) GetDC((HWND) hWnd_address);
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL open_file(char *szFileName)					   
{
    AlertBox("Sorry, opening files is not working yet.");
    return TRUE;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL FileSave(WORD wFlags)
{
    AlertBox("Ha! You don't really want to save the file, do you?");
    return TRUE;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL save()
{
    return(FileSave(0));
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL save_as()
{
    return(FileSave(4));
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jint paste_object(jint hWnd_address)
{
    return 0;
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void set_up_backwards_pointers(JNIEnv *env, jobject container)
{
    nativeMethodInterfacePointer = container;
    container_type = JAVA_CONTAINER;
}
			       

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *unicode_to_ascii(WCHAR *unicode)
{
    char *ascii;
    int len, i;

    len = wcslen(unicode) + 1;
    ascii = (char *) malloc(len * sizeof(char));

    for (i=0; i<len; i++)
	ascii[i] = (char) unicode[i];

    return ascii;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *unicode_to_ascii_identifier(WCHAR *unicode)
{
    char *ascii;
    int len, i, j;
    WCHAR c;

    len = wcslen(unicode);
    ascii = (char *) malloc((len + 1) * sizeof(char));
    dprintf(0, "making string of length %d", len);

    for (i=0; i<len; i++) {
	c = unicode[i];
	/* if (IS_IDENTIFIER_CHAR(c)) { */
	if (((c>='a')&&(c<='z'))||
	    ((c>='A')&&(c<='Z'))||
	    ((c>='0')&&(c<='9'))||
	    (c=='_')) {
	    ascii[j++] = (char) c;
	} else {
	    dprintf(0, "nope, %d ain't no identfier char", c);
	}
    }
    ascii[j] = 0;

    return ascii;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
WCHAR *ascii_to_unicode(char *ascii)
{
    WCHAR *unicode;
    int len, i;

    len = strlen(ascii) + 1;
    unicode = (WCHAR *) malloc(len * sizeof(WCHAR));

    for (i=0; i<len; i++)
	unicode[i] = (WCHAR) ascii[i];

    return unicode;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *java_to_c_string(JNIEnv *env, jstring jstr)
{
    dprintf(0, "Error: could not convert java string to UTF string because");
    dprintf(0, "I don't have a pointer to the VM.");
    return NULL;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jstring c_to_java_string(JNIEnv *env, char *str)
{
    dprintf(0, "Error: could not convert UTF string to java string because");
    dprintf(0, "I don't have a pointer to the VM.");
    return NULL;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jstring wstring_to_jstring(JNIEnv *env, WCHAR *wstr)
{
    dprintf(0, "Error: could not convert UTF string to java string because");
    dprintf(0, "I don't have a pointer to the VM.");
    return NULL;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
WCHAR *java_to_unicode_string(JNIEnv *env, jstring str)
{
    dprintf(0,
         "Error: could not convert java string to unicode string because");
    dprintf(0, "I don't have a pointer to the VM.");
    return NULL;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_com_NativeMethodBroker_containerSetup
 (JNIEnv *env, jclass pThis,
  jstring external_name,
  jint external_appInstance)
{
    char *external_gszname;

    external_gszname = java_to_c_string(env, external_name);
    if (external_gszname == (char *) 4)
	dprintf(2, "external name = %s\n", external_gszname);
    set_up_backwards_pointers(env, pThis);
    container_setup(env, external_gszname, external_appInstance);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void set_up_container_callbacks(void *set_open_function, void *clear_open_function,
				void *redraw_function, long ghwnd)
{
    ntw_SetOpen_pointer = set_open_function;
    ntw_ClearOpen_pointer = clear_open_function;
    ntw_Redraw_pointer = redraw_function;
    ghwndMain = (HWND) ghwnd;

    container_type = C_CONTAINER;
}
			       

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void client_force_redraw(PCOMOBJ pObj)
{
    setDirty(TRUE);
    if (container_type == C_CONTAINER) {
	ntw_Redraw_pointer(pObj);
    } else if (container_type == JAVA_CONTAINER) {
	dprintf(2, "Calling into java");

	dprintf(0, "Error: could not call Java method because I don't have a ");
	dprintf(0, "pointer to the VM.");
	return;
    } else {
	AlertBox("Don't know how to force redraw");
    }
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void client_set_open_in_window(PCOMOBJ pObj, short fShow)
{
    if (container_type == C_CONTAINER) {
	if ((fShow == 1) && (ntw_SetOpen_pointer)) {
	    ntw_SetOpen_pointer(pObj);
	} else {
	    ntw_ClearOpen_pointer(pObj);
	}
    } else if (container_type == JAVA_CONTAINER) {

	dprintf(2, "Calling into java");

	dprintf(0, "Error: could not call Java method because I don't have a ");
	dprintf(0, "pointer to the VM.");
	return;
    } else {
	AlertBox("Don't know how to set open");
    }
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL PromptToSave()
{
    // if (getDirty())
    dprintf(PROGRESS, "You have not saved this document, Slim.");
    return TRUE;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
CLSID *get_clsid_from_user (long hWnd_address)
{
    HWND hWnd;
    char szFile[OLEUI_CCHPATHMAX];
    UINT uiRet;
    OLEUIINSERTOBJECT  insert_object;

    hWnd = (HWND) hWnd_address;
    dprintf(PROGRESS, "InsertOleObj");

    /* Fill the info struct with zeroes and fill in any fields we might need to.  
       Mostly this is a case of copying the example source code. */
    memset(&insert_object, 0, sizeof(insert_object));
    insert_object.cbStruct = sizeof(insert_object);
    insert_object.dwFlags = IOF_SELECTCREATENEW | IOF_SHOWHELP;
    insert_object.hWndOwner = hWnd;
    szFile[0] = '\0';
    insert_object.lpszFile = szFile;
    insert_object.cchFile = sizeof(szFile);

    uiRet = OleUIInsertObject(&insert_object);

    if (uiRet != OLEUI_OK) {
	if (uiRet != OLEUI_CANCEL)
	    if (uiRet == OLEUI_ERR_HWNDOWNERINVALID)
		AlertBox("The specified hwnd address, %x, was not a valid HWND",
			 hWnd_address);
	    else
		AlertBox("Insert Dialog failed (%d)", uiRet);
	return NULL;
    }

    if (insert_object.dwFlags & IOF_SELECTCREATEFROMFILE) {
	dprintf(PROGRESS,"Before File creation warning");
	AlertBox("File creation not supported yet");
	dprintf(PROGRESS,"After File creation warning");
	return NULL;
    }

    if (insert_object.dwFlags & IOF_CHECKLINK) {
	AlertBox("Linking is not supported yet");
	return NULL;
    }

    /* should only be this case left */
    ASSERT(insert_object.dwFlags & IOF_SELECTCREATENEW); 
  
    return &(insert_object.clsid);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
LPDISPATCH get_idispatch_from_iunknown(LPUNKNOWN pUnk)
{
    LPDISPATCH pdisp;
    LPVIEWOBJECT2 pview;
    LPVIEWOBJECT pview1;
    HRESULT hr;

    if (!pUnk) {
	dprintf(1, "Error: received null pUnknown");
	return NULL;
    }

    dprintf(4, "************************************************************");
    dprintf(4, "************************************************************");
    dprintf(4, "************************************************************");
    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IViewObject2,
				      (void FAR* FAR*)&pview);
    if (FAILED(hr)) {
	if (pview) {
	    pview->lpVtbl->Release(pview);
	    dprintf(2, "This object seems to support IViewObject2,");
	    dprintf(2, "although queryinterface failed");
	} else {
	    dprintf(2, "This object does *not* support IViewObject2");
	}
    } else {
	dprintf(2, "This object SUPPORTS IViewObject2");
	pview->lpVtbl->Release(pview);
    }

    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IViewObject,
				      (void FAR* FAR*)&pview1);
    if (FAILED(hr)) {
	if (pview1) {
	    pview1->lpVtbl->Release(pview1);
	    dprintf(2, "This object seems to support IViewObject,");
	    dprintf(2, "although queryinterface failed");
	} else {
	    dprintf(2, "This object does *not* support IViewObject");
	}
    } else {
	dprintf(2, "This object SUPPORTS IViewObject");
	pview1->lpVtbl->Release(pview1);
    }


    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IDispatch, (void FAR* FAR*)&pdisp);
    if (FAILED(hr)) {
	/* pUnk->lpVtbl->Release(pUnk); */
	if (pdisp) {
	    /* pdisp->lpVtbl->Release(pdisp); */
	    dprintf(2, "This object seems to support IDispatch,");
	    dprintf(2, "although queryinterface failed");
	} else {
	    dprintf(2, "This object does *not* support IDispatch");
	}
	return NULL;
    } else {
	dprintf(2, "This object SUPPORTS IDispatch");
    }

    dprintf(4, "************************************************************");
    dprintf(4, "************************************************************");
    dprintf(4, "************************************************************");

    /* pUnk->lpVtbl->Release(pUnk); */
    return pdisp;
}  

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
LPUNKNOWN create_object_from_progid(LPOLESTR pszProgID)
{
    CLSID clsid;
    HRESULT hr;
    LPUNKNOWN pUnk;
    
    /* Retrieve CLSID from the progID that the user specified */
    hr = CLSIDFromProgID(pszProgID, &clsid);
    if (FAILED(hr)) {
	AlertBox("Failed to get clsid from progid");
	return NULL;
    }
    
    /* Create an instance of the automation object and ask for the IDispatch interface */
    hr = CoCreateInstance(&clsid, NULL, CLSCTX_LOCAL_SERVER, &IID_IUnknown,
			  (void FAR* FAR*)&pUnk);
    if (FAILED(hr)) {
	dprintf(1, "CoCreateInstance returned failure 0x%x", hr);
	AlertBox("Failed to create instance");
	/* if (pUnk) pUnk->lpVtbl->Release(pUnk); */
	return NULL;
    }
    dprintf(3, "CoCreated instance (%x)", hr);
    return pUnk;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void jemit_everything(JNIEnv *env)
{
}

jshort get_short_value(JNIEnv *env, jobject object)
{
    return (jshort) 0;
}


jint get_int_value(JNIEnv *env, jobject object)
{
    return (jint) 0;
}


jfloat get_float_value(JNIEnv *env, jobject object)
{
    return (jfloat) 0.0;
}


jlong get_date_value(JNIEnv *env, jobject object)
{
    return (jlong) 0;
}


jlong get_long_value(JNIEnv *env, jobject object)
{
    return (jlong) 0;
}


jint get_color_value(JNIEnv *env, jobject object)
{
    return (jint) 0;
}


jboolean get_boolean_value(JNIEnv *env, jobject object)
{
    return (jboolean) FALSE;
}


BSTR get_string_value(JNIEnv *env, jobject object)
{
    return (BSTR) NULL;
}


jshort get_vartype(JNIEnv *env, jobject object)
{
    return (jshort) 0;
}



#else /* WIN32 */

#endif /* WIN32 */

/******************************************************************************

    Module:      ConfirmExitDlg.cpp
    Copyright: 
           
    Author(s): Prihodko Vladimir

    Description:  Implementation of confirm exit dialog for twng


    File Organization:
    Section:      INCLUDE FILES
    Section:      DEFINES
    Section:      GLOBALS
    Section:      FUNCTION GROUP

    External Interface:

        FUNCTIONS: 
            Asks (if necessary) user to exit (see detailed description below)
            bool ConfirmExitDialog_AskToExit();

            Return dialog window handle (usable for testing only)
            const HWND& GetConfirmExitDialogHandle();

        GLOBAL CONSTANTS: 
            Registry section to hold values
            LPCTSTR ConfirmExitDialog_RegSection = TEXT("UiSettings");

            Registry entry to hold state of "Don't ask again" checkbox
            LPCTSTR ConfirmExitDialog_DontAskAgain_RegEntry = TEXT("DontAskAgainOnExit");

    Dependencies:

    Notes:

    Modifications:
    11/04/09,  adding these comments.  File created.

*********************************************************************************/

//////////////////////////////////////////////////////////////////////////////////
//
// Section:      INCLUDE FILES
// Description:  All required include files are referenced here.
//
// Notes:
//
// Modifications:
// 
//////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConfirmExitDlg.h"

//////////////////////////////////////////////////////////////////////////////////
//
// Section:      DEFINES
// Description:  All preprocessor defines are placed here.
//
// Notes:
//
// Modifications:
// 
//////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////////////
//
// Section:      GLOBALS
// Description:  All global variables defined here
//
// Notes:
//
// Modifications:
// 
//////////////////////////////////////////////////////////////////////////////////

// Dialog window handle
static HWND dialogHandle = 0;					

// Registry section to hold values
LPCTSTR ConfirmExitDialog_RegSection = TEXT("UiSettings");

// Registry entry to hold state of "Don't ask again" checkbox
LPCTSTR ConfirmExitDialog_DontAskAgain_RegEntry = TEXT("DontAskAgainOnExit");

//////////////////////////////////////////////////////////////////////////////////
//
// Section:      FUNCTION GROUP
// Description:  
//
// Notes:
//
// Modifications:
// 
//////////////////////////////////////////////////////////////////////////////////
// Prototypes for internally used functions
static int CALLBACK ConfirmExitDialog_DialogProc(HWND, UINT, WPARAM, LPARAM);
static int ConfirmExitDialog_OnInitDialog(HWND, WPARAM, LPARAM);
static int ConfirmExitDialog_OnCommand(HWND, WPARAM, LPARAM);
static int ConfirmExitDialog_OnDestroy(HWND);

//--------------------------------------------------------------------------------
//  bool ConfirmExitDialog_AskToExit()
//
//  Asks (if necessary) user to exit.
//
//  Show dialog with question "Are you sure you want to exit Telewindows?"
//  in case if "Don't ask again" checkbox of this dialog was not checked before
//  (in some of previous or in shis sessions).
//  Otherwise dialog not displayed.
//
//  If dialog displayed then function return true if user clicked "Yes" button.
//  If dialog not displayed function return true immediately.
//  If user click "No" button or press "Esc" key then function return false.
//
//--------------------------------------------------------------------------------
bool ConfirmExitDialog_AskToExit()
{
    // read of last "Don't ask again" checkbox state from registry
    bool dontAskAgain = (AfxGetApp()->GetProfileInt(ConfirmExitDialog_RegSection,
            ConfirmExitDialog_DontAskAgain_RegEntry, 0) != 0);
    if (dontAskAgain)	// If last checkbox state is checked
    {
        // Exit application at once, without prompting of user
        return true;
    }
    else
    {
        // Prompt of user
        INT_PTR result = DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_CONFIRMEXIT),
            0, ConfirmExitDialog_DialogProc);
        // Exit if dialog returned IDYES,  that is to say "Yes" button was clicked,
        // or on error (otherwise, on error, user won't be able to quit)
        return (-1 == result) || (result == IDYES);
    }
    
}

//--------------------------------------------------------------------------------
//
// Return dialog window handle
// (see ConfirmExitDialog_OnInitDialog and ConfirmExitDialog_OnDestroy)
//
//--------------------------------------------------------------------------------
const HWND& GetConfirmExitDialogHandle()
{
    return dialogHandle;
}

/*********************************************************************************

                            IMPLEMENTATION

            All functions below using internally only


*********************************************************************************/

//--------------------------------------------------------------------------------
//
//  Dialog procedure
//  Simply call corresponding message handler and return result of this call.
//
//--------------------------------------------------------------------------------
static int CALLBACK ConfirmExitDialog_DialogProc(HWND hwndDlg, UINT uMsg, 
                                                 WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:		return ConfirmExitDialog_OnInitDialog(hwndDlg, wParam, lParam);
    case WM_COMMAND:		return ConfirmExitDialog_OnCommand(hwndDlg, wParam, lParam);
    case WM_DESTROY:		return ConfirmExitDialog_OnDestroy(hwndDlg);
    default:				return FALSE;
    }
}

//////////////////////////////////////////////////////////////////////////////////
//
// MESSAGES HANDLERS
//
//--------------------------------------------------------------------------------
//
// WM_INITDIALOG message handler.
// Save dialog window handle.
// 
//--------------------------------------------------------------------------------
static int ConfirmExitDialog_OnInitDialog(HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
    dialogHandle = hwndDlg;
    return TRUE;
}

//--------------------------------------------------------------------------------
//
// WM_COMMAND message handler (handle button clicks)
//
//--------------------------------------------------------------------------------
static int ConfirmExitDialog_OnCommand(HWND hwndDlg, WPARAM wParam, LPARAM lParam)
{
    UINT idControl = LOWORD(wParam);
    UINT notifyCode = HIWORD(wParam);

    if (BN_CLICKED == notifyCode)			// button clicked
    {
        switch (idControl)					// which button exactly?
        {
        case IDYES:							// "Yes" button clicked 
        case IDNO:							// "No" button clicked 
            {
                // If user clicks "Yes" or "No" button we must 
                // save checkbox state to registry
                // get checkbox state from dialog
                int checkboxState = SendDlgItemMessage(hwndDlg, IDC_DONTASK_CHECK, 
                            BM_GETCHECK, 0, 0);
                checkboxState = (BST_CHECKED == checkboxState ? 1 : 0);
                // write it to registry
                AfxGetApp()->WriteProfileInt(ConfirmExitDialog_RegSection,
                        ConfirmExitDialog_DontAskAgain_RegEntry, checkboxState);
                // pass button id
                EndDialog(hwndDlg, idControl);
                return TRUE;
            }
        case IDCANCEL:						// "Esc" key pressed
            EndDialog(hwndDlg, IDCANCEL);	// pass button id
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------------------------
//
// WM_DESTROY message handler (set dialog handle to invalid)
//
//--------------------------------------------------------------------------------
static int ConfirmExitDialog_OnDestroy(HWND hwndDlg)
{
    
    dialogHandle = 0;
    return TRUE;
}
//
// END OF MESSAGE HANDLERS
//
//////////////////////////////////////////////////////////////////////////////////

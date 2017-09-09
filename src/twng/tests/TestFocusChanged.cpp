#include "stdafx.h"
#include "TestFocusChanged.h"
#include "DynamicTabsDlg.h"
#include "msincls.h"

extern "C" HWND g2pvt_create_dialogMFC (DIALOGINFO *dlgInfo, int handle);
extern BOOL g2pvt_create_mfc_control (HWND hwndParent, CONTROLITEM *pcontrol,
                               TABITEM *ptabitem);
extern BOOL g2pvt_create_child_control (HWND hwndParent, CONTROLITEM *pcontrol,
                                        TABITEM *ptabitem);
extern HWND hwndMain;

extern "C" LPG2INFO g2pvt_make_new_window_info(HWND hwnd, int handle);

CPPUNIT_TEST_SUITE_REGISTRATION(TestFocusChanged);

static DIALOGINFO* MakeDlgInfo(GENSYMDIALOG* dialog)
{
	DIALOGINFO *dlgInfo;
	dlgInfo = (DIALOGINFO *) malloc(sizeof(DIALOGINFO));

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(),L"G2"); 
	CPPUNIT_ASSERT(hIcon);

	ZeroMemory((LPVOID)dlgInfo, sizeof(DIALOGINFO));

	dlgInfo->_pdialog = dialog;
	dlgInfo->_tabPages = NULL;
	dlgInfo->_controlHwndList = NULL;
	dlgInfo->_numControlHwnds = 0;
	dlgInfo->icon = (int)hIcon;
	dlgInfo->resizable = 0;

	return dlgInfo;
}

void TestFocusChanged::test()
{
	
	TABITEM *pTabItem = NULL;
	G2EVENT *event;
	LPG2INFO lpG2Info;
	
	BOOL bFocusSet, bFocusKill;
	bFocusSet = bFocusKill = FALSE;

	DIALOGINFO* pDialogInfo = MakeDlgInfo(dialog);
	
	HWND hWnd = g2pvt_create_dialogMFC (pDialogInfo, 12);

	dialog->hwnd = hWnd;

	lpG2Info = g2pvt_make_new_window_info(hWnd, 12);
	
	g2pvt_create_mfc_control(hWnd, pTab, pTabItem);
	pDialogInfo = (DIALOGINFO *)GetWindowLong(hWnd, GWL_USERDATA);
	pTabItem = pDialogInfo->_tabPages;
	g2pvt_create_child_control(hWnd,pTextBox,pTabItem);

	pDialogInfo = (DIALOGINFO *)GetWindowLong(hWnd, GWL_USERDATA);
	pDialogInfo->_pdialog->control_count = 2;
	pDialogInfo->_pdialog->pcontrols = pControls;

	CONTROLITEM* pTextDialog = pDialogInfo->_pdialog->pcontrols[1];
	CONTROLHWND* ctrlTextBox = pDialogInfo->_controlHwndList;

	if(ctrlTextBox->controlId == pTextDialog->_controlId)
	{
		HWND hTextBox = ctrlTextBox->hwndControl;		
		if (pTextDialog->_type == ctTextBx) {			
			
			hwndMain = dialog->hwnd;
			GhwndWin = hTextBox;
			
			SendMessage(hTextBox,WM_SETFOCUS,0,0);
			LPG2INFO lpG2Info = GetlpG2Info(dialog->hwnd);
			event = lpG2Info->events_tail;	
			if(event != NULL)
			{
				if(event->hwnd == hTextBox && event->type == 11)		
					bFocusSet = TRUE;		
				delete event;
				lpG2Info->events_tail = NULL;
			}

			SendMessage(hTextBox,WM_KILLFOCUS,0,0);
			lpG2Info = GetlpG2Info(dialog->hwnd);
			event = lpG2Info->events_tail;	
			if(event != NULL)
				if(event->hwnd == hTextBox && event->type == 11)		
					bFocusKill = TRUE;

		}
	}	
	CPPUNIT_ASSERT(bFocusSet && bFocusKill);
}

void TestFocusChanged::setUp()
{
	pTab = new CONTROLITEM();
	ZeroMemory((LPVOID)pTab, sizeof(CONTROLITEM));
	pTab->_dialogId = 58; //12
	pTab->_controlId = 16;
	pTab->_parentControlId = -1;
	pTab->_type = 32;
	pTab->_x = 1;
	pTab->_y = 1;
	pTab->_width = 332;
	pTab->_height = 116;
	pTab->_mText = L"Test Tab-1";
	pTab->_respcode = 0;
	pTab->_g2styles = 256;
	pTab->_styles = 1409351680;


	pTextBox = new CONTROLITEM();
	ZeroMemory((LPVOID)pTextBox, sizeof(CONTROLITEM));
	pTextBox->_dialogId = 12;
	pTextBox->_controlId = 18;
	pTextBox->_parentControlId = pTab->_controlId;
	pTextBox->_parentControlText = L"Parent Control Text";
	pTextBox->_type = 128;
	pTextBox->_x = 62;
	pTextBox->_y = 43;
	pTextBox->_width = 332;
	pTextBox->_height = 116;
	pTextBox->_mText = L"This is text-box";
	pTextBox->_respcode = 12;
	pTextBox->_g2styles = 256;
	pTextBox->	_styles = 1342242944;
	
	pControls = new CONTROLITEM*[2];
	pControls[0] = pTab;
	pControls[1] = pTextBox;

	int len = 0;
	int guess_ncontrols = 0;
	dialog = (GENSYMDIALOG *) malloc(sizeof(GENSYMDIALOG));

	ZeroMemory((LPVOID) dialog, sizeof(GENSYMDIALOG));
	dialog->pcontrols = (CONTROLITEM **) malloc(guess_ncontrols *
	sizeof(CONTROLITEM));

	int nTextLen = 20;	
	wchar_t *szBuf = NULL;
	szBuf = new wchar_t[nTextLen];
	ZeroMemory((PVOID)szBuf, sizeof(wchar_t) * (nTextLen));

	//CONTROLITEMRESPONSE** pCtrlResponse =  (CONTROLITEMRESPONSE **) malloc(guess_ncontrols * sizeof(CONTROLITEMRESPONSE));
	CONTROLITEMRESPONSE** pCtrlResponse;
	pCtrlResponse = new CONTROLITEMRESPONSE*[2];
	pCtrlResponse[0] = (CONTROLITEMRESPONSE *) malloc(sizeof(CONTROLITEMRESPONSE));
	//ZeroMemory((LPVOID) (*pCtrlResponse), sizeof(CONTROLITEMRESPONSE));
	pCtrlResponse[0]->_controlId = pTab->_controlId;
	pCtrlResponse[0]->_mResponseString = szBuf;
	

	GENSYMDLGRESPONSE* pResponse = (GENSYMDLGRESPONSE *) malloc(sizeof(GENSYMDLGRESPONSE));
	ZeroMemory((LPVOID) pResponse, sizeof(GENSYMDLGRESPONSE));
	pResponse->response_count = 1;
	pResponse->dialog_id = pTab->_dialogId;
	pResponse->initiating_control_id = pTab->_controlId;
	pResponse->presponses = pCtrlResponse; 

	ZeroMemory((LPVOID)dialog->pcontrols,guess_ncontrols * sizeof(CONTROLITEM));
	dialog->control_count = 0;
	dialog->array_size = guess_ncontrols;
	dialog->g2_id = 1111;	// G2-assigned integer handle
	dialog->dialog_id = 0;
	dialog->width = 334;
	dialog->height = 156;
	dialog->_iDlgType = 2;
	dialog->_mTitle = L"FocusChanged Test Case.";
	dialog->mResponse = pResponse;
}

void TestFocusChanged::tearDown()
{
	if(dialog->mResponse != NULL)
	{
		GENSYMDLGRESPONSE* pdlgresponse = dialog->mResponse; 
		for (int i = 0; i < pdlgresponse->response_count; i++) {
			if (pdlgresponse->presponses[i]) {
			  if(pdlgresponse->presponses[i]->_mResponseString)
 			free(pdlgresponse->presponses[i]->_mResponseString);
			  delete pdlgresponse->presponses[i];
			  pdlgresponse->presponses[i] = NULL;
			}
		}
		delete pdlgresponse->presponses; 
		pdlgresponse->presponses = NULL;
	}
	delete dialog->mResponse;
	delete pTab;
	delete pTextBox;
	delete dialog;
}

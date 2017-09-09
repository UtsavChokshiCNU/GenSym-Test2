#include "stdafx.h"
#include "TestGdiDecrease.h"
#include "Windows.h"
#include "dyndlgs.h"
#include <string>
#include "MainFrm.h"
#include "DynamicBaseDlg.h"

extern "C" HWND g2pvt_create_dialogMFC (DIALOGINFO *dlgInfo, int handle);
extern "C"   void g2pvt_destroy_containing_pane_if_any(HWND hwnd, int handle);
	
CPPUNIT_TEST_SUITE_REGISTRATION(TestGdiDecrease);


void TestGdiDecrease::IconDestroy()
{

	GENSYMDIALOG *new_dialog;
	int len = 0;
	int guess_ncontrols = 0;
	new_dialog = (GENSYMDIALOG *) malloc(sizeof(GENSYMDIALOG));

	ZeroMemory((LPVOID) new_dialog, sizeof(GENSYMDIALOG));
	new_dialog->pcontrols = (CONTROLITEM **) malloc(guess_ncontrols *
	sizeof(CONTROLITEM));

	ZeroMemory((LPVOID)new_dialog->pcontrols,
	guess_ncontrols * sizeof(CONTROLITEM));
	new_dialog->control_count = 0;
	new_dialog->array_size = guess_ncontrols;
	new_dialog->g2_id = 1111;	// G2-assigned integer handle
	new_dialog->dialog_id = 0;
	new_dialog->width = 100;
	new_dialog->height = 200;
	new_dialog->_iDlgType = 2;
	new_dialog->mResponse = NULL;

	DIALOGINFO *dlgInfo;
	dlgInfo = (DIALOGINFO *) malloc(sizeof(DIALOGINFO));

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(),L"G2"); 
	CPPUNIT_ASSERT(hIcon);

	ZeroMemory((LPVOID)dlgInfo, sizeof(DIALOGINFO));

	dlgInfo->_pdialog = new_dialog;
	dlgInfo->_tabPages = NULL;
	dlgInfo->_controlHwndList = NULL;
	dlgInfo->_numControlHwnds = 0;
	dlgInfo->icon = (int)hIcon;
	dlgInfo->resizable = 0;

	int id = 0xFF;
	HWND hwndDlg = g2pvt_create_dialogMFC(dlgInfo, id);
	CPPUNIT_ASSERT(hwndDlg);

	CWnd * pWnd = CWnd::FromHandle(hwndDlg);
	CPPUNIT_ASSERT(pWnd);

	HICON cpyIcon = CopyIcon(hIcon);
	pWnd->SetIcon(cpyIcon,FALSE);

	HICON delIcon = pWnd->GetIcon(FALSE);
	CPPUNIT_ASSERT(delIcon);

	g2pvt_destroy_containing_pane_if_any(hwndDlg, id); //destroy icon
	
	CPPUNIT_ASSERT(pWnd->GetIcon(FALSE) == 0);
}

void TestGdiDecrease::setUp()
{
}

void TestGdiDecrease::tearDown()
{
}

#include "TestLockedDialog.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestLockedDialog);

#define USE_PROTOTYPES

extern "C" {
	#include "dyndlgs.h"
	#include "cprim.h"

    extern GENSYMDIALOG *list_of_dialogs;
	BOOL IsCommandLocked(ULONG cmd);

	long g2ext_start_dialog (long g2_id, long guess_ncontrols, long width, long height,
                         long type, LPWSTR pTitle);

	GENSYMDIALOG *g2pvt_find_dialog(int g2_id);

	void g2ext_lock_dialog (long dialog_id, long locked_p);
	BOOL IsLockedDialog(HWND hWnd);

	long g2ext_show_dialog (long pDialog, long xPos, long yPos, long mdi_child_p,
			long dock, long neighbor, long icon, long resizable_p);
}

LRESULT CALLBACK DynamicDlgProc (HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

static int commands[] = {SC_SIZE, SC_MOVE, SC_MINIMIZE, SC_MAXIMIZE, SC_NEXTWINDOW, SC_PREVWINDOW,
			SC_CLOSE, SC_MOUSEMENU, SC_KEYMENU, SC_RESTORE};

void TestLockedDialog::testIsCommandLocked()
{
	for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++)
	{
		CPPUNIT_ASSERT(IsCommandLocked(commands[i]));
	}
}

void TestLockedDialog::testStartAndLockDialog()
{
	int id = 0x101;
	long dialog = g2ext_start_dialog(id, 1, 100, 100, 0, L"testStartAndLockDialog");

	GENSYMDIALOG* dlg = g2pvt_find_dialog(id);

	CPPUNIT_ASSERT(dlg != NULL);
	CPPUNIT_ASSERT(dlg->g2_id == id);
	CPPUNIT_ASSERT(dlg->is_locked == FALSE);

	g2ext_lock_dialog(id, TRUE);
	CPPUNIT_ASSERT(dlg->is_locked == TRUE);

	dlg->hwnd = (HWND) 0x1000;
	CPPUNIT_ASSERT(IsLockedDialog(dlg->hwnd));
}

void TestLockedDialog::testLockDialog()
{
	int id = 0x102;
	long dialog = g2ext_start_dialog(id, 1, 100, 100, 0, L"testLockDialog");
	long wnd = g2ext_show_dialog(dialog, 0, 0, FALSE, 0, 0, 0, TRUE);

	typedef Cpointer (*g2pointer_to_cpointer_func_t)(G2pointer);

	g2pointer_to_cpointer_func_t g2pointer_to_cpointer =
		(g2pointer_to_cpointer_func_t) g2ext_map_g2pointer_to_cpointer;

	hWnd = (HWND) g2pointer_to_cpointer(wnd);

	CPPUNIT_ASSERT(hWnd != NULL);
	CPPUNIT_ASSERT(!IsLockedDialog(hWnd));

	for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++)
	{
		CPPUNIT_ASSERT(DynamicDlgProc(hWnd, WM_SYSCOMMAND, commands[i], 0) == 0);
	}

	g2ext_lock_dialog(id, TRUE);
	CPPUNIT_ASSERT(IsLockedDialog(hWnd));

	for (int j = 0; j < sizeof(commands)/sizeof(commands[0]); j++)
	{
		CPPUNIT_ASSERT(DynamicDlgProc(hWnd, WM_SYSCOMMAND, commands[j], 0) == 1);
		CPPUNIT_ASSERT(SendMessage(hWnd, WM_SYSCOMMAND, commands[j], 0) == 0);
	}
}

void TestLockedDialog::setUp()
{
	hWnd = NULL;
}

void TestLockedDialog::tearDown()
{
	if (hWnd != NULL)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}
	list_of_dialogs = 0;
}

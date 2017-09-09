#include "stdafx.h"
#include "TestDialogDismiss.h"

#include "Twng.h"
#include "dyndlgs.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDialogDismiss);

extern "C" {

	Cpointer  g2ext_map_g2pointer_to_cpointer(G2pointer);

	long g2ext_start_dialog (long g2_id, long guess_ncontrols, long width, long height,
		long type, LPWSTR pTitle);

	GENSYMDIALOG *g2pvt_find_dialog(int g2_id);

	long g2ext_show_dialog (long pDialog, long xPos, long yPos, long mdi_child_p,
		long dock, long neighbor, long icon, long resizable_p);

	long g2pvt_dismiss_dialog (GENSYMDIALOG *dialog, long respcode);
}

void TestDialogDismiss::test()
{
	int g2_id = 12;
	long dialog_id = g2ext_start_dialog(g2_id, 32, 100, 100, 2, L"TestDialogDismiss");
	long dialog_g2pointer = g2ext_show_dialog(dialog_id, 0, 0, 1, 0, 0, -2, 0);

	GENSYMDIALOG* dlg = g2pvt_find_dialog(g2_id);

	CPPUNIT_ASSERT(dlg != NULL);
	CPPUNIT_ASSERT(dlg->g2_id == g2_id);

	GENSYMDIALOG* dlg_temp = (GENSYMDIALOG*) g2ext_map_g2pointer_to_cpointer(dialog_id);
	CPPUNIT_ASSERT(dlg == dlg_temp);

	HWND hwndDlg = (HWND)g2ext_map_g2pointer_to_cpointer(dialog_g2pointer);
	CPPUNIT_ASSERT(hwndDlg == dlg->hwnd);

	g2pvt_dismiss_dialog(dlg, 1);
	Sleep(50);

	hwndDlg = (HWND)g2ext_map_g2pointer_to_cpointer(dialog_g2pointer);
	CPPUNIT_ASSERT(hwndDlg == NULL); //test dialog->dialog_g2pointer has been decached
}

void TestDialogDismiss::setUp()
{
}

void TestDialogDismiss::tearDown()
{
}

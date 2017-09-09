#include "TestDynamicTabDlg.h"


//CPPUNIT_TEST_SUITE_REGISTRATION(TestDynamicTabDlg);



    extern TABITEM *get_tab_dialog (HWND hwnd, UINT controlId, UINT nTabNum);


void TestDynamicTabDlg::testTab()
{
    pParent = new CWnd();
    pTab = new CG2TabWidget;
    CONTROLITEM pcontrol = {59, 32, 16, -1, L"", 10, 10, 180,
                        160, 1409351680, 336, L"Tab 1\Tab 2Tab 1  0",
                        0, 0, 0, 0};
    RECT rectAdj={15, 16, 285, 276};
    pTab->CreateTabs(pParent, &pcontrol, &rectAdj);
    TABITEM *p_cur_tabitem;
    for(int i = 0; i<2; i++)
    {
        p_cur_tabitem = get_tab_dialog(pParent->m_hWnd, pcontrol._controlId, i);
        CPPUNIT_ASSERT(p_cur_tabitem->hwndChildDlg == NULL);
			CPPUNIT_ASSERT(TRUE);
    }
}
void TestDynamicTabDlg::setup()
{
}

void TestDynamicTabDlg::tearDown()
{
}

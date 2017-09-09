// ExplorerTheme.h: interface for the CExplorerTheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_)
#define AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExplorerTabPaintManager : public CXTPTabPaintManager
{
public:
	CExplorerTabPaintManager();

	void DrawNavigateButton(CDC* pDC, CXTPTabManagerNavigateButton* pButton, CRect& rc);
	
public:
	class CExplorerTabAppearance : public CXTPTabPaintManager::CAppearanceSetPropertyPage
	{
	public:
		void DrawSingleButton(CDC* pDC, CXTPTabManagerItem* pItem);
		CXTPResourceImages m_images;
	};
};

#endif // !defined(AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_)

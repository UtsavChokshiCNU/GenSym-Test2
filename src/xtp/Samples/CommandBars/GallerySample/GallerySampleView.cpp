// GallerySampleView.cpp : implementation of the CGallerySampleView class
//

#include "stdafx.h"
#include "GallerySample.h"

#include "GallerySampleDoc.h"
#include "CntrItem.h"
#include "GallerySampleView.h"
#include "MainFrm.h"
#include "GalleryItems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleView

IMPLEMENT_DYNCREATE(CGallerySampleView, CRichEditView)

BEGIN_MESSAGE_MAP(CGallerySampleView, CRichEditView)
	//{{AFX_MSG_MAP(CGallerySampleView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FORMAT_FONTCOLOR_AUTOMATIC, OnFormatFontcolorAutomatic)
	ON_COMMAND(ID_FORMAT_FONTCOLOR_NOHIGHLIGHT, OnFormatFontcolorNoHighlight)

	ON_UPDATE_COMMAND_UI(ID_FORMAT_FONTCOLOR_AUTOMATIC, OnUpdateFormatFontcolorAutomatic)
	ON_COMMAND(ID_FORMAT_FONTCOLOR_MORECOLORS, OnFormatFontcolorMorecolors)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)

	ON_UPDATE_COMMAND_UI(ID_FORMAT_BOLD, OnUpdateCharBold)
	ON_COMMAND(ID_FORMAT_BOLD, OnCharBold)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_ITALIC, OnUpdateCharItalic)
	ON_COMMAND(ID_FORMAT_ITALIC, OnCharItalic)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_UNDERLINE, OnUpdateCharUnderline)
	ON_COMMAND(ID_FORMAT_UNDERLINE, OnCharUnderline)

	ON_COMMAND(ID_TEXT_SUBSCRIPT, OnEmptyCommand)
	ON_COMMAND(ID_TEXT_SUPERSCRIPT, OnEmptyCommand)
	ON_COMMAND(ID_CHAR_STRIKETHROUGH, OnEmptyCommand)
	ON_COMMAND(ID_FONT_CLEAR, OnEmptyCommand)
	ON_COMMAND(ID_TEXT_CHANGECASE, OnEmptyCommand)


	ON_XTP_EXECUTE(ID_GALLERY_FONTBACKCOLOR, OnGalleryFontBackColor)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTBACKCOLOR, OnUpdateGalleryFontBackColor)	

	ON_XTP_EXECUTE(ID_GALLERY_FONTTEXTCOLOR, OnGalleryFontTextColor)
	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTTEXTCOLOR, OnUpdateGalleryFontTextColor)	


	ON_UPDATE_COMMAND_UI(ID_FORMAT_FONTCOLOR, OnUpdateButtonText)
	ON_COMMAND(ID_FORMAT_FONTCOLOR, OnButtonText)

	ON_UPDATE_COMMAND_UI(ID_FORMAT_BACKCOLOR, OnUpdateBack)
	ON_COMMAND(ID_FORMAT_BACKCOLOR, OnButtonBack)


	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTFACE, OnUpdateGalleryFontFace)	

	ON_UPDATE_COMMAND_UI(ID_GALLERY_FONTSIZE, OnUpdateGalleryFontSize)	


	ON_UPDATE_COMMAND_UI(ID_EDIT_FONT, OnUpdateComboFont)
	ON_XTP_EXECUTE(ID_EDIT_FONT, OnEditFont)

	ON_UPDATE_COMMAND_UI(ID_EDIT_SIZE, OnUpdateComboSize)
	ON_XTP_EXECUTE(ID_EDIT_SIZE, OnEditSize)


	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_XTP_EXECUTE(ID_EDIT_UNDO, OnEditUndo)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleView construction/destruction

CGallerySampleView::CGallerySampleView()
{
	m_clrText = COLORREF_NULL;
	m_clrBack = COLORREF_NULL;
}

CGallerySampleView::~CGallerySampleView()
{
}

void CGallerySampleView::OnEmptyCommand()
{

}

BOOL CGallerySampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CGallerySampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleView printing

BOOL CGallerySampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CGallerySampleView::OnDestroy()
{
	CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CGallerySampleView diagnostics

#ifdef _DEBUG
void CGallerySampleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CGallerySampleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CGallerySampleDoc* CGallerySampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGallerySampleDoc)));
	return (CGallerySampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleView message handlers

void CGallerySampleView::OnGalleryFontTextColor(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pControl = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pControl)
	{
		CXTPControlGalleryItem* pItem = pControl->GetItem(pControl->GetSelectedItem());
		if (pItem)
		{
			m_clrText = (COLORREF)pItem->GetID();
			OnButtonText();
		}

		*pResult = TRUE; // Handled
	}
}

void CGallerySampleView::OnUpdateGalleryFontTextColor(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pControl = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));

	if (pControl)
	{
		pControl->SetCheckedItem(m_clrText);
	}

	pCmdUI->Enable(TRUE);
}

void CGallerySampleView::OnGalleryFontBackColor(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pControl = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pControl)
	{
		CXTPControlGalleryItem* pItem = pControl->GetItem(pControl->GetSelectedItem());
		if (pItem)
		{
			m_clrBack = (COLORREF)pItem->GetID();
			OnButtonBack();
		}

		*pResult = TRUE; // Handled
	}
}

void CGallerySampleView::OnUpdateGalleryFontBackColor(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pControl = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));

	if (pControl)
	{
		pControl->SetCheckedItem(m_clrBack);
	}

	pCmdUI->Enable(TRUE);
}


void CGallerySampleView::OnUpdateGalleryFontFace(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CGallerySampleView::OnUpdateGalleryFontSize(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CGallerySampleView::OnFormatFontcolorAutomatic() 
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	cfm.dwMask |= CFM_COLOR;
	cfm.dwEffects |= CFE_AUTOCOLOR ;
	GetRichEditCtrl().SetSelectionCharFormat(cfm);

	m_clrText = COLORREF_NULL;
}

void CGallerySampleView::OnFormatFontcolorNoHighlight()
{
	CHARFORMAT2 cfm;
	cfm.cbSize =  sizeof(CHARFORMAT2);
	::SendMessage(GetRichEditCtrl().GetSafeHwnd(), EM_GETCHARFORMAT, 1, (LPARAM)&cfm);

	cfm.dwMask |= CFM_BACKCOLOR;
	cfm.dwEffects |= CFE_AUTOBACKCOLOR ;
	::SendMessage(GetRichEditCtrl().GetSafeHwnd(), EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cfm);

	m_clrBack = COLORREF_NULL;
}

void CGallerySampleView::OnUpdateFormatFontcolorAutomatic(CCmdUI* pCmdUI) 
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	pCmdUI->SetCheck(cfm.dwEffects & CFE_AUTOCOLOR? TRUE: FALSE);	
}


void CGallerySampleView::OnUpdateButtonText(CCmdUI* pCmd)
{

	CXTPControlPopupColor* pPopup = DYNAMIC_DOWNCAST(CXTPControlPopupColor, CXTPControl::FromUI(pCmd));
	if (pPopup)
	{
		pPopup->SetColor(m_clrText == COLORREF_NULL ? 0 : m_clrText);
	}

	pCmd->Enable(TRUE);
}

void CGallerySampleView::OnButtonText()
{
	CHARFORMAT& cfm = GetCharFormatSelection( );
	cfm.dwMask |= CFM_COLOR;
	cfm.dwEffects &= ~CFE_AUTOCOLOR ;
	cfm.crTextColor = m_clrText;
	GetRichEditCtrl().SetSelectionCharFormat(cfm);

}

void CGallerySampleView::OnUpdateBack(CCmdUI* pCmdUI)
{

	CXTPControlPopupColor* pPopup = DYNAMIC_DOWNCAST(CXTPControlPopupColor, CXTPControl::FromUI(pCmdUI));
	if (pPopup)
	{
		pPopup->SetColor(m_clrBack == COLORREF_NULL ? 0xFFFFFF : m_clrBack);
	}

	pCmdUI->Enable(TRUE);
}

void CGallerySampleView::OnButtonBack()
{
	CHARFORMAT2 cfm;
	cfm.cbSize =  sizeof(CHARFORMAT2);
	::SendMessage(GetRichEditCtrl().GetSafeHwnd(), EM_GETCHARFORMAT, 1, (LPARAM)&cfm);

	cfm.dwMask |= CFM_BACKCOLOR;
	cfm.dwEffects &= ~CFE_AUTOBACKCOLOR ;
	cfm.crBackColor = m_clrBack;
	::SendMessage(GetRichEditCtrl().GetSafeHwnd(), EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cfm);
}


void CGallerySampleView::OnFormatFontcolorMorecolors() 
{
	CColorDialog cd(m_clrText);
	if (cd.DoModal())
	{
		m_clrText = cd.GetColor();
		OnButtonText();
	}	
}


void CGallerySampleView::OnUpdateComboFont(CCmdUI* pCmd)
{
	CXTPControlComboBox* pFontCombo = (CXTPControlComboBox*)CXTPControl::FromUI(pCmd);

	pCmd->Enable(TRUE);

	if (pFontCombo && pFontCombo->GetType() == xtpControlComboBox)
	{
		CHARFORMAT& cf = GetCharFormatSelection();

		if (pFontCombo->HasFocus())
			return;
		
		// the selection must be same font and charset to display correctly
		if ((cf.dwMask & (CFM_FACE | CFM_CHARSET)) == (CFM_FACE | CFM_CHARSET))
			pFontCombo->SetEditText(CString(cf.szFaceName));
		else
			pFontCombo->SetEditText(_T(""));
	}
}


void CGallerySampleView::OnEditFont(NMHDR* pNMHDR, LRESULT* pResult)
{
	USES_CONVERSION;

	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		CString strFont = pControl->GetEditText();
	
	#if (_MSC_VER < 1300)
		CHARFORMAT cf;
	#else
		CHARFORMAT2 cf;
	#endif
		cf.dwMask = CFM_FACE;
				
	#if (_RICHEDIT_VER >= 0x0200)
		lstrcpyn(cf.szFaceName, strFont, LF_FACESIZE);
	#else
		lstrcpynA(cf.szFaceName, T2A((LPTSTR)(LPCTSTR)strFont), LF_FACESIZE);
	#endif
		SetCharFormat(cf);

		*pResult = 1; // Handled;
	}
}


void CGallerySampleView::OnUpdateComboSize(CCmdUI* pCmd)
{
	CXTPControlComboBox* pFontCombo = (CXTPControlComboBox*)CXTPControl::FromUI(pCmd);

	pCmd->Enable(TRUE);

	if (pFontCombo && pFontCombo->GetType() == xtpControlComboBox)
	{
		CHARFORMAT& cf = GetCharFormatSelection();

		if (pFontCombo->HasFocus())
			return;

		int nTwip = (cf.dwMask & CFM_SIZE) ? cf.yHeight : -1;
		
		pFontCombo->SetEditText(CXTPControlSizeComboBox::TwipsToPointString(nTwip));
	}
}

void CGallerySampleView::OnEditSize(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{

	#if (_MSC_VER < 1300)
		CHARFORMAT cf;
	#else
		CHARFORMAT2 cf;
	#endif

		int nSize = CXTPControlSizeComboBox::GetTwipSize(pControl->GetEditText());
		if (nSize > 0)
		{
			cf.dwMask = CFM_SIZE;
			cf.yHeight = nSize;				

			SetCharFormat(cf);
		}

		*pResult = 1; // Handled;
	}
}


void CGallerySampleView::OnUpdateEditUndo(CCmdUI* pCmd)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmd));

	if (pControlUndo)
	{
		pCmd->Enable(GetRichEditCtrl().CanUndo());

		CXTPControlGalleryItems* pItems = pControlUndo->GetItems();
		pItems->RemoveAll();

		int nCount = RAND_S() % 20 + 3;

		for (int i = 0; i < nCount; i++)
		{
			CString str;
			str.Format(_T("Undo String %i"), i + 1);
			pItems->AddItem(new CGalleryItemUndo(str), i);
		}

		pControlUndo->OnSelectedItemChanged();
		pControlUndo->SetHeight(pItems->GetItemSize().cy * nCount + 2);

	}
	else
	{
		CRichEditView::OnUpdateEditUndo(pCmd);
	}

}

void CGallerySampleView::OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlUndo)
	{
		CString str;
		str.Format(_T("Undo last %i actions"), pControlUndo->GetSelectedItem() + 1);

		AfxMessageBox(str);
	}
	else
	{
		CRichEditView::OnEditUndo();
	}

	*pResult = 1; // Handled;
}

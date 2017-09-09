// CGridCellImage.h: interface for the CGridCellImage class.
//
// 
//  Heidi Goddard
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDIMAGECELL_H__3479ED0D_B57D_4940_B83D_9E2296ED75B5__INCLUDED_)
#define AFX_GRIDIMAGECELL_H__3479ED0D_B57D_4940_B83D_9E2296ED75B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCell.h"

class CGridCellImage : public CGridCell  
{
    DECLARE_DYNCREATE(CGridCellImage)

public:
    virtual void OnClick( CPoint PointCellRelative);
protected:
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);
    virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
    virtual void EndEdit();
public:
private:

 CRect m_rectCell;
 CRect m_IconArea;
};

#endif // !defined(AFX_GRIDIMAGECELL_H__3479ED0D_B57D_4940_B83D_9E2296ED75B5__INCLUDED_)

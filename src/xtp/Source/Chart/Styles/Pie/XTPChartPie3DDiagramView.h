// XTPChartPie3DDiagramView.h
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPCHARTPIE3DDIAGRAMVIEW_H__)
#define __XTPCHARTPIE3DDIAGRAMVIEW_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CXTPChartPie;
class CXTPChartPie3DDiagramDomain;
class CXTPChartDiagram3D;


class CXTPChartPie3DDiagramView : public CXTPChartPieDiagramView
{
public:
	CXTPChartPie3DDiagramView(CXTPChartDiagram* pDiagram, CXTPChartElementView* pParent);

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to do rotation.
	// parameters:
	//     dx - The angle to rotate about X coordinate.
	//     dy - The angle to rotate about Y coordinate.
	// Remarks:
	//-----------------------------------------------------------------------
	BOOL PerformRotation(int dx, int dy);

public:
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL OnSetCursor(CPoint point);

protected:
	CPoint m_ptOldPosition;
};


#endif //#if !defined(__XTPCHARTPIE3DDIAGRAMVIEW_H__)

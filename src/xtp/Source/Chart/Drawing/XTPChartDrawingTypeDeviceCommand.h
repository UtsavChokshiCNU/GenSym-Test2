// XTPChartDrawingTypeDeviceCommand.h
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
#if !defined(__XTPCHARTDRAWINGTYPEDEVICECOMMAND_H__)
#define __XTPCHARTDRAWINGTYPEDEVICECOMMAND_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CXTPChartDeviceCommand;
class CXTPChartDeviceContext;
class CXTPChartOpenGLDeviceContext;
class CXTPChartFont;
class CXTPChartMatrix;
class CXTPChartElement;

//===========================================================================
// Summary:
//     This class is a kind of CXTPChartDeviceCommand and it does handle some
//     house keeping works when the drawing mode is switched between native
//     and OpenGL.
// Remarks:
//===========================================================================
class _XTP_EXT_CLASS CXTPChartDrawingTypeDeviceCommand : public CXTPChartDeviceCommand
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPChartDrawingTypeDeviceCommand object.
	// Parameters:
	//      bNativeDrawing - TRUE if the drawing is native and FALSE if the drawing
	//      is OpenGL.
	// Remarks:
	//-----------------------------------------------------------------------
	CXTPChartDrawingTypeDeviceCommand(BOOL bNativeDrawing);

protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Override this function to do some ground works if any, before the OpenGL
	//      mode drawing.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	virtual void BeforeExecute(CXTPChartOpenGLDeviceContext* pDC);
	virtual void BeforeExecute(CXTPChartDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     Override this function to do some final cut if any, after the OpenGL
	//     drawing.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	virtual void AfterExecute(CXTPChartOpenGLDeviceContext* pDC);
	virtual void AfterExecute(CXTPChartDeviceContext* pDC);

protected:
	BOOL m_bDrawingType;        //TRUE if the native drawing is used and FALSE if OpenGL is used.
	BOOL m_bOldDrawingType;     //Stores the old drawing mode.
};

//===========================================================================
// Summary:
//     This class is a kind of CXTPChartDeviceCommand and it draws the element and
//     does some additional task to smooth the drawings using antialiasing.
// Remarks:
//===========================================================================
class _XTP_EXT_CLASS CXTPChartPolygonAntialiasingDeviceCommand : public CXTPChartDeviceCommand
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPChartPolygonAntialiasingDeviceCommand object.
	// Parameters:
	//      bAntiAlias - TRUE if the antialiasing is enabled and FALSE if the
	//      antialiasing is disabled.
	// Remarks:
	//-----------------------------------------------------------------------
	CXTPChartPolygonAntialiasingDeviceCommand(BOOL bAntiAlias = TRUE);
	virtual ~CXTPChartPolygonAntialiasingDeviceCommand();

protected:
	//-----------------------------------------------------------------------
	// Summary:
	//      This override do some ground works if any, before the OpenGL mode
	//      antialiased drawing of polygons.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void BeforeExecute(CXTPChartOpenGLDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     Override this function to write the drawing code in OpenGL for
	//     specific objects.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//     An instruction to execute the drawing of the object triggers the
	//     drawing of children as well.
	//-----------------------------------------------------------------------
	void Execute(CXTPChartOpenGLDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     This override do some final cut if any, after the OpenGL antialiased
	//     drawing of polygons.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void AfterExecute(CXTPChartOpenGLDeviceContext* pDC);

	void RestoreImage(CSize size);
	//-----------------------------------------------------------------------
	// Summary:
	//      This override do some ground works if any, before the native mode
	//      antialiased drawing of polygons.
	// Parameters:
	//     pDC - A pointer to the chart native device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void BeforeExecute(CXTPChartDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     This override do some final cut if any, after the native antialiased
	//     drawing of polygons.
	// Parameters:
	//     pDC - A pointer to the chart native device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void AfterExecute(CXTPChartDeviceContext* pDC);

protected:
	int shiftCount;
	double shifts[4];
	int viewport[4];                //The view port.
	double projectionMatrix[16];    //The projection matrix.
	LPBYTE pixelData;               //The pixel data.

	BOOL m_bAntiAlias;              //TRUE if antialiasing enabled, FALSE if not.
	long m_bOldAntiAlias;           //The previous value of anti aliasing.
};


#endif //#if !defined(__XTPCHARTDRAWINGTYPEDEVICECOMMAND_H__)

// XTPChartLightDeviceCommand.h
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
#if !defined(__XTPCHARTLIGHTDEVICECOMMAND_H__)
#define __XTPCHARTLIGHTDEVICECOMMAND_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//===========================================================================
// Summary:
//     This class is a kind of CXTPChartDeviceCommand and it helps in drawing
//     lighting for OpenGL drawing.
// Remarks:
//===========================================================================
class _XTP_EXT_CLASS CXTPChartLightingDeviceCommand : public CXTPChartDeviceCommand
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPChartLightingDeviceCommand object.
	// Parameters:
	//      ambientColor            - The ambient color.
	//      materialSpecularColor   - The material specular reflection color.
	//      materialEmissionColor   - The material emission color.
	//      materialShininess       - The material shininess value.
	// Remarks:
	//-----------------------------------------------------------------------
	CXTPChartLightingDeviceCommand(CXTPChartColor ambientColor, CXTPChartColor materialSpecularColor,
		CXTPChartColor materialEmissionColor, float materialShininess);

protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to do some final cut if any, after the drawing.
	// Parameters:
	//     pDC - A pointer to the OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void AfterExecute(CXTPChartOpenGLDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to write the drawing code in OpenGL for
	//     specific objects.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void ExecuteOverride(CXTPChartOpenGLDeviceContext* pDC);

protected:
	CXTPChartColor m_ambientColor;           //This specifies the ambient RGBA reflectance of the material.
	CXTPChartColor m_materialSpecularColor;  //This specifies the specular RGBA reflectance of the material.
	CXTPChartColor m_materialEmissionColor;  //This specifies the RGBA emitted light intensity of the material.
	float m_materialShininess;              //This float value specifies the RGBA specular exponent of the material.

};
//===========================================================================
// Summary:
//     This class is a kind of CXTPChartDeviceCommand and it helps in providing
//     light source for  drawing lighting for OpenGL.
// Remarks:
//===========================================================================
class _XTP_EXT_CLASS CXTPChartLightDeviceCommand : public CXTPChartDeviceCommand
{
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPChartLightingDeviceCommand object.
	// Parameters:
	//      index                   - The light source number.
	//      ambientColor            - This specifies the ambient RGBA intensity of the light.
	//                                Ambient light is the average volume of light that is created
	//                                by emission of light from all of the light sources surrounding
	//                                (or located inside of) the lit area.
	//      diffuseColor            - This specifies the diffuse RGBA intensity of the light.Diffuse
	//                                light represents a directional light cast by a light source.
	//      specularColor           - This specifys the specular RGBA intensity of the light.The
	//                                specular light reflects off the surface in a sharp and uniform way.
	//      position                - The light source position.
	//      spotDirection           - The spot light direction.
	//      spotExponent            - The spot exponent, a floating-point value that specifies the
	//                                intensity distribution of the light.
	//      spotCutoff              - The spot cut off value.This floating-point value specifies
	//                                the maximum spread angle of a light source
	//      constantAttenuation     - The constant attennuation.Constant attenuation affects the
	//                                overall intensity of the light, regardless of the distance
	//                                of a surface from the light source.
	//      linearAttenuation       - The linear attenuation.In linear attenuation ss a light moves
	//                                away from a surface, the intensity of light striking the surface
	//                                is inversely proportional to the distance between the light and
	//                                the object.
	//      quadraticAttenuation    - The quadratic attenuation.In Quadratic attenuation, the light
	//                                intensity is attenuated by the square of the distance between
	//                                the surface and the light.
	// Remarks:
	//-----------------------------------------------------------------------
	CXTPChartLightDeviceCommand(int index, CXTPChartColor ambientColor, CXTPChartColor diffuseColor, CXTPChartColor specularColor,
		CXTPChartDiagramPoint position, CXTPChartDiagramPoint spotDirection, float spotExponent, float spotCutoff, float constantAttenuation, float linearAttenuation, float quadraticAttenuation);

protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to do some final cut if any, after the drawing.
	// Parameters:
	//     pDC - A pointer to the OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void AfterExecute(CXTPChartOpenGLDeviceContext* pDC);

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to write the drawing code in OpenGL for
	//     specific objects.
	// Parameters:
	//     pDC - A pointer to the chart OpenGL device context.
	// Remarks:
	//-----------------------------------------------------------------------
	void ExecuteOverride(CXTPChartOpenGLDeviceContext* pDC);

protected:
	int m_index;                            //The light source index.
	CXTPChartColor m_ambientColor;           //The ambient light color.
	CXTPChartColor m_diffuseColor;           //The diffuse light color.
	CXTPChartColor m_specularColor;          //The specular light color.
	CXTPChartDiagramPoint m_position;        //The position of the light in homogeneous object coordinates.
	CXTPChartDiagramPoint m_spotDirection;   //The direction of the light in homogeneous object coordinates.
	float m_spotExponent;                   //The intensity distribution of the light.
	float m_spotCutoff;                     //The maximum spread angle of a light source.
	float m_constantAttenuation;            //The constant attenuation.It affects the overall intensity of the light,
	                                        //regardless of the distance of a surface from the light source.
	float m_linearAttenuation;              //The linear attenuation.In linear attenuation a light moves
	                                        //away from a surface, the intensity of light striking the surface
	                                        //is inversely proportional to the distance between the light and
	                                        //the object.
	float m_quadraticAttenuation;           //The Quadratic attenuation, Here the light intensity is attenuated by
	                                        //the square of the distance between the surface and the light.
	bool m_directional;                     //TRUE if the light is directional, FALSE if not.
};


#endif //#if !defined(__XTPCHARTLIGHTDEVICECOMMAND_H__)

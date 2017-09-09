// convert.h
//
// Header file for conversion routines
//
#ifndef _CONVERT_H
#define _CONVERT_H

#include "stdafx.h"
#include "AXClient.h"

// Convert a ActiveX array to a Java Sequence object with object conversions
HRESULT ArrayToSequence(SAFEARRAY *arr, IDispatch **Sequence);
HRESULT ArrayToVariant(SAFEARRAY *arr, VARIANT *pvar);

// Convert a Java Sequence to a ActiveX safe array
HRESULT SequenceToArray(IDispatch *Sequence, SAFEARRAY **arr, int lowerBound, bool colapseSymbols = false);
HRESULT SequenceToVariant(IDispatch *Sequence, VARIANT *varResult, int lowerBound, bool colapseSymbols = false);

HRESULT ComToJava(IDispatch *ComObject, IDispatch **JavaObject);

HRESULT JavaToCom(IDispatch *JavaObject, VARIANT *ComObject, bool colapseSymbols = false);

BSTR BSTRToJava(BSTR str, VARIANT *pvar);

BSTR BSTRToJavaSymbolObject(BSTR str, IDispatch **ppObj);

BSTR OLECHARToJavaSymbol(OLECHAR *str, VARIANT *pvar);

HRESULT JavaToBSTR(IDispatch *JavaObject, BSTR *str);

HRESULT JavaToItem(IDispatch *JavaObject, G2Item2 **ComObject);

HRESULT JavaToSymbol(IDispatch *JavaObject, IG2Symbol **ComObject);

HRESULT JavaVariantToComVariant(VARIANT JavaVariant, VARIANT *ComVariant);

HRESULT ComVariantToJavaVariant(VARIANT ComVariant, VARIANT *JavaVariant);

HRESULT JavaToStructure(IDispatch *JavaObject, IG2Structure** CommObject);

HRESULT CreateStructure(CLSID clsid, SAFEARRAY *NameValuePairs,
                        IG2Structure **Structure);

HRESULT CreateSymbol(BSTR SymbolName, IG2Symbol **Symbol);

HRESULT JavaArrayToSequence(SAFEARRAY *arr, IDispatch **Sequence);

HRESULT CreateJavaObject(OLECHAR *classname, IDispatch **Object);

HRESULT JavaVariantArrayToComVariant(SAFEARRAY* parray, VARIANT* pComVariant);

HRESULT JavaObjectArrayToComVariant(SAFEARRAY* parray, VARIANT* pComVariant);

HRESULT JavaVariantArrayToItems(SAFEARRAY* pJavaArray, VARIANT* pComVariant);

HRESULT WorkspaceElementsToItems(VARIANT varElements, SAFEARRAY** ppItems);

void UpperCase(BSTR str, WCHAR *out);

HRESULT NewUpperCaseBSTR(BSTR str, VARIANT *pvar);

#endif // _CONVERT_H

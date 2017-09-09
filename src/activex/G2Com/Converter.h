// Converter.h: interface for the Converter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERTER_H__0E3EC6DB_BF34_48B3_8323_B86A0AA4E8F8__INCLUDED_)
#define AFX_CONVERTER_H__0E3EC6DB_BF34_48B3_8323_B86A0AA4E8F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Datum.h"

class Converter  
{
public:
	Converter();
	virtual ~Converter();

	static void		DatumsToArrayVarOrVar(Datum* pRetVals, long lNrRetVals, VARIANT* pOutVar);
    static HRESULT	SafeArrayToDatumArray(SAFEARRAY *pSA, Datum **ppDatum, long *pNrArgs) ;	
    static HRESULT  BetterVariantCopyInd(VARIANT* pvDst, VARIANT* pvSrc) ;
};

#endif // !defined(AFX_CONVERTER_H__0E3EC6DB_BF34_48B3_8323_B86A0AA4E8F8__INCLUDED_)

#include "AXClientConnectionPointImpl.h"

//////////////////////////////////////////////////////////////////////////////
// CProxy_G2ItemEvents
template <class T>
class CProxy_G2ItemEvents : public IAXClientConnectionPointImpl<T, &DIID__G2ItemEvents, CComDynamicUnkArray>
{
public:
//methods:
//_G2ItemEvents : IDispatch
public:
	void Fire_SubscribedAttributeChanged(
		BSTR AttributeName,
		VARIANT * NewValue)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[1].vt = VT_BSTR;
				pvars[1].bstrVal= AttributeName;
				pvars[0].vt = VT_VARIANT | VT_BYREF;
				pvars[0].byref= NewValue;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}

	void Fire_ItemDeleted(void)
	{
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}

};


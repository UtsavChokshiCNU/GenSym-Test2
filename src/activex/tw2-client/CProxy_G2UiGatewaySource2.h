#include "AXClientConnectionPointImpl.h"

//////////////////////////////////////////////////////////////////////////////
// CProxy_G2UiGatewaySource2
template <class T>
class CProxy_G2UiGatewaySource2 : public IAXClientConnectionPointImpl<T, &DIID__G2UiGatewaySource2, CComDynamicUnkArray>
{
public:
//methods:
//_G2UiGatewaySource2 : IDispatch
public:
	void Fire_G2Connected()
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
				pDispatch->Invoke(0x0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}
	void Fire_G2Disconnected()
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
				pDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}
	void Fire_G2StateChange(
		G2States NewState)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[0].vt = VT_I4;
				pvars[0].lVal= NewState;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	void Fire_GotMessage(
		BSTR Message)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[0].vt = VT_BSTR;
				pvars[0].bstrVal= Message;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	void Fire_Error(
		BSTR Message)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[0].vt = VT_BSTR;
				pvars[0].bstrVal= Message;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	void Fire_UserLoggedIn()
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
				pDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}
	void Fire_UserLoggedOut()
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
				pDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}
	void Fire_UserModeChanged(
		BSTR NewUserMode)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[0].vt = VT_BSTR;
				pvars[0].bstrVal= NewUserMode;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0xa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	void Fire_ShowWorkspace(
		IG2Item * Workspace,
		IG2Structure * Particulars,
		IDispatch * WorkspaceShowingEvent)
	{
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				pvars[2].vt = VT_DISPATCH;
				pvars[2].pdispVal= Workspace;
				pvars[1].vt = VT_DISPATCH;
				pvars[1].pdispVal= Particulars;
				pvars[0].vt = VT_DISPATCH;
				pvars[0].pdispVal= WorkspaceShowingEvent;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0xb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}
	void Fire_HideWorkspace(
		IG2Item * Workspace,
		IDispatch * WorkspaceShowingEvent)
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
				pvars[1].vt = VT_DISPATCH;
				pvars[1].pdispVal= Workspace;
				pvars[0].vt = VT_DISPATCH;
				pvars[0].pdispVal= WorkspaceShowingEvent;
				DISPPARAMS disp = { pvars, NULL, 2, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0xc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}

};


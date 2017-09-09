
//////////////////////////////////////////////////////////////////////////////
// CProxy_WrapEvents
template <class T>
class CProxy_WrapEvents : public IConnectionPointImpl<T, &DIID__WrapEvents, CComDynamicUnkArray>
{
public:
//methods:
//_WrapEvents : IDispatch
public:
	void Fire_MyFire(
		long x)
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
				pvars[0].lVal= x;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
		delete[] pvars;
	}

};


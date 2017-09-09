
//////////////////////////////////////////////////////////////////////////////
// CProxyBridgeTesterDispatch
class CProxyBridgeTesterDispatch : public CComPtr<IDispatch>
{
//methods:
//BridgeTesterDispatch : IDispatch
public:
	void show(
		VARIANT_BOOL parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x14, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void wait(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x15, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	short getShortValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x16, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.iVal;
	}
	void addMouseMotionListener(
		IDispatch * MouseMotionListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseMotionListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x17, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL handleEvent(
		IDispatch * Event1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Event1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x18, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setIntArrayWithIndex(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x19, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void mouseEntered(
		IDispatch * MouseEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x1a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setIntValue(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x1b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getActionListener()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x1c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void keyTyped(
		IDispatch * KeyEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= KeyEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x1d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void list(
		IDispatch * PrintWriter1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= PrintWriter1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x1e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void addFocusListener(
		IDispatch * FocusListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= FocusListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x1f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT getShortArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x20, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	void removeBridgeTesterListener(
		IDispatch * BridgeTesterListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= BridgeTesterListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x21, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * add(
		BSTR String1,
		IDispatch * Component2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_BSTR;
		pvars[1].bstrVal= String1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Component2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x22, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void repaint(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x23, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL action(
		IDispatch * Event1,
		IDispatch * Object2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Event1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x24, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setLocale(
		IDispatch * Locale1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Locale1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x25, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setIntArray(
		VARIANT intArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &intArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x26, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void print(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x27, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void add1(
		IDispatch * Component1,
		IDispatch * Object2,
		long parm3)
	{
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Component1;
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Object2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0x28, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeNotify()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x29, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	VARIANT getComponents()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x2a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	void move(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x2b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	OLE_COLOR getForeground()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x2c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.ulVal;
	}
	IDispatch * getInsets()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x2d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	VARIANT getBooleanArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x2e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	IDispatch * createImage(
		long parm1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x2f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void setName(
		BSTR String1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BSTR;
		pvars[0].bstrVal= String1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x30, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setCharArrayWithIndex(
		long parm1,
		short parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x31, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	BSTR toString()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x32, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.bstrVal;
	}
	void setStringValue(
		BSTR String1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BSTR;
		pvars[0].bstrVal= String1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x33, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setBounds(
		long parm1,
		long parm2,
		long parm3,
		long parm4)
	{
		VARIANTARG* pvars = new VARIANTARG[4];
		for (int i = 0; i < 4; i++)
			VariantInit(&pvars[i]);
		pvars[3].vt = VT_I4;
		pvars[3].lVal= parm1;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm2;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm3;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm4;
		DISPPARAMS disp = { pvars, NULL, 4, 0 };
		p->Invoke(0x34, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	long checkImage(
		IDispatch * Image1,
		long parm2,
		long parm3,
		IDispatch * ImageObserver4)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[4];
		for (int i = 0; i < 4; i++)
			VariantInit(&pvars[i]);
		pvars[3].vt = VT_DISPATCH;
		pvars[3].pdispVal= Image1;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm2;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm3;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ImageObserver4;
		DISPPARAMS disp = { pvars, NULL, 4, 0 };
		p->Invoke(0x35, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.lVal;
	}
	IDispatch * getPeer()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x36, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * preferredSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x37, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	float getFloatArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x38, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.fltVal;
	}
	void setStringArray(
		VARIANT StringArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &StringArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x39, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void remove(
		IDispatch * MenuComponent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MenuComponent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x3a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeMouseMotionListener(
		IDispatch * MouseMotionListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseMotionListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x3b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeComponentListener(
		IDispatch * ComponentListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ComponentListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x3c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void hide()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x3d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * size()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x3e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void removeAll()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x3f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	VARIANT_BOOL isBooleanValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x40, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	void setDoubleValue(
		double parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_R8;
		pvars[0].dblVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x41, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getMaximumSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x42, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void repaint1(
		long parm1,
		long parm2,
		long parm3,
		long parm4,
		long parm5)
	{
		VARIANTARG* pvars = new VARIANTARG[5];
		for (int i = 0; i < 5; i++)
			VariantInit(&pvars[i]);
		pvars[4].vt = VT_I4;
		pvars[4].lVal= parm1;
		pvars[3].vt = VT_I4;
		pvars[3].lVal= parm2;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm3;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm4;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm5;
		DISPPARAMS disp = { pvars, NULL, 5, 0 };
		p->Invoke(0x43, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setByteArrayWithIndex(
		long parm1,
		short parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x44, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeFocusListener(
		IDispatch * FocusListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= FocusListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x45, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL equals(
		IDispatch * Object1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x46, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void * getFont()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x47, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.byref;
	}
	void setDoubleArray(
		VARIANT doubleArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &doubleArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x48, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeContainerListener(
		IDispatch * ContainerListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ContainerListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x49, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL gotFocus(
		IDispatch * Event1,
		IDispatch * Object2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Event1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x4a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setLongValue(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x4b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void mousePressed(
		IDispatch * MouseEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x4c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	BSTR getStringArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x4d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.bstrVal;
	}
	void resize(
		IDispatch * Dimension1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Dimension1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x4e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	long getLongValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x4f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.lVal;
	}
	void repaint2()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x50, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * getGraphics()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x51, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void addMouseListener(
		IDispatch * MouseListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x52, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void printAll(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x53, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL mouseExit(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0x54, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	IDispatch * insets()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x55, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void repaint3(
		long parm1,
		long parm2,
		long parm3,
		long parm4)
	{
		VARIANTARG* pvars = new VARIANTARG[4];
		for (int i = 0; i < 4; i++)
			VariantInit(&pvars[i]);
		pvars[3].vt = VT_I4;
		pvars[3].lVal= parm1;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm2;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm3;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm4;
		DISPPARAMS disp = { pvars, NULL, 4, 0 };
		p->Invoke(0x56, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getLocationOnScreen()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x57, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * getComponentAt(
		IDispatch * Point1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Point1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x58, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void reshape(
		long parm1,
		long parm2,
		long parm3,
		long parm4)
	{
		VARIANTARG* pvars = new VARIANTARG[4];
		for (int i = 0; i < 4; i++)
			VariantInit(&pvars[i]);
		pvars[3].vt = VT_I4;
		pvars[3].lVal= parm1;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm2;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm3;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm4;
		DISPPARAMS disp = { pvars, NULL, 4, 0 };
		p->Invoke(0x59, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL inside(
		long parm1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x5a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	short getShortArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x5b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.iVal;
	}
	void addPropertyChangeListener(
		IDispatch * PropertyChangeListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= PropertyChangeListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x5c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeMouseListener(
		IDispatch * MouseListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x5d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	float getFloatValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x5e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.fltVal;
	}
	VARIANT_BOOL mouseEnter(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0x5f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	short getCharArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x60, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.iVal;
	}
	long getComponentCount()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x61, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.lVal;
	}
	void add2(
		IDispatch * PopupMenu1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= PopupMenu1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x62, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void deliverEvent(
		IDispatch * Event1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Event1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x63, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void list1()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x64, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	VARIANT_BOOL isAncestorOf(
		IDispatch * Component1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Component1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x65, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void nextFocus()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x66, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void actionPerformed(
		IDispatch * ActionEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ActionEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x67, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void mouseClicked(
		IDispatch * MouseEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x68, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeVetoableChangeListener(
		IDispatch * VetoableChangeListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= VetoableChangeListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x69, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT getFloatArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x6a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	VARIANT_BOOL prepareImage(
		IDispatch * Image1,
		long parm2,
		long parm3,
		IDispatch * ImageObserver4)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[4];
		for (int i = 0; i < 4; i++)
			VariantInit(&pvars[i]);
		pvars[3].vt = VT_DISPATCH;
		pvars[3].pdispVal= Image1;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm2;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm3;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ImageObserver4;
		DISPPARAMS disp = { pvars, NULL, 4, 0 };
		p->Invoke(0x6b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setBooleanValue(
		VARIANT_BOOL parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x6c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL contains(
		IDispatch * Point1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Point1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x6d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	IDispatch * getComponent(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x6e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void printComponents(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x6f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * minimumSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x70, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	VARIANT_BOOL isShowing()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x71, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	void enable()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x72, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * locate(
		long parm1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x73, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void addContainerListener(
		IDispatch * ContainerListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ContainerListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x74, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * createImage1(
		IDispatch * ImageProducer1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ImageProducer1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x75, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void setBooleanArray(
		VARIANT booleanArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &booleanArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x76, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x77, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void setBackground(
		OLE_COLOR Color1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I2;
		pvars[0].ulVal= Color1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x78, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setCharValue(
		short parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x79, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	short getByteArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x7a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.iVal;
	}
	IDispatch * getLayout()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x7b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * getBounds()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x7c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void addNotify()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x7d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	long checkImage1(
		IDispatch * Image1,
		IDispatch * ImageObserver2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Image1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ImageObserver2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x7e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.lVal;
	}
	void setShortValue(
		short parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x7f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	short getCharValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x80, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.iVal;
	}
	void notify()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x81, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void setCharArray(
		VARIANT charArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &charArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x82, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL lostFocus(
		IDispatch * Event1,
		IDispatch * Object2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Event1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x83, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void show1()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x84, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void disable()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x85, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	VARIANT_BOOL isVisible()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x86, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	void setShortArray(
		VARIANT shortArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &shortArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x87, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void keyReleased(
		IDispatch * KeyEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= KeyEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x88, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT getCharArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x89, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	VARIANT_BOOL keyUp(
		IDispatch * Event1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Event1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x8a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void list2(
		IDispatch * PrintStream1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= PrintStream1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x8b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getComponentAt1(
		long parm1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x8c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void setVisible(
		VARIANT_BOOL parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x8d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setDoubleArrayWithIndex(
		long parm1,
		double parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_R8;
		pvars[0].dblVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x8e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setFont(
		Font * Font1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_EMPTY | VT_BYREF;
		pvars[0].byref= Font1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x8f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void addComponentListener(
		IDispatch * ComponentListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ComponentListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x90, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void mouseExited(
		IDispatch * MouseEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x91, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	long getIntArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x92, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.lVal;
	}
	long countComponents()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x93, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.lVal;
	}
	void setLayout(
		IDispatch * LayoutManager1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= LayoutManager1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x94, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setBounds1(
		IDispatch * Rectangle1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Rectangle1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x95, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void notifyAll()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x96, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * location()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x97, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void paintComponents(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x98, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setForeground(
		OLE_COLOR Color1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I2;
		pvars[0].ulVal= Color1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x99, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * add3(
		IDispatch * Component1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Component1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0x9a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	long hashCode()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x9b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.lVal;
	}
	IDispatch * getLocation()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x9c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	VARIANT_BOOL isEnabled()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x9d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	IDispatch * add4(
		IDispatch * Component1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Component1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0x9e, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	IDispatch * getColorModel()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0x9f, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * getToolkit()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void setEnabled(
		VARIANT_BOOL parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xa1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void addKeyListener(
		IDispatch * KeyListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= KeyListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xa2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void wait1()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void requestFocus()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void layout()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * bounds()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * getClass()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xa7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void setBooleanArrayWithIndex(
		long parm1,
		VARIANT_BOOL parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xa8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setShortArrayWithIndex(
		long parm1,
		short parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xa9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	BSTR getStringValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xaa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.bstrVal;
	}
	VARIANT_BOOL mouseDrag(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0xab, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void update(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xac, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getMinimumSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xad, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void addBridgeTesterListener(
		IDispatch * BridgeTesterListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= BridgeTesterListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xae, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	IDispatch * getTreeLock()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xaf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	VARIANT getStringArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xb0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	void validate()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xb1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void setSize(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xb2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void mouseReleased(
		IDispatch * MouseEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= MouseEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xb3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setByteValue(
		short parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I2;
		pvars[0].iVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xb4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	double getDoubleValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xb5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.dblVal;
	}
	void setLocation(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xb6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL mouseDown(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0xb7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void wait2(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xb8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void paint(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xb9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	short getByteValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xba, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.iVal;
	}
	VARIANT_BOOL mouseUp(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0xbb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	VARIANT_BOOL mouseMove(
		IDispatch * Event1,
		long parm2,
		long parm3)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[3];
		for (int i = 0; i < 3; i++)
			VariantInit(&pvars[i]);
		pvars[2].vt = VT_DISPATCH;
		pvars[2].pdispVal= Event1;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm2;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm3;
		DISPPARAMS disp = { pvars, NULL, 3, 0 };
		p->Invoke(0xbc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setSize1(
		IDispatch * Dimension1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Dimension1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xbd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removeKeyListener(
		IDispatch * KeyListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= KeyListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xbe, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void removePropertyChangeListener(
		IDispatch * PropertyChangeListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= PropertyChangeListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xbf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL postEvent(
		IDispatch * Event1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Event1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xc0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	BSTR getName()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xc1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.bstrVal;
	}
	void remove1(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xc2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setByteArray(
		VARIANT byteArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &byteArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xc3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void remove2(
		IDispatch * Component1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Component1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xc4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT getDoubleArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xc5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	double getDoubleArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xc6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.dblVal;
	}
	IDispatch * getParent()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xc7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	IDispatch * getCursor()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xc8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	VARIANT_BOOL contains1(
		long parm1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xc9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	VARIANT getByteArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xca, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	void setFloatValue(
		float parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_R4;
		pvars[0].fltVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xcb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void resize1(
		long parm1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xcc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	long getIntValue()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xcd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.lVal;
	}
	void paintAll(
		IDispatch * Graphics1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Graphics1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xce, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void invalidate()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xcf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	VARIANT_BOOL imageUpdate(
		IDispatch * Image1,
		long parm2,
		long parm3,
		long parm4,
		long parm5,
		long parm6)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[6];
		for (int i = 0; i < 6; i++)
			VariantInit(&pvars[i]);
		pvars[5].vt = VT_DISPATCH;
		pvars[5].pdispVal= Image1;
		pvars[4].vt = VT_I4;
		pvars[4].lVal= parm2;
		pvars[3].vt = VT_I4;
		pvars[3].lVal= parm3;
		pvars[2].vt = VT_I4;
		pvars[2].lVal= parm4;
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm5;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm6;
		DISPPARAMS disp = { pvars, NULL, 6, 0 };
		p->Invoke(0xd0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void list3(
		IDispatch * PrintStream1,
		long parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= PrintStream1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xd1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setFloatArray(
		VARIANT floatArray1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_VARIANT;
		pvars[0].pvarVal= &floatArray1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xd2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL keyDown(
		IDispatch * Event1,
		long parm2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Event1;
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xd3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setByteValue1(
		long parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xd4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL prepareImage1(
		IDispatch * Image1,
		IDispatch * ImageObserver2)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Image1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= ImageObserver2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xd5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	VARIANT_BOOL isValid()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xd6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	VARIANT getIntArray()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xd7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return *varResult.pvarVal;
	}
	float getAlignmentY()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xd8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.fltVal;
	}
	void add5(
		IDispatch * Component1,
		IDispatch * Object2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_DISPATCH;
		pvars[1].pdispVal= Component1;
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xd9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	float getAlignmentX()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xda, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.fltVal;
	}
	IDispatch * getFontMetrics(
		Font * Font1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_EMPTY | VT_BYREF;
		pvars[0].byref= Font1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xdb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.pdispVal;
	}
	void doLayout()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xdc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	void setFloatArrayWithIndex(
		long parm1,
		float parm2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_R4;
		pvars[0].fltVal= parm2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xdd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void keyPressed(
		IDispatch * KeyEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= KeyEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xde, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL getBooleanArrayWithIndex(
		long parm1)
	{
		VARIANT varResult;
		VariantInit(&varResult);
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_I4;
		pvars[0].lVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xdf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		delete[] pvars;
		return varResult.boolVal;
	}
	void setLocation1(
		IDispatch * Point1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Point1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setCursor(
		IDispatch * Cursor1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Cursor1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void enable1(
		VARIANT_BOOL parm1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_BOOL;
		pvars[0].boolVal= parm1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void addVetoableChangeListener(
		IDispatch * VetoableChangeListener1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= VetoableChangeListener1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	VARIANT_BOOL isFocusTraversable()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xe4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.boolVal;
	}
	void transferFocus()
	{
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xe5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	}
	IDispatch * getLocale()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xe6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}
	void dispatchEvent(
		IDispatch * AWTEvent1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= AWTEvent1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void setStringArrayWithIndex(
		long parm1,
		BSTR String2)
	{
		VARIANTARG* pvars = new VARIANTARG[2];
		for (int i = 0; i < 2; i++)
			VariantInit(&pvars[i]);
		pvars[1].vt = VT_I4;
		pvars[1].lVal= parm1;
		pvars[0].vt = VT_BSTR;
		pvars[0].bstrVal= String2;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };
		p->Invoke(0xe8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void printObjectInField(
		IDispatch * Object1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= Object1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xe9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	void list4(
		IDispatch * PrintWriter1)
	{
		VARIANTARG* pvars = new VARIANTARG[1];
		for (int i = 0; i < 1; i++)
			VariantInit(&pvars[i]);
		pvars[0].vt = VT_DISPATCH;
		pvars[0].pdispVal= PrintWriter1;
		DISPPARAMS disp = { pvars, NULL, 1, 0 };
		p->Invoke(0xea, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
		delete[] pvars;
	}
	OLE_COLOR getBackground()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xeb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.ulVal;
	}
	IDispatch * getPreferredSize()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		DISPPARAMS disp = { NULL, NULL, 0, 0 };
		p->Invoke(0xec, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
		return varResult.pdispVal;
	}

};


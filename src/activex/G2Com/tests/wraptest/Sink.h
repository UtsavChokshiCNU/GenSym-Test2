// Sink.h : Declaration of the CSink

#ifndef __SINK_H_
#define __SINK_H_

#include "resource.h"       // main symbols

class Cwrap;

/////////////////////////////////////////////////////////////////////////////
// CSink
const IID IID_source = {0x95A884F0, 0xF4C8, 0x11D1, {0x86, 0x62, 0x00, 0x00, 0x86, 0x18, 0xF4, 0x71}};

class ATL_NO_VTABLE CSink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSink, &CLSID_Sink>,
	public IDispatchImpl<ISink, &IID_ISink, &LIBID_WRAPTESTLib>
{
public:
	Cwrap *EventObj;
	CSink()
	{
	}

	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, 
		VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);

DECLARE_REGISTRY_RESOURCEID(IDR_SINK)

BEGIN_COM_MAP(CSink)
	COM_INTERFACE_ENTRY(ISink)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IID(IID_source, CSink)  // this will add the beans outgoing interface to the com map
END_COM_MAP()

// ISink
public:
};

#endif //__SINK_H_

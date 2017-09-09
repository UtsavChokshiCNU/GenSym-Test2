// Sink.cpp : Implementation of CSink
#include "stdafx.h"
#include "wraptest.h"
#include "Sink.h"
#include "wrap.h"

/////////////////////////////////////////////////////////////////////////////
// CSink


// Override the Invoke method and forward it to the connection object.

HRESULT CSink::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, 
	VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr) {

	ATLTRACE("Got invoke on outgoing interface:%d\n",dispIdMember);
	EventObj->Fire_MyFire(dispIdMember);
	return S_OK;
}
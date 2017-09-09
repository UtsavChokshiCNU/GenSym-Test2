#ifndef _G2GATEWAY_H_
#define _G2GATEWAY_H_

#include "Gateway.h"

/*
 * CG2Gateway wrapper class 
 */

class CG2GatewayObj: public CG2Gateway
{

	public: 
		virtual unsigned long __stdcall AddRef();
		virtual unsigned long __stdcall Release();
		virtual HRESULT __stdcall QueryInterface( REFIID iid, void** ppvObject );
	public:
		int getRequestLen();
		long G2ClientConnect(VARIANT_BOOL WaitFlag);
		void G2ClientDisconnect();
};

#endif

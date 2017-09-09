// RPCRequest.cpp: implementation of the RPCRequest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2Com.h"
#include "Gateway.h"
#include "RPCRequest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//
// Note that, for the sake of efficiency, the constructor takes ownership of the array 
// of Datum pointed to by pArgsIn.  It does not create a copy.  If necessary, this is
// the responsibility of the caller.
//
RPCRequest::RPCRequest(GsiContext *Context, TCHAR *name, Datum *pArgsIn, long nrArgsIn, 
                     requestType rt) : mName(name),      mpArgsIn(pArgsIn), 
                                       mCount(nrArgsIn), mNrRetVals(0), 
                                       mpRetVals(NULL),  RequestObj(Context, rt)
{
}


RPCRequest::~RPCRequest()
{
    if (mpArgsIn)
        delete [] mpArgsIn ;
    if (mpRetVals)
        delete [] mpRetVals ;
}

// G2Com.cpp : Implementation of DLL Exports.

/* ========================================================================= */
/*                                                                           */
/*  History:                                                                 */
/*  --------                                                                 */
/*  1.0 rev 3: The following changes were made to Ver. 1.1/1.2 (same code):  */
/*             - OnStartPage and OnEndPage were added to enable proper       */
/*               behavior with ASP.                                          */
/*             - A new interface, IG2Gateway2 was added for the ASP methods  */
/*             - GsiThread's _endthread was moved out of the destructor to   */
/*               permit proper cleanup.                                      */
/*             - changed ATLTRACE statements to provide more useful info     */
/*             - the version number of the G2Gateway coclass was changed to  */
/*               2 in Gateway.rgs.                                           */
/*                                                                           */
/*  1.0 rev 4: Rebuilt with GSI 5.1r13 to resolve HQ-4425311 (High CPU       */
/*             utilization in AXL due to GSI bug in reclaiming data          */
/*             structures).  Only changes to AXL files were:                 */
/*             - the /I and /libpath project settings                        */
/*             - the version number in the version resource                  */
/*             - the version number in the kb's title                        */
/*             - this comment                                                */
/*                                                                           */
/*  1.0 rev 5: Rebuilt with GSI 7.0b0.  The changes were the same as for     */
/*             ver. 1.4.                                                     */
/*                                                                           */
/*  1.0 rev 6: Built with GSI 7.0r0.                                         */
/*                                                                           */
/*  1.0 rev 7: Added support for G2 structures.                              */
/*             Added G2Reset and G2Started events.                           */
/*                                                                           */
/*  1.0 rev 8: Added support for G2 items, arrays, & lists.                  */
/*                                                                           */
/*  1.1 rev 0: Items by reference                                            */
/*                                                                           */
/*  8.1 rev.0  Restructured so that GSI access is limited to a single thread.*/
/*                                                                           */
/* ========================================================================= */

// Note: Proxy/Stub Information
//        To build a separate proxy/stub DLL,
//        run nmake -f G2Comps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "G2Com.h"
#include "GsiThread.h"
#include "GsiContext.h"

#include "G2Com_i.c"
#include "Gateway.h"
#include "GatewayProp.h"
#include "G2StructureEntry.h"
#include "G2Structure.h"
#include "G2Item.h"
#include "G2Attribute.h"
#include "G2ListOrArray.h"
#include "G2Symbol.h"
#include "G2LAElement.h"
#include "G2ItemRef.h"
#include "G2Workspace.h"
#include "G2Window.h"
#include "G2ComConfigurator.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_G2Gateway, CG2Gateway)
OBJECT_ENTRY(CLSID_GatewayProp, CGatewayProp)
OBJECT_ENTRY(CLSID_G2StructureEntry, CG2StructureEntry)
OBJECT_ENTRY(CLSID_G2Structure, CG2Structure)
OBJECT_ENTRY(CLSID_G2Item, CG2Item)
OBJECT_ENTRY(CLSID_G2Attribute, CG2Attribute)
OBJECT_ENTRY(CLSID_G2ListOrArray, CG2ListOrArray)
OBJECT_ENTRY(CLSID_G2LAElement, CG2LAElement)
OBJECT_ENTRY(CLSID_G2Symbol, CG2Symbol)
OBJECT_ENTRY(CLSID_G2ItemRef, CG2ItemRef)
OBJECT_ENTRY(CLSID_G2Workspace, CG2Workspace)
OBJECT_ENTRY(CLSID_G2Window, CG2Window)
OBJECT_ENTRY(CLSID_G2ComConfigurator, CG2ComConfigurator)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
    BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    ATLTRACE2(atrAxlMethodCalls,3,"Got call to DllMain\n");
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        ATLTRACE2(atrAxlMethodCalls,3,"Detaching DLL\n");
        _Module.Term();
    }
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    ATLTRACE2(atrAxlMethodCalls,3,"Checking for Unload\n");
    if (GsiThreadObj)
        return S_FALSE;  // if run loop still running, do not exit.
    if (EventThreadCount)
        return S_FALSE;  // event threads still running, do not detach
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    _Module.UnregisterServer(TRUE);
    return S_OK;
}


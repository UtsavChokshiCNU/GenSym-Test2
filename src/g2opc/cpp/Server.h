// Server.h: interface for the CServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVER_H__E25B5153_EDD7_48A9_9BC9_76B03FF89B80__INCLUDED_)
#define AFX_SERVER_H__E25B5153_EDD7_48A9_9BC9_76B03FF89B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COPCShutdown ; // forward reference

class CServer  
{
public:
    CServer() ;
	virtual ~CServer();
    void    FirstUse(CLSID clsid, IOPCServer *pServer) ;
    void    AddGroup2ServerList(CGroup *pGroup) ;
    void    RemoveGroupFromServerList(OPCHANDLE hGroupS) ;

    CLSID               m_clsid ;
    IOPCServer          *m_pOPCServer ;
    long                m_nr_ctxs_using ;
    CGroup              *m_pGroups ;

    // Shutdown Callback info
    // ----------------------
    bool                b_usesV2shutdown ;
    IConnectionPoint    *p_ShutdownConnectionPoint ;
	COPCShutdown        *mp_shutdown_object;
    DWORD               sd_cookie ;

};

#endif // !defined(AFX_SERVER_H__E25B5153_EDD7_48A9_9BC9_76B03FF89B80__INCLUDED_)

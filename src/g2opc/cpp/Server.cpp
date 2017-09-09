// Server.cpp: implementation of the CServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServer::CServer()
{
    memset(this, 0, sizeof(CServer)) ;
    mp_shutdown_object = new COPCShutdown ;
}


CServer::~CServer()
{
    long dbgct ;
    mp_shutdown_object->Release() ;
    mp_shutdown_object = NULL ;
    if (m_pOPCServer)
    {
        dbgct=m_pOPCServer->Release() ;
        if (!dbgct)
            m_pOPCServer = NULL ;
    }
}


void CServer::FirstUse(CLSID clsid, IOPCServer *pServer) 
{
    m_clsid = clsid ;
    m_pOPCServer = pServer ;
    m_nr_ctxs_using = 1 ;
    m_pGroups = NULL ;
    if (mp_shutdown_object == NULL)
        mp_shutdown_object = new COPCShutdown ;
}



void CServer::AddGroup2ServerList(CGroup *pGroup)
{
    if (m_pGroups == NULL)
        m_pGroups = pGroup ;
    else
    {
        pGroup->mp_Next = m_pGroups ;
        m_pGroups = pGroup ;
    }
}

void    CServer::RemoveGroupFromServerList(OPCHANDLE hGroupS)
{
    CGroup  *pPrior = NULL ;
    CGroup  *pNext = NULL ;
    bool    first = true ;

    pNext = m_pGroups ;
    while (pNext != NULL)
        if (pNext->m_group_handle == hGroupS)
        {
            if (pPrior == NULL)
                this->m_pGroups = pNext->mp_Next ;
            else
                pPrior->mp_Next = pNext->mp_Next ;
            delete pNext ;
            break ;
        }
        else
        {
            pPrior = pNext ;
            pNext = pNext->mp_Next ;
        }   
}
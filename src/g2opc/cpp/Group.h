// Group.h: interface for the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUP_H__52F7663D_D71A_4495_8E11_EACD1034A29C__INCLUDED_)
#define AFX_GROUP_H__52F7663D_D71A_4495_8E11_EACD1034A29C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAdviseSink ;
class COPCDataCallback ;

class CGroup  
{
public:
	CGroup(gsi_int ctxNr, OPCHANDLE server_assigned_handle);
	virtual ~CGroup();

    gsi_int             m_ctxNr ;
    OPCHANDLE           m_group_handle ;
    COPCDataCallback    *mp_callback_object ;
    CAdviseSink         *mp_advise_sink ;
    CGroup              *mp_Next ;
};

#endif // !defined(AFX_GROUP_H__52F7663D_D71A_4495_8E11_EACD1034A29C__INCLUDED_)

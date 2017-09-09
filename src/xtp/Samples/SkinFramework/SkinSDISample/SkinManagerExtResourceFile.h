// SkinManagerExtResourceFile.h: interface for the CSkinManagerExtResourceFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_)
#define AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinManagerExtResourceFile : public CXTPSkinManagerResourceFile  
{
public:
	CSkinManagerExtResourceFile();
	virtual ~CSkinManagerExtResourceFile();

public:
	virtual BOOL Open(LPCTSTR lpszResourcePath, LPCTSTR lpszIniFileName);

	virtual void Close();

	virtual CXTPSkinImage* LoadImage(CString strImageFile);

	virtual BOOL ReadString(CString& str);

protected:
	CStdioFile* m_pIniFile;
};

#endif // !defined(AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_)

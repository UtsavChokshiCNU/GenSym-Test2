// ResourceExport.h: interface for the CResourceExport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEEXPORT_H__4CA1236F_BE43_422F_ADF4_434D7912760E__INCLUDED_)
#define AFX_RESOURCEEXPORT_H__4CA1236F_BE43_422F_ADF4_434D7912760E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct DIRECTORY;

class CResourceExport  
{
public:
	CResourceExport();
	virtual ~CResourceExport();

	void ExportDll(CXTPPropExchangeXMLNode* pResources, LPCTSTR lpszOutput);
	void ExportRc(CXTPPropExchangeXMLNode* pResources, LPCTSTR lpszOutput);

private:
	void ExportDllStringTable(DIRECTORY* pRoot);
	void ExportDllMenus(DIRECTORY* pRoot);
	void ExportDllMenuItems(CMemFile* pFile, CXTPPropExchange* pResourceMenu);
	void ExportDllDialogs(DIRECTORY* pRoot);
	void ExportDllDialogControls(CMemFile* pFile, CXTPPropExchange* pResourceDialog);

private:
	void ExportRcStringTable(CFile& file);
	void ExportRcMenus(CFile& file);
	void ExportRcMenuItems(CFile& file, DWORD dwParent, CXTPPropExchange* pResourceMenu, const CString& strIndent);
	void ExportRcDialogs(CFile& file);
	void ExportRcDialogControls(CFile& file, DWORD dwParent, CXTPPropExchange* pResourceDialog);

private:
	void ExchangeString(CXTPPropExchange* pPX, LPCTSTR pszPropName, LPSTR lpString);
	int GetDialogControlsCount(CXTPPropExchange* pResourceDialog);
	void AlignFile(CMemFile* pFile, DWORD dwPosition);


protected:
	CXTPPropExchangeXMLNode* m_pResources;
	XTP_RESOURCEMANAGER_LANGINFO* m_pLanguageInfo;

};

#endif // !defined(AFX_RESOURCEEXPORT_H__4CA1236F_BE43_422F_ADF4_434D7912760E__INCLUDED_)

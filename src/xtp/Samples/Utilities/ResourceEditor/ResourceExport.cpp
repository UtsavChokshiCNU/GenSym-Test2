// ResourceExport.cpp: implementation of the CResourceExport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResourceExport.h"
#include "ResourceViewRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



class CBufferFile  : public CMemFile
{
public:
	CBufferFile(int nFileSize = 120000)
		: CMemFile(nFileSize)
	{

	}
public:
	LPBYTE GetBuffer() {
		return m_lpBuffer + GetPosition();
	}
	LPBYTE GetBufferHeader() {
		return m_lpBuffer;
	}
};

#pragma pack(push, 1)

typedef struct
{
	WORD dlgVer;
	WORD signature;
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	WORD cDlgItems;
	short x;
	short y;
	short cx;
	short cy;
} DLLDLGTEMPLATEEX;

typedef struct
{
	DWORD helpID;
	DWORD exStyle;
	DWORD style;
	short x;
	short y;
	short cx;
	short cy;
	DWORD id;
} DLLDLGITEMTEMPLATEEX;

#pragma pack(pop)


struct DIRECTORY;
typedef CArray<DIRECTORY*, DIRECTORY*> CArrayDirectories;



struct DIRECTORY
{
	DIRECTORY()
	{
		nID	 = 0;
		nResourceOffset = 0;

		lpFatEntry = 0;
		lpFatDataEntry = 0;
		pResource = NULL;
	}
	~DIRECTORY()
	{
		for (int i = 0; i < arrDirs.GetSize(); i++)
		{
			delete arrDirs[i];
		}
		if (pResource)
			delete pResource;
	}
	int GetNumberOfIdEntries()
	{
		return (int)arrDirs.GetSize() - GetNumberOfNamedEntries();
	}
	int GetNumberOfNamedEntries()
	{
		int nCount = 0;
		for (int i = 0; i < arrDirs.GetSize(); i++)
		{
			if (!arrDirs[i]->strName.IsEmpty())
			{
				nCount++;
			}
		}
		return nCount;
	}

	DIRECTORY* AddDirectory(CString strSub);
	DIRECTORY* AddDirectory(int nSub);


	CString strName;
	CString strResource;
	int nID;
	int nResourceOffset;
	CBufferFile* pResource;

	PIMAGE_RESOURCE_DIRECTORY_ENTRY lpFatEntry;
	PIMAGE_RESOURCE_DATA_ENTRY lpFatDataEntry;
	CArrayDirectories arrDirs;
};

DIRECTORY* DIRECTORY::AddDirectory(CString strSub)
{
	int i;
	for (i = 0; i < arrDirs.GetSize(); i++)
	{
		if (arrDirs[i]->strName.IsEmpty())
			break;

		if (arrDirs[i]->strName == strSub)
		{
			return arrDirs[i];
		}

		if (arrDirs[i]->strName > strSub)
		{
			break;
		}
	}

	DIRECTORY* pType = new DIRECTORY();
	pType->strName = strSub;
	arrDirs.InsertAt(i, pType);

	return pType;
}

DIRECTORY* DIRECTORY::AddDirectory(int nSub)
{
	int i;
	for (i = 0; i <arrDirs.GetSize(); i++)
	{
		if (arrDirs[i]->nID == nSub)
		{
			return arrDirs[i];
		}
		if (arrDirs[i]->nID > nSub)
		{
			break;
		}
	}
	DIRECTORY* pType = new DIRECTORY();
	pType->nID = nSub;
	arrDirs.InsertAt(i, pType);

	return pType;
}

DIRECTORY* AddDirectory(DIRECTORY* pRootDir, CString strType, CString strResourceName, UINT nLocale = 0x409)
{
	DIRECTORY* pType = pRootDir->AddDirectory(strType);
	DIRECTORY* pResName = pType->AddDirectory(strResourceName);
	DIRECTORY* pEntry = pResName->AddDirectory(nLocale);
	return pEntry;
}

DIRECTORY* AddDirectory(DIRECTORY* pRootDir, int nID, CString strResourceName, UINT nLocale = 0x409)
{
	DIRECTORY* pType = pRootDir->AddDirectory(nID);
	DIRECTORY* pResName = pType->AddDirectory(strResourceName);
	DIRECTORY* pEntry = pResName->AddDirectory(nLocale);
	return pEntry;
}

DIRECTORY* AddDirectory(DIRECTORY* pRootDir, int nID, int nResourceName, UINT nLocale = 0x409)
{
	DIRECTORY* pType = pRootDir->AddDirectory(nID);
	DIRECTORY* pResName = pType->AddDirectory(nResourceName);
	DIRECTORY* pEntry = pResName->AddDirectory(nLocale);
	return pEntry;
}


void WriteFAT(CBufferFile* lpFAT, DIRECTORY* pDirectory, CArrayDirectories* pDataDirs)
{

	IMAGE_RESOURCE_DIRECTORY dir;
	ZeroMemory(&dir, sizeof(IMAGE_RESOURCE_DIRECTORY));

	dir.NumberOfIdEntries = (WORD)pDirectory->GetNumberOfIdEntries();
	dir.NumberOfNamedEntries = (WORD)pDirectory->GetNumberOfNamedEntries();
	lpFAT->Write(&dir, sizeof(IMAGE_RESOURCE_DIRECTORY));
	int i;

	for (i = 0; i < pDirectory->arrDirs.GetSize(); i++)
	{
		IMAGE_RESOURCE_DIRECTORY_ENTRY entry;
		ZeroMemory(&entry, sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));

		DIRECTORY* pSubDir = pDirectory->arrDirs[i];

		if (pSubDir->arrDirs.GetSize() > 0)
		{
			entry.DataIsDirectory = 1;
		}

		if (pSubDir->strName.IsEmpty())
		{
			entry.Id = (WORD)pSubDir->nID;
		}
		else
		{
			entry.NameIsString = 1;
		}

		pSubDir->lpFatEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)lpFAT->GetBuffer();
		lpFAT->Write(&entry, sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));	
	}

	for (i = 0; i < pDirectory->arrDirs.GetSize(); i++)
	{
		DIRECTORY* pSubDir = pDirectory->arrDirs[i];
		PIMAGE_RESOURCE_DIRECTORY_ENTRY lpEntry = pSubDir->lpFatEntry;

		if (pSubDir->arrDirs.GetSize() > 0)
		{
			lpEntry->OffsetToDirectory = lpFAT->GetPosition();
			WriteFAT(lpFAT, pSubDir, pDataDirs);
		}
		else
		{
			lpEntry->OffsetToData = (DWORD)lpFAT->GetPosition();

			IMAGE_RESOURCE_DATA_ENTRY data;

			ZeroMemory(&data, sizeof(IMAGE_RESOURCE_DATA_ENTRY));

			pSubDir->lpFatDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)lpFAT->GetBuffer();

			lpFAT->Write(&data, sizeof(IMAGE_RESOURCE_DATA_ENTRY));	

			pDataDirs->Add(pSubDir);
		}
	}
}
void WriteFATNames(CBufferFile* lpFAT, DIRECTORY* pDirectory)
{
	USES_CONVERSION;

	int i;
	for (i = 0; i < pDirectory->arrDirs.GetSize(); i++)
	{
		DIRECTORY* pSubDir = pDirectory->arrDirs[i];
		if (!pSubDir->strName.IsEmpty())
		{
			PIMAGE_RESOURCE_DIRECTORY_ENTRY lpEntry = pSubDir->lpFatEntry;
			lpEntry->NameOffset = lpFAT->GetPosition();

			WORD Length = (WORD)pSubDir->strName.GetLength();
			lpFAT->Write(&Length, sizeof(Length));

			LPCWSTR lpw = T2W((LPTSTR)(LPCTSTR)pSubDir->strName);
			lpFAT->Write(lpw, (pSubDir->strName.GetLength()) * sizeof(WCHAR));
		}
	}
	for (i = 0; i < pDirectory->arrDirs.GetSize(); i++)
	{
		DIRECTORY* pSubDir = pDirectory->arrDirs[i];

		if (pSubDir->arrDirs.GetSize() > 0)
		{
			WriteFATNames(lpFAT, pSubDir);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResourceExport::CResourceExport()
{
	m_pResources = NULL;
	m_pLanguageInfo = 0;
}

CResourceExport::~CResourceExport()
{

}

struct STRINGTABLE
{
	STRINGTABLE()
	{
		ZeroMemory(m_bstr, sizeof(m_bstr));

	}
	~STRINGTABLE()
	{
		for (int i = 0; i < 16; i++)
		{
			if (m_bstr[i])
			{
				SysFreeString(m_bstr[i]);
			}
		}

	}
	BSTR m_bstr[16];
};

void CResourceExport::ExportDllMenuItems(CMemFile* pFile, CXTPPropExchange* pResourceMenu)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResourceMenu->GetEnumerator(_T("menuitem")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionMenuItem(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		
		PX_DWord(&ptrSectionMenuItem, _T("id"), dwId);
		
		BSTR bstrValue = 0;		
		PX_Bstr(&ptrSectionMenuItem, _T("caption"), bstrValue, 0);

		BOOL bPopup = (((CXTPPropExchangeXMLNode*)&ptrSectionMenuItem)->IsSectionExists(_T("menuitem")));

		WORD mtOption = 0, mtID = 0;
		if (bPopup)
			mtOption |= MF_POPUP;
		if (!pos)
			mtOption |= MF_END;

		if (!bPopup && dwId == 0)
			mtOption |= MF_SEPARATOR;
		
		pFile->Write(&mtOption, sizeof(WORD));

		mtID = (WORD)dwId;

		if (!bPopup)
			pFile->Write(&mtID, sizeof(WORD));

		LPCWSTR lpDispalyName = (LPCWSTR)bstrValue;
		WORD wLength = 0;

		if (lpDispalyName)
		{
			wLength = (WORD)wcslen(lpDispalyName);
			pFile->Write(lpDispalyName, (1 + wLength) * sizeof(WCHAR));
		}
		else
		{
			pFile->Write(&wLength, sizeof(WCHAR));
		}

		if (bstrValue)
		{
			SysFreeString(bstrValue);
		}

		if (bPopup)
		{
			ExportDllMenuItems(pFile, &ptrSectionMenuItem);
		}
	}	
}

AFX_INLINE DWORD AlignDWord(DWORD uLong)  {  return ((uLong + 3) & ~3); }

void CResourceExport::ExportDllMenus(DIRECTORY* pRoot)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorMenus(m_pResources->GetEnumerator(_T("menu")));
	POSITION pos = ptrEnumeratorMenus->GetPosition();
	while (pos)
	{
		CXTPPropExchangeSection ptrSection(ptrEnumeratorMenus->GetNext(pos));
		DWORD dwId = 0;
		
		PX_DWord(&ptrSection, _T("id"), dwId);
		if (dwId == 0)
			continue;

		DIRECTORY* pDirectory = AddDirectory(pRoot, (WORD)(DWORD_PTR)RT_MENU, dwId, m_pLanguageInfo->wLanguage);
		CBufferFile* pFile = pDirectory->pResource = new CBufferFile(10000);

		WORD wVerison = 0;
		WORD wOffset = 0;

		pFile->Write(&wVerison, sizeof(WORD));
		pFile->Write(&wOffset, sizeof(WORD));
		ExportDllMenuItems(pFile, &ptrSection);

		AlignFile(pFile, 0);
	}
}

int CResourceExport::GetDialogControlsCount(CXTPPropExchange* pResourceDialog)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumerator(pResourceDialog->GetEnumerator(_T("control")));
	POSITION pos = ptrEnumerator->GetPosition();
	int nCount = 0;

	while (pos)
	{
		CXTPPropExchangeSection ptrSection(ptrEnumerator->GetNext(pos));
		nCount++;
	}

	return nCount;
}

void CResourceExport::AlignFile(CMemFile* pFile, DWORD dwPosition)
{
	DWORD dwAlign = 0;
	DWORD dwSize = DWORD(pFile->GetPosition() - dwPosition);
	
	DWORD dwBytes = AlignDWord(dwSize) - dwSize;
	ASSERT(dwBytes >= 0 && dwBytes < 4);
	
	pFile->Write(&dwAlign, dwBytes);
}

void CResourceExport::ExportDllDialogControls(CMemFile* pFile, CXTPPropExchange* pResourceDialog)
{
	USES_CONVERSION;
	
	CXTPPropExchangeEnumeratorPtr ptrEnumerator(pResourceDialog->GetEnumerator(_T("control")));
	POSITION pos = ptrEnumerator->GetPosition();

	while (pos)
	{
		CXTPPropExchangeSection ptrSection(ptrEnumerator->GetNext(pos));

		DLLDLGITEMTEMPLATEEX templ;
		ZeroMemory(&templ, sizeof(DLLDLGITEMTEMPLATEEX));
		WORD dwEmpty = 0;
		DWORD dwPosition = (DWORD)pFile->GetPosition();

		RECT rcPos = {0, 0, 0, 0};
		PX_Rect(&ptrSection, _T("position"), rcPos, rcPos);
		templ.x = (short)rcPos.left;
		templ.y = (short)rcPos.top;
		templ.cx = (short)rcPos.right;
		templ.cy = (short)rcPos.bottom;

		PX_DWord(&ptrSection, _T("style"), templ.style, WS_CHILD | WS_VISIBLE | WS_GROUP);
		PX_DWord(&ptrSection, _T("styleex"), templ.exStyle, 0);

		int id = 0;
		PX_Int(&ptrSection, _T("id"), id, 0);

		templ.id = id == 0 ? (DWORD)IDC_STATIC : (DWORD)id;

		pFile->Write(&templ, sizeof(DLLDLGITEMTEMPLATEEX));
		
		CString strClass;
		PX_String(&ptrSection, _T("class"), strClass, _T("STATIC"));
		WORD nClass = 0;

		if (strClass == _T("BUTTON")) nClass = 0x0080;
		if (strClass == _T("EDIT")) nClass = 0x0081;
		if (strClass == _T("STATIC")) nClass = 0x0082;
		if (strClass == _T("LISTBOX")) nClass = 0x0083;
		if (strClass == _T("SCROLLBAR")) nClass = 0x0084;
		if (strClass == _T("COMBOBOX")) nClass = 0x0085;

		if (nClass != 0)
		{
			WORD dwSignature = 0xFFFF;
			pFile->Write(&dwSignature, sizeof(WORD));
			pFile->Write(&nClass, sizeof(WORD));
		}
		else
		{
			pFile->Write(T2CW(strClass), (strClass.GetLength() + 1) * sizeof(WCHAR));
		}

		int nResource = 0;
		BOOL bExists = PX_Int(&ptrSection, _T("resource"), nResource);
		if (bExists)
		{
			WORD dwSignature = 0xFFFF;
			WORD dwResource = (WORD)nResource;
			pFile->Write(&dwSignature, sizeof(WORD));
			pFile->Write(&dwResource, sizeof(WORD));	
		}
		else
		{
			BSTR bstrValue = 0;		
			PX_Bstr(&ptrSection, _T("caption"), bstrValue, 0);
			
			if (bstrValue)
			{
				pFile->Write(bstrValue, (1 + (int)wcslen(bstrValue)) * sizeof(WCHAR));
			}
			else
			{
				pFile->Write(&dwEmpty, sizeof(WORD));
			}
			
			if (bstrValue)
				SysFreeString(bstrValue);

		}
		pFile->Write(&dwEmpty, sizeof(WORD)); // extraCount;


		AlignFile(pFile, dwPosition);
	}
}


void CResourceExport::ExportDllDialogs(DIRECTORY* pRoot)
{
	USES_CONVERSION;

	CXTPPropExchangeEnumeratorPtr ptrEnumeratorDialog(m_pResources->GetEnumerator(_T("dialog")));
	POSITION pos = ptrEnumeratorDialog->GetPosition();
	while (pos)
	{
		CXTPPropExchangeSection ptrSection(ptrEnumeratorDialog->GetNext(pos));
		DWORD dwId = 0;
		
		PX_DWord(&ptrSection, _T("id"), dwId);
		if (dwId == 0)
			continue;


		DIRECTORY* pDirectory = AddDirectory(pRoot, (WORD)(DWORD_PTR)RT_DIALOG, dwId, m_pLanguageInfo->wLanguage);
		CBufferFile* pFile = pDirectory->pResource = new CBufferFile(10000);

		DLLDLGTEMPLATEEX templ;
		ZeroMemory(&templ, sizeof(DLLDLGTEMPLATEEX));
		RECT rcPos = {0, 0, 0, 0};

		PX_DWord(&ptrSection, _T("style"), templ.style);
		PX_DWord(&ptrSection, _T("styleex"), templ.exStyle, 0);
		PX_Rect(&ptrSection, _T("position"), rcPos, rcPos);

		templ.dlgVer = 1;
		templ.signature = 0xFFFF;
		templ.cDlgItems = (WORD)GetDialogControlsCount(&ptrSection);
		templ.x = (short)rcPos.left;
		templ.y = (short)rcPos.top;
		templ.cx = (short)rcPos.right;
		templ.cy = (short)rcPos.bottom;
		templ.style |= DS_SETFONT;
		templ.helpID = dwId;

		WORD dwEmpty = 0;

		pFile->Write(&templ, sizeof(DLLDLGTEMPLATEEX));
		
		pFile->Write(&dwEmpty, sizeof(WORD));  // menu;
		pFile->Write(&dwEmpty, sizeof(WORD));  // windowClass;

		BSTR bstrValue = 0;		
		PX_Bstr(&ptrSection, _T("caption"), bstrValue, 0);

		if (bstrValue)
		{
			pFile->Write(bstrValue, (1 + (int)wcslen(bstrValue)) * sizeof(WCHAR));
		}
		else
		{
			pFile->Write(&dwEmpty, sizeof(WORD));
		}

		if (bstrValue)
			SysFreeString(bstrValue);

		if (templ.style & DS_SETFONT)
		{
			int nHeight = 8;
			PX_Int(&ptrSection, _T("fontsize"), nHeight, 8);
			WORD pointsize = (WORD)nHeight, weight = 0;
			BYTE bItalic = 0, charset = 0;

			pFile->Write(&pointsize, sizeof(WORD));
			pFile->Write(&weight, sizeof(WORD));
			pFile->Write(&bItalic, sizeof(BYTE));
			pFile->Write(&charset, sizeof(BYTE));
			
			CString strFont;		
			PX_String(&ptrSection, _T("fontface"), strFont, _T("MS Sans Serif"));
		
			if (!strFont.IsEmpty())
			{
				pFile->Write(T2CW(strFont), (1 + strFont.GetLength()) * sizeof(WCHAR));
			}
			else
			{
				pFile->Write(&dwEmpty, sizeof(WORD));
			}
		}

		AlignFile(pFile, 0);

		if (templ.cDlgItems > 0)
		{
			ExportDllDialogControls(pFile, &ptrSection);			
		}
	}
}


void CResourceExport::ExportDllStringTable(DIRECTORY* pRoot)
{
	CMap<UINT, UINT, STRINGTABLE*, STRINGTABLE*> mapStrings;

	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(m_pResources->GetEnumerator(_T("string")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionString(ptrEnumeratorStrings->GetNext(pos));
		BSTR bstrValue = 0;
		DWORD dwId = 0;
		
		PX_DWord(&ptrSectionString, _T("id"), dwId);
		PX_Bstr(&ptrSectionString, _T("value"), bstrValue, 0);

		int IdTable = (dwId >> 4) + 1;
		STRINGTABLE* pst = NULL;
		if (!mapStrings.Lookup(IdTable, pst))
		{
			pst = new STRINGTABLE;
			mapStrings.SetAt(IdTable, pst);
		}

		int nIndex = dwId - (((IdTable - 1 ) << 4));
		ASSERT(nIndex >= 0 && nIndex < 16);
		pst->m_bstr[nIndex] = bstrValue;
	}

	pos = mapStrings.GetStartPosition();
	while (pos)
	{
		UINT Id;
		STRINGTABLE* pst;

		mapStrings.GetNextAssoc(pos, Id, pst);
		
		DIRECTORY* pDirectory = AddDirectory(pRoot, (WORD)(DWORD_PTR)RT_STRING, Id, m_pLanguageInfo->wLanguage);
		CBufferFile* pFile = pDirectory->pResource = new CBufferFile(10000);
		for (int i = 0; i < 16; i++)
		{
			WORD wLength = 0;
			
			if (pst->m_bstr[i] != 0)
			{
				LPCWSTR lpDispalyName = (LPCWSTR)pst->m_bstr[i];
				wLength = (WORD)wcslen(lpDispalyName);
				pFile->Write(&wLength, sizeof(WORD));
				pFile->Write(lpDispalyName, wLength * sizeof(WCHAR));
			}
			else
			{
				pFile->Write(&wLength, sizeof(WORD));
			}
		}
		AlignFile(pFile, 0);

		delete pst;
	}
}

void CResourceExport::ExportDll(CXTPPropExchangeXMLNode* pResources, LPCTSTR lpszOutput)
{
	m_pResources = pResources;

	DWORD nLangId = 0;
	PX_DWord(m_pResources, _T("LANGID"), nLangId);

	m_pLanguageInfo = CXTPResourceManager::GetLanguageInfo(nLangId);
	if (!m_pLanguageInfo)
	{
		m_pResources = NULL;
		return;
	}



	DIRECTORY* pRoot = new DIRECTORY();

	ExportDllStringTable(pRoot);
	ExportDllDialogs(pRoot);
	ExportDllMenus(pRoot);

	CString lpszResourcePath = lpszOutput ? lpszOutput : _T("C:\\out.dll");


	CFile file;
	file.Open(lpszResourcePath, CFile::modeWrite | CFile::modeCreate);

	PIMAGE_DOS_HEADER pDosExeHdr = (PIMAGE_DOS_HEADER)(_alloca(512));
	{

		HRSRC hResource = ::FindResource(::GetModuleHandle(NULL), _T("DOSHEADER"), _T("BIN"));

		if (hResource == NULL)
			return;

		HGLOBAL hGlobal = LoadResource(::GetModuleHandle(NULL), hResource);
		if (hGlobal == NULL)
			return;

		LPBYTE pHeader = (LPBYTE)::LockResource(hGlobal);
		memcpy(pDosExeHdr, pHeader, 512);

		UnlockResource(hGlobal);
		FreeResource(hGlobal);
	}

	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS((LPBYTE)pDosExeHdr + (DWORD) pDosExeHdr->e_lfanew);


	CBufferFile FAT;
	CArrayDirectories DataDirs;
	WriteFAT(&FAT, pRoot, &DataDirs);
	WriteFATNames(&FAT, pRoot);

	file.Write(pDosExeHdr, 512);
	file.Write(FAT.GetBufferHeader(), (UINT)FAT.GetLength());
	int nOffset = (int)FAT.GetLength();

	for (int i = 0; i < DataDirs.GetSize(); i++)
	{
		DIRECTORY* pSubDir = DataDirs[i];
		
		if (pSubDir->pResource)
		{
			DWORD dwSize = (DWORD)pSubDir->pResource->GetLength();

			pSubDir->lpFatDataEntry->OffsetToData = nOffset + 0x00001000;
			pSubDir->lpFatDataEntry->Size = dwSize;

			file.Write(pSubDir->pResource->GetBufferHeader(), dwSize);
			nOffset += dwSize;
		}
		else
		{
			CFile filebmp;
			filebmp.Open(pSubDir->strResource, CFile::modeRead);

			DWORD dwSize = (DWORD)((int)filebmp.GetLength() - pSubDir->nResourceOffset);
			LPBYTE pBitmapInfo =(LPBYTE) malloc(dwSize);
			if (pSubDir->nResourceOffset > 0) filebmp.Seek(pSubDir->nResourceOffset, CFile::begin);
			filebmp.Read(pBitmapInfo, dwSize);
			filebmp.Close();	

			pSubDir->lpFatDataEntry->OffsetToData = nOffset + 0x00001000;
			pSubDir->lpFatDataEntry->Size = dwSize;

			file.Write(pBitmapInfo, dwSize);
			free(pBitmapInfo);
			nOffset += dwSize;
		}
	
	}
	int nAdd = 0x1000 - (nOffset & 0xFFF);
	LPBYTE lpAlign = (LPBYTE)_alloca(0x200 + nAdd);
	ZeroMemory(lpAlign, 0x200 + nAdd);
	lpAlign[nAdd + 4] = 0x8;
	file.Write(lpAlign, 0x200 + nAdd);
	nOffset += nAdd;


	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNTHeader );
	pSection->Misc.VirtualSize = nOffset;
	pSection->SizeOfRawData = nOffset;
	pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size = nOffset;

	pSection++;
	pSection->VirtualAddress = nOffset + 0x1000;
	pSection->PointerToRawData = nOffset + 0x200;
	pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress = nOffset + 0x1000;

	pNTHeader->OptionalHeader.SizeOfImage = nOffset + 0x2000;
	pNTHeader->OptionalHeader.SizeOfInitializedData = nOffset + 0x200;

	file.SeekToBegin();
	file.Write(pDosExeHdr, 512);
	file.Write(FAT.GetBufferHeader(), (UINT)FAT.GetLength());

	file.Close();


	delete pRoot;


	m_pLanguageInfo= NULL;
	m_pResources = NULL;
}

void Replace(LPSTR lpszData, LPCSTR lpszOld, LPCSTR lpszNew)
{
	int nSourceLen = (int)strlen(lpszOld);
	int nReplacementLen = (int)strlen(lpszNew);
	
	int nOldLength = (int)strlen(lpszData);
	LPSTR lpszStart = lpszData;
	LPSTR lpszTarget;
		
	while ((lpszTarget = strstr(lpszStart, lpszOld)) != NULL)
	{
		int nBalance = nOldLength - int(lpszTarget - lpszData + nSourceLen);
	
		memmove(lpszTarget + nReplacementLen, lpszTarget + nSourceLen,
			nBalance);

		memcpy(lpszTarget, lpszNew, nReplacementLen);
			
		lpszStart = lpszTarget + nReplacementLen;
		lpszStart[nBalance] = '\0';
		nOldLength += (nReplacementLen - nSourceLen);
	}
}

void WriteString(CFile& file, const CString& str)
{
	USES_CONVERSION;
	file.Write(T2CA((LPCTSTR)str), str.GetLength());
}

void WriteString(CFile& file, LPSTR str)
{
	file.Write(str, (int)strlen(str));
}

void CResourceExport::ExchangeString(CXTPPropExchange* pPX, LPCTSTR pszPropName, LPSTR lpString)
{
	BSTR bstrValue = 0;
	PX_Bstr(pPX, pszPropName, bstrValue, 0);

	ASSERT(!bstrValue || wcslen(bstrValue) < 500);

	lpString[0] = 0;
	WideCharToMultiByte(m_pLanguageInfo->nCodePage, 0, bstrValue, -1, lpString, 512, 0, 0);
	
	Replace(lpString, "\\", "\\\\");
	Replace(lpString, "\n", "\\n");
	Replace(lpString, "\r", "\\r");
	Replace(lpString, "\t", "\\t");
	Replace(lpString, "\"", "\"\"");
	
	SysFreeString(bstrValue);
}

void CResourceExport::ExportRcStringTable(CFile& file)
{
	LPCSTR lpszHeader = 
		"/////////////////////////////////////////////////////////////////////////////\r\n"
		"//\r\n"
		"// String Table\r\n"
		"//\r\n\r\n"
		"STRINGTABLE\r\n"
		"BEGIN\r\n";
		
	WriteString(file, lpszHeader);
	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(m_pResources->GetEnumerator(_T("string")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionString(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		
		char lpString[512];
		PX_DWord(&ptrSectionString, _T("id"), dwId);
		ExchangeString(&ptrSectionString, _T("value"), lpString);
	
		WriteString(file, "    ");

		CString strResourceName = GetResourceName(dwId);

		WriteString(file, strResourceName);
		file.Write("                                  ", max(1, 34 - strResourceName.GetLength()));

		WriteString(file, "\"");
		WriteString(file, lpString);
		WriteString(file, "\"\r\n");
	}

	WriteString(file, "END\r\n\r\n");	
};

void CResourceExport::ExportRcMenuItems(CFile& file, DWORD dwParent, CXTPPropExchange* pResourceMenu, const CString& strIndent)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResourceMenu->GetEnumerator(_T("menuitem")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionMenuItem(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		
		PX_DWord(&ptrSectionMenuItem, _T("id"), dwId);
		
		char lpString[512];
		ExchangeString(&ptrSectionMenuItem, _T("caption"), lpString);

		if (((CXTPPropExchangeXMLNode*)&ptrSectionMenuItem)->IsSectionExists(_T("menuitem")))
		{
			WriteString(file, strIndent);
			WriteString(file, "POPUP \"");
			WriteString(file, lpString);
			WriteString(file, "\"\r\n");
			WriteString(file, strIndent);
			WriteString(file, "BEGIN\r\n");
			
			ExportRcMenuItems(file, dwParent, &ptrSectionMenuItem, strIndent + _T("    "));
			WriteString(file, strIndent);
			WriteString(file, "END\r\n");
		}
		else if (dwId != 0)
		{
			WriteString(file, strIndent);
			WriteString(file, "MENUITEM \"");

			WriteString(file, lpString);
			
			WriteString(file, "\", ");
			CString strResourceName = GetResourceName(dwId, dwParent);
			WriteString(file, strResourceName);
			
			WriteString(file, "\r\n");
		}
		else
		{
			WriteString(file, strIndent);
			WriteString(file, "MENUITEM SEPARATOR\r\n");
		}
	}
}

void CResourceExport::ExportRcMenus(CFile& file)
{
	LPCSTR lpszHeader = 
		"/////////////////////////////////////////////////////////////////////////////\r\n"
		"//\r\n"
		"// Menu\r\n"
		"//\r\n\r\n";

	WriteString(file, lpszHeader);
	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(m_pResources->GetEnumerator(_T("menu")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionMenu(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		
		PX_DWord(&ptrSectionMenu, _T("id"), dwId);
		if (dwId == 0)
			continue;
		CString strResourceName = GetResourceName(dwId);

		CString strMenuHeader; 
		strMenuHeader.Format(_T("%s MENU DISCARDABLE\r\nBEGIN\r\n"), (LPCTSTR)strResourceName);		
		WriteString(file, strMenuHeader);

		ExportRcMenuItems(file, dwId, &ptrSectionMenu, _T("    "));

		WriteString(file, "END\r\n\r\n");	
	}
}

void CResourceExport::ExportRcDialogControls(CFile& file, DWORD dwParent, CXTPPropExchange* pResourceDialog)
{
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(pResourceDialog->GetEnumerator(_T("control")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionControl(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		DWORD dwStyle = 0, styleex = 0;
		RECT rc = {0, 0, 0, 0};
		CString strClass;
		
		PX_DWord(&ptrSectionControl, _T("id"), dwId);
		PX_DWord(&ptrSectionControl, _T("style"), dwStyle, WS_CHILD | WS_VISIBLE | WS_GROUP);
		PX_DWord(&ptrSectionControl, _T("styleex"), styleex, 0);

		PX_Rect(&ptrSectionControl, _T("position"), rc, rc);
		PX_String(&ptrSectionControl, _T("class"), strClass, _T("STATIC"));
		
		CString strResourceName = dwId == 0 ? _T("IDC_STATIC") :
			dwId == IDOK ? _T("IDOK") : 
			dwId == IDCANCEL ? _T("IDCANCEL") : 
			dwId == ID_HELP ? _T("ID_HELP") : 
			GetResourceName(dwId, dwParent);

		char lpCaption[512];
		ExchangeString(&ptrSectionControl, _T("caption"), lpCaption);

		LPCSTR strType = NULL;
		DWORD dwStyleDefault = (WS_CHILD | WS_VISIBLE | WS_TABSTOP);

		DWORD bsStyle = dwStyle & 0xF;
		BOOL bAddCaption = TRUE;
	
		if (strClass.CompareNoCase(_T("BUTTON")) == 0)
		{
			if (bsStyle == BS_DEFPUSHBUTTON) strType = "    DEFPUSHBUTTON   \"";
			if (bsStyle == BS_PUSHBUTTON)    strType = "    PUSHBUTTON      \"";
			if (bsStyle == BS_RADIOBUTTON)   strType = "    RADIOBUTTON     \"";

			if (bsStyle == BS_GROUPBOX) 
			{
				strType = "    GROUPBOX        \"";
				dwStyleDefault = (WS_CHILD | WS_VISIBLE);
			}

			dwStyleDefault += bsStyle;
		}
		else if (strClass.CompareNoCase(_T("STATIC")) == 0)
		{
			if (bsStyle == SS_LEFT)   strType = "    LTEXT           \"";
			if (bsStyle == SS_RIGHT)  strType = "    RTEXT           \"";
			if (bsStyle == SS_CENTER) strType = "    CTEXT           \"";
			
			dwStyleDefault = (WS_CHILD | WS_VISIBLE | WS_GROUP) + bsStyle;
		}
		else if (strClass.CompareNoCase(_T("COMBOBOX")) == 0)
		{
			strType = "    COMBOBOX        ";
			bAddCaption = FALSE;
		}
		else if (strClass.CompareNoCase(_T("LISTBOX")) == 0)
		{
			strType = "    LISTBOX         ";
			bAddCaption = FALSE;
		}
		else if (strClass.CompareNoCase(_T("EDIT")) == 0)
		{
			strType = "    EDITTEXT        ";
			bAddCaption = FALSE;
		}



		CString str;
		
		if (strType == NULL)
		{
			WriteString(file, "    CONTROL         \"");
			WriteString(file, lpCaption);
			
			str.Format(_T("\",%s,\"%s\",0x%x,%i,%i,%i,%i"), (LPCTSTR)strResourceName, 
				(LPCTSTR)strClass, dwStyle, 
				rc.left, rc.top, rc.right, rc.bottom);
			WriteString(file, str);
		}
		else
		{
			WriteString(file, strType);
			if (bAddCaption)
			{
				WriteString(file, lpCaption);
				WriteString(file, "\",");
			}
			
			str.Format(_T("%s,%i,%i,%i,%i"), (LPCTSTR)strResourceName,
				rc.left, rc.top, rc.right, rc.bottom);
			WriteString(file, str);

			if (dwStyle != dwStyleDefault || styleex != 0)
			{
				str.Format(_T(",0x%x"), dwStyle);
				WriteString(file, str);
			}
		}

		if (styleex != 0)
		{
			str.Format(_T(",0x%x"), styleex);
			WriteString(file,str);
		}

		WriteString(file, "\r\n");
	}
}


void CResourceExport::ExportRcDialogs(CFile& file)
{
	LPCSTR lpszHeader = 
		"/////////////////////////////////////////////////////////////////////////////\r\n"
		"//\r\n"
		"// Dialog\r\n"
		"//\r\n\r\n";

	WriteString(file, lpszHeader);
	
	CXTPPropExchangeEnumeratorPtr ptrEnumeratorStrings(m_pResources->GetEnumerator(_T("dialog")));
	POSITION pos = ptrEnumeratorStrings->GetPosition();
	
	while (pos)
	{
		CXTPPropExchangeSection ptrSectionDailog(ptrEnumeratorStrings->GetNext(pos));
		DWORD dwId = 0;
		DWORD dwStyle = 0, dwExStyle = 0;
		RECT rc = {0, 0, 0, 0};
		CString strFace;
		
		PX_DWord(&ptrSectionDailog, _T("id"), dwId);
		PX_DWord(&ptrSectionDailog, _T("style"), dwStyle);
		PX_DWord(&ptrSectionDailog, _T("styleex"), dwExStyle, 0);
		PX_Rect(&ptrSectionDailog, _T("position"), rc, rc);
		PX_String(&ptrSectionDailog, _T("fontface"), strFace, _T("MS Sans Serif"));
	
		char lpCaption[512];
		ExchangeString(&ptrSectionDailog, _T("caption"), lpCaption);

		if (dwId == 0)
			continue;
		CString strResourceName = GetResourceName(dwId);

		CString strHeader; 
		strHeader.Format(_T("%s DIALOGEX DISCARDABLE %i, %i, %i, %i\r\n"), 
			(LPCTSTR)strResourceName, rc.left, rc.top, rc.right, rc.bottom);		
		WriteString(file, strHeader);

		if (dwExStyle != 0)
		{
			strHeader.Format(_T("EXSTYLE 0x%x\r\n"), dwExStyle);		
			WriteString(file, strHeader);
		}

		strHeader.Format(_T("STYLE 0x%x\r\n"), dwStyle);		
		WriteString(file, strHeader);

		WriteString(file, "CAPTION \""); WriteString(file, lpCaption); WriteString(file, "\"\r\n");
		WriteString(file, "FONT 8, \""); WriteString(file, strFace); WriteString(file, "\"\r\n");

		WriteString(file, "BEGIN\r\n");

		ExportRcDialogControls(file, dwId, &ptrSectionDailog);

		WriteString(file, "END\r\n\r\n");	
	}
}


void CResourceExport::ExportRc(CXTPPropExchangeXMLNode* pResources, LPCTSTR lpszOutput)
{
	m_pResources = pResources;
	
	CString lpszResourcePath = lpszOutput ? lpszOutput : _T("C:\\out.rc");

	CFile file;
	file.Open(lpszResourcePath, CFile::modeWrite | CFile::modeCreate);

	DWORD nLangId = 0;
	PX_DWord(m_pResources, _T("LANGID"), nLangId);

	m_pLanguageInfo = CXTPResourceManager::GetLanguageInfo(nLangId);
	if (!m_pLanguageInfo)
	{
		WriteString(file, "Not found");
		m_pResources = NULL;
		return;
	}

	CString strHeader;
	strHeader.Format(
		_T("// Codejock ResourceEditor generated resource script.\r\n")
		_T("//\r\n\r\n#include \"afxres.h\"\r\n\r\n")
		_T("/////////////////////////////////////////////////////////////////////////////\r\n")
		_T("// %s resources\r\n\r\n")
		_T("#if !defined(AFX_RESOURCE_DLL)\r\n")
		_T("#ifdef _WIN32\r\n")
		_T("LANGUAGE %s, %s\r\n")
		_T("#pragma code_page(%i)\r\n")
		_T("#endif //_WIN32\r\n\r\n"), m_pLanguageInfo->lpszCaption, 
		m_pLanguageInfo->lpszLang, m_pLanguageInfo->lpszSubLang, m_pLanguageInfo->nCodePage);

	WriteString(file, strHeader);

	ExportRcDialogs(file);
	ExportRcMenus(file);
	ExportRcStringTable(file);

	WriteString(file, "#endif\r\n");

	file.Close();
	
	m_pLanguageInfo = NULL;
	m_pResources = NULL;
}

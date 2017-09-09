// SearchThread.cpp : implementation file
//

#include "stdafx.h"
#include "grep.h"
#include "SearchThread.h"
#include "SearchOptions.h"
#include "MainFrm.h"
#include "GrepView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchThread

IMPLEMENT_DYNCREATE(CSearchThread, CWinThread)


long GetLineNumber(TCHAR* lpszFileBuffer, int nIndex)
{
	long nLine = 1;
	while (nIndex--)
	{
		if (*lpszFileBuffer == _T('\n')) nLine++;
		lpszFileBuffer++;
	}

	return nLine;
}

void CSearchThread::AddRecord(CXTPReportControl& wndControl, TCHAR* lpszFileBuffer, TCHAR* lpszEndBuffer, long nIndex, long nLength,
					CString strMatch, CString strReplace, CString strPath, CFileFind& finder)
{
	USES_CONVERSION;

	TCHAR* lpszMatch = lpszFileBuffer + nIndex;
	TCHAR* lpszMatchBeginLine = lpszMatch;
	TCHAR* lpszMatchEndLine = lpszMatchBeginLine + nLength;
	
	int nMaxPreview = 80;

	while (nMaxPreview-- && lpszMatchBeginLine != lpszFileBuffer && *(lpszMatchBeginLine - 1) != '\n')
		lpszMatchBeginLine--;

	if (*lpszMatchEndLine != '\n')
	{
		nMaxPreview = 80;

		while (nMaxPreview-- && lpszMatchEndLine != lpszEndBuffer && *(lpszMatchEndLine + 1) != '\n' )
			lpszMatchEndLine++;
	}
	TCHAR tchEndLine = *lpszMatchEndLine;
	*lpszMatchEndLine = '\0';


	CString strBeginLine;
	long nBeginLineLength = long(lpszMatch - lpszMatchBeginLine);
	STRNCPY_S(strBeginLine.GetBufferSetLength(nBeginLineLength), nBeginLineLength + 1, lpszMatchBeginLine, nBeginLineLength);


	CString strEndLine;
	long nEndLineLength = long(lpszMatchEndLine - lpszMatch - nLength);
	STRNCPY_S(strEndLine.GetBufferSetLength(nEndLineLength), nEndLineLength + 1, lpszMatch + nLength, nEndLineLength);

	wndControl.AddRecord(new CGrepRecord
		(finder.GetFilePath(), strPath, finder.GetFileName(), strMatch,
		GetLineNumber(lpszFileBuffer, nIndex),
		strBeginLine + strMatch + strEndLine,
		strBeginLine + strReplace + strEndLine, nIndex, nLength, strReplace));

	*lpszMatchEndLine = tchEndLine;

	m_searchResult.nMatchingLines++;
}

void CSearchThread::SetMessageText()
{
	CString strMessage;
	strMessage.Format(_T("Matching lines: %i        Matching files: %i        Total files searched: %i"), 
		m_searchResult.nMatchingLines, m_searchResult.nMatchingFiles, m_searchResult.nTotalFiles);
	
	m_pMainFrame->SetMessageText(strMessage);
	m_pMainFrame->DelayPopulate();		
}

#ifdef _UNICODE
#define CT2BSTR(x) (BSTR)(LPCWSTR)x
#else
#define CT2BSTR(x) (BSTR)A2CW(x)
#endif

int FindNext(const CString& str, const CString& strFind, int nIndex, CSearchOptions* pOptions)
{
	nIndex = str.Find(strFind, nIndex);
	
	if (!pOptions->m_bMatchWholeWords)
		return nIndex;

	while (nIndex != -1)
	{
		
		if (CheckMatchWholeWords(str, nIndex, strFind.GetLength()))
			return nIndex;
		
		nIndex = str.Find(strFind, nIndex + 1);
		
	}
	return nIndex;
}

BOOL CSearchThread::ProcessFile(CString strPath, CFileFind& finder)
{
	USES_CONVERSION;
	
	if (!m_pReportControl)
		return FALSE;

	CSearchOptions* pOptions = GetSearchOptions();
	ASSERT(pOptions);

	CFile file;
	if (!file.Open(finder.GetFilePath(), CFile::modeRead))
		return TRUE;

	DWORD dwCount = (DWORD)file.GetLength();

	char* pchData = new char[dwCount + 1];
	file.Read(pchData, dwCount);
	pchData[dwCount] = 0;

#ifdef _UNICODE
	TCHAR* lpszFileBuffer = new TCHAR[dwCount + 1];
	_mbstowcsz(lpszFileBuffer, pchData, dwCount+1);
#else
	char* lpszFileBuffer = pchData;
#endif


	file.Close();
	TCHAR* lpszEndBuffer = lpszFileBuffer + dwCount;

	
	BOOL bContinue = TRUE;

	if (pOptions->m_bBatchMode)
	{
		CString str(lpszFileBuffer);
		
		if (!pOptions->m_bMatchCase)
		{
			str.MakeLower();
		}

		CString strFind, strReplace;
		
		int nIndex = m_batchSearch.FindNext(str, 0, pOptions, strFind, strReplace);
		
		if (nIndex != -1)
		{
			m_searchResult.nMatchingFiles++;
		}
		
		while (nIndex != -1)
		{
			int nLength = strFind.GetLength();

			CString strMatch;
			STRNCPY_S(strMatch.GetBufferSetLength(nLength), nLength + 1, lpszFileBuffer + nIndex, nLength);
			
			if (m_bCancel)
			{
				bContinue = FALSE;
				break;
			}
			
			AddRecord(*m_pReportControl, lpszFileBuffer, lpszEndBuffer, nIndex, nLength,
				strMatch, strReplace, strPath, finder);
			
			nIndex = m_batchSearch.FindNext(str, nIndex + strFind.GetLength(), pOptions, strFind, strReplace);			
		}

	}
	else if (!pOptions->pRegExp)
	{
		CString str(lpszFileBuffer);
		CString strFind = pOptions->m_strFind;

		if (!pOptions->m_bMatchCase)
		{
			str.MakeLower();
			strFind.MakeLower();
		}

		int nLength = strFind.GetLength();
		int nIndex = FindNext(str, strFind, 0, pOptions);

		if (nIndex != -1)
		{
			m_searchResult.nMatchingFiles++;
		}

		while (nIndex != -1)
		{
			CString strMatch;
			STRNCPY_S(strMatch.GetBufferSetLength(nLength), nLength + 1, lpszFileBuffer + nIndex, nLength);

			if (m_bCancel)
			{
				bContinue = FALSE;
				break;
			}

			CString strReplace = pOptions->m_strReplace;
			AddRecord(*m_pReportControl, lpszFileBuffer, lpszEndBuffer, nIndex, nLength,
					strMatch, strReplace, strPath, finder);

			nIndex = FindNext(str, strFind, nIndex + strFind.GetLength(), pOptions);
			
		}
	}
	else
	{

		try
		{
#ifndef _UNICODE
			BSTR bstrBuffer = new WCHAR[dwCount + 1];
			_mbstowcsz(bstrBuffer, lpszFileBuffer, dwCount+1);
#else
			BSTR bstrBuffer = (BSTR)lpszFileBuffer;
#endif
			IMatchCollectionPtr MatchesPtr = pOptions->pRegExp->Execute(bstrBuffer);

			int nCount = MatchesPtr.GetInterfacePtr()? MatchesPtr->Count: 0;

			if (nCount > 0)
			{
				m_searchResult.nMatchingFiles++;
			}

			for (int i = 0; i < nCount; i++)
			{
				IMatchPtr MatchPtr = MatchesPtr->Item[i];

				int nIndex = MatchPtr->FirstIndex;
				int nLength =MatchPtr->Length;

				CString strMatch;
				STRNCPY_S(strMatch.GetBufferSetLength(nLength), nLength + 1, lpszFileBuffer + nIndex, nLength);

				_bstr_t bstrResult =pOptions->pRegExp->Replace(CT2BSTR(strMatch), CT2BSTR(pOptions->m_strReplace));
				CString strReplace = (LPCWSTR)bstrResult;

				if (m_bCancel)
				{
					bContinue = FALSE;
					break;
				}

				AddRecord(*m_pReportControl, lpszFileBuffer, lpszEndBuffer, nIndex, nLength,
					strMatch, strReplace, strPath, finder);
			
			}
#ifndef _UNICODE
			delete[] bstrBuffer;
#endif

		}
		catch (_com_error& e)
		{
			CString strDescription(BSTR(e.Description()));
			if (strDescription.IsEmpty())
				strDescription = _T("Error in regular expression.");
			strDescription += " Continue?";

			bContinue = AfxMessageBox(strDescription, MB_YESNO) == IDNO? FALSE: TRUE;				
		}
	}


	delete[] lpszFileBuffer;

#ifdef _UNICODE
	delete[] pchData;
#endif
	
	if (bContinue)
	{
		SetMessageText();
	}

	return bContinue;

}

BOOL MatchFileType(CString strFileName, CString strMask)
{
	if (strMask == _T("*.*"))
		return TRUE;

	strMask.MakeLower();
	strFileName.MakeLower();
	
	strFileName += _T(";");
	strMask += _T(";");

	CString str = strMask;
	while (str != _T(";") && str != _T(""))
	{
		int nIndex = str.Find(_T(';'));
		if (nIndex != -1)
		{
			strMask = str.Mid(nIndex + 1);
			str = str.Left(nIndex + 1);
		}
		else
		{
			strMask.Empty();
		}

		str.Replace(_T("*;"), _T(""));
		str.Replace(_T(";*"), _T(""));
		str.Replace(_T("*"), _T(""));

		if (strFileName.Find(str) >= 0)
			return TRUE;

		str = strMask;
	}

	return FALSE;
}


BOOL CSearchThread::ProcessPath(CString strPath)
{
	CFileFind finder;

	CString strWildcard = strPath + _T("\\*.*") ;

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		// skip . and .. files; otherwise, we'd
		// recur infinitely!

		if (finder.IsDots())
			continue;

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
		{
			if (GetSearchOptions()->m_bIncludeSubFolders)
			{
				if (GetSearchOptions()->m_bFindInHiddenFiles || !finder.IsHidden())
				{
					if (!ProcessPath(finder.GetFilePath()))
						return FALSE;
				}
			}
			continue;
		}

		if (MatchFileType(finder.GetFileName(), GetSearchOptions()->m_strFileTypes))
		{
			if (GetSearchOptions()->m_bFindInHiddenFiles || !finder.IsHidden())
			{
				m_searchResult.nTotalFiles++;			

				if (!ProcessFile(strPath, finder))
					return FALSE;
			}
		}

		if (m_bCancel)
			return FALSE;
	}

	finder.Close();

	return TRUE;

}

CSearchThread::CSearchThread()
{
	m_pMainFrame = NULL;
	m_pReportControl = NULL;
	m_bAutoDelete = TRUE;
	m_bCancel = FALSE;

	ZeroMemory(&m_searchResult, sizeof(SEARCH_RESULT));
}

CSearchThread::~CSearchThread()
{
}

BOOL CSearchThread::InitInstance()
{
	USES_CONVERSION;

	AfxOleInit();

	IRegExpPtr regExp;

	CSearchOptions* pOptions = GetSearchOptions();
	ASSERT(pOptions);


	if (pOptions->m_bRegularExpressions)
	{
		HRESULT hr = regExp.CreateInstance(__uuidof(RegExp));

		if (FAILED(hr))
		{
			AfxMessageBox(_T("RegExp not found"));
		}
		else
		{
			pOptions->pRegExp = regExp;
			regExp->Global = VARIANT_TRUE;
			regExp->IgnoreCase = pOptions->m_bMatchCase? VARIANT_FALSE: VARIANT_TRUE;
			regExp->Pattern = _bstr_t(CT2BSTR(pOptions->m_strFind));
		}
	}

	BOOL bFailed = FALSE;
	
	if (pOptions->m_bBatchMode)
	{
		if (!m_batchSearch.LoadMatches(pOptions->m_strBatchFile, pOptions))
		{
			AfxMessageBox(_T("Matches not found"));

			bFailed = TRUE;
		}
		
	}

	if (!bFailed)
	{
		ProcessPath(pOptions->m_strPath);
	}

	pOptions->pRegExp = 0;

	// TODO:  perform and per-thread initialization here
	return FALSE;
}

int CSearchThread::ExitInstance()
{
	m_pMainFrame->PostMessage(WM_SEARCHFINISHED);
	
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSearchThread, CWinThread)
	//{{AFX_MSG_MAP(CSearchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchThread message handlers

// BatchSearch.h: interface for the CBatchSearch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_)
#define AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSearchOptions;

BOOL CheckMatchWholeWords(const CString& str, int nIndex, int nLength);


class CBatchSearch  
{
	struct CMatch
	{
		CString strFindString;
		CString strReplaceString;
	};

	struct CNode
	{
		CNode();		
		~CNode();

		CMap<TCHAR, TCHAR, CNode*, CNode*> nextMap;
		int nMatch;
		CNode* parentNode;
		TCHAR pch;
		CNode* linkNode;
	};

public:
	CBatchSearch();
	virtual ~CBatchSearch();

	BOOL LoadMatches(CString strBatchFile, CSearchOptions* pOptions);
	void BuildTree();

	CArray<CMatch, CMatch&> m_arrMatches;

	int FindNext(const CString& strBuffer, int nIndex, CSearchOptions* pOptions, CString& strFindString, CString& strReplaceString);
	CNode* GetLink(CNode* v);
	CNode* GoNextChar(CNode* v, TCHAR c);

protected:
	CNode* m_pRootNode;
};

#endif // !defined(AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_)

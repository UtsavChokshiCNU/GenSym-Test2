// BatchSearch.cpp: implementation of the CBatchSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "BatchSearch.h"
#include "SearchOptions.h"

static LPCTSTR szSeps = _T("~() \t<>{}:;,.=%\"'!@#$^&*-\\|[]/?+\r\n");

BOOL CheckMatchWholeWords(const CString& str, int nIndex, int nLength)
{
	BOOL bSepAfter = FALSE;
	BOOL bSepBefore = FALSE;
	
	if (nIndex + nLength >= str.GetLength())
		bSepAfter = TRUE;
	else
		bSepAfter = (_tcschr(szSeps, str[nIndex + nLength]) != 0);
	
	if (nIndex == 0)
		bSepBefore = TRUE;
	else
		bSepBefore = (_tcschr(szSeps, str[nIndex - 1]) != 0);
	
	if (bSepAfter && bSepBefore)
		return TRUE;
	
	return FALSE;
}


CBatchSearch::CNode::CNode()
{
	nMatch = -1;
	parentNode = NULL;
	pch = 0;
	linkNode = NULL;
}


CBatchSearch::CNode::~CNode()
{
	POSITION pos = nextMap.GetStartPosition();
	while (pos)
	{
		TCHAR c;
		CNode* pNext;
		nextMap.GetNextAssoc(pos, c, pNext);

		delete pNext;
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBatchSearch::CBatchSearch()
{
	m_pRootNode = new CNode();

}

CBatchSearch::~CBatchSearch()
{
	delete m_pRootNode;
}

BOOL CBatchSearch::LoadMatches(CString strBatchFile, CSearchOptions* pOptions)
{
	m_arrMatches.RemoveAll();

	CXTPPropExchangeXMLNode px(TRUE, 0, _T("Grep"));
	
	if (!px.LoadFromFile(strBatchFile))
		return FALSE;


	CXTPPropExchangeEnumeratorPtr pEnumerator(px.GetEnumerator(_T("Match")));
	POSITION pos = pEnumerator->GetPosition(0);

	while (pos)
	{
		CXTPPropExchangeSection sec(pEnumerator->GetNext(pos));	

		CMatch match;
		PX_String(&sec, _T("FindString"), match.strFindString);
		PX_String(&sec, _T("ReplaceString"), match.strReplaceString);

		if (!pOptions->m_bMatchCase)
		{
			match.strFindString.MakeLower();
		}

		if (!match.strFindString.IsEmpty())
		{
			m_arrMatches.Add(match);
		}
	}

	BuildTree();

	return m_arrMatches.GetSize() > 0;
}

void CBatchSearch::BuildTree()
{
	for (int i = 0; i < (int)m_arrMatches.GetSize(); i++)
	{
		CString strFindString = m_arrMatches[i].strFindString;

		CNode* pNode = m_pRootNode;

		for (int j = 0; j < strFindString.GetLength(); j++) 
		{
			TCHAR c = strFindString[j];

			CNode* pNext;
			if (!pNode->nextMap.Lookup(c, pNext))
			{
				pNext = new CNode();
				pNext->parentNode = pNode;
				pNext->pch = c;
				pNode->nextMap[c] = pNext;
			}
			pNode = pNext;
		}
		pNode->nMatch = i;
	}
}


CBatchSearch::CNode* CBatchSearch::GetLink(CNode* v) 
{
	if (!v->linkNode)
	{	
		if (v == m_pRootNode || v->parentNode == m_pRootNode)
			v->linkNode = m_pRootNode;
		else
			v->linkNode = GoNextChar(GetLink(v->parentNode), v->pch);
	}
	return v->linkNode;
}

CBatchSearch::CNode* CBatchSearch::GoNextChar(CNode* v, TCHAR c) 
{
	CNode* pNextNode = NULL;

	if (v->nextMap.Lookup(c, pNextNode))
		return pNextNode;

	return v == m_pRootNode ? m_pRootNode : GoNextChar(GetLink(v), c);
}

int CBatchSearch::FindNext(const CString& strBuffer, int nIndex, CSearchOptions* pOptions, CString& strFindString, CString& strReplaceString)
{
	CNode* pNode = m_pRootNode;

	for (; nIndex < strBuffer.GetLength(); nIndex++)
	{
		TCHAR c = strBuffer[nIndex];

		pNode = GoNextChar(pNode, c);

		if (pNode->nMatch != -1)
		{
			strFindString = m_arrMatches[pNode->nMatch].strFindString;
			strReplaceString = m_arrMatches[pNode->nMatch].strReplaceString;
			
			int nIndexFind = nIndex - strFindString.GetLength() + 1; 

			if (!pOptions->m_bMatchWholeWords || CheckMatchWholeWords(strBuffer, nIndexFind, strFindString.GetLength()))
				return nIndexFind;

		}
	}

	return -1;
}
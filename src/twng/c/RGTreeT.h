#ifndef RGTREET_H
#define RGTREET_H

/**********************************************************************************************
 *                                                                                            *
 *  FILE: RGTreeT.h                                                                           *
 *                                                                                            *
 *  DESCRIPTION:                                                                              *
 *       Template class for implementing a tree structure like the WinAPI tree control        *
 *                                                                                            *
 *  René Greiner                                                                              *
 *		eMail: rene.greiner@gmx.de                                                            *
 *                                                                                            *
 **********************************************************************************************/

// abstract iteration position
//struct __POSITION { };
//typedef __POSITION* POSITION;

typedef int (CALLBACK* CompareFunc)( LPARAM lParam1, LPARAM lParam2);
typedef void (CALLBACK* DeleteFunc)( POSITION pos, LPARAM lParam);

template<class _T> inline void swap_classes( _T& t1, _T& t2)
{
	_T temp = t1;
	t1 = t2;
	t2 = temp;
}

template<class _ITEMDATA> class CRGTreeT
{
	// lParam1 < lParam2	=>  < 0
	// lParam1 > lParam2	=>	> 0
	// lParam1 == lParam2	=>  = 0
	
#pragma pack(push,4)
	typedef struct CTreeItem
	{
		CTreeItem*		pTIParent;
		CTreeItem*		pTIPrev;
		CTreeItem*		pTINext;
		CTreeItem*		pTIChildFirst;
		CTreeItem*		pTIChildLast;
		int				nChildCount;
		_ITEMDATA		ItemData;
		CTreeItem()		
		{
			nChildCount = 0; pTIChildFirst = pTIChildLast = NULL; 
		}
	} CTreeItem;
	
#pragma pack(pop)
#define INC_ITEMS(pParent)	{pParent->nChildCount++; m_nCount++;}
#define DEC_ITEMS(pParent)	{pParent->nChildCount--; m_nCount--;}
	
public:
	// Construction / Destruction
	CRGTreeT();
	~CRGTreeT();

	// returns the count of all items
	UINT GetItemCount() const;
	// returns the count of all child items 
	UINT GetChildCount( /*[in]*/ POSITION posParent) const;

	// returns the root
	POSITION GetRootPosition() const;
	// returns the parent of an item
	POSITION GetParentPosition( /*[in]*/ POSITION pos) const;

	// adds an items at the begin of the list
	POSITION AddHead( /*[in]*/ const _ITEMDATA *pItemData, /*[in]*/ POSITION posParent=NULL);
	// adds an items at the end of the list
	POSITION AddTail( /*[in]*/ const _ITEMDATA *pItemData, /*[in]*/ POSITION posParent=NULL);
	POSITION InsertAfter( /*[in]*/ const _ITEMDATA *pItemData, POSITION posParent=NULL, /*[in]*/POSITION posAfter=NULL);

	// Remove the item at position pos including all subitems
	void RemoveAt( /*[in]*/ POSITION pos);
	// Removes all items
	void RemoveAll();

	// returns the first/last child item of the item at position posParent
	POSITION GetChildPosition( /*[in]*/ POSITION posParent, /*[in]*/ BOOL bFirst=TRUE) const;
	// returns the next list element, NULL if none
	POSITION GetNextPosition( /*[in]*/ POSITION pos) const;
	// returns the previous element, NULL if none
	POSITION GetPrevPosition( /*[in]*/ POSITION pos) const;

	// returning a copy of the ITEMDATA at position pos
	void GetAt( /*[in]*/ POSITION pos, /*[out]*/ _ITEMDATA* pItemData) const;
	// Returning a pointer to the ITEMDATA at position pos
	_ITEMDATA* GetAt( /*[in]*/ POSITION pos);
	// replace the ITEMDATA at position pos
	void SetAt( /*[in]*/ POSITION pos, /*[in]*/ const _ITEMDATA* pItemData);

	// sort childrens of the item at position posParent
	BOOL SortChildren( /*[in]*/ POSITION posParent, /*[in]*/ BOOL bAscending=TRUE);

	// search for an item based on the compare function
	POSITION Find( /*[in]*/ const _ITEMDATA *pItemData, /*[in]*/ POSITION posParent);
	// setting a callback function for sorting and finding items
	CompareFunc SetCompareFunc( /*[in]*/ CompareFunc func);
	DeleteFunc SetDeleteFunc( /*[in]*/ DeleteFunc func, LPARAM lParam);

protected:
	// remove all childs from an item
	void RemoveChilds( POSITION pos);
	// quick sort algorithms for sorting up- or downwards
	void QSortA( /*[in]*/ CTreeItem **pLow, /*[in]*/ CTreeItem **pHigh);
	void QSortD( /*[in]*/ CTreeItem **pLow, /*[in]*/ CTreeItem **pHigh);

private:
	CTreeItem			m_ItemRoot;
	UINT					m_nCount;
	CompareFunc		m_pCompareFunc;
	DeleteFunc		m_pDeleteFunc;
	LPARAM				m_lParamDeleteFunc;
};


template<class _ITEMDATA>
inline CRGTreeT<_ITEMDATA>::CRGTreeT()
{
	m_nCount = 0;
	memset( &m_ItemRoot, 0, sizeof(CTreeItem));
	m_pCompareFunc = NULL;
	m_pDeleteFunc = NULL;
}

template<class _ITEMDATA>
inline CRGTreeT<_ITEMDATA>::~CRGTreeT()
{
	RemoveAll();
}

template<class _ITEMDATA>
inline UINT CRGTreeT<_ITEMDATA>::GetItemCount() const
{
	return m_nCount;
}

template<class _ITEMDATA>
inline UINT CRGTreeT<_ITEMDATA>::GetChildCount( POSITION posParent) const
{
	return (posParent ? (CTreeItem*)posParent : &m_ItemRoot)->nChildCount;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::GetRootPosition() const
{
	return (POSITION)m_ItemRoot.pTIChildFirst;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::GetParentPosition( POSITION pos) const
{
	ASSERT(pos);
	return ((CTreeItem*)pos)->pTIParent == &m_ItemRoot ? NULL : (POSITION)((CTreeItem*)pos)->pTIParent;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::AddHead( const _ITEMDATA *pItemData, POSITION posParent)
{
	CTreeItem *pParent = posParent ? (CTreeItem*)posParent : &m_ItemRoot;
	CTreeItem *pItem = new CTreeItem;
	pItem->ItemData = *pItemData;
	pItem->pTIParent = pParent;
	pItem->pTIPrev = NULL;
	if( pParent->pTIChildFirst)
	{
		pParent->pTIChildFirst->pTIPrev = pItem;
		pItem->pTINext = pParent->pTIChildFirst;
	}
	else
	{
		pItem->pTINext = NULL;
		pParent->pTIChildLast = pItem;
	}
	pParent->pTIChildFirst = pItem;

	INC_ITEMS( pParent)
	return (POSITION)pItem;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::AddTail( const _ITEMDATA *pItemData, POSITION posParent)
{
	register CTreeItem *pParent = posParent ? (CTreeItem*)posParent : &m_ItemRoot;
	register CTreeItem *pItem = new CTreeItem;
	pItem->ItemData = *pItemData;
	pItem->pTINext = NULL;
	pItem->pTIParent = pParent;
	if( pParent->pTIChildLast)
	{
		pParent->pTIChildLast->pTINext = pItem;
		pItem->pTIPrev = pParent->pTIChildLast;
	}
	else
	{
		pItem->pTIPrev = NULL;
		pParent->pTIChildFirst = pItem;
	}
	pParent->pTIChildLast = pItem;

	INC_ITEMS( pParent)
	return (POSITION)pItem;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::InsertAfter( const _ITEMDATA *pItemData, POSITION posParent, POSITION posAfter)
{
	if( posAfter == NULL
		|| posAfter == (POSITION)TVI_ROOT)
		return AddTail( pItemData, posParent);

	CTreeItem *pParent = posParent ? (CTreeItem*)posParent : &m_ItemRoot;
	CTreeItem *pAfter = (CTreeItem*)posAfter;
	if( pAfter->pTIParent != pParent)
		return NULL;
	if( pParent->pTIChildLast == pAfter)
		return AddTail( pItemData, posParent);

	CTreeItem *pItem = new CTreeItem;
	ASSERT(pItem);
	pItem->ItemData = *pItemData;
	pItem->pTIParent = pParent;

	pItem->pTIPrev = pAfter;
	pItem->pTINext = pAfter->pTINext;
	pAfter->pTINext = pItem;
	pItem->pTINext->pTIPrev = pItem;

	INC_ITEMS( pParent)
	return (POSITION)pItem;
}

template<class _ITEMDATA>
inline void CRGTreeT<_ITEMDATA>::RemoveAt( POSITION pos)
{
	RemoveChilds( GetChildPosition( pos));
	CTreeItem *pNext = ((CTreeItem*)pos)->pTINext;
	CTreeItem *pPrev = ((CTreeItem*)pos)->pTIPrev;
	CTreeItem *pParent = ((CTreeItem*)pos)->pTIParent;
	if( pPrev)
		pPrev->pTINext = pNext;
	else
		pParent->pTIChildFirst = pNext;

	if( pNext)
		pNext->pTIPrev = pPrev;
	else
		pParent->pTIChildLast = pPrev;

	if( m_pDeleteFunc)
		(*m_pDeleteFunc)( pos, m_lParamDeleteFunc);
	delete (CTreeItem*)pos;
	DEC_ITEMS( pParent)
}

template<class _ITEMDATA>
inline void CRGTreeT<_ITEMDATA>::RemoveAll()
{
	RemoveChilds( (POSITION)m_ItemRoot.pTIChildFirst);
	m_ItemRoot.pTIChildFirst = m_ItemRoot.pTIChildLast = NULL;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::GetChildPosition( POSITION posParent, BOOL bFirst) const
{
	if( !posParent)
		return GetRootPosition();
	return (POSITION)(bFirst ? ((CTreeItem*)posParent)->pTIChildFirst : ((CTreeItem*)posParent)->pTIChildLast);
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::GetNextPosition( POSITION pos) const
{
	return (POSITION)((CTreeItem*)pos)->pTINext;
}

template<class _ITEMDATA>
inline POSITION CRGTreeT<_ITEMDATA>::GetPrevPosition( POSITION pos) const
{
	return (POSITION)((CTreeItem*)pos)->pTIPrev;
}

template<class _ITEMDATA>
inline void CRGTreeT<_ITEMDATA>::GetAt( POSITION pos, _ITEMDATA* pItemData) const
{
	*pItemData = ((CTreeItem*)pos)->ItemData;
}

template<class _ITEMDATA>
inline _ITEMDATA* CRGTreeT<_ITEMDATA>::GetAt( POSITION pos)
{
	return &((CTreeItem*)pos)->ItemData;
}

template<class _ITEMDATA>
inline void CRGTreeT<_ITEMDATA>::SetAt( POSITION pos, const _ITEMDATA* pItemData)
{
	((CTreeItem*)pos)->ItemData = *pItemData;
}

template<class _ITEMDATA>
inline CompareFunc CRGTreeT<_ITEMDATA>::SetCompareFunc( CompareFunc func)
{
	swap_classes( func, m_pCompareFunc);
	return func;
}

template<class _ITEMDATA>
inline DeleteFunc CRGTreeT<_ITEMDATA>::SetDeleteFunc( DeleteFunc func, LPARAM lParam)
{
	swap_classes( func, m_pDeleteFunc);
	m_lParamDeleteFunc = lParam;
	return func;
}

template<class _ITEMDATA>
BOOL CRGTreeT<_ITEMDATA>::SortChildren( POSITION posParent, BOOL bAscending)
{
	if( !m_pCompareFunc)
		return FALSE;
	CTreeItem *pParent = posParent ? (CTreeItem*)posParent : &m_ItemRoot;
	if( !pParent->nChildCount)
		return FALSE;

	CTreeItem **pItemArray = (CTreeItem**)malloc( pParent->nChildCount*sizeof(CTreeItem*));
	register CTreeItem **pArItem = pItemArray;
	for( CTreeItem *pItem=pParent->pTIChildFirst; pItem; pItem=pItem->pTINext)
		*pArItem++ = pItem;

	CTreeItem **pEnde = pItemArray+pParent->nChildCount-1;
	pArItem = pItemArray;
	if( bAscending)
		QSortA( pArItem, pEnde);
	else
		QSortD( pArItem, pEnde);

	CTreeItem *pTIPrev = NULL;
	pParent->pTIChildFirst = *pArItem;
	for( ; pArItem != pEnde; )
	{
		(*pArItem)->pTIPrev = pTIPrev;
		pTIPrev->pTINext = (pTIPrev = *pArItem++, *pArItem);
	}
	(*pArItem)->pTIPrev = pTIPrev;
	(*pArItem)->pTINext = NULL;
	pParent->pTIChildLast = *pArItem;

	free( pItemArray);
	return TRUE;
}

template<class _ITEMDATA>
POSITION CRGTreeT<_ITEMDATA>::Find( const _ITEMDATA *pItemData, POSITION posParent)
{
	if( !m_pCompareFunc)
		return NULL;
	CTreeItem *pParent = posParent ? (CTreeItem*)posParent : &m_ItemRoot;
	for( CTreeItem *pItem=pParent->pTIChildFirst; pItem; pItem=pItem->pTINext)
		if( !(*m_pCompareFunc)( (LPARAM)pItemData, (LPARAM)&pItem->ItemData))
			return (POSITION)pItem;
	return NULL;
}


// protected functions

template<class _ITEMDATA>
void CRGTreeT<_ITEMDATA>::RemoveChilds( POSITION pos)
{
	if( m_pDeleteFunc)
		for( POSITION posNext; pos; pos=posNext)
		{
			RemoveChilds( GetChildPosition( pos));
			posNext = GetNextPosition( pos);
			DEC_ITEMS( ((CTreeItem*)pos)->pTIParent)
			(*m_pDeleteFunc)( pos, m_lParamDeleteFunc);
			delete (CTreeItem*)pos;
		}
	else
		for( POSITION posNext; pos; pos=posNext)
		{
			RemoveChilds( GetChildPosition( pos));
			posNext = GetNextPosition( pos);
			DEC_ITEMS( ((CTreeItem*)pos)->pTIParent)
			delete (CTreeItem*)pos;
		}
}

template<class _ITEMDATA>
void CRGTreeT<_ITEMDATA>::QSortA( CTreeItem **pLow, CTreeItem **pHigh)
{
	if( pLow >= pHigh)
		return;
	const LPARAM lMedian = (LPARAM)&(*(pLow+(pHigh-pLow+1)/2))->ItemData;
	CTreeItem **p1 = pLow, **p2 = pHigh;
	do
	{
		for( ; (*m_pCompareFunc)( (LPARAM)&(*p1)->ItemData, lMedian) < 0; p1++);
		for( ; (*m_pCompareFunc)( lMedian, (LPARAM)&(*p2)->ItemData) < 0; p2--);
		if( p1 <= p2)
			swap_classes( *p1++, *p2--);
	}
	while( p1 < p2);
	QSortA( pLow, p2);
	QSortA( p1, pHigh);
}

template<class _ITEMDATA>
void CRGTreeT<_ITEMDATA>::QSortD( CTreeItem **pLow, CTreeItem **pHigh)
{
	if( pLow >= pHigh)
		return;
	const LPARAM lMedian = (LPARAM)&(*(pLow+(pHigh-pLow+1)/2))->ItemData;
	CTreeItem **p1 = pLow, **p2 = pHigh;
	do
	{
		for( ; (*m_pCompareFunc)( (LPARAM)&(*p1)->ItemData, lMedian) > 0; p1++);
		for( ; (*m_pCompareFunc)( lMedian, (LPARAM)&(*p2)->ItemData) > 0;	p2--);
		if( p1 <= p2)
			swap_classes( *p1++, *p2--);
	}
	while( p1 < p2);
	QSortD( pLow, p2);
	QSortD( p1, pHigh);
}

#endif //RGTREET_H
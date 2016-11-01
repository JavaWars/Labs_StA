#include "range_list.hpp"
#include "Range.h"
#include <cassert>

void RangeListInit ( RangeList & _list )
{
    _list.m_pFirst = _list.m_pLast = nullptr;
}


void RangeListDestroy ( RangeList & _list )
{
	RangeListClear( _list );
}


void RangeListClear ( RangeList & _list )
{
    RangeList::Node * pCurrent = _list.m_pFirst;
    while ( pCurrent )
    {
        RangeList::Node * pTemp = pCurrent->m_pNext;
        delete pCurrent;
        pCurrent = pTemp;
    }

    _list.m_pFirst = _list.m_pLast = nullptr;
}


bool RangeListIsEmpty ( const RangeList & _list )
{
    return _list.m_pFirst == nullptr;
}


int RangeListSize ( const RangeList & _list )
{
    int nElements = 0;
    const RangeList::Node * pNode = _list.m_pFirst;
    while ( pNode )
    {
        ++ nElements;
        pNode = pNode->m_pNext;
    }

    return nElements;
}


void RangeListPushBack ( RangeList & _list, const range & _data)
{
    RangeList::Node * pNewNode = new RangeList::Node;
    pNewNode->m_range = _data;
    pNewNode->m_pNext = nullptr;

    if ( ! _list.m_pFirst )
    {
        assert( ! _list.m_pLast );
        _list.m_pFirst = pNewNode;
    }
    else
        _list.m_pLast->m_pNext = pNewNode;

    _list.m_pLast = pNewNode;
}


void RangeListPushFront ( RangeList & _list, const range & _data)
{
    RangeList::Node * pNewNode = new RangeList::Node;
    pNewNode->m_range= _data;
    pNewNode->m_pNext = _list.m_pFirst;

    _list.m_pFirst = pNewNode;
    
    if ( ! _list.m_pLast )
        _list.m_pLast = pNewNode;
}


void RangeListInsertAfter ( RangeList & _list, RangeList::Node * _pPrevNode, const range & _data)
{
    assert( !RangeListIsEmpty( _list ) );

    if ( _pPrevNode == _list.m_pLast )
		RangeListPushBack( _list, _data );

    else
    {
        RangeList::Node * pNewNode = new RangeList::Node;
        pNewNode->m_range = _data;

        pNewNode->m_pNext = _pPrevNode->m_pNext;

        _pPrevNode->m_pNext = pNewNode;
    }
}


void RangeListInsertBefore ( RangeList & _list, RangeList::Node * _pNextNode, const range & _data)
{
    assert( !RangeListIsEmpty( _list ) );

    if ( _pNextNode == _list.m_pFirst )
		RangeListPushFront( _list, _data );

    else
    {
        RangeList::Node * pCurrent = _list.m_pFirst;
        while ( pCurrent && pCurrent->m_pNext != _pNextNode )
            pCurrent = pCurrent->m_pNext;

        assert( pCurrent );

        RangeList::Node * pNewNode = new RangeList::Node;
        pNewNode->m_range = _data;

        pNewNode->m_pNext = _pNextNode;
        
        pCurrent->m_pNext = pNewNode;

    }
}


void RangeListPopFront ( RangeList & _list )
{
    assert( !RangeListIsEmpty( _list ) );

    RangeList::Node * pFirst = _list.m_pFirst;

    if ( _list.m_pFirst == _list.m_pLast )
        _list.m_pFirst = _list.m_pLast = nullptr;

    else
        _list.m_pFirst = pFirst->m_pNext;

    delete pFirst;    
}


void RangeListPopBack ( RangeList & _list )
{
    assert( !RangeListIsEmpty( _list ) );

    RangeList::Node * pLast = _list.m_pLast;

    if ( _list.m_pFirst == _list.m_pLast )
        _list.m_pFirst = _list.m_pLast = nullptr;

    else
    {
        RangeList::Node * pCurrent = _list.m_pFirst;
        while ( pCurrent->m_pNext != _list.m_pLast )
            pCurrent = pCurrent->m_pNext;

        _list.m_pLast = pCurrent;
        pCurrent->m_pNext = nullptr;
    }

    delete pLast;
}


void RangeListDeleteAfter ( RangeList & _list, RangeList::Node * _pPrevNode )
{
    assert( !RangeListIsEmpty( _list ) );

    assert( _list.m_pLast != _pPrevNode );

    RangeList::Node * pDyingNode = _pPrevNode->m_pNext;
    _pPrevNode->m_pNext = pDyingNode->m_pNext;

    if ( _list.m_pLast == pDyingNode )
        _list.m_pLast = _pPrevNode;
        
    delete pDyingNode;
}


void RangeListDeleteBefore ( RangeList & _list, RangeList::Node * _pNextNode )
{
    assert( !RangeListIsEmpty( _list ) );

    assert( _list.m_pFirst != _pNextNode );

    RangeList::Node * pPrevNode = _list.m_pFirst, * pCurrentNode = _list.m_pFirst->m_pNext;
    if ( pCurrentNode == _pNextNode )
    {
        delete _list.m_pFirst;
        _list.m_pFirst = _pNextNode;
    }

    else
    {
        while ( pCurrentNode->m_pNext != _pNextNode )
        {
            pPrevNode = pCurrentNode;
            pCurrentNode = pCurrentNode->m_pNext;
        }

        pPrevNode->m_pNext = _pNextNode;
        delete pCurrentNode;
    }
}


void RangeListDeleteNode ( RangeList & _list, RangeList::Node * _pNode )
{
    if ( _list.m_pFirst == _pNode )
		RangeListPopFront( _list );

    else if ( _list.m_pLast == _pNode )
		RangeListPopBack( _list );

    else
		RangeListDeleteBefore( _list, _pNode->m_pNext );
}


void RangeListPrint ( const RangeList & _list, std::ostream & _stream, char _sep )
{
    const RangeList::Node * pCurrent = _list.m_pFirst;
	_stream << "{ ";
    while ( pCurrent )
    {
		if (pCurrent->m_pNext)
			printRange(pCurrent->m_range, _stream, _sep);
		else
		{
			printRange(pCurrent->m_range, _stream, ' ');
		}
        pCurrent = pCurrent->m_pNext;
    }
	_stream << "}\n";
}

range * RangeListGetLast(const RangeList & _list)
{
	return &_list.m_pLast->m_range;
}

range * RangeListGetFirst(const RangeList & _list)
{
	return &_list.m_pFirst->m_range;
}

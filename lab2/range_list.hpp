#ifndef _INTEGER_LIST_HPP_
#define _INTEGER_LIST_HPP_

#include <iostream>
#include "Range.h"

struct RangeList
{
    struct Node
    {
        range m_range;
        Node * m_pNext;
    };

    Node * m_pFirst, * m_pLast;
};

void RangeListInit (RangeList & _list );

void RangeListDestroy (RangeList & _list );

bool RangeListIsEmpty ( const RangeList & _list );

int RangeListSize ( const RangeList & _list );

void RangeListClear (RangeList & _list );

void RangeListPushBack (RangeList & _list, const range & _data );

void RangeListPushFront (RangeList & _list, const range & _data);

void RangeListInsertAfter (RangeList & _list, RangeList::Node * _pPrevNode, const range & _data);

void RangeListInsertBefore (RangeList & _list, RangeList::Node * _pNextNode, const range & _data);

void RangeListPopBack (RangeList & _list );

void RangeListPopFront (RangeList & _list );

void RangeListDeleteAfter (RangeList & _list, RangeList::Node * _pPrevNode );

void RangeListDeleteBefore (RangeList & _list, RangeList::Node * _pNextNode );

void RangeListDeleteNode ( RangeList & _list, RangeList::Node * _pNode );

void RangeListPrint ( const RangeList & _list, std::ostream & _o, char _sep = ' ' );

range * RangeListGetLast(const RangeList & _list);

range * RangeListGetFirst(const RangeList & _list);

#endif //  _INTEGER_FORWARD_LIST_HPP_
#include "set.hpp"
#include "range_list.hpp"

#include <cassert>


struct Set
{
	RangeList m_data;
};


Set * SetCreate()
{
	Set * pSet = new Set;
	RangeListInit(pSet->m_data);
	return pSet;
}


void SetDestroy(Set * _pSet)
{
	RangeListDestroy(_pSet->m_data);
	delete _pSet;
}


void SetClear(Set & _set)
{
	RangeListClear(_set.m_data);
}


bool SetIsEmpty(const Set & _set)
{
	return RangeListIsEmpty(_set.m_data);
}


int SetSize(const Set & _set)
{
	return RangeListSize(_set.m_data);
}


bool SetHasKey(const Set & _set, int _key)
{
	RangeList::Node * pNode = _set.m_data.m_pFirst;
	while (pNode)
	{
		if (isInRange(pNode->m_range, _key))
			return true;
		else if (isValSmallerThanRange(pNode->m_range, _key))
			return false;
		pNode = pNode->m_pNext;
	}
	return false;
}

void UniteIfNeed(Set &_set, RangeList::Node & _node, RangeList::Node * _prevNode = NULL)
{
	if (_prevNode)
	{//has prev

		if (isPosibleAddValueToRange(_prevNode->m_range, *_node.m_range.m_pFirst)) {

			if (isSecondValueInRange(_node.m_range))
			{
				range * newElement = UniteRange(_prevNode->m_range, _node.m_range);
				RangeListInsertAfter(_set.m_data, _prevNode, *newElement);
				RangeListDeleteNode(_set.m_data, &_node);
				RangeListDeleteNode(_set.m_data, _prevNode);
			}
			else
			{
				addValueToRange(_prevNode->m_range, *_node.m_range.m_pFirst);
				RangeListDeleteNode(_set.m_data, &_node);
			}
		}
	}

	if (_node.m_pNext)
		//has next
		if ((isPosibleAddValueToRange(_node.m_range, *_node.m_pNext->m_range.m_pFirst)))
		{
			if (isSecondValueInRange(_node.m_pNext->m_range))
			{
				range * newElement = UniteRange(_node.m_range, _node.m_pNext->m_range);
				RangeListDeleteNode(_set.m_data, _node.m_pNext);
				RangeListInsertAfter(_set.m_data, &_node, *newElement);
				RangeListDeleteNode(_set.m_data, &_node);
			}
			else
			{
				addValueToRange(_node.m_range, *_node.m_pNext->m_range.m_pFirst);
				RangeListDeleteNode(_set.m_data, _node.m_pNext);
			}
		}
}

void SetInsertKey(Set & _set, int _key)
{
	if (RangeListIsEmpty(_set.m_data))
	{
		RangeListPushBack(_set.m_data, *createRange(_key));
	}

	else
	{
		RangeList::Node * pNode = _set.m_data.m_pFirst;
		if (isValSmallerThanRange(pNode->m_range, _key))
		{
			//вставить перед или расширить(нормализация)
			if (isPosibleAddValueToRange(pNode->m_range, _key))
			{
				addValueToRange(pNode->m_range, _key);
				UniteIfNeed(_set, *pNode, NULL);
			}
			else
			{
				RangeListPushFront(_set.m_data, *createRange(_key));
			}
		}

		else
		{
			RangeList::Node * pPrevNode = nullptr;
			while (pNode)
			{
				if (isInRange(pNode->m_range, _key))
					return;

				else if (!pNode->m_pNext)
				{
					if (isPosibleAddValueToRange(pNode->m_range, _key))
					{
						addValueToRange(pNode->m_range, _key);
						UniteIfNeed(_set, *pNode, pPrevNode);//
					}
					else {
						RangeListPushBack(_set.m_data, *createRange(_key));
					}
					return;
				}

				else if (isValSmallerThanRange(pNode->m_pNext->m_range, _key))
				{
					//вставить после или расширить(нормализация)
					if (isPosibleAddValueToRange(pNode->m_range, _key))
					{
						addValueToRange(pNode->m_range, _key);
						UniteIfNeed(_set, *pNode, pPrevNode);//
					}
					else
					{
						RangeListInsertAfter(_set.m_data, pNode, *createRange(_key));
						UniteIfNeed(_set, *pNode->m_pNext);
					}

					return;
				}

				else
				{
					pPrevNode = pNode;
					pNode = pNode->m_pNext;
				}
			}

			assert(!"We should never get here");
		}
	}
}


void SetDeleteKey(Set & _set, int _key)
{
	RangeList::Node * pNode = _set.m_data.m_pFirst;
	while (pNode)
	{
		if (isInRange(pNode->m_range, _key))
		{
			if (needSeparation(pNode->m_range, _key))
			{//separate 1 range for 2
				range * newRange1 = createEmptyRange(), *newRange2 = createEmptyRange();
				separateRangeByValue(pNode->m_range, *newRange1, *newRange2, _key);
				RangeListInsertAfter(_set.m_data, pNode, *newRange2);
				RangeListInsertAfter(_set.m_data, pNode, *newRange1);
				RangeListDeleteNode(_set.m_data, pNode);
			}
			else
			{
				delFromRange(pNode->m_range, _key);//modify node 
				if (isEmpty(pNode->m_range)) RangeListDeleteNode(_set.m_data, pNode);
			}
			return;
		}
		else if (isValSmallerThanRange(pNode->m_range, _key))
			break;

		pNode = pNode->m_pNext;
	}
}

void SetPrint(const Set & _set)
{
	RangeListPrint(_set.m_data, std::cout, ',');
}

void InsertRangeToSet(Set & _set, range & _range)
{
	if (!SetIsEmpty(_set))
	{
		range *lastValInSet = RangeListGetLast(_set.m_data);
		if (isInRange(*lastValInSet, *_range.m_pFirst) || (isInRange(_range, *lastValInSet->m_pFirst)) ||
			(isPosibleAddValueToRange(_range, *lastValInSet->m_pFirst)) || (isPosibleAddValueToRange(*lastValInSet, *_range.m_pFirst)))
		{
			range *result = UniteRange(*lastValInSet, _range);
			RangeListPopBack(_set.m_data);
			RangeListPushBack(_set.m_data, *result);
		}
		else
		{
			RangeListPushBack(_set.m_data, _range);
		}
	}
	else
	{
		RangeListPushBack(_set.m_data, _range);
	}
}

void SetUnite(const Set & _set1,
	const Set & _set2,
	Set & _targetSet)
{
	SetClear(_targetSet);

	RangeList::Node * pNode1 = _set1.m_data.m_pFirst;
	RangeList::Node * pNode2 = _set2.m_data.m_pFirst;
	while (pNode1 || pNode2)
	{
		if (pNode1 && pNode2)
		{
			//check new with existing
			if ((!isInRange(pNode1->m_range, *pNode2->m_range.m_pFirst)) && (!isInRange(pNode2->m_range, *pNode1->m_range.m_pFirst)) &&
				(*pNode1->m_range.m_pFirst > *pNode2->m_range.m_pFirst + 1))
			{
				InsertRangeToSet(_targetSet, pNode2->m_range);
				pNode2 = pNode2->m_pNext;
			}
			else if ((!isInRange(pNode1->m_range, *pNode2->m_range.m_pFirst)) && (!isInRange(pNode2->m_range, *pNode1->m_range.m_pFirst)) &&
				(*pNode1->m_range.m_pFirst < *pNode2->m_range.m_pFirst - 1))
			{
				InsertRangeToSet(_targetSet, pNode1->m_range);
				pNode1 = pNode1->m_pNext;
			}
			else
			{
				InsertRangeToSet(_targetSet, *UniteRange(pNode1->m_range, pNode2->m_range));
				pNode1 = pNode1->m_pNext;
				pNode2 = pNode2->m_pNext;
			}
		}
		else if (pNode1)
		{
			InsertRangeToSet(_targetSet, pNode1->m_range);
			pNode1 = pNode1->m_pNext;
		}
		else
		{
			InsertRangeToSet(_targetSet, pNode2->m_range);
			pNode2 = pNode2->m_pNext;
		}
	}
}

void moveNodes(RangeList::Node ** pNode1, RangeList::Node ** pNode2)
{
	bool move = false;
	if ((*pNode1)->m_pNext)
	{
		int  maxNode2 = getBiggerFromRange((*pNode2)->m_range);
		if (*(*(*pNode1)->m_pNext).m_range.m_pFirst > maxNode2)
		{
			(*pNode2) = (*pNode2)->m_pNext;
			move = true;
		}
	}
	else
	{
		if ((*pNode2))
			(*pNode2) = (*pNode2)->m_pNext;
		move = true;
	}

	if ((*pNode2))
	{
		int maxNode1 = getBiggerFromRange((*pNode1)->m_range), minNode2 = *(*pNode2)->m_range.m_pFirst;
		if (maxNode1 < minNode2)
		{
			(*pNode1) = (*pNode1)->m_pNext;
		}
		else
		{
			if (!move)
			{
				*(pNode1) = (*pNode1)->m_pNext;
			}
		}
	}
	else
	{
		*(pNode1) = (*pNode1)->m_pNext;
	}
}

void SetIntersect(const Set & _set1,
	const Set & _set2,
	Set & _targetSet)
{
	SetClear(_targetSet);

	RangeList::Node * pNode1 = _set1.m_data.m_pFirst;
	RangeList::Node * pNode2 = _set2.m_data.m_pFirst;
	while (pNode1 && pNode2)
	{
		if ((isInRange(pNode1->m_range, *pNode2->m_range.m_pFirst)) ||
			(isInRange(pNode2->m_range, *pNode1->m_range.m_pFirst))||
			((pNode2->m_range.m_pSecond) && (isInRange(pNode1->m_range, *pNode2->m_range.m_pSecond))))
		{
			InsertRangeToSet(_targetSet, *IntersectRanges(pNode1->m_range, pNode2->m_range));
		}
		moveNodes(&pNode1,&pNode2);
	}
}

void SetDifference(const Set & _set1,
	const Set & _set2,
	Set & _targetSet)
{
	SetClear(_targetSet);

	RangeList::Node * pNode1 = _set1.m_data.m_pFirst;
	RangeList::Node * pNode2 = _set2.m_data.m_pFirst;
	while (pNode1)
	{
		if (pNode2)
		{
			if (isEqual(pNode1->m_range, pNode2->m_range))
			{
				pNode1 = pNode1->m_pNext;
				pNode2 = pNode2->m_pNext;
			}
			else
			{
				if (isInRange(pNode1->m_range, *(pNode2->m_range.m_pFirst)) ||
					(isInRange(pNode2->m_range, *pNode1->m_range.m_pFirst) ||
					((pNode2->m_range.m_pSecond) && (isInRange(pNode1->m_range, *pNode2->m_range.m_pSecond)))))
				{
					range *r1=&pNode1->m_range, *r2=&pNode2->m_range;
					while (!isEmpty(*r2))
					{
						range *result1 = createEmptyRange(), *result2 = createEmptyRange();
						subRanges(*r1, *r2, *result1, *result2);

						if (!isEmpty(*result1))
						{
							InsertRangeToSet(_targetSet, *result1);
						}
						if (!isEmpty(*result2)) {
							r1 = result2;
							pNode2 = pNode2->m_pNext;
							r2 = &pNode2->m_range;
							if (!pNode2)
							{
								InsertRangeToSet(_targetSet,*result2);
							}
							else
							{
								if (getBiggerFromRange(*result2) < *(pNode2->m_range).m_pFirst)
								{
									InsertRangeToSet(_targetSet, *result2);
								}
							}
						}
						else
						{
							r2 = createEmptyRange();
						}
					}
				}
				else
				{
					if (getBiggerFromRange(pNode1->m_range) <*(pNode2->m_range).m_pFirst)
						InsertRangeToSet(_targetSet, pNode1->m_range);
				}
				moveNodes(&pNode1,&pNode2);
			}
		}
		else
		{
				InsertRangeToSet(_targetSet, pNode1->m_range);
				pNode1 = pNode1->m_pNext;
		}
	}
}
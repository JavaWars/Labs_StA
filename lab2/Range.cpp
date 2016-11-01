#include "Range.h"
#include <cassert>
#include <iostream>
using namespace std;
range * createEmptyRange()
{
	range * result = new range;

	result->m_pFirst = NULL;
	result->m_pSecond = NULL;

	return result;
}

range * createRange(int _val)
{
	range * result = createEmptyRange();
	addValueToRange(*result, _val);
	return result;
}

void makeNormal(range * _range)
{
	if (_range->m_pSecond)
		if (*_range->m_pFirst == *_range->m_pSecond) {
			delete _range->m_pSecond;
			_range->m_pSecond = NULL;
		}
}

void giveMemory(range * _range)
{
	_range->m_pFirst = new int;
	_range->m_pSecond = new int;
}
range * UniteRange(const range & _r1,const range & _r2)
{
	range * result = createEmptyRange();
	result->m_pFirst = new int;
	if (*_r1.m_pFirst <= *_r2.m_pFirst)
	{
		*result->m_pFirst=(*_r1.m_pFirst);
		addValueToRange(*result,*_r2.m_pFirst);//
	}
	else
	{
		*result->m_pFirst = (*_r2.m_pFirst);
		addValueToRange(*result, *_r1.m_pFirst);
	}

	if (_r1.m_pSecond && _r2.m_pSecond)
	{
		result->m_pSecond = new int;
		if (*_r1.m_pSecond < *_r2.m_pSecond)
		{
			*result->m_pSecond = *_r2.m_pSecond;
		}
		else
		{
			*result->m_pSecond = *_r1.m_pSecond;
		}
	}
	else
	{
		if (!_r1.m_pSecond && _r2.m_pSecond)
		{
			result->m_pSecond = new int;
			*result->m_pSecond = (*_r2.m_pSecond>*_r1.m_pFirst)? *_r2.m_pSecond : *_r1.m_pFirst;
		}
		if (!_r2.m_pSecond && _r1.m_pSecond)
		{
			result->m_pSecond = new int;
			*result->m_pSecond = (*_r1.m_pSecond>*_r2.m_pFirst)? *_r1.m_pSecond : *_r2.m_pFirst;
		}
	}

	return result;
}

range * IntersectRanges(const range & _range, const range & _range2)
{
	range * result = createEmptyRange();
	giveMemory(result);

	int deltaRange1=0, deltaRange2=0;
	if (_range.m_pSecond)
	{
		deltaRange1 = *_range.m_pSecond - *_range.m_pFirst;
	}
	if (_range2.m_pSecond)
	{
		deltaRange2 = *_range2.m_pSecond - *_range2.m_pFirst;
	}

	if (deltaRange1 == 0)
	{
		*result->m_pFirst = *_range.m_pFirst;
		result->m_pSecond = NULL;
		return result;
	}
	if (deltaRange2 == 0)
	{
		*result->m_pFirst = *_range2.m_pFirst;
		result->m_pSecond = NULL;
		return result;
	}
		
	*result->m_pFirst = (*_range.m_pFirst > *_range2.m_pFirst) ? *_range.m_pFirst : *_range2.m_pFirst;
	*result->m_pSecond = (*_range.m_pSecond<*_range2.m_pSecond)? *_range.m_pSecond : *_range2.m_pSecond;

	makeNormal(result);
	return result;
}

void deleteRange(range * _range)
{
	delete _range->m_pFirst;
	delete _range->m_pSecond;
	delete _range;
}

bool isEmpty(const range & _range)
{
	if (&_range == NULL) return true;
	if ((!_range.m_pFirst) && (!_range.m_pSecond)) return true;
	return false;
}

bool isEqual(const range & _range1, const range & _range2)
{
	if ((*_range1.m_pFirst == *_range2.m_pFirst))
	{
		if ((_range1.m_pSecond == NULL) && (_range2.m_pSecond == NULL))return true;


		if ((_range1.m_pSecond) && (_range2.m_pSecond))
		{
			if (*_range1.m_pSecond == *_range2.m_pSecond) return true;
		}
	}
	return false;
}

void addValueToRange(range & _range, int _val)
{
	
	if (isInRange(_range, _val)) return;

	if (!_range.m_pFirst)//not null
	{//add to empty
		_range.m_pFirst = new int;
		*_range.m_pFirst = _val;
		return;
	}
	else
	{

		if (!_range.m_pSecond)
		{
			_range.m_pSecond = new int;
			if (*_range.m_pFirst == (_val + 1))
			{//>>
				*_range.m_pSecond = *_range.m_pFirst;
				--*_range.m_pFirst;
			}
			else
			{//new second
				*_range.m_pSecond = _val;
			}
		}
		else
		{//-- or ++
			if ((_val + 1) == *_range.m_pFirst)--*_range.m_pFirst;
			if (*_range.m_pSecond == (_val - 1))++*_range.m_pSecond;
		}

	}
}

bool isInRange(const range & _range, int _val)
{
	if (_val == NULL) return false;
	if (&_range == NULL) return false;
	if (_range.m_pFirst)
	{
		if (*_range.m_pFirst == _val) return true;
	}

	if (_range.m_pSecond)
	{
		if ((*_range.m_pSecond == _val)) return true;
	}

	if ((_range.m_pFirst != NULL && _range.m_pSecond != NULL))
	{
		if ((*_range.m_pFirst <= _val) && (_val <= *_range.m_pSecond)) return true;
	}

	return false;
}

void delFromRange(range & _range, int _val)
{
	if (_range.m_pSecond && _range.m_pFirst)
	{
		if (*_range.m_pSecond == _val)--*(_range.m_pSecond);

		if (_range.m_pFirst)
			if (*_range.m_pFirst == _val)++*(_range.m_pFirst);
		
		makeNormal(&_range);
	}
	else
	{
		if (_range.m_pFirst) {
			delete _range.m_pFirst;
			_range.m_pFirst = NULL;
		}
		if (_range.m_pSecond)
		{
			delete _range.m_pSecond;
			_range.m_pSecond = NULL;
		}
	}
}

void separateRangeByValue(const range & _range, range & _resultSmaller, range & _resultBigger, int _val)
{
	if (isInRange(_range, _val))
	{
		if (needSeparation)
		{
			_resultSmaller.m_pFirst = new int;
			_resultSmaller.m_pSecond = new int;

			*_resultSmaller.m_pFirst = *_range.m_pFirst;
			*_resultSmaller.m_pSecond = _val - 1;
			makeNormal(&_resultSmaller);

			_resultBigger.m_pFirst = new int;
			_resultBigger.m_pSecond = new int;

			*_resultBigger.m_pFirst = _val + 1;
			*_resultBigger.m_pSecond = *_range.m_pSecond;
			makeNormal(&_resultBigger);
		}
		else assert(!"you can use this function for delete first or last val");
	}
}

void subRanges(const range & _rangeMain, const range & _rangeSub, range & _resultSmaller, range & _resultBigger)
{
	if (_rangeMain.m_pSecond)
	{
		if (*_rangeMain.m_pFirst < *_rangeSub.m_pFirst)
		{
			_resultSmaller = *createEmptyRange();
			giveMemory(&_resultSmaller);
			*_resultSmaller.m_pFirst = *_rangeMain.m_pFirst;
			*_resultSmaller.m_pSecond = *_rangeSub.m_pFirst-1;
			makeNormal(&_resultSmaller);
		}

		int min;
		if (_rangeSub.m_pSecond)
		{
			min = *_rangeSub.m_pSecond + 1;
		}
		else
		{
			min = *_rangeSub.m_pFirst + 1;
		}
			if (min <= *_rangeMain.m_pSecond)
			{
				_resultBigger = *createEmptyRange();
				giveMemory(&_resultBigger);
				*_resultBigger.m_pFirst = min;
				*_resultBigger.m_pSecond = *_rangeMain.m_pSecond;
				makeNormal(&_resultBigger);
			}
	}
	else
	{
		if (*_rangeMain.m_pFirst == *_rangeSub.m_pFirst) return;
	}
}

bool needSeparation(const range & _range, int _val)
{
	//assert((_range.m_pFirst != NULL) || (_range.m_pSecond != NULL));
	if ((!_range.m_pFirst) || (!_range.m_pSecond)) return false;
	if ((_val > *_range.m_pFirst) && (_val < *_range.m_pSecond)) return true;//if val == first or second, we need modify this range
	return false;
}

bool isSecondValueInRange(const range & _range)
{
	if (_range.m_pSecond) return true;
	return false;
}

bool isPosibleAddValueToRange(const range & _range, int _val)
{
	if (_range.m_pFirst)
	{
		if (*_range.m_pFirst == (_val + 1)) return true;
	}

	if (_range.m_pSecond)
	{
		if (*_range.m_pSecond == (_val - 1)) return true;
	}

	if ((_range.m_pSecond == NULL) && ((*_range.m_pFirst + 1) == _val))return true;
	return false;
}

bool isValSmallerThanRange(const range & _range, int _val)
{
	if (_val < *_range.m_pFirst) return true;
	return false;
}

int getBiggerFromRange(const range & _range)
{
	if (_range.m_pSecond) return *_range.m_pSecond;
	
	return *_range.m_pFirst;
}

void printRange(const range & _range, std::ostream & _o, char _sep)
{
	if (_range.m_pFirst != NULL) _o << (*_range.m_pFirst);
	if (_range.m_pSecond != NULL) _o << "-" << *(_range.m_pSecond);
	_o << _sep;
}
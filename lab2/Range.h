#ifndef _RANGE_
#define _RANGE_

#include <iostream>

struct range
{
	int *m_pFirst;
	int *m_pSecond;
};

range * createEmptyRange();

range * createRange(int _val);

void deleteRange(range * _range);

range * UniteRange(const range & _r1, const  range & _r2);

range *IntersectRanges(const range & _range, const range & _range2);

void subRanges(const range & _rangeMain, const range & _rangeSub, range & _resultSmaller, range & _resultBigger);

void addValueToRange(range & _range, int _val);

bool isEmpty(const range & _range);

bool isEqual(const range & _range1, const range & _range2);

bool isInRange(const range & _range, int _val);

void delFromRange(range & _range, int _val);

void separateRangeByValue(const range & _range, range & _resultSmaller, range & _resultBigger,int _val);

bool needSeparation(const range & _range,int _val);

bool isSecondValueInRange(const range & _range);

bool isPosibleAddValueToRange(const range & _range, int _val);

void printRange(const range & _range, std::ostream & _o, char _sep = ' ');

bool isValSmallerThanRange(const range & _range, int _val);

int getBiggerFromRange(const range & _range);
#endif  !_RANGE_


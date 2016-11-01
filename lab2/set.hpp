#ifndef _INTEGER_SET_HPP_
#define _INTEGER_SET_HPP_

#include "Range.h"

struct Set;

Set * SetCreate ();

void SetDestroy ( Set * _pSet );

void SetClear ( Set & _set );

bool SetIsEmpty ( const Set & _set );

bool SetHasKey ( const Set & _set, int _key );

void SetInsertKey ( Set & _set, int _key );

void SetDeleteKey ( Set & _set, int _key );

void SetPrint(const Set & _set);

void SetUnite ( const Set & _set1,
                       const Set & _set2,
                       Set & _targetSet );

void SetIntersect ( const Set & _set1,
                           const Set & _set2,
                           Set & _targetSet );

void SetDifference ( const Set & _set1,
                            const Set & _set2,
                            Set & _targetSet );
 

#endif //  _INTEGER_SET_HPP_

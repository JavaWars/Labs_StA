#ifndef _template_queue_solution_
#define _template_queue_solution_
#include <cassert>
#include "template_queue.h"
#include <iostream>
template<typename T>
TemplateQueue<T> * TemplateQueueCreate(int _fixedSize)
{
	assert(_fixedSize > 0);

	TemplateQueue<T> * pNewQueue = new TemplateQueue<T>;

	pNewQueue->m_Size = _fixedSize + 1;
	pNewQueue->m_pData = new T[pNewQueue->m_Size];
	TemplateQueueClear<T>(*pNewQueue);

	return pNewQueue;
}

template<typename T>
void TemplateQueueDestroy(TemplateQueue<T> * _pQueue)
{
	delete[] _pQueue->m_pData;
	delete _pQueue;
}

template<typename T>
void TemplateQueueClear(TemplateQueue<T> & _queue)
{
	_queue.m_FrontIndex = 0;
	_queue.m_BackIndex = 0;
}

template<typename T>
int TemplateQueueSize(const TemplateQueue<T> & _queue)
{
	// |-|-|-|-|-|-|        |-|-|-|-|-|-|  
	//   F     B                B     F

	return (_queue.m_FrontIndex <= _queue.m_BackIndex) ?
		_queue.m_BackIndex - _queue.m_FrontIndex :
		_queue.m_BackIndex + _queue.m_Size - _queue.m_FrontIndex;

}

template<typename T>
bool TemplateQueueIsEmpty(const TemplateQueue<T> & _queue)
{
	return TemplateQueueSize(_queue) == 0;
}

template<typename T>
bool TemplateQueueIsFull(const TemplateQueue<T> & _queue)
{
	return TemplateQueueSize(_queue) == (_queue.m_Size - 1);
}

template<typename T>
int TemplateQueueNextIndex(const TemplateQueue<T> & _queue, int _index)
{
	int index = _index + 1;
	if (index == _queue.m_Size)
		index = 0;
	return index;
}

template<typename T>
void TemplateQueuePush(TemplateQueue<T> & _queue, T _value)
{
	assert(!TemplateQueueIsFull(_queue));

	_queue.m_pData[_queue.m_BackIndex] = _value;
	_queue.m_BackIndex = TemplateQueueNextIndex(_queue, _queue.m_BackIndex);
}

template<typename T>
void TemplateQueuePush(TemplateQueue<T> & _queue, TemplateQueue<T> & _queue2)
{

	while (!TemplateQueueIsEmpty(_queue2))
	{
		assert(!TemplateQueueIsFull(_queue));

		TemplateQueuePush(_queue, TemplateQueueFront(_queue2));
		TemplateQueuePop(_queue2);
	}
}

template<typename T>
void TemplateQueuePop(TemplateQueue<T> & _queue)
{
	assert(!TemplateQueueIsEmpty(_queue));
	_queue.m_FrontIndex = TemplateQueueNextIndex(_queue, _queue.m_FrontIndex);
}

template<typename T>
T TemplateQueueFront(const TemplateQueue<T> & _queue)
{
	assert(!TemplateQueueIsEmpty(_queue));
	return _queue.m_pData[_queue.m_FrontIndex];
}

template<typename T>
int TemplateQueueCountOfElements(const TemplateQueue<T> & _queue)
{
	if (_queue.m_FrontIndex < _queue.m_BackIndex)
	{
		return ((_queue.m_BackIndex - _queue.m_FrontIndex));
	}
	else
	{
		if (_queue.m_FrontIndex > _queue.m_BackIndex)
		{
			return (_queue.m_Size - (_queue.m_FrontIndex-_queue.m_BackIndex));
		}
	}
	return 0;
}
#endif //_template_queue_solution_

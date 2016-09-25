#ifndef _TEMPLATE_QUEUE_
#define _TEMPLATE_QUEUE_

template<typename T>
struct TemplateQueue
{
	T * m_pData;
	int m_Size;
	int m_FrontIndex;
	int m_BackIndex;
};


template<typename T>
TemplateQueue<T> * TemplateQueueCreate ( int _fixedSize );

template<typename T>
void TemplateQueueDestroy ( TemplateQueue<T> * _pQueue );

template<typename T>
void TemplateQueueClear ( TemplateQueue<T> & _queue );

template<typename T>
bool TemplateQueueIsEmpty ( const TemplateQueue<T> & _queue );

template<typename T>
bool TemplateQueueIsFull ( const TemplateQueue<T> & _queue );

template<typename T>
void TemplateQueuePush ( TemplateQueue<T> & _queue, T _value );

template<typename T>
void TemplateQueuePush(TemplateQueue<T> & _queue, TemplateQueue<T> & _queue2);

template<typename T>
void TemplateQueuePop ( TemplateQueue<T> & _queue );

template<typename T>
T TemplateQueueFront ( const TemplateQueue<T> & _queue );

template<typename T>
int TemplateQueueCountOfElements(const TemplateQueue<T> & _queue);
#include "template_queue_circular_array_impl.inl"

#endif // _TEMPLATE_QUEUE_
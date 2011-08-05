/*

Copyright (c) 2010, Anton Petersson < anton (at) anp.nu >
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _ANP_THREADSAFEQUEUE_H_
#define _ANP_THREADSAFEQUEUE_H_

#include <queue>

namespace anp
{
namespace threading
{
	template<typename T>
	struct InternalThreadSafeQueue;
	
	template<typename T>
	class ThreadSafeQueue
	{
	public:
		ThreadSafeQueue();
		virtual ~ThreadSafeQueue();
	
		void push(const T &element);
		T &front();
		void pop();
		unsigned int getSize() const;
		bool isEmpty() const;
	private:
		InternalThreadSafeQueue<T> *m_queue;
	};
	
	template<typename T>
	struct InternalThreadSafeQueue
	{
		std::queue<T> m_queue;
	};

	template<typename T>
	ThreadSafeQueue<T>::ThreadSafeQueue()
	{
		m_queue = new InternalThreadSafeQueue<T>;
	}
	
	template<typename T>
	ThreadSafeQueue<T>::~ThreadSafeQueue()
	{
		delete m_queue;
	}

	template<typename T>
	void ThreadSafeQueue<T>::push(const T &element)
	{
		m_queue->m_queue.push(element);
	}
	
	template<typename T>
	T &ThreadSafeQueue<T>::front()
	{
		return m_queue->m_queue.front();
	}

	template<typename T>
	void ThreadSafeQueue<T>::pop()
	{
		m_queue->m_queue.pop();
	}
	
	template<typename T>
	unsigned int ThreadSafeQueue<T>::getSize() const
	{
		return m_queue->m_queue.size();
	}
	
	template<typename T>
	bool ThreadSafeQueue<T>::isEmpty() const
	{
		return m_queue->m_queue.empty();
	}
}
}

#endif // _ANP_THREADSAFEQUEUE_H_

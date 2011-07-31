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

/**
 * @file anp_threading.cpp
 * Implementation of generic parts of the threading api.
 */

#include "anp_threading.h"
#include <basedefs.h>
#include <anp_exceptions.h>
#include <stdexcept>

namespace anp
{
namespace threading
{
	
	/**
	 * @brief
	 * Allocate memory and initialize a Thread object.
	 * 
	 * @param[out] thread
	 * The created Thread object.
	 * 
	 * @return
	 * RES_OK on success, an error code otherwise.
	 * 
	 * @remark
	 * Does @b NOT create a thread. Use createThread for that.
	 * 
	 * @sa
	 * destroyThreadObject
	 */
	Result createThreadObject(ThreadPlatformSpecific **thread);
	
	/**
	 * @brief
	 * Destroys the thread object.
	 * 
	 * @param[in] thread
	 * The thread object to destroy.
	 * 
	 * @sa
	 * createThreadObject
	 */
	void destroyThreadObject(ThreadPlatformSpecific *thread);
	
	Thread::Thread():
	m_thread(NULL)
	{
		if ( RES_OK != createThreadObject(&m_thread) )
		{
			throw anp::ConstructionException("Failed to create thread object");
		}
	}
	
	Thread::~Thread()
	{
		destroyThreadObject(m_thread);
	}
	
	/**
	 * @brief
	 * Allocate memory and initialize a Mutex object.
	 * 
	 * @param[out] mutex
	 * The created mutex object.
	 * 
	 * @return
	 * RES_OK on success, an error code otherwise.
	 * 
	 * @remark
	 * Does @b NOT create a thread. Use createThread for that.
	 * 
	 * @sa
	 * destroyMutexObject
	 */
	Result createMutexObject(MutexPlatformSpecific **mutex);
	
	/**
	 * @brief
	 * Destroys the Mutex object.
	 * 
	 * @param[in] mutex
	 * The mutex object to destroy.
	 * 
	 * @sa
	 * createMutexObject
	 */
	void destroyMutexObject(MutexPlatformSpecific *mutex);
	
	Mutex::Mutex():
	m_mutex(NULL)
	{
		if ( RES_OK != createMutexObject(&m_mutex) )
		{
			throw anp::ConstructionException("Failed to create mutex object");
		}
	}
	
	Mutex::~Mutex()
	{
		destroyMutexObject(m_mutex);
	}
	
	Lock::Lock(Mutex &mutex):
	m_mutex(mutex)
	{
		if ( m_mutex.lock() != RES_OK )
		{
			throw std::runtime_error("Failed to aquire/lock a mutex");
		}
	}
	
	Lock::~Lock()
	{
		m_mutex.unlock();
	}
	
	TryLock::TryLock(Mutex &mutex):
	m_mutex(mutex)
	{
		if ( !m_mutex.tryLock() )
		{
			throw std::runtime_error("Failed to aquire/lock a mutex");
		}
	}
	
	TryLock::~TryLock()
	{
		m_mutex.unlock();
	}	
	
	
	/**
	 * @brief
	 * Allocate memory for and initialize an Event object.
	 * 
	 * @param[out] event
	 * The created Event object.
	 * 
	 * @return
	 * RES_OK on success, an error code otherwise.
	 * 
	 * @sa
	 * destroyEventObject
	 */
	Result createEventObject(EventPlatformSpecific **event);
	
	/**
	 * @brief
	 * Destroys the Event object.
	 * 
	 * @param[in] event
	 * The event object to destroy.
	 * 
	 * @sa
	 * createEventObject
	 */
	void destroyEventObject(EventPlatformSpecific *event);

	Event::Event():
	m_event(NULL)
	{
		if ( RES_OK != createEventObject(&m_event) )
		{
			throw anp::ConstructionException("Failed to create event object");
		}
	}
	
	Event::~Event()
	{
		destroyEventObject(m_event);
	}
} // namespace threading
} // namespace anp

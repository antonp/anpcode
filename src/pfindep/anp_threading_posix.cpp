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
 * @file anp_threading_posix.cpp
 * Posix implementation of the anp threading API.
 */


#include <anpcode/anp_threading.h>
#include <pthread.h>
#include <errno.h>
#include <stdexcept>
#include <new>

namespace anp
{
namespace threading
{
	////////////////
	// Data types //
	////////////////
	
	struct ThreadPlatformSpecific
	{
		pthread_t m_thread;
	};
	
	struct MutexPlatformSpecific
	{
		pthread_mutex_t m_mutex;
	};
	
	struct ThreadAttributesPlatformSpecific
	{
		pthread_attr_t m_attributes;
	};
	
	struct EventPlatformSpecific
	{
		pthread_cond_t m_cond;
		pthread_mutex_t m_mutex;
	};
	
	///////////////
	// Functions //
	///////////////
	
	// Thread
	void createThreadObject(ThreadPlatformSpecific **thread)
	{
		if ( NULL == thread )
		{
            throw std::invalid_argument("thread == NULL");
		}
		*thread = new ThreadPlatformSpecific;
		if ( NULL == *thread )
		{
		    // Not sure how new behaves on android, so making sure it's thrown
            throw std::bad_alloc();
		}
	}

	void destroyThreadObject(ThreadPlatformSpecific *thread)
	{
		if ( NULL != thread )
		{
			delete thread;
		}
	}
	
	void Thread::create(const ThreadAttributesPlatformSpecific *attr,
		void *(*startRoutine)(void *), void *arg)
	{
		/// @todo Add support for attr parameter
		
		// attr and arg are allowed to be NULL
		if ( NULL != startRoutine )
		{
			if ( 0 != pthread_create(&m_thread->m_thread, NULL,
				startRoutine, arg) )
			{
                throw std::runtime_error("pthread_create() failed");
			}
		}
	}
	
	void Thread::join(void **valuePtr)
	{
		if ( 0 != pthread_join(m_thread->m_thread, valuePtr) )
        {
            throw std::runtime_error("pthread_join() failed");
        }
	}
	
	// Mutex
	void createMutexObject(MutexPlatformSpecific **mutex)
	{
		if ( NULL == mutex )
		{
            throw std::invalid_argument("mutex is NULL");
		}
		*mutex = new MutexPlatformSpecific;
		if ( NULL == *mutex )
		{
            throw std::bad_alloc();
		}
		pthread_mutex_init(&((*mutex)->m_mutex), NULL);
	}

	void destroyMutexObject(MutexPlatformSpecific *mutex)
	{
		if ( NULL != mutex )
		{
			pthread_mutex_destroy(&mutex->m_mutex);
			delete mutex;
		}
	}
	
	void Mutex::lock()
	{
		if ( 0 != pthread_mutex_lock(&m_mutex->m_mutex) )
		{
            throw std::runtime_error("pthread_mutex_lock() failed");		
		}
	}
	
	bool Mutex::tryLock()
	{
		int ret = pthread_mutex_trylock(&m_mutex->m_mutex);
		switch ( ret )
		{
		case 0:
			return true;
		case EBUSY:
			return false;
		case EINVAL:
			throw std::invalid_argument("tryLock(): Not an initialized mutex (EINVAL)");
		case EFAULT:
			throw std::invalid_argument("tryLock(): Invalid pointer (EFAULT)");
		default:
			throw std::runtime_error("tryLock(): Undefined behavior (UNKNOWN)");
		}
	}

	void Mutex::unlock()
	{
        if ( 0 == pthread_mutex_unlock(&m_mutex->m_mutex) )
        {
            throw std::runtime_error("pthread_mutex_unlock() failed");        
        }
	}
	
	// Event
	void createEventObject(EventPlatformSpecific **event)
	{
		if ( NULL == event )
		{
			throw std::invalid_argument("event is NULL");
		}
		*event = new EventPlatformSpecific;
		if ( NULL == *event )
		{
            throw std::bad_alloc();
		}
		pthread_cond_init(&((*event)->m_cond), NULL);
		pthread_mutex_init(&((*event)->m_mutex), NULL);
	}
	
	void destroyEventObject(EventPlatformSpecific *event)
	{
		if ( NULL != event )
		{
			pthread_cond_destroy(&event->m_cond);
			pthread_mutex_destroy(&event->m_mutex);
			delete event;
		}
	}
	
	void Event::wait()
	{
		pthread_mutex_lock(&m_event->m_mutex);
		pthread_cond_wait(&m_event->m_cond, &m_event->m_mutex);
		pthread_mutex_unlock(&m_event->m_mutex);
	}
	
	void Event::signal()
	{
		pthread_mutex_lock(&m_event->m_mutex);
		if ( 0 != pthread_cond_signal(&m_event->m_cond) )
		{
            throw std::runtime_error("pthread_cond_signal() failed");
		}
		pthread_mutex_unlock(&m_event->m_mutex);
	}
	
	void Event::signalBroadcast()
	{
		pthread_mutex_lock(&m_event->m_mutex);
		pthread_cond_broadcast(&m_event->m_cond);
		pthread_mutex_unlock(&m_event->m_mutex);
	}
	
} // namespace threading
} // namespace anp

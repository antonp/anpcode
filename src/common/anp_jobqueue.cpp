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
 * @file anp_jobqueue.cpp
 * Implementation of the job queue system.
 */

#include <anpcode/anp_jobqueue.h>

namespace anp
{
namespace threading
{
	
	Job::Job():
	m_status(JOBSTATUS_CREATED)
	{
		
	}
	
	Job::~Job()
	{
		/// @todo If m_status == JOBSTATUS_EXECUTING,
		/// thread.join() !
	}
	
	void Job::execute()
	{
		m_status = JOBSTATUS_EXECUTING;
		executeCustom();
	}
	
	Job::JobStatus Job::getStatus() const
	{
		return m_status;
	}
	
	
	JobQueue::JobQueue():
	m_dying(0)
	{
		
	}

	JobQueue::~JobQueue()
	{
		
	}
	
	void JobQueue::start()
	{
		for ( uint32 i=0; i<MAX_THREADS; ++i )
		{
			m_workers[i].start(this);
		}
	}
	
	void JobQueue::stopWait()
	{
		WorkerThread *worker = NULL;
		m_dyingMutex.lock();
		m_dying = 1;
		m_dyingMutex.unlock();
		for ( uint32 i=0; i<MAX_THREADS; ++i )
		{
			worker = m_workers+i;
			worker->stop(); // Raise dying flag
		}
		
		m_newJobEvent.signalBroadcast(); // Wake up all workers
		for ( uint32 i=0; i<MAX_THREADS; ++i )
		{
			worker = m_workers+i;
			m_workers->join(); // Wait for it to finish			
		}
		
		// All workers have been stopped
		// so it is safe to clean up the queue
		// without locking it
		Job *job = NULL;
		while ( !m_queue.empty() )
		{
			job = m_queue.front();
			m_queue.pop();
			delete job;
			job = NULL;
		}
	}
	
	void JobQueue::waitForJobsToBeCompleted()
	{
		m_jobQueueMutex.lock();
		while ( !m_queue.empty() )
		{
			m_jobQueueMutex.unlock();
			m_jobsCompleted.wait();
			m_jobQueueMutex.lock();
		}
		m_jobQueueMutex.unlock();
	}
	
	bool32 JobQueue::waitForJob(Job **job)
	{
		uint32 dying = 0;
		
		*job = NULL;
		
		m_jobQueueMutex.lock();

		// Wait for a job to be added to the queue
		// (but what if there are already jobs in the queue?)
		while ( m_queue.empty() ) {
			m_jobQueueMutex.unlock();
			/// @todo Spurious wakeups; Is there really a new job?
			m_newJobEvent.wait();
			// Here, just in between the wait and acquire calls,
			// we can't lose the job to another thread. Only
			// one is released upon a signal().
			//   However, spurious wakeups can happen, so check anyway.
			m_dyingMutex.lock();
			dying = m_dying;
			m_dyingMutex.unlock();
			if ( 1 == dying )
			{
				return false;
			}
			
			
			m_jobQueueMutex.lock();
		}

		*job = m_queue.front();
		m_queue.pop();
		if ( m_queue.empty() )
		{
			m_jobsCompleted.signal();
		}
		m_jobQueueMutex.unlock();
		
		return true;
	}
	
	void JobQueue::addJob(Job *job)
	{
		bool32 empty = false;
		
		m_jobQueueMutex.lock();
		m_queue.push(job);
		//empty = m_queue.empty();
		m_jobQueueMutex.unlock();
		
		//if ( empty )
		//{
//			m_newJobEvent.signal();
		//}
		m_newJobEvent.signal();
	}
	
} // namespace threading
} // namespace anp

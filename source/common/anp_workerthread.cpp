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
 * @file anp_workerthread.cpp
 * Implementation of the WorkerThread.
 */

#include "anp_workerthread.h"
#include <anp_jobqueue.h>

namespace anp
{
namespace threading
{
	WorkerThread::WorkerThread():
	m_dying(0)
	{
		
	}
	
	WorkerThread::~WorkerThread()
	{
		
	}
	
	void WorkerThread::start(JobQueueWorkerInterface *jobQueue)
	{
		m_jobQueue = jobQueue;
		m_thread.create(NULL, threadEntry, (void *)this);
	}
	
	void WorkerThread::stop()
	{
		/// @todo implement, force stop or raise a dying flag and wait?
		m_dyingMutex.lock();
		m_dying = 1;
		m_dyingMutex.unlock();
	}
	
	void WorkerThread::join()
	{
		m_thread.join(NULL);
	}
	
	void WorkerThread::loop()
	{
		Job *job = NULL;
		uint32 dying = 0;

		m_dyingMutex.lock();
		dying = m_dying;
		m_dyingMutex.unlock();

		while ( 0 == dying ) {
			if ( m_jobQueue->waitForJob(&job) == false || NULL == job )
			{
				// The job queue is shutting down
				break;
			}

			if ( NULL != job )
			{
				job->execute();
			}

			delete job;
			job = NULL;
			
			m_dyingMutex.lock();
			dying = m_dying;
			m_dyingMutex.unlock();
		}
	}
	
	void *WorkerThread::threadEntry(void *arg)
	{
		((WorkerThread *)arg)->loop();
	}
	
} // namespace threading
} // namespace anp

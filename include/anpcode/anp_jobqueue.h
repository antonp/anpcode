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
 * @file anp_jobqueue.h
 * Provides an api to create jobs or tasks and add them to a queue.
 * A number of worker threads will then work their way through the
 * queue.
 */

#ifndef _ANP_JOBQUEUE_H_
#define _ANP_JOBQUEUE_H_

#include <anpcode/basedefs.h>
#include <anpcode/anp_threading.h>
#include <anpcode/anp_workerthread.h> // forward declare when dynamic amount
#include <queue>

namespace anp
{
namespace threading
{
	/**
	 * @brief
	 * Job base class.
	 */
	class Job
	{
	public:
		Job();
		virtual ~Job();
		
		void execute();
		
		enum JobStatus
		{
			JOBSTATUS_CREATED,
			JOBSTATUS_QUEUED,
			JOBSTATUS_EXECUTING
		};
		
		JobStatus getStatus() const;
	protected:
		JobStatus m_status;
		
		virtual void executeCustom() = 0;
	};

	class JobQueueOperatorInterface
	{
	public:
		virtual void start() = 0;
		virtual void stopWait() = 0;
		virtual void waitForJobsToBeCompleted() = 0;
		virtual void addJob(Job *job) = 0;
	};
	
	class JobQueueWorkerInterface
	{
	public:
		virtual bool32 waitForJob(Job **job) = 0;
	};

	class JobQueue:
		public JobQueueOperatorInterface,
		public JobQueueWorkerInterface
	{
	public:
		JobQueue();
		~JobQueue();
		
		void start();
		void stopWait();
		void waitForJobsToBeCompleted();
		bool32 waitForJob(Job **job);
		void addJob(Job *job);
	private:
		std::queue<Job *> m_queue;
		Mutex m_jobQueueMutex;
		Event m_newJobEvent;
		Event m_jobsCompleted;
		uint32 m_dying;
		Mutex m_dyingMutex;
		
		enum
		{
			MAX_THREADS=1
		};
		/// @todo make dynamic amount, changeable at runtime
		WorkerThread m_workers[MAX_THREADS];
	};

} // namespace threading
} // namespace anp

#endif // _ANP_JOBQUEUE_H_

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

#ifndef _ANP_THREADING_H_
#define _ANP_THREADING_H_

/**
 * @file anp_threading.h
 * Provides a generic interface for working with threads.
 * A platform specific implementation must be provided/linked in.
 * @todo Create wrapper object calling createThreadObject in constructor
 * and destroyThreadObject in destructor.
 */

namespace anp
{
namespace threading
{
    /**
     * @brief
     * The ThreadPlatformSpecific object represents a single
     * thread and can be used to carry out operations on that thread.
     */
    struct ThreadPlatformSpecific;

    /**
     * @brief
     * The MutexPlatformSpecific object can be used for
     * synchronizing threads.
     */
    struct MutexPlatformSpecific;

    /**
     * @brief
     * Attributes and creation options for a thread.
     */
    struct ThreadAttributesPlatformSpecific;

    /**
     * @brief
     * The EventPlatformSpecific object represents a synchronization
     * event.
     */
    struct EventPlatformSpecific;

    /**
     * @brief
     * This class wraps the platform specific thread handle/identifier.
     * It can be created on the stack!
     */
    class Thread
    {
    public:
        Thread();
        virtual ~Thread();

        /**
         * @brief
         * Creates a thread.
         *
         * @param[in] attr
         * Attributes and creation options of the thread.
         *
         * @param[in] startRoutine
         * Entry function for the thread.
         *
         * @param[in] arg
         * Argument to be passed to the threads startRoutine.
         */
        void create(const ThreadAttributesPlatformSpecific *attr,
            void *(*startRoutine)(void *), void *arg);

        /**
         * @brief
         * Wait for thread to finish. Exactly like pthread_join.
         *
         * @param thread
         * The thread to wait for.
         *
         * @param valuePtr
         * No clue.
         */
        void join(void **valuePtr);

    private:
        ThreadPlatformSpecific *m_thread;
    };

    class Mutex
    {
    public:
        Mutex();
        ~Mutex();

        /**
         * @brief
         * Locks the mutex.
         */
        void lock();

        /**
         * @brief
         * Tries to lock the mutex. Does not block.
         *
         * @return
         * true if the lock succeeded and false otherwise.
         */
        bool tryLock();

        /**
         * @brief
         * Unlocks the mutex.
         */
        void unlock();
    private:
        MutexPlatformSpecific *m_mutex;
    };

    /**
     * @brief
     * The typical lock mechanism.
     */
    class Lock
    {
    public:
        Lock(Mutex &mutex);
        ~Lock();
    private:
        Mutex &m_mutex;
    };

    /**
     * @brief
     * Like Lock, but uses Mutex::tryLock instead.
     */
    class TryLock
    {
    public:
        TryLock(Mutex &mutex);
        ~TryLock();
    private:
        Mutex &m_mutex;
    };

    class Event
    {
    public:
        Event();
        ~Event();

        void wait();
        void signal();
        void signalBroadcast();
    private:
        EventPlatformSpecific *m_event;
    };

    template<typename T, T INIT>
    class ProtectedData
    {
    public:
        ProtectedData():m_data(INIT) { };

        void set(T value) {
            m_mutex.lock();
            m_data = value;
            m_mutex.unlock();
        }
        void get(T &value) const {
            m_mutex.lock();
            value = m_data;
            m_mutex.unlock();
        }
    protected:
        mutable Mutex m_mutex;
        T m_data;
    };
} // namespace threading
} // namespace anp

#endif // _ANP_THREADING_H_

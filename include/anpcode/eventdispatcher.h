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

#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include <list>
#include <stdexcept>

namespace anp
{

template <typename E>
class ISubscriber
{
public:
    virtual ~ISubscriber() { }
    virtual void receiveEvent(E &event) = 0;
};

template <typename E>
class IEventDispatcherSource
{
public:
    virtual ~IEventDispatcherSource() { }
    virtual void dispatch(E &event) = 0;
};

template <typename S>
class IEventDispatcherSubscriber
{
public:
    virtual ~IEventDispatcherSubscriber() { }
    virtual void subscribe(S *subscriber) = 0;
    virtual void unsubscribe(S *subscriber) = 0;
};

// Subscriber, Event
template <typename S, typename E>
class EventDispatcher: public IEventDispatcherSubscriber<S>,
                       public IEventDispatcherSource<E>
{
public:
    void subscribe(S *subscriber)
    {
        m_subscribers.push_back(subscriber);
    }

    void unsubscribe(S *subscriber)
    {
        typename std::list<S *>::iterator i;
        for ( i=m_subscribers.begin();
              i != m_subscribers.end(); i++ )
        {
            if ( (*i) == subscriber )
            {
                m_subscribers.erase(i);
                return;
            }
        }
        throw std::runtime_error("Unable to find specified subscriber");
    }

    void dispatch(E &event)
    {
        typename std::list<S *>::iterator i;
        for ( i=m_subscribers.begin();
              i != m_subscribers.end(); i++ )
        {
            (*i)->receiveEvent(event);
        }
    }
private:
    std::list<S *> m_subscribers;
};

}

#endif // _EVENTDISPATCHER_H_

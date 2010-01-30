#ifndef _EVENTDISPATCHER_H_
#define _EVENTDISPATCHER_H_

#include <list>
#include <stdexcept>

namespace anp
{

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

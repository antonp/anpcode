#ifndef _LOG_SINGLETON_H_
#define _LOG_SINGLETON_H_

#include "log.h"
#include "basedefs.h"

namespace anp
{

class LogSingleton: public anp::Log
{
public:
	static LogSingleton &getInstance();
	static void releaseInstance();
private:
	LogSingleton() { }
	~LogSingleton() { }
	
	static uint32 m_refCount;
	static LogSingleton *m_instance;
};

/**
	Makes sure that LogSingleton::releaseInstance() gets called.
*/
class LogSingletonHelper
{
public:
	LogSingletonHelper():
	m_log(LogSingleton::getInstance())
	{
		
	}
	~LogSingletonHelper()
	{
		LogSingleton::releaseInstance();
	}
	void addMessage(const anp::dstring &message)
	{
		m_log.addMessage(message);
	}
	
	void operator()(const anp::dstring message)
	{
		m_log.addMessage(message);
	}
private:
	LogSingleton &m_log;
};

#define LOG_SINGLETON_MSG(message) LogSingleton::getInstance().addMessage(message);\
									LogSingleton::releaseInstance();

}

#endif // _LOG_SINGLETON_H_

#include "../log_singleton.h"

namespace anp
{

LogSingleton &LogSingleton::getInstance()
{
	if ( m_instance != NULL )
	{
		m_refCount++;
		return *m_instance;
	} else
	{
		m_instance = new LogSingleton;
		// Rely on new throwing an exception if allocation fails
		m_refCount++;
		return *m_instance;
	}
}

void LogSingleton::releaseInstance()
{
	if ( m_refCount > 0 )
	{
		if ( --m_refCount == 0 )
		{
			delete m_instance;
			m_instance = NULL;
		}
	}
}

uint32 LogSingleton::m_refCount = 0;
LogSingleton *LogSingleton::m_instance = NULL;

}

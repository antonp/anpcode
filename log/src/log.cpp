#include "../log.h"
#include <stdexcept>

namespace anp
{

/**
	Default constructor.

	Does nothing special.
*/
Log::Log():
m_logInterfaceCount(0)
{
	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		m_logInterfaces[i] = NULL;
	}
}

/**
	Destructor.
*/
Log::~Log()
{
	
}

/**
	Adds a message to the log.

	@param[in] message The message as a string.
*/
void Log::addMessage(const anp::dstring &message)
{
	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] != NULL )
		{
			m_logInterfaces[i]->present(message);
		}
	}
}

/**
	Adds a log (user) interface to the list of log interfaces.

	@param[in] logInterface The interface to add.
*/
void Log::addLogInterface(anp::ILogInterface *logInterface)
{
	if ( logInterface == NULL )
	{
		throw std::invalid_argument("logInterface == NULL");
	}

	if ( m_logInterfaceCount < MAX_LOGINTERFACES )
	{
		// Find the spot
		for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
		{
			if ( m_logInterfaces[i] == NULL )
			{
				m_logInterfaces[i] = logInterface;
				++m_logInterfaceCount;
				return;
			}
		}
		throw std::logic_error("m_logInterfaceCount < MAX_LOGINTERFACES, yet there is no empty spot");
	} else
	{
		throw std::overflow_error("Internal list of log interfaces is full");
	}
}

/**
	Removes a log (user) interface from the list.

	@param[in] logInterface The interface to remove.
*/
void Log::removeLogInterface(anp::ILogInterface *logInterface)
{
	if ( logInterface == NULL )
	{
		throw std::invalid_argument("logInterface == NULL");
	}

	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] == logInterface )
		{
			m_logInterfaces[i] = NULL;
			--m_logInterfaceCount;
			break;
		}
	}
}

}

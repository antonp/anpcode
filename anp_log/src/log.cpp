#include "../log.h"

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
	Adds a message to the log.

	@param[in] message The message as a string.

	@todo Optimize this function. If the there were never any gaps in the list it wouldn't be necessary to go through the whole list here OR check for NULL pointers.
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

	@return RES_OK on success, RES_OUTOFBOUNDS if the list of interfaces is full.
*/
anp::Result Log::addLogInterface(anp::ILogInterface *logInterface)
{
	ANP_REQUIRE_DIRECT(logInterface != NULL);

	if ( m_logInterfaceCount < MAX_LOGINTERFACES )
	{
		// Find the spot
		for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
		{
			if ( m_logInterfaces[i] == NULL )
			{
				m_logInterfaces[i] = logInterface;
				++m_logInterfaceCount;
				return anp::RES_OK;
			}
		}
		return anp::RES_INTERNALERROR;
	} else
	{
		return anp::RES_OUTOFBOUNDS;
	}
}

/**
	Removes a log (user) interface from the list.

	@param[in] logInterface The interface to remove.

	@return RES_OK on success or RES_NOTFOUND if the interface is not in the list.
*/
anp::Result Log::removeLogInterface(anp::ILogInterface *logInterface)
{
	ANP_REQUIRE_DIRECT(logInterface != NULL);

	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] == logInterface )
		{
			m_logInterfaces[i] = NULL;
			--m_logInterfaceCount;
			return anp::RES_OK;
		}
	}
	return anp::RES_NOTFOUND;
}

}

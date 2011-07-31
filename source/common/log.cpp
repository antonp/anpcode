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

#include "log.h"
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
	Adds an error message to the log.

    @param[in] tag The log tag.
	@param[in] message The message as a string.
    @param[in] file The source file that generated the message.
    @param[in] line The source line that generated the message.
*/
void Log::loge(const anp::dstring &tag,
               const anp::dstring &message,
               const anp::dstring &file,
               const anp::dstring &line)
{
	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] != NULL )
		{
			m_logInterfaces[i]->present(tag, message, file, line);
		}
	}
}

/**
	Adds an informational message to the log.

    @param[in] tag The log tag.
	@param[in] message The message as a string.
    @param[in] file The source file that generated the message.
    @param[in] line The source line that generated the message.
*/
void Log::logi(const anp::dstring &tag, const anp::dstring &message, const anp::dstring &file, const anp::dstring &line)
{
	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] != NULL )
		{
			m_logInterfaces[i]->present(tag, message, file, line);
		}
	}
}

/**
	Adds a debug message to the log.

    @param[in] tag The log tag.
	@param[in] message The message as a string.
    @param[in] file The source file that generated the message.
    @param[in] line The source line that generated the message.
*/
void Log::logd(const anp::dstring &tag,
               const anp::dstring &message,
               const anp::dstring &file,
               const anp::dstring &line)
{
	for ( anp::uint32 i=0; i<MAX_LOGINTERFACES; ++i )
	{
		if ( m_logInterfaces[i] != NULL )
		{
			m_logInterfaces[i]->present(tag, message, file, line);
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

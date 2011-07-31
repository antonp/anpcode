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

#ifndef _LOG_H_
#define _LOG_H_

#include <basedefs.h>
#include <anp_str.h>

namespace anp
{

class ILogInterface
{
public:
	virtual void present(const anp::dstring &tag,
                         const anp::dstring &message,
                         const anp::dstring &file,
                         const anp::dstring &line) = 0;
};

class Log
{
public:
	Log();
	virtual ~Log();

    void loge(const anp::dstring &tag,
              const anp::dstring &message,
              const anp::dstring &file="<file n/a>",
              const anp::dstring &line="<line n/a>");
	void logi(const anp::dstring &tag,
              const anp::dstring &message,
              const anp::dstring &file="<file n/a>",
              const anp::dstring &line="<line n/a>");
    void logd(const anp::dstring &tag,
              const anp::dstring &message,
              const anp::dstring &file="<file n/a>",
              const anp::dstring &line="<line n/a>");

	void addLogInterface(anp::ILogInterface *logInterface);
	void removeLogInterface(anp::ILogInterface *logInterface);
private:
	enum
	{
		MAX_LOGINTERFACES=10
	};

	anp::ILogInterface *m_logInterfaces[MAX_LOGINTERFACES];
	anp::uint32 m_logInterfaceCount;
};

}

#endif // _LOG_H_

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

#ifndef _LOG_SINGLETON_H_
#define _LOG_SINGLETON_H_

#include <anpcode/log.h>

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

    static unsigned int m_refCount;
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
    void logi(const std::string &tag,
              const std::string &message,
              const std::string &file="<file n/a>",
              const std::string &line="<line n/a>")
    {
        m_log.logi(message, file, line);
    }

    // todo: logd, loge etc

    void addLogInterface(anp::ILogInterface *logInterface);
    void removeLogInterface(anp::ILogInterface *logInterface);

private:
    LogSingleton &m_log;
};

#define TOSTRING_INNER(s) #s
#define TOSTRING(s) TOSTRING_INNER(s)
#define ANPLOGE(tag, message) anp::LogSingleton::getInstance().loge(tag, message, __FILE__, TOSTRING(__LINE__));\
                                    anp::LogSingleton::releaseInstance();
#define ANPLOGI(tag, message) anp::LogSingleton::getInstance().logi(tag, message, __FILE__, TOSTRING(__LINE__));\
                                    anp::LogSingleton::releaseInstance();
#define ANPLOGD(tag, message) anp::LogSingleton::getInstance().logd(tag, message, __FILE__, TOSTRING(__LINE__));\
                                    anp::LogSingleton::releaseInstance();

}

#endif // _LOG_SINGLETON_H_


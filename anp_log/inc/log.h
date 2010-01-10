#ifndef _LOG_H_
#define _LOG_H_

#include "../../anp_basecode/inc/basedefs.h"
#include "../../anp_basecode/inc/mgestr.h"

namespace anp
{

class ILogInterface
{
public:
	virtual void present(const anp::dstring &message) = 0;
};

class Log
{
public:
	Log();

	void addLogMessage(const anp::dstring &message);

	anp::RESULT addLogInterface(anp::ILogInterface *logInterface);
	anp::RESULT removeLogInterface(anp::ILogInterface *logInterface);
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

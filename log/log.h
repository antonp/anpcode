#ifndef _LOG_H_
#define _LOG_H_

#include <basedefs.h>
#include <anp_str.h>

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
	virtual ~Log();

	void addMessage(const anp::dstring &message);

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

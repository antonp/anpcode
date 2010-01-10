#ifndef _ANP_STR_H_
#define _ANP_STR_H_

#include "basedefs.h"
#include <string>

/// @file anp_str.h This file defines some basic string types
/// @todo DCHAR, define own string manipulation functions or macros (perhaps just wrappers around stl)

namespace firc
{
#ifdef ANP_UNICODE
	typedef std::wstring dstring;
//	#define anp_dstring std::wstring;
#else
	typedef std::string dstring;
//	#define anp_dstring std::string;
#endif
}

#ifdef ANP_UNICODE
	#define _D(x) (L#x)
#else
	#define _D(x) (x)
#endif

#endif // _ANP_STR_H_

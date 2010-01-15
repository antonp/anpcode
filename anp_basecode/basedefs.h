#ifndef _BASEDEFS_H_
#define _BASEDEFS_H_

#ifndef NULL
  #define NULL 0
#endif

namespace anp
{

#ifdef WINDOWS_32
  typedef long long				int64;
  typedef unsigned long long	uint64;
  typedef int					int32;
  typedef unsigned int			uint32;
  typedef short					int16;
  typedef unsigned short		uint16;
  typedef char					int8;
  typedef unsigned char			uint8;

  typedef uint32				bool32;
  typedef uint8					bool8;
  
  typedef int32					word;
  typedef uint32				uword;
#endif

#ifdef TARGET_UBUNTU64
  typedef long long				int64;
  typedef unsigned long long	uint64;
  typedef int					int32;
  typedef unsigned int			uint32;
  typedef short					int16;
  typedef unsigned short		uint16;
  typedef char					int8;
  typedef unsigned char			uint8;

  typedef uint32				bool32;
  typedef uint8					bool8;
  
  typedef int64					word;
  typedef uint64				uword;
#endif

//#define ANP_TRUE 1
//#define ANP_FALSE 0
enum
{
	FALSE = 0,
	TRUE = 1
};

#ifdef ANP_UNICODE
  #define DCHAR unsigned short
//  typedef unsigned short		DCHAR;
#else
  #define DCHAR char
//  typedef char					DCHAR;
#endif

enum Result
{
	RES_OK 				= 0,
	RES_FAILED,
	RES_INVALID_PARAMETER,
	RES_NOTFOUND,
	RES_OUTOFBOUNDS,
	RES_INTERNALERROR,
	RES_MEMALLOC_FAILED,
	RES_CONNECTION_CLOSED,
	RES_BUFFER_TOO_SMALL,
	RES_CONSTRUCTION_FAILED
};

} // namespace anp

#define ANP_CLEANUP_LABEL anpCleanUpLabel1:
#define ANP_GOTO_CLEANUP_LABEL goto anpCleanUpLabel1
#define ANP_GOTO_CLEANUP_LABEL_IF(expr) if ( expr ) { ANP_GOTO_CLEANUP_LABEL; }
#define ANP_REQUIRE(expr, resVar) if ( !(expr) ) { resVar = anp::RES_INVALID_PARAMETER; ANP_GOTO_CLEANUP_LABEL; }
#define ANP_REQUIRE_DIRECT(expr) if ( !(expr) ) { return anp::RES_INVALID_PARAMETER; }

#define ANP_DELETE(obj) if ( obj != NULL ) { delete obj; obj = NULL; }
#define ANP_DELETE_ARRAY(obj) if ( obj != NULL ) { delete[] obj; obj = NULL; }

#endif // _BASEDEFS_H_


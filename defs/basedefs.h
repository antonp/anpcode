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
  
#ifdef  TARGET_LINUX_64
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

#ifdef TARGET_LINUX32
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

enum
{
	FALSE = 0,
	TRUE = 1
};

#ifdef ANP_UNICODE
  #define DCHAR unsigned short
#else
  #define DCHAR char
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


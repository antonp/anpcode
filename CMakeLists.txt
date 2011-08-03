# cmake build file.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(anpcode)

# defs can be handled from here

# common handled here too?

IF(UNIX)
    IF(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
        ADD_DEFINITIONS(-DTARGET_LINUX_32)
    ELSEIF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        ADD_DEFINITIONS(-DTARGET_LINUX_64)
    ENDIF(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
ELSEIF(WIN32)
        MESSAGE(FATAL_ERROR "WIN32 not configured")
ENDIF(UNIX)

INCLUDE_DIRECTORIES(include)

SET(ANPCODE_SRCS src/common/anp_jobqueue.cpp
                 src/common/anp_workerthread.cpp
                 src/common/log.cpp
                 src/common/log_singleton.cpp
                 src/pfindep/anp_threading.cpp)

IF(UNIX)
    SET(ANPCODE_SRCS ${ANPCODE_SRCS} src/pfindep/anp_dynamic_library_posix.cpp
                                     src/pfindep/anp_threading_posix.cpp
                                     src/pfindep/anp_timing_posix.cpp)
ELSE(UNIX)
    MESSAGE(FATA_ERROR "Only UNIX/posix implemented in pfindep")
ENDIF(UNIX)



ADD_LIBRARY(anpcode SHARED ${ANPCODE_SRCS})


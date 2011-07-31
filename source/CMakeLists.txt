# cmake build file.
# this actually never worked, just did it to get
# accustomed to cmake

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

INCLUDE_DIRECTORIES(${anpcode_SOURCE_DIR}/defs)

SET(COMMON_SRCS common/anp_jobqueue.cpp
                common/anp_workerthread.cpp
                common/log.cpp
                common/log_singleton.cpp)

ADD_LIBRARY(anpcode ${COMMON_SRCS})

# pfindep handled by sub make list
#ADD_SUBDIRECTORY(pfindep)


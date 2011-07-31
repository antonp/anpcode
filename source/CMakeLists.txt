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

INCLUDE_DIRECTORIES(${anpcode_SOURCE_DIR}/defs)
INCLUDE_DIRECTORIES(pfindep)
INCLUDE_DIRECTORIES(common)

SET(ANPCODE_SRCS common/anp_jobqueue.cpp
                 common/anp_workerthread.cpp
                 common/log.cpp
                 common/log_singleton.cpp)

IF(UNIX)
    SET(ANPCODE_SRCS ${ANPCODE_SRCS} pfindep/anp_dynamic_library_posix.cpp
                                     pfindep/anp_threading_posix.cpp
                                     pfindep/anp_timing_posix.cpp)
ELSE(UNIX)
    MESSAGE(FATA_ERROR "Only UNIX/posix implemented in pfindep")
ENDIF(UNIX)



ADD_LIBRARY(anpcode ${ANPCODE_SRCS})


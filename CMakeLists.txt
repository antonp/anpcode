# cmake build file.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(anpcode)

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
SET_TARGET_PROPERTIES(anpcode
                      PROPERTIES
                      COMPILE_FLAGS "-fPIC"
                      VERSION 1.0.0
                      SOVERSION 1)
INSTALL(TARGETS anpcode
        DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

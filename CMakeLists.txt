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
                      COMPILE_FLAGS "-fPIC -Wall"
                      VERSION 0.1.0
                      SOVERSION 0)
INSTALL(TARGETS anpcode
        DESTINATION lib${LIB_SUFFIX}
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

INSTALL(FILES include/anpcode/anp_dynamic_library.h
              include/anpcode/anp_exceptions.h
              include/anpcode/anp_jobqueue.h
              include/anpcode/anp_threading.h
              include/anpcode/anp_threadsafequeue.h
              include/anpcode/anp_timing.h
              include/anpcode/anp_workerthread.h
              include/anpcode/eventdispatcher.h
              include/anpcode/iwritablecontainer.h
              include/anpcode/log.h
              include/anpcode/log_singleton.h
              include/anpcode/stdvector.h
        DESTINATION include/anpcode
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)


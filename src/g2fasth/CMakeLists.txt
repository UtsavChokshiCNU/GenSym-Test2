CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


#project name
PROJECT(g2fasth CXX)

include(CheckCXXCompilerFlag)

if (CMAKE_COMPILER_IS_GNUCXX)
    # This is an elaborate way to set the right `-std` flag
    # for GNU C++. Newer versions of CMAKE have direct support
    # for this with `target_compile_features()` or target property
    # CXX_STANDARD - like:
    # `set_property(TARGET tgt PROPERTY CXX_STANDARD 11)`
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if (COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
    elseif (COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")
    else()
	message(FATAL_ERROR "This GNU C++ doesn't support C++11 at all")
    endif()
endif()

INCLUDE_DIRECTORIES(include ../gsi/c)

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	SET(BIN_DIR "/x64")
else()
	SET(BIN_DIR "")
endif()
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib ${CMAKE_SOURCE_DIR}/../../dst/gsi/opt${BIN_DIR} ${CMAKE_SOURCE_DIR}/../../dst/rtl/opt${BIN_DIR} ${CMAKE_SOURCE_DIR}/../../dst/ext/opt${BIN_DIR})

SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
SET(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG")
SET(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MTd /Zi  /Ob0 /Od /RTC1")
SET(CMAKE_C_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG")

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../lib" CACHE INTERNAL "")

SET (SRCS include/base_suite.hpp
	include/g2fasth.hpp
	include/g2fasth_enums.hpp
	include/g2fasth_typedefs.hpp
	include/gsi_callbacks.h
	include/junit_report.hpp
	include/libgsi.hpp
	include/logger.hpp
	include/suite.hpp
	include/test_agent.hpp
	include/test_case_graph.hpp
	include/test_run_spec.hpp
	include/tinyxml2.hpp
	include/xml_serialization.hpp
	include/tinythread.h
	include/thread_pool.h
	include/fast_mutex.h
	src/g2fasth.cpp
	src/gsi_callbacks.cpp
	src/libgsi.cpp
	src/logger.cpp
	src/tinyxml2.cpp
	src/tinythread.cpp
	src/thread_pool.cpp
	src/xml_serialization.cpp)
SET (TESTSRCS include/catch.hpp
	src/tests-async.cpp
	src/tests-timeout.cpp
	src/tests-timer.cpp
	src/tests-case-order.cpp
	src/tests-execution-engine.cpp
	src/tests-before-after.cpp
	src/tests-preconditions.cpp
	src/tests-g2-options.cpp
	src/tests-fail-remaining.cpp
	src/tests-graph.cpp
	src/tests-graph-of-test-cases.cpp
	src/tests-junit.cpp
	src/tests-logger.cpp
	src/tests-main.cpp
	src/tests-declare-g2-variable.cpp
	src/tests-gsi-variables.cpp
	src/tests-reason.cpp
	src/tests-suite.cpp
	src/tests-suite-results.cpp
	src/tests-suite-scheduling.cpp
	src/tests-test-scheduling.cpp
	src/tests-threads.cpp
	src/tests-wide-strings.cpp)
ADD_LIBRARY(libg2fasth ${SRCS})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin" CACHE INTERNAL "")
ADD_EXECUTABLE(testg2fasth ${TESTSRCS})
add_definitions(-DCATCH_CONFIG_NO_WINDOWS_SEH)
add_definitions(-DCATCH_CONFIG_NO_POSIX_SIGNALS)

if(WIN32)
	add_definitions(-DGSI_USE_DLL)
	TARGET_LINK_LIBRARIES (testg2fasth libg2fasth gsi)
	add_custom_command(TARGET testg2fasth POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/../../dst/gsi/opt${BIN_DIR}/gsi.dll $<TARGET_FILE_DIR:testg2fasth>)
else()
	TARGET_LINK_LIBRARIES (testg2fasth gsi rtl tcp dl libg2fasth rt)
endif()

ADD_SUBDIRECTORY(test)
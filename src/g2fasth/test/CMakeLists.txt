CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0015 NEW)

#project name
PROJECT(basetest)

#library file path
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

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin" CACHE INTERNAL "")

ADD_EXECUTABLE(basetest basetest.cpp MySuite.cpp MySuite.hpp)

if(WIN32) 
	add_definitions(-DGSI_USE_DLL) 
	TARGET_LINK_LIBRARIES (basetest libg2fasth gsi)
	add_custom_command(TARGET basetest POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/../../dst/gsi/opt${BIN_DIR}/gsi.dll $<TARGET_FILE_DIR:basetest>)
else()
	TARGET_LINK_LIBRARIES (basetest gsi rtl tcp dl libg2fasth rt)
endif()

ADD_EXECUTABLE(rpc_test rpc_test.cpp ../../gsi/c/gsi_misc.c rt-suite.cpp rt-suite.hpp)

if(WIN32) 
	add_definitions(-DGSI_USE_DLL) 
	TARGET_LINK_LIBRARIES (rpc_test libg2fasth gsi)
	add_custom_command(TARGET rpc_test POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/../../dst/gsi/opt${BIN_DIR}/gsi.dll $<TARGET_FILE_DIR:rpc_test>)
else()
	TARGET_LINK_LIBRARIES (rpc_test gsi rtl tcp dl libg2fasth rt)
endif()

cmake_minimum_required(VERSION 2.8)

PROJECT(dmcsv)

IF (WIN32)
    MESSAGE(STATUS "Now is windows")

    SET(DMOS_NAME "win")

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
    IF(MSVC)
        ADD_DEFINITIONS(/bigobj)
        IF (MSVC_VERSION GREATER_EQUAL 1900)
            INCLUDE(CheckCXXCompilerFlag)
            CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
            IF (_cpp_latest_flag_supported)
                ADD_COMPILE_OPTIONS("/std:c++latest")
            ENDIF()
    	ENDIF()
    ENDIF()
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systems")  

    SET(DMOS_NAME "mac") 

    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS")  
 
    SET(DMOS_NAME "lin") 
    
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g" )
ENDIF ()

ADD_DEFINITIONS(-DUSE_DMCSV)
IF (WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/test)

LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

FILE(GLOB_RECURSE DMCSV_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/include/*.c
${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
${CMAKE_CURRENT_SOURCE_DIR}/include/*.h

${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

IF (WIN32)
    LIST(APPEND DMCSV_SOURCES)
ENDIF(WIN32)

ADD_LIBRARY(dmcsv ${DMCSV_SOURCES})

FILE(GLOB_RECURSE DMCSVTEST_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/test/gtest-all.cc
${CMAKE_CURRENT_SOURCE_DIR}/test/gtest_main.cc
${CMAKE_CURRENT_SOURCE_DIR}/test/dmcsvtest.cpp)

ADD_EXECUTABLE(dmcsvtest ${DMCSVTEST_SOURCES})
TARGET_LINK_LIBRARIES(dmcsvtest dmcsv)

FILE(GLOB_RECURSE DMCSVTOOL_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/test/dmcsvtool.cpp)

ADD_EXECUTABLE(dmcsvtool ${DMCSVTOOL_SOURCES})
TARGET_LINK_LIBRARIES(dmcsvtool dmcsv)


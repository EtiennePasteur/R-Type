cmake_minimum_required(VERSION 2.6.2)
project(R_Type)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BUILD)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Shared/Include)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SharedLibs/Interfaces)

include(cmake/ucm.cmake)

enable_testing()

if(MSVC)
    add_definitions(-DMSVC)
elseif(APPLE)
    add_definitions(-DAPPLE)
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_subdirectory(SFML EXCLUDE_FROM_ALL)
endif()
add_subdirectory(Shared)
if (NOT RTYPE_BUILD_SERVER_ONLY)
    add_subdirectory(Client)
endif()
add_subdirectory(Server)

ucm_set_runtime(STATIC)

add_subdirectory(SharedLibs)
add_subdirectory(UnitTests)
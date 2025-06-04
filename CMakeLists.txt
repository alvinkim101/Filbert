cmake_minimum_required(VERSION 3.10)
project(Filbert)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8") # Unicode support requires compiling with /utf-8
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

add_subdirectory(Filbert)
add_subdirectory(Editor)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)

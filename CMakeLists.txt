cmake_minimum_required(VERSION 3.5.1)
project(BuildAnalyzer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall 
    -Wextra 
    -Werror 
    -pedantic-errors
    -fno-omit-frame-pointer
    -msse4.2)

add_definitions(-DRAPIDJSON_SSE42)
add_subdirectory(thirdparty/rapid_json)
add_subdirectory(thirdparty/llvm-Demangle)

add_executable(build_analyzer
    src/analyze/build_analyzer.cpp
    src/analyze/source_analyzer.cpp
    src/events/event_type.cpp
    src/file_system/file_reader.cpp
    src/parser/parser.cpp
    src/config.cpp
    src/main.cpp)
    
target_include_directories(build_analyzer
    PRIVATE
        src)
    
target_link_libraries(build_analyzer
    PRIVATE
        rapid_json demangle)

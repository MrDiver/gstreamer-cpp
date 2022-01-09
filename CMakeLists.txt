cmake_minimum_required(VERSION 3.16)
project(gstreamer_cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)
set(CMAKE_CXX_STANDARD 20)

include(SetupGStreamer.cmake)
include(FormatFile.cmake)

set(GSTREAMER_CPP_SRC_F
    src/core/Bin.cpp
    src/core/Bus.cpp
    src/core/Element.cpp
    src/core/ElementFactory.cpp
    src/core/Message.cpp
    src/core/Object.cpp
    src/core/Pipeline.cpp
    src/core.cpp
)

add_library(${PROJECT_NAME} "")
target_include_directories(${PROJECT_NAME} PUBLIC include)
add_gstreamer(${PROJECT_NAME})
# format_file(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(include)

add_executable(media_demo test/demo.cpp)
target_link_libraries(media_demo ${PROJECT_NAME})
target_include_directories(media_demo PUBLIC ${PROJECT_NAME} PUBLIC test)
add_gstreamer(media_demo)

#Find System Thread Library
find_package(Threads REQUIRED)
message(VERBOSE "Search for Threads")
if(${Threads_FOUND})
    message(VERBOSE "Found - ${CMAKE_THREAD_LIBS_INIT}")
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
    target_link_libraries(media_demo Threads::Threads)
endif(${Threads_FOUND})

# Compile tests only if compiled from main CMakeLists.txt
if(IS_MAIN_PROJECT)
    # add_executable(test_core "test/tests.cpp")
    # target_link_libraries(test_core gtest_main) # Linking google tests
    # gtest_discover_tests(test_core) # Add tests to google tests
    format_file(${PROJECT_NAME})
endif(IS_MAIN_PROJECT)

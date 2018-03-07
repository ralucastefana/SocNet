cmake_minimum_required(VERSION 3.3)
project(ProiectRCServer)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_path(THREAD_INCLUDE_DIR pthread.h)
find_library(THREAD_LIBRARY pthread)
find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)
if(NOT SQLITE3_INCLUDE_DIR)
    message(SEND_ERROR "Failed to find sqlite3.h")
endif()
if(NOT SQLITE3_LIBRARY)
    message(SEND_ERROR "Failed to find the sqlite3 library")
endif()

set(SOURCE_FILES main.cpp Structs/Structs.h Server/Server.h Server/Server.cpp Database/Database.cpp Database/Database.h)
add_executable(ProiectRCServer ${SOURCE_FILES})


target_link_libraries(ProiectRCServer
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${SQLITE3_LIBRARY}
        ${THREAD_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        rt)

target_link_libraries(ProiectRCServer
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${SQLITE3_LIBRARY}
        ${THREAD_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        rt)

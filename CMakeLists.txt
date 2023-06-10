cmake_minimum_required(VERSION 3.25)
project(Trading_Engine)

set(CMAKE_CXX_STANDARD 17)

# Add the new source files
set(SOURCES
        main.cpp
        OrderBookEntry.cpp
        MerkelMain.cpp)

set(HEADERS
        OrderBookEntry.h
        OrderBookEntry.cpp OrderBookEntry.h MerkelMain.cpp MerkelMain.h)

# Add the executable target
add_executable(Trading_Engine ${SOURCES} ${HEADERS})

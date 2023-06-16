cmake_minimum_required(VERSION 3.25)
project(Trading_Engine)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
set(SOURCES
        main.cpp
        OrderBookEntry.cpp
        MerkelMain.cpp
        CSVReader.cpp CSVReader.h Wallet.cpp Wallet.h)

# Add the header files
set(HEADERS
        OrderBookEntry.h
        MerkelMain.h
        CSVReader.cpp CSVReader.h Wallet.cpp Wallet.h OrderBook.cpp OrderBook.h)

# Add the executable target
add_executable(Trading_Engine ${SOURCES} ${HEADERS})

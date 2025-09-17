cmake_minimum_required(VERSION 3.16)
project(chess_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address,undefined -O1")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
    main.cpp
    Board/board.cpp
    Utils/utils.cpp
    Player/player.cpp
    Pieces/Piece/piece.cpp
    Rules/rules.cpp
    Rules/move_generator.cpp
)

add_executable(chess ${SOURCES})
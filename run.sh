#!/bin/bash
g++ \
-g -fsanitize=address,undefined -O1 \
main.cpp \
Board/board.cpp \
Utils/utils.cpp \
Player/player.cpp \
Pieces/Piece/piece.cpp \
-o chess
./chess
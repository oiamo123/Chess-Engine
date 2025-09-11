#!/bin/bash
g++ \
main.cpp \
Board/board.cpp \
Utils/utils.cpp \
Player/player.cpp \
Pieces/Piece/piece.cpp \
-o chess
./chess
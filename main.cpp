#include <iostream>
#include "./Board/board.cpp"
using std::cout;
using std::endl;

int main() {
    Board board;
    board.display();
    return 0;
}

/*
Board
 - Handles the chessboard and state (who's turn is it), piece placement, legal moves, castling rights etc
Pieces
 - Represents the individual chess pieces and their movements
 - Responsible for their own movement logic and where they can move to
*/

#include <iostream>
#include "./Board/board.h"
#include "./Utils/utils.h"

using std::cout;
using std::endl;

int main() {
    Board board;
    
    board.create();
    board.display();

    Utils::printBitboard(board.board);
    const string color = Utils::getColor(1);
    const string type = Utils::getType(2);
    const string square = Utils::getSquare(2);

    cout << "Color: " << color << ", Type: " << type << ", Square: " << square << endl;

    return 0;
}

/*
Board
 - Handles the chessboard and state (who's turn is it), piece placement, legal moves, castling rights etc
Pieces
 - Represents the individual chess pieces and their movements
 - Responsible for their own movement logic and where they can move to
*/

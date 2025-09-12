#include <iostream>
#include "./Board/board.h"
#include "./Utils/utils.h"
#include "./Pieces/Piece/piece.h"

using std::cout;
using std::endl;

int main() {
    Board board;
    board.create();
    board.display();

    int32_t move = 0;
    move |= (uint8_t)Color::White << 24;
    move |= (uint8_t)PieceType::Pawn << 16; 
    move |= (uint8_t)Square::E2 << 8; 
    move |= (uint8_t)Square::E4;      

    board.move(move);
    board.display();

    return 0;
}

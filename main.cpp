#include <iostream>
#include "./Board/board.h"
#include "./Utils/utils.h"
#include "./Pieces/Piece/piece.h"

using std::cout;
using std::endl;
using std::uint8_t;
using std::uint32_t;

int main() {
    Board board;
    board.create();
    board.display();

    const uint32_t move = Utils::createMove(
        (uint8_t)PieceType::Pawn, 
        (uint8_t)Color::White, 
        (uint8_t)Square::E2, 
        (uint8_t)Square::E4
    );

    board.move(move);
    board.display();

    return 0;
}

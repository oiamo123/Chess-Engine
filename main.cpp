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

    const int32_t move = Utils::createMove((int8_t)PieceType::Pawn, (int8_t)Color::White, (int8_t)Square::E2, (int8_t)Square::E4);

    board.move(move);
    board.display();

    return 0;
}

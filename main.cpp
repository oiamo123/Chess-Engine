#include <iostream>
#include "./Utils/utils.h"
#include "./Rules/MoveGenerator/move_generator.h"
#include "./Rules/RayGenerator/ray_generator.h"
#include "./Board/board.h"
#include "./Utils/global.h"
#include <array>

using std::cout;
using std::endl;
using std::uint8_t;
using std::uint32_t;

int main() {
    MoveGenerator moveGenerator = MoveGenerator();
    Board board;
    board.create();

    uint32_t move1 = Utils::createMove((uint8_t)PieceType::Pawn, (uint8_t)Color::White, (uint8_t)Square::E2, (uint8_t)Square::E4);
    uint32_t move2 = Utils::createMove((uint8_t)PieceType::Pawn, (uint8_t)Color::Black, (uint8_t)Square::D7, (uint8_t)Square::D5);
    uint32_t move3 = Utils::createMove((uint8_t)PieceType::Pawn, (uint8_t)Color::White, (uint8_t)Square::B2, (uint8_t)Square::A4);
    uint32_t move4 = Utils::createMove((uint8_t)PieceType::Queen, (uint8_t)Color::Black, (uint8_t)Square::D8, (uint8_t)Square::C4);
    uint32_t move5 = Utils::createMove((uint8_t)PieceType::Queen, (uint8_t)Color::White, (uint8_t)Square::D1, (uint8_t)Square::A5);
    uint32_t move6 = Utils::createMove((uint8_t)PieceType::Pawn, (uint8_t)Color::Black, (uint8_t)Square::A7, (uint8_t)Square::A6);

    board.move(move1);
    board.move(move2);
    board.move(move3);
    board.move(move4);
    board.move(move5);
    board.move(move6);

    uint64_t white = board.players[0].getAllPieces();
    uint64_t black = board.players[1].getAllPieces();

    Utils::printBitboard(board.players[0].getAllPieces());
    Utils::printBitboard(board.players[1].getAllPieces());

    board.display();

    uint64_t moves = moveGenerator.generateQueenMoves((uint8_t)Square::A5, black, white);
    cout << "Queen Moves: \n" << endl;
    Utils::printBitboard(moves);
}

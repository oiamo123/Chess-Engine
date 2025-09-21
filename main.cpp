#include <array>
#include <iostream>
#include <chrono>
#include "./Utils/utils.h"
#include "./Rules/MoveGenerator/move_generator.h"
#include "./Rules/RayGenerator/ray_generator.h"
#include "./Board/board.h"
#include "./Utils/global.h"

using std::cout;
using std::endl;
using std::array;
using std::uint8_t;
using std::uint32_t;

uint64_t generateQueenMovesNaive(uint8_t from, uint64_t opponentPieces, uint64_t friendlyPieces) {
    uint64_t moves = 0ULL;
    uint64_t allPieces = opponentPieces | friendlyPieces;

    // Queen directions (N, S, E, W, NE, NW, SE, SW)
    const int directions[8] = { 1, -1, 8, -8, 9, -9, 7, -7 };

    for (int dir : directions) {
        int sq = from;
        while (true) {
            int rank = sq / 8;
            int file = sq % 8;

            int next = sq + dir;
            int nextRank = next / 8;
            int nextFile = next % 8;

            // Check if off-board (rank/file wrap)
            if (next < 0 || next >= 64) break;
            if (std::abs(nextRank - rank) > 1 && (dir == 1 || dir == -1)) break;  // file wrap
            if (std::abs(nextFile - file) > 1 && (dir == 8 || dir == -8)) break;  // rank wrap
            if (std::abs(nextFile - file) > 1 && (dir == 7 || dir == -7 || dir == 9 || dir == -9)) break; // diag wrap

            sq = next;
            uint64_t bb = 1ULL << sq;

            moves |= bb; // add move

            if (allPieces & bb) { // stop at first blocker
                break;
            }
        }
    }

    return moves & ~friendlyPieces; // cannot capture own pieces
}

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


    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++) {
        for (int sq = 0; sq < 64; sq++) {
            volatile uint64_t moves = moveGenerator.generateQueenMoves(sq, black, white);
        }
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    cout << "Ray-based: " << duration1.count() << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; i++) {
        for (int sq = 0; sq < 64; sq++) {
            volatile uint64_t moves = generateQueenMovesNaive(sq, black, white);
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    cout << "Naive loop: " << duration2.count() << endl;
}

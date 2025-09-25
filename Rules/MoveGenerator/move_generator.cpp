#include "./move_generator.h"
#include "../RayGenerator/ray_generator.h"
#include "../../Utils/utils.h"
#include "../../Utils/global.h"
#include <array>
#include <tuple>
#include <iostream>

using std::int8_t;
using std::uint8_t;
using std::uint64_t;
using std::array;
using std::tuple;
using std::cout;
using std::endl;

alignas(64) uint64_t MoveGenerator::raysN[64];
alignas(64) uint64_t MoveGenerator::raysNE[64];
alignas(64) uint64_t MoveGenerator::raysE[64];
alignas(64) uint64_t MoveGenerator::raysSE[64];
alignas(64) uint64_t MoveGenerator::raysS[64];
alignas(64) uint64_t MoveGenerator::raysSW[64];
alignas(64) uint64_t MoveGenerator::raysW[64];
alignas(64) uint64_t MoveGenerator::raysNW[64];
alignas(64) uint64_t MoveGenerator::knightmoves[64];
alignas(64) uint64_t MoveGenerator::kingmoves[64];
alignas(64) uint64_t MoveGenerator::pawnAttacksWhite[48];
alignas(64) uint64_t MoveGenerator::pawnAttacksBlack[48];
alignas(64) uint64_t MoveGenerator::pawnPushesWhite[48];
alignas(64) uint64_t MoveGenerator::pawnPushesBlack[48];

enum class PawnMoveType : uint8_t {
    Pushes = 0,
    Attacks
};

MoveGenerator::MoveGenerator() {
    auto nMasks = RayGenerator::generateNMasks();
    auto neMasks = RayGenerator::generateNEMasks();
    auto eMasks = RayGenerator::generateEMasks();
    auto seMasks = RayGenerator::generateSEMasks();
    auto sMasks = RayGenerator::generateSMasks();
    auto swMasks = RayGenerator::generateSWMasks();
    auto wMasks = RayGenerator::generateWMasks();
    auto nwMasks = RayGenerator::generateNWMasks();

    std::copy(nMasks.begin(), nMasks.end(), raysN);
    std::copy(neMasks.begin(), neMasks.end(), raysNE);
    std::copy(eMasks.begin(), eMasks.end(), raysE);
    std::copy(seMasks.begin(), seMasks.end(), raysSE);
    std::copy(sMasks.begin(), sMasks.end(), raysS);
    std::copy(swMasks.begin(), swMasks.end(), raysSW);
    std::copy(wMasks.begin(), wMasks.end(), raysW);
    std::copy(nwMasks.begin(), nwMasks.end(), raysNW);

    auto knighttable = MoveGenerator::generateKnightTable();
    auto kingtable = MoveGenerator::generateKingTable();
    betweenTable = generateBetweenTable();
    pawnmoves = MoveGenerator::generatePawnTables();

    std::copy(knighttable.begin(), knighttable.end(), knightmoves);
    std::copy(kingtable.begin(), kingtable.end(), kingmoves);
};

/*
// OLD
All sliding pieces work on the exact same concept. But basically:
1. Pre generate all valid move from a square in a specific direction ie North, North East, East, South East etc etc
2. Take the opponent pieces and friendly pieces, and & them with the valid rays for that piece so Bishop -> NE, SE, SW, NW
3. Depending on the direction, the blocking piece will either be the biggest index or the smallest index, or in other words left most (lmb) or right most bit (rmb)
4. We can take the lmb or rmb, and create a mask so that either everything to the left or right of that bit is masked off, removing invalid moves in that direction.
-> https://goiamo.dev/notes/chess-engines/move-generation


// NEW
All sliding pieces use a "between" board.
1. We can pregenerate all the possible squares that a rook and bishop could slide to IE: ./is_between.jpg
2. Using this board, we can lookup:
    - The rays for the piece type IE Rook (0)
    - The from square
    - The to square
    - betweenTable[piecetype][from][to]
3. This allows us to just ((allPieces & betweenTable[pieceType][from][to]) && (friendlyPieces & to)) to check if the move is valid.
4. The board also works for checks and pins. We can loop over all sliding 
   pieces and do betweenTable[pieceType][kingPos][opponentQueen] & allPieces. If
   there isn't a piece, well then we know the king is in check.
-> https://goiamo.dev/notes/chess-engines/is-between-table
*/

// PUBLIC
uint64_t MoveGenerator::getBetweenMove(uint8_t from, uint8_t to, uint8_t piece) {
    return betweenTable[piece - 2][from][to];
}

tuple<uint64_t, uint64_t> MoveGenerator::getPawnMove(uint8_t from, uint8_t color) {
    return std::make_tuple(pawnmoves[color][0][from], pawnmoves[color][1][from]);
}

uint64_t MoveGenerator::getKnightMove(uint64_t from) {
    return knightmoves[from];
}

uint64_t MoveGenerator::getKingMove(uint64_t from) {
    return kingmoves[from];
}


// PRIVATE
array<uint64_t, 64> MoveGenerator::generateKingTable() {
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t bit = 1ULL << square;
        uint64_t moves = 0ULL;

        moves |= (bit << 8);
        moves |= (bit >> 8);
        if (!(bit & FILE_H)) moves |= (bit << 1);
        if (!(bit & FILE_A)) moves |= (bit >> 1);
        if (!(bit & FILE_H)) moves |= (bit << 9);
        if (!(bit & FILE_A)) moves |= (bit << 7);
        if (!(bit & FILE_H)) moves |= (bit >> 7);
        if (!(bit & FILE_A)) moves |= (bit >> 9);

        table[square] = moves;
    }

    return table;
};

array<uint64_t, 64> MoveGenerator::generateKnightTable() {
    const array<int8_t, 8> knightMoves = { -10, -17, -15, -6, 6, 10, 15, 17 };
    array<uint64_t, 64> table;

    for (uint8_t square = 0; square < 64; square++) {
        uint64_t moves = 0ULL;
        uint8_t rank = square / 8;
        uint8_t file = square % 8;

        for (uint8_t move : knightMoves) {
            uint8_t targetSquare = square + move;
            uint8_t targetRank = targetSquare / 8;
            uint8_t targetFile = targetSquare % 8;

            if (targetSquare >= 0 && targetSquare < 64 &&
                abs(targetRank - rank) + abs(targetFile - file) == 3) 
            {
                moves |= Utils::indexToBitboard(targetSquare);
            }
        }

        table[square] = moves;
    }

    return table;
};

array<array<array<uint64_t, 64>, 2>, 2> MoveGenerator::generatePawnTables() {
    array<array<array<uint64_t, 64>, 2>, 2> pm;

    for (uint8_t square = 8; square < 56; square++) {
        uint64_t bitboard = Utils::indexToBitboard(square);
        uint64_t attacks = 0ULL;
        uint64_t pushes = 0ULL;

        pushes |= bitboard << 8;
        if (bitboard & RANK_2) pushes |= bitboard << 16;

        if (!(bitboard & FILE_A)) attacks |= bitboard << 7;
        if (!(bitboard & FILE_H)) attacks |= bitboard << 9;

        pm[(uint8_t)Color::White][(uint8_t)PawnMoveType::Pushes][square] = pushes;
        pm[(uint8_t)Color::White][(uint8_t)PawnMoveType::Attacks][square] = attacks;
    }

    for (uint8_t square = 8; square < 56; square++) {
        uint64_t bitboard = Utils::indexToBitboard(square);
        uint64_t attacks = 0ULL;
        uint64_t pushes = 0ULL;

        pushes |= bitboard >> 8;
        if (bitboard & RANK_7) pushes |= bitboard >> 16;

        if (!(bitboard & FILE_H)) attacks |= bitboard >> 7;
        if (!(bitboard & FILE_A)) attacks |= bitboard >> 9;
        
        pm[(uint8_t)Color::Black][(uint8_t)PawnMoveType::Pushes][square] = pushes;
        pm[(uint8_t)Color::Black][(uint8_t)PawnMoveType::Attacks][square] = attacks;
    }

    return pm;
}

array<array<array<uint64_t, 64>, 64>, 3> MoveGenerator::generateBetweenTable() {
    array<array<array<uint64_t, 64>, 64>, 3> bt{};

    for (uint8_t from = 0; from < 64; from++) {
        for (uint8_t to = 0; to < 64; to++) {
            if (from == to) continue;

            uint64_t mask = 0ULL;

            if (Utils::sameDiagonal(from, to)) {
                mask = rayBetween(from, to);
                bt[(uint8_t)PieceType::Bishop - 2][from][to] = mask;
                bt[(uint8_t)PieceType::Queen - 2][from][to] = mask;
                Utils::printBitboard(mask);
            }

            if (Utils::sameRank(from, to) || Utils::sameFile(from, to)) {
                mask = rayBetween(from, to);
                bt[(uint8_t)PieceType::Rook - 2][from][to] = mask;
                bt[(uint8_t)PieceType::Queen - 2][from][to] = mask;
                Utils::printBitboard(mask);
            }
        }
    }

    return bt;
}

uint64_t MoveGenerator::rayBetween(uint8_t from, uint8_t to) {
    uint64_t mask = 0ULL;

    int fromRank = from / 8, fromFile = from % 8;
    int toRank   = to   / 8, toFile   = to   % 8;

    int dRank = (toRank > fromRank) ? 1 : (toRank < fromRank ? -1 : 0);
    int dFile = (toFile > fromFile) ? 1 : (toFile < fromFile ? -1 : 0);

    if ((dRank == 0 && dFile == 0) || (dRank != 0 && dFile != 0 && abs(toRank - fromRank) != abs(toFile - fromFile))) {
        return 0ULL;
    }

    int r = fromRank + dRank;
    int f = fromFile + dFile;
    while (r != toRank || f != toFile) {
        int sq = r * 8 + f;
        if (sq == to) break;
        mask |= 1ULL << sq;
        r += dRank;
        f += dFile;
    }

    return mask;
}
#include "./utils.h"
#include "../Player/player.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>

using std::stringstream;
using std::vector;
using std::cout;
using std::endl;

void Utils::parseFen(const string& fen, FenParams& fenParams) {
    if (!fen.empty()) return;
    
    vector<string> tokens;
    stringstream ss(fen);
    string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    string boardString = tokens[0];
    string toMoveString = tokens[1];
    string whiteCastlingString = tokens[2];
    string blackCastlingString = tokens[3];
    string halfMovesString = tokens[4];
    string fullMovesString = tokens[5];

    uint8_t curIndex = 0;
    array<uint8_t, 8> whiteCount{};
    array<uint8_t, 8> blackCount{};
    whiteCount.fill(0);
    blackCount.fill(0);

    for (char c : boardString) {
        if (isdigit(c)) {
            curIndex += c - '0'; 
            continue;
        }

        char cLower = tolower(c);
        bool isBlack = (c == cLower);
        Color friendly = isBlack ? Color::Black : Color::White;
        auto& pieceCount = isBlack ? blackCount : whiteCount;
        auto& pieces = isBlack ? fenParams.blackPieces : fenParams.whitePieces;

        uint8_t pt = 0;
        uint8_t baseIndex = 0;

        switch (cLower) {
            case 'p': 
                pt = (uint8_t)PieceType::Pawn;   
                baseIndex = (uint8_t)PieceIndex::P1; 
                break;
            case 'n': 
                pt = (uint8_t)PieceType::Knight; 
                baseIndex = (uint8_t)PieceIndex::N1; 
                break;
            case 'b': 
                pt = (uint8_t)PieceType::Bishop; 
                baseIndex = (uint8_t)PieceIndex::B1; 
                break;
            case 'r': 
                pt = (uint8_t)PieceType::Rook;   
                baseIndex = (uint8_t)PieceIndex::R1; 
                break;
            case 'q': 
                pt = (uint8_t)PieceType::Queen;  
                baseIndex = (uint8_t)PieceIndex::Q;  
                break;
            case 'k': 
                pt = (uint8_t)PieceType::King;   
                baseIndex = (uint8_t)PieceIndex::K;  
                break;
            default: 
                continue; 
        }

        uint8_t pi = baseIndex + pieceCount[pt];
        pieces[pt].push_back(pi);
        pieceCount[pt]++;
        
        curIndex++;
    }
}


string Utils::getDirection(const uint8_t direction) {
    switch (direction) {
        case static_cast<uint8_t>(Direction::N): return "North";
        case static_cast<uint8_t>(Direction::NE): return "North East";
        case static_cast<uint8_t>(Direction::E): return "East";
        case static_cast<uint8_t>(Direction::SE): return "South East";
        case static_cast<uint8_t>(Direction::S): return "South";
        case static_cast<uint8_t>(Direction::SW): return "South West";
        case static_cast<uint8_t>(Direction::W): return "West";
        case static_cast<uint8_t>(Direction::NW): return "North West";
        default: return "";
    }
}

string Utils::getType(const uint8_t type) {
    switch (type) {
        case static_cast<uint8_t>(PieceType::Pawn): return "Pawn";
        case static_cast<uint8_t>(PieceType::Knight): return "Knight";
        case static_cast<uint8_t>(PieceType::Bishop): return "Bishop";
        case static_cast<uint8_t>(PieceType::Rook): return "Rook";
        case static_cast<uint8_t>(PieceType::Queen): return "Queen";
        case static_cast<uint8_t>(PieceType::King): return "King";
        default: return "Unknown";
    }
}

string Utils::getColor(const uint8_t color) {
    return (color == static_cast<uint8_t>(Color::White)) ? "White" : "Black";
}

string Utils::getSquare(const uint64_t square) {
    if (square == 0) return "??";

    int file = __builtin_ctzll(square) % 8;
    int rank = __builtin_ctzll(square) / 8;

    char fileChar = 'a' + file;
    char rankChar = '1' + rank;

    return string(1, fileChar) + string(1, rankChar);
}


bool Utils::sameRank(const uint8_t from, const uint8_t to) {
    return (from / 8) == (to / 8);
}

bool Utils::sameFile(const uint8_t from, const uint8_t to) {
    return (from % 8) == (to % 8);
}

bool Utils::sameDiagonal(const uint8_t from, const uint8_t to) {
    return (from / 8 - from % 8) == (to / 8 - to % 8);
}


void Utils::printBitboard(const uint64_t bitboard) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            if (bitboard & (1ULL << square)) {
                cout << "1 ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

uint64_t Utils::indexToBitboard(const uint8_t index) {
    if (index > 63) {
        return 0;
    }

    return 1ULL << index;
}

uint8_t Utils::bitboardToIndex(const uint64_t bitboard) {
    return __builtin_ctzll(bitboard);
}

tuple<uint8_t, uint8_t, uint8_t, uint8_t> Utils::parseMove(const uint32_t move) {
    uint8_t piece = (move >> 24) & MASK_8;
    uint8_t color = (move >> 16) & MASK_8;
    uint8_t from = (move >> 8) & MASK_8;
    uint8_t to = move & MASK_8;

    return { piece, color, from, to };
}

uint32_t Utils::createMove(const uint8_t piece, const uint8_t color, const uint8_t from, const uint8_t to) {
    int32_t move = 0;
    move |= (uint8_t)piece << 24;
    move |= (uint8_t)color << 16;
    move |= (uint8_t)from << 8;
    move |= (uint8_t)to;

    return move;
}
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
using std::stoi;

// parses fen string
void Utils::parseFen(const string& fen, FenParams& fenParams) {    
    vector<string> tokens;
    stringstream ss(fen);
    string token;

    // split on spaces
    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    // assign each portion
    string boardString = tokens[0];
    string toMoveString = tokens[1];
    string castlingString = tokens[2];
    string enPassantString = tokens[3];
    string halfMovesString = tokens[4];
    string fullMovesString = tokens[5];

    uint8_t curIndex = 0;
    array<uint8_t, 8> whiteCount{};
    array<uint8_t, 8> blackCount{};
    whiteCount.fill(0);
    blackCount.fill(0);

    for (char c : boardString) {
        // ignore /
        if (c == '/') {
            continue;
        }

        // if digit, cur square += that digit
        if (isdigit(c)) {
            curIndex += c - '0'; 
            continue;
        }

        // if the letter lowercased is equal to itself, it's black, otherwise white
        char cLower = tolower(c);
        bool isBlack = (c == cLower);
        Color friendly = isBlack ? Color::Black : Color::White;
        auto& pieceCount = isBlack ? blackCount : whiteCount;
        auto& pieces = isBlack ? fenParams.blackPieces : fenParams.whitePieces;

        // get the piece type
        uint8_t pieceType = 0;        
        switch (cLower) {
            case 'p': 
                pieceType = (uint8_t)PieceType::Pawn;                   
                break;
            case 'n': 
                pieceType = (uint8_t)PieceType::Knight;                 
                break;
            case 'b': 
                pieceType = (uint8_t)PieceType::Bishop;                 
                break;
            case 'r': 
                pieceType = (uint8_t)PieceType::Rook;                   
                break;
            case 'q': 
                pieceType = (uint8_t)PieceType::Queen;                  
                break;
            case 'k': 
                pieceType = (uint8_t)PieceType::King;                   
                break;
            default: 
                continue; 
        }

        // we can add the current square to an array for pawns, so we know there's a pawn on square '15' for example
        // also want to track the piece count ie 8 pawns or 2 pawns
        pieces[pieceType].push_back(curIndex);
        pieceCount[pieceType]++;
        
        curIndex++;
    }    

    // parse turn to play
    fenParams.turn = toMoveString == "w" ? (uint8_t)Color::White : (uint8_t)Color::Black;

    // parses castling rights
    auto parseCastle = [](const string& castlingRights) -> array<array<bool, 2>, 2> {
        array<array<bool, 2>, 2> rights{};
        rights[0].fill(false);
        rights[1].fill(false);

        if (castlingRights == "-") return rights;

        for (char c : castlingRights) {
            switch (c) {
                case 'K': rights[(int)Color::White][1] = true; break;
                case 'Q': rights[(int)Color::White][0] = true; break;
                case 'k': rights[(int)Color::Black][1] = true; break;
                case 'q': rights[(int)Color::Black][0] = true; break;
            }
        }
        return rights;
    };

    // parses en passant
    auto parseEnPassant = [](const string& s) -> uint8_t {
        if (s == "-") return NO_SQUARE;
        uint8_t file = s[0] - 'a';          
        uint8_t rank = s[1] - '1';        
        return rank * 8 + file;           
    };

    fenParams.castlingRights = parseCastle(castlingString);
    fenParams.enPassantSquare = enPassantString != "-" ? parseEnPassant(enPassantString) : NO_SQUARE;
    fenParams.halfMoves = stoi(halfMovesString);
    fenParams.fullMoves = stoi(fullMovesString);
}

// debug utility functions
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
#pragma once
#include "fen2bitboard.h"

namespace chess {

constexpr bitBoard nA  = 0xFeFeFeFeFeFeFeFe;
constexpr bitBoard nAB = 0xFcFcFcFcFcFcFcFc;
constexpr bitBoard  nH = 0x7f7f7f7f7f7f7f7f;
constexpr bitBoard nGH = 0x3f3f3f3f3f3f3f3f;

constexpr bitBoard nBCDEFGH = 0x0101010101010101;
constexpr bitBoard nABCDEFG = 0x8080808080808080;

struct ChessData{
    int movesQuantity {0};
    bitBoard movesMask {0};
};

class Figure {
    ChessData m_data;
public:
    ChessData getKnightData(int pos);
    ChessData getQueenData(bitBoard pos);
    ChessData getRookData(bitBoard pos);
    ChessData getBishopData(bitBoard pos);
};

}

#pragma once
#include "fen2bitboard.h"
#include "knight_moves.h"

namespace chess {
    std::vector<chess::bitBoard> getFigureMoves(char* fen);
}

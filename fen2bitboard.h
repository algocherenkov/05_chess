#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace chess
{
enum class Piece
{
   whitePawns,
   whiteKnights,
   whiteBishops,
   whiteRooks,
   whiteQueens,
   whiteKing,

   blackPawns,
   blackKnights,
   blackBishops,
   blackRooks,
   blackQueens,
   blackKing,

   chessTypesNumber
};

using bitBoard = unsigned long long;
constexpr int CHESS_LINE_LENGTH = 8;
constexpr int FEN_MAX_LENGTH = 72;

class Fen2BitBoard{
public:
    Fen2BitBoard()
    {
        m_figureMap.emplace('r', Piece::blackRooks);
        m_figureMap.emplace('n', Piece::blackKnights);
        m_figureMap.emplace('b', Piece::blackBishops);
        m_figureMap.emplace('q', Piece::blackQueens);
        m_figureMap.emplace('k', Piece::blackKing);
        m_figureMap.emplace('p', Piece::blackPawns);
        m_figureMap.emplace('R', Piece::whiteRooks);
        m_figureMap.emplace('N', Piece::whiteKnights);
        m_figureMap.emplace('B', Piece::whiteBishops);
        m_figureMap.emplace('Q', Piece::whiteQueens);
        m_figureMap.emplace('K', Piece::whiteKing);
        m_figureMap.emplace('P', Piece::whitePawns);
    }

    std::vector<bitBoard> convert(char *fen);

private:    
    std::unordered_map<char, Piece> m_figureMap;
};
}

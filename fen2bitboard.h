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
constexpr int DRAWBOARD_MAX_LENGTH = 22;

constexpr bitBoard RIGHT_BORDER_MASK = 0x8080808080808080;
constexpr bitBoard LEFT_BORDER_MASK = 0x0101010101010101;
constexpr bitBoard UPPER_BORDER_MASK = 0xFF00000000000000;
constexpr bitBoard BOTTOM_BORDER_MASK = 0x00000000000000FF;

constexpr bitBoard RIGHT_UPPER_BORDER_MASK = 0xFF80808080808080;
constexpr bitBoard RIGHT_BOTTOM_BORDER_MASK = 0x80808080808080FF;
constexpr bitBoard LEFT_UPPER_BORDER_MASK = 0xFF01010101010101;
constexpr bitBoard LEFT_BOTTOM_BORDER_MASK = 0x01010101010101FF;

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
    std::vector<std::string> drawBoard(char* fen);

private:    
    std::vector<std::string> m_board;
    std::unordered_map<char, Piece> m_figureMap;
};
}

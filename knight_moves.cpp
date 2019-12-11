#include "knight_moves.h"
#include <math.h>

namespace chess {

void Figure::countMoves(bitBoard &posBits)
{
    while (posBits != 0)
    {
        posBits &= (posBits - 1);
        m_data.movesQuantity++;
    }
}

ChessData Figure::getQueenData(bitBoard posBits)
{
    bitBoard rookLike = getRookData(posBits).movesMask;
    bitBoard bishopLike = getBishopData(posBits).movesMask;
    m_data.movesMask = rookLike | bishopLike;
    posBits = m_data.movesMask;
    countMoves(posBits);

    return m_data;
}

//works only for one rook in bitBoard
ChessData Figure::getRookData(bitBoard pos)
{
    const auto bitPosition = std::log(pos)/std::log(2);

    int horizontalBitsLine = int(bitPosition) / CHESS_LINE_LENGTH;
    m_data.movesMask = (MOVES_LINE << (CHESS_LINE_LENGTH*horizontalBitsLine))^pos;

    bitBoard verticalBitsLine = pos >> (CHESS_LINE_LENGTH*horizontalBitsLine);

    for(int i = 0; i < CHESS_LINE_LENGTH; i++)
    {
        if(i == horizontalBitsLine)
            continue;
        verticalBitsLine |= verticalBitsLine << CHESS_LINE_LENGTH;
    }

    m_data.movesMask |= verticalBitsLine;
    m_data.movesMask ^= pos;
    pos = m_data.movesMask;
    countMoves(pos);
    return m_data;
}

ChessData Figure::getBishopData(bitBoard pos)
{
    bitBoard leftBottom = pos, leftUpper = pos, rightBottom = pos, rightUpper = pos;

    for(int i = 1; i < CHESS_LINE_LENGTH; i++)
    {
        if(LEFT_BOTTOM_BORDER_MASK & leftBottom)
            break;
        leftBottom |= leftBottom >> 9;        
    }

    for(int i = 1; i < CHESS_LINE_LENGTH; i++)
    {
        if(LEFT_UPPER_BORDER_MASK &leftUpper)
            break;
        leftUpper |= leftUpper << 7;        
    }

    for(int i = 1; i < CHESS_LINE_LENGTH; i++)
    {
        if(RIGHT_BOTTOM_BORDER_MASK & rightBottom)
            break;
        rightBottom |= rightBottom >> 7;        
    }

    for(int i = 1; i < CHESS_LINE_LENGTH; i++)
    {
        if(RIGHT_UPPER_BORDER_MASK &rightUpper)
            break;
        rightUpper |= rightUpper << 9;        
    }

    m_data.movesMask = leftBottom | leftUpper | rightBottom | rightUpper;
    m_data.movesMask ^= pos;
    pos = m_data.movesMask;
    countMoves(pos);
    return m_data;
}

ChessData Figure::getKingData(int pos)
{
    bitBoard kingBits = static_cast<bitBoard>(std::pow(2, pos));
    m_data.movesMask = (nH & (kingBits <<  7 | kingBits >> 1 | kingBits >> 9))
                 |  (nA & (kingBits << 9 | kingBits << 1 | kingBits >> 7))
                 | (kingBits << 8 | kingBits >> 8);

    kingBits = m_data.movesMask;

    countMoves(kingBits);

    return m_data;
}

ChessData Figure::getKnightData(int pos)
{
    bitBoard knightBits = static_cast<bitBoard>(std::pow(2, pos));
    m_data.movesMask = (nGH & (knightBits <<  6 | knightBits >> 10))
                 |  (nH & (knightBits << 15 | knightBits >> 17))
                 | (nA  & (knightBits << 17 | knightBits >> 15))
                 | (nAB & (knightBits << 10 | knightBits >>  6));

    knightBits = m_data.movesMask;

    countMoves(knightBits);

    return m_data;
}
}

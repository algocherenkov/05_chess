#include "knight_moves.h"
#include <math.h>

namespace chess {

ChessData Figure::getKnightData(int pos)
{
    bitBoard knightBits = static_cast<bitBoard>(std::pow(2, pos));
    m_data.movesMask =
            (nBCDEFGH & (knightBits <<  1 | knightBits <<  2 | knightBits <<  3 | knightBits <<  4 | knightBits <<  5 | knightBits <<  6 | knightBits <<  7 |
                         ))
                 |  (nABCDEFG & (knightBits >> 1 | knightBits >> 2 | knightBits >> 3 | knightBits >> 4 | knightBits >> 5 | knightBits >> 6 | knightBits >> 7))
                 | (nA  & (knightBits << 17 | knightBits >> 15))
                 | (nAB & (knightBits << 10 | knightBits >>  6));

    knightBits = m_data.movesMask;

    while (knightBits != 0)
    {
        knightBits &= (knightBits - 1);
        m_data.movesQuantity++;
    }

    return m_data;
}

ChessData Figure::getQueenData(bitBoard posBits)
{
    m_data.movesMask = (nGH & (posBits <<  6 | posBits >> 10))
                 |  (nH & (posBits << 15 | posBits >> 17))
                 | (nA  & (posBits << 17 | posBits >> 15))
                 | (nAB & (posBits << 10 | posBits >>  6));

    posBits = m_data.movesMask;

    while (posBits != 0)
    {
        posBits &= (posBits - 1);
        m_data.movesQuantity++;
    }

    return m_data;
}
}

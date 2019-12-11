#include "queen_rook_bishop.h"
namespace chess {

void cutExtraPositionsAccordingToDirection(bitBoard shiftData, bitBoard& movesMask, int shift, bitBoard dirMask, bool eaterSign)
{
    if(dirMask & shiftData)
        return;

    bool noMovePoint = false;    
    for(int j = 1; j < CHESS_LINE_LENGTH; j++)
    {
        switch (dirMask) {
        case RIGHT_BORDER_MASK:
        case UPPER_BORDER_MASK:
        case RIGHT_UPPER_BORDER_MASK:
        case LEFT_UPPER_BORDER_MASK:

            shiftData <<= shift;
            break;
        case LEFT_BORDER_MASK:
        case BOTTOM_BORDER_MASK:
        case RIGHT_BOTTOM_BORDER_MASK:
        case LEFT_BOTTOM_BORDER_MASK:

            shiftData >>= shift;
            break;
        default:
            break;
        }

        if(noMovePoint)
            movesMask &= ~shiftData;

        if(!(shiftData & movesMask) && !noMovePoint)
        {
            noMovePoint = true;
            if(eaterSign)
                movesMask |= shiftData;
        }

        if(dirMask & shiftData)
            break;
    }
}

void combineResults(std::vector<bitBoard>& tempResults, bitBoard& result)
{
    for(auto& res: tempResults)
        result &= res;
}

std::vector<bitBoard> getFiguresRBQMoves(char *fen)
{
    std::vector<bitBoard> result;
    std::vector<bitBoard> tempResults;
    Fen2BitBoard converter;
    Figure unit;

    auto bitResult = converter.convert(fen);    
    ChessData figureData = unit.getRookData(bitResult[static_cast<int>(Piece::whiteRooks)]);

    for(size_t i = 0; i < static_cast<size_t>(Piece::chessTypesNumber); i++)
    {
        auto tempBitBoard = figureData.movesMask & bitResult[i];
        if(!tempBitBoard)
            continue;

        tempResults.push_back(figureData.movesMask ^ tempBitBoard);

        bool eaterSign = i < 6? false: true;
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults.back(), 1, LEFT_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults.back(), 1, RIGHT_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults.back(), 8, UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults.back(), 8, BOTTOM_BORDER_MASK, eaterSign);
    }

    if(!tempResults.empty())
        combineResults(tempResults, figureData.movesMask);
    result.push_back(figureData.movesMask);

    tempResults.clear();
    unit.clear();
    figureData = unit.getBishopData(bitResult[static_cast<int>(Piece::whiteBishops)]);

    for(size_t i = 0; i < static_cast<size_t>(Piece::chessTypesNumber); i++)
    {
        auto tempBitBoard = figureData.movesMask & bitResult[i];
        if(!tempBitBoard)
            continue;

        tempResults.push_back(figureData.movesMask ^ tempBitBoard);

        bool eaterSign = i < 6? false: true;
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults.back(), 7, LEFT_UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults.back(), 9, RIGHT_UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults.back(), 7, RIGHT_BOTTOM_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults.back(), 9, LEFT_BOTTOM_BORDER_MASK, eaterSign);
    }
    if(!tempResults.empty())
        combineResults(tempResults, figureData.movesMask);
    result.push_back(figureData.movesMask);

    tempResults.clear();
    unit.clear();
    figureData = unit.getQueenData(bitResult[static_cast<int>(Piece::whiteQueens)]);

    for(size_t i = 0; i < static_cast<size_t>(Piece::chessTypesNumber); i++)
    {
        auto tempBitBoard = figureData.movesMask & bitResult[i];
        if(!tempBitBoard)
            continue;

        tempResults.push_back(figureData.movesMask ^ tempBitBoard);

        bool eaterSign = i < 6? false: true;
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 1, LEFT_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 1, RIGHT_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 8, UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 8, BOTTOM_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 7, LEFT_UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 9, RIGHT_UPPER_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 7, RIGHT_BOTTOM_BORDER_MASK, eaterSign);
        cutExtraPositionsAccordingToDirection(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults.back(), 9, LEFT_BOTTOM_BORDER_MASK, eaterSign);
    }
    if(!tempResults.empty())
        combineResults(tempResults, figureData.movesMask);
    result.push_back(figureData.movesMask);

    return result;
}
}

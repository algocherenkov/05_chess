#include "queen_rook_bishop.h"
namespace chess {

enum class ShiftDirection {
    RIGHT_SHIFT,
    RIGHT_UP_SHIFT,
    LEFT_SHIFT,
    LEFT_UP_SHIFT,
    UP_SHIFT,
    DOWN_SHIFT,
    RIGHT_DOWN_SHIFT,
    LEFT_DOWN_SHIFT,
};

void shiftToDirectionAndCutExtraPositions(bitBoard rookInitPos, bitBoard& movesMask, int shift, ShiftDirection dir, bool eaterSign)
{
    bool noMovePoint = false;
    for(int j = 1; j < CHESS_LINE_LENGTH; j++)
    {
        switch (dir) {
        case ShiftDirection::RIGHT_SHIFT:
        case ShiftDirection::UP_SHIFT:
        case ShiftDirection::RIGHT_UP_SHIFT:
        case ShiftDirection::LEFT_UP_SHIFT:
            rookInitPos <<= shift;
            break;
        case ShiftDirection::LEFT_SHIFT:
        case ShiftDirection::DOWN_SHIFT:
        case ShiftDirection::RIGHT_DOWN_SHIFT:
        case ShiftDirection::LEFT_DOWN_SHIFT:
            rookInitPos >>= shift;
            break;
        default:
            break;
        }

        if(noMovePoint)
            movesMask &= ~rookInitPos;

        if(!(rookInitPos & movesMask) && !noMovePoint)
        {
            noMovePoint = true;
            if(eaterSign)
                movesMask |= rookInitPos;
        }

        if(BOARD_EDGE & rookInitPos)
            break;
    }
}

void combineResults(std::vector<bitBoard>& tempResults, bitBoard& result)
{
    for(auto& res: tempResults)
        result &= res;
}

std::vector<bitBoard> getFigureMoves(char *fen)
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
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults[i], 1, ShiftDirection::LEFT_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults[i], 1, ShiftDirection::RIGHT_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults[i], 8, ShiftDirection::UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteRooks)], tempResults[i], 8, ShiftDirection::DOWN_SHIFT, eaterSign);
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
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults[i], 7, ShiftDirection::LEFT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults[i], 9, ShiftDirection::RIGHT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults[i], 7, ShiftDirection::RIGHT_DOWN_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteBishops)], tempResults[i], 9, ShiftDirection::LEFT_DOWN_SHIFT, eaterSign);
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
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 1, ShiftDirection::LEFT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 1, ShiftDirection::RIGHT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 8, ShiftDirection::RIGHT_DOWN_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 8, ShiftDirection::LEFT_DOWN_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 7, ShiftDirection::LEFT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 9, ShiftDirection::RIGHT_UP_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 7, ShiftDirection::RIGHT_DOWN_SHIFT, eaterSign);
        shiftToDirectionAndCutExtraPositions(bitResult[static_cast<int>(Piece::whiteQueens)], tempResults[i], 9, ShiftDirection::LEFT_DOWN_SHIFT, eaterSign);
    }
    if(!tempResults.empty())
        combineResults(tempResults, figureData.movesMask);
    result.push_back(figureData.movesMask);

    return result;
}
}

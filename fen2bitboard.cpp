#include "fen2bitboard.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <assert.h>
#include <math.h>
#include <cctype>

std::vector<converter::bitBoard> converter::Fen2BitBoard::convert(char* fen)
{
    std::vector<bitBoard> board(static_cast<size_t>(Piece::chessTypesNumber));
    char* token = std::strtok(fen, "/");
    int counter = CHESS_TOKEN_MAX_LENGTH - 1;
    while (token != nullptr) {

        for(int i = 0; i < CHESS_TOKEN_MAX_LENGTH; i++)
        {
            if(std::isdigit(token[i]))
            {
                i += token[i];
                continue;
            }

            auto it = m_figureMap.find(token[i]);
            if(it != m_figureMap.end())
            {
                board[static_cast<bitBoard>(it->second)] |=
                        static_cast<bitBoard>(std::pow(2, CHESS_LINE_LENGTH*counter + i));
            }
            else
            {
                assert(false && "No such chess unit");
            }
        }
        counter--;
        token = std::strtok(nullptr, "/");
    }

    return board;
}

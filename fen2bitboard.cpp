#include "fen2bitboard.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <assert.h>
#include <math.h>
#include <cctype>
#include <stdlib.h>

void stripString(char* fen)
{
    std::string data(fen);
    size_t posCarrier = data.find("\r");
    if(posCarrier != std::string::npos)
        data.erase(posCarrier);

    size_t posNewLine = data.find("\n");
    if(posNewLine != std::string::npos)
        data.erase(posNewLine);

    std::strcpy(fen, data.c_str());
}

std::vector<chess::bitBoard> chess::Fen2BitBoard::convert(char* fen)
{
    stripString(fen);
    std::vector<bitBoard> board(static_cast<size_t>(Piece::chessTypesNumber));
    char* token = std::strtok(fen, "/");
    int counter = CHESS_LINE_LENGTH - 1;
    int gap = 0;


    while (token != nullptr) {
        bool prevIsAlpha = false;
        for(int i = 0; i < static_cast<int>(std::strlen(token)); i++)
        {            
            if(std::isdigit(token[i]))
            {
                prevIsAlpha = false;
                gap += std::atoi(&token[i]);
                if(gap == CHESS_LINE_LENGTH)
                    gap = 0;
                continue;
            }

            if(gap && !prevIsAlpha)
                gap -= 1;

            auto it = m_figureMap.find(token[i]);
            if(it != m_figureMap.end())
            {
                board[static_cast<bitBoard>(it->second)] |=
                        static_cast<bitBoard>(std::pow(2, CHESS_LINE_LENGTH*counter + i + gap));
                prevIsAlpha = true;
            }
            else
            {
                assert(false && "No such chess unit");
            }
        }
        gap = 0;
        counter--;
        token = std::strtok(nullptr, "/");
    }

    return board;
}

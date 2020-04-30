#include "fen2bitboard.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <assert.h>
#include <math.h>
#include <cctype>
#include <stdlib.h>

constexpr char border = '|';
constexpr char dot = '.';
constexpr char space = ' ';
constexpr char plus = '+';
constexpr char minus = '-';

void stripString(char* fen, bool stripAppendix = false)
{
    std::string data(fen);

    if (stripAppendix)
    {
        auto pos = data.find(' ');
        
        if (pos != std::string::npos)
        {
            data.erase(pos);
            std::strcpy(fen, data.c_str());
            return;
        }
    }

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

void drawClearBoard(std::vector<std::string>& board)
{
    char number = '8';    
    char letter = 'a';    

    board[0].push_back(space);
    board[0].push_back(space);

    board[0].push_back(plus);
    for (int i = 0; i < 17; i++)
        board[0].push_back(minus);
    board[0].push_back(plus);

    for (int i = 1; i < 9; i++)
    {
        board[i].push_back(number);
        board[i].push_back(space);
        board[i].push_back(border);

        for (int j = 0; j < 8; j++)
        {
            board[i].push_back(space);
            board[i].push_back(dot);
        }

        board[i].push_back(space);
        board[i].push_back(border);
        number--;
    }

    board[9].push_back(space);
    board[9].push_back(space);

    board[9].push_back(plus);
    for (int i = 0; i < 17; i++)
        board[9].push_back(minus);
    board[9].push_back(plus);

    for(int i = 0; i < 4; i++)
        board[10].push_back(space);

    for (int i = 0; i < 7; i++)
    {
        board[10].push_back(letter++);
        board[10].push_back(space);
    }
    board[10].push_back(letter);
}

std::vector<std::string> chess::Fen2BitBoard::drawBoard(char* fen)
{
    std::vector<std::string> result;
    result.resize(11);

    drawClearBoard(result);

    stripString(fen, true);
    char* token = std::strtok(fen, "/");
    int horizontalCounter = 1;

    while (token != nullptr) {
        bool prevIsAlpha = false;
        int gap = 0;
        std::string tempLine;
        tempLine.resize(16, dot);

        for (int i = 0; i < static_cast<int>(std::strlen(token)); i++)
        {
            if (std::isdigit(token[i]))
            {
                prevIsAlpha = false;
                gap += std::atoi(&token[i]);
                if (gap == CHESS_LINE_LENGTH * 2)
                    gap = 0;
                continue;
            }

            if (gap && !prevIsAlpha)
                gap -= 1;

            tempLine[i + gap] = token[i];

            prevIsAlpha = true;
        }
        
        for (int i = 1; i < tempLine.size(); i += 2)
            tempLine.insert(i, " ");

        result[horizontalCounter].replace(result[horizontalCounter].begin() + 4, result[horizontalCounter].begin() + 19, 
            tempLine.begin(), tempLine.begin() + 15);
        horizontalCounter++;
        token = std::strtok(nullptr, "/");
    }

    return result;
}

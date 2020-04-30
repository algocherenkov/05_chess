#include <iostream>
#include "fen2bitboard.h"
#include "knight_moves.h"
#include "queen_rook_bishop.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>
#include <fstream>

constexpr int TEST_COUNT = 10;

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(FEN_2_BitBoard)
{
    chess::Fen2BitBoard instance;
    char* buffer = new char[chess::FEN_MAX_LENGTH];
    std::vector<chess::bitBoard> output(static_cast<size_t>(chess::Piece::chessTypesNumber));
    std::string filename = "../../../0.BITS/1744.0.Bitboard - FEN/test.0.in";
    char* digit = new char[1];
    digit[0] = '0';
    digit[1] = '\0';

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        std::ifstream file(filename.c_str());
        if (file.is_open())
        {
            file.getline(buffer, chess::FEN_MAX_LENGTH,'\n');
            output = instance.convert(buffer);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        filename.replace(filename.find("in"), strlen("in"), "out");
        file.open(filename.c_str());
        if (file.is_open())
        {
            chess::bitBoard temp;
            for(size_t i = 0; i < static_cast<size_t>(chess::Piece::chessTypesNumber); i++)
            {
                file >> temp;
                BOOST_CHECK_MESSAGE(output[i] == temp,
                                    "FEN was converted wrong: convertd value - " << output[i] << ", real - " << temp
                                    << ", test name - " << filename);
            }
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(43, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(knight_moves_masks)
{
    constexpr size_t DATA_NUMBER = 2;
    std::string filename = "../../../0.BITS/3710.0.Bitboard - knight/test.0.in";
    char* digit = new char[1];
    digit[0] = '0';
    digit[1] = '\0';

    int input = 0;
    chess::Figure knight;
    chess::ChessData moves;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        std::ifstream file(filename.c_str());
        if (file.is_open())
        {
            file >> input;
            moves = knight.getKnightData(input);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        filename.replace(filename.find("in"), strlen("in"), "out");
        file.open(filename.c_str());
        if (file.is_open())
        {
            chess::bitBoard temp[2];
            for(size_t i = 0; i < DATA_NUMBER; i++)
            {
                file >> temp[i];
            }
            BOOST_CHECK_MESSAGE(moves.movesQuantity == static_cast<int>(temp[0]),
                                "wrong moves quantity: expected - " << temp[0] << ", real - " << moves.movesQuantity
                                << ", test name - " << filename);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(46, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
        knight.clear();
    }
}

BOOST_AUTO_TEST_CASE(queen_rook_bishop_moves_masks)
{    
    char* buffer = new char[chess::FEN_MAX_LENGTH];
    std::string filename = "../../../0.BITS/3710.0.Bitboard - queen/test.0.in";

    char* digit = new char[1];
    digit[0] = '0';
    digit[1] = '\0';

    std::vector<chess::bitBoard> result;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        std::ifstream file(filename.c_str());
        if (file.is_open())
        {
            file.getline(buffer, chess::FEN_MAX_LENGTH,'\n');
            result = chess::getFiguresRBQMoves(buffer);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        filename.replace(filename.find("in"), strlen("in"), "out");
        file.open(filename.c_str());
        if (file.is_open())
        {
            chess::bitBoard temp;
            for(size_t i = 0; i < result.size(); i++)
            {
                file >> temp;
                BOOST_CHECK_MESSAGE(result[i] == temp,
                                    "number " << i << ", error: result value - " << result[i] << ", real - " << temp
                                    << ", test name - " << filename);
            }
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(45, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(king_moves_masks)
{
    constexpr size_t DATA_NUMBER = 2;
    std::string filename = "../../../0.BITS/3710.0.Bitboard - king/test.0.in";

    char* digit = new char[1];
    digit[0] = '0';
    digit[1] = '\0';

    int input = 0;
    chess::Figure king;
    chess::ChessData moves;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        std::ifstream file(filename.c_str());
        if (file.is_open())
        {
            file >> input;
            moves = king.getKingData(input);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        filename.replace(filename.rfind("in"), strlen("in"), "out");
        file.open(filename.c_str());
        if (file.is_open())
        {
            chess::bitBoard temp[2];
            for(size_t i = 0; i < DATA_NUMBER; i++)
            {
                file >> temp[i];
            }
            BOOST_CHECK_MESSAGE(moves.movesQuantity == static_cast<int>(temp[0]),
                                "wrong moves quantity: expected - " << temp[0] << ", real - " << moves.movesQuantity
                                << ", test name - " << filename);
            BOOST_CHECK_MESSAGE(moves.movesMask == temp[1],
                                "wrong mask: expected - " << temp[1] << ", real - " << moves.movesMask
                                << ", test name - " << filename);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(44, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(FEN_to_ASCII)
{
    constexpr size_t DATA_NUMBER = 11; 
    std::string filename = "../../../1.FEN/1743.1.FEN - ASCII/test.0.in";
    
    chess::Fen2BitBoard instance;
    std::vector<std::string> board;
    char* buffer = new char[chess::FEN_MAX_LENGTH];

    char* digit = new char[1];
    digit[0] = '0';
    digit[1] = '\0';

    int input = 0;

    for(int i = 0; i < TEST_COUNT; i++)
    {
        std::ifstream file(filename.c_str());
        if (file.is_open())
        {
            file.getline(buffer, chess::FEN_MAX_LENGTH, '\n');
            board = instance.drawBoard(buffer);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        filename.replace(filename.rfind("in"), strlen("in"), "out");
        file.open(filename.c_str());
        if (file.is_open())
        {
            char* answer = new char[chess::DRAWBOARD_MAX_LENGTH];
            for (size_t i = 0; i < DATA_NUMBER; i++)
            {
                file.getline(answer, chess::DRAWBOARD_MAX_LENGTH, '\n');

                BOOST_CHECK_MESSAGE(memcmp(answer, board[i].data(), board[i].size()) == 0,
                    "wrong string: expected - " << answer << ", real - " << std::string(board[i].data(), board[i].data() + chess::DRAWBOARD_MAX_LENGTH)
                    << ", test name - " << filename);
            }
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(39, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}
BOOST_AUTO_TEST_SUITE_END()

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
using namespace std;

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(FEN_2_BitBoard)
{
    chess::Fen2BitBoard instance;
    char* buffer = new char[chess::FEN_MAX_LENGTH];
    std::vector<chess::bitBoard> output(static_cast<size_t>(chess::Piece::chessTypesNumber));
    std::string filename = "./fen2bitboard/test.0.in";
    char* digit = new char[1];
    digit[0] = '0';

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        ifstream file(filename.c_str());
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
        filename.replace(20, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(knight_moves_masks)
{
    constexpr size_t DATA_NUMBER = 2;
    std::string filename = "./knight_moves/test.0.in";
    char* digit = new char[1];
    digit[0] = '0';
    int input = 0;
    chess::Figure knight;
    chess::ChessData moves;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        ifstream file(filename.c_str());
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
        filename.replace(20, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(queen_rook_bishop_moves_masks)
{    
    char* buffer = new char[chess::FEN_MAX_LENGTH];
    std::string filename = "./queen_rook_bishop_moves/test.0.in";
    std::string digit("0");
    std::vector<chess::bitBoard> result;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        ifstream file(filename.c_str());
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
        filename.replace(31, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}

BOOST_AUTO_TEST_CASE(king_moves_masks)
{
    constexpr size_t DATA_NUMBER = 2;
    std::string filename = "./king_moves/test.0.in";
    char* digit = new char[1];
    digit[0] = '0';
    int input = 0;
    chess::Figure king;
    chess::ChessData moves;

    for(int i = 0; i < TEST_COUNT; i ++)
    {
        ifstream file(filename.c_str());
        if (file.is_open())
        {
            file >> input;
            moves = king.getKingData(input);
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
            BOOST_CHECK_MESSAGE(moves.movesMask == temp[1],
                                "wrong mask: expected - " << temp[1] << ", real - " << moves.movesMask
                                << ", test name - " << filename);
            file.close();
        }
        else
            BOOST_TEST_MESSAGE("Cannot open file\n\n");

        digit[0] += 1;
        filename.replace(20, 1, digit);
        filename.replace(filename.find("out"), strlen("out"), "in");
    }
}
BOOST_AUTO_TEST_SUITE_END()

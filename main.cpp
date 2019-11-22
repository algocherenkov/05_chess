#include <iostream>
#include "fen2bitboard.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>
#include <fstream>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>
using namespace std;

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)
converter::Fen2BitBoard instance;
BOOST_AUTO_TEST_CASE(simple)
{
    char* buffer = new char[converter::FEN_MAX_LENGTH];
    std::vector<converter::bitBoard> output(static_cast<size_t>(converter::Piece::chessTypesNumber));
    ifstream file("test.0.in");
    if (file.is_open())
    {
        file.getline(buffer,converter::FEN_MAX_LENGTH,'\n');
        output = instance.convert(buffer);
        file.close();

    }
    else
        BOOST_TEST_MESSAGE("Файл не открыт\n\n");

}

BOOST_AUTO_TEST_SUITE_END()

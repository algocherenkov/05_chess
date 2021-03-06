cmake_minimum_required(VERSION 3.5)

project(05_chess LANGUAGES CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_BUILD_TYPE DEBUG)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()
include_directories(${Boost_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED
    fen2bitboard.h fen2bitboard.cpp
    knight_moves.h knight_moves.cpp
    queen_rook_bishop.h queen_rook_bishop.cpp)

add_executable(${PROJECT_NAME}_test "main.cpp")

set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_compile_options(lboost_system)

target_link_libraries(${PROJECT_NAME}_test
        ${Boost_LIBRARIES}
        ${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME}_test PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

enable_testing()

add_test(test_version_valid ${PROJECT_NAME}_test)

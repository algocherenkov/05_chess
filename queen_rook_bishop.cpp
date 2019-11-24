#include "queen_rook_bishop.h"
namespace chess {

std::vector<bitBoard> chess::getFigureMoves(char *fen)
{
    Fen2BitBoard converter;
    auto bitResult = converter.convert(fen);
}

}

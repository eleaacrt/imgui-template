#include "headers/Piece.hpp"

string Piece::get_label() const
{
    if (_color == Colors::Black) {
        return _black_label;
    } else if (_color == Colors::White) {
        return _white_label;
    } else {
        return "undefined";
    }
}

int Piece::distance(int x1, int x2) const
{
    return (x2 - x1) ? (x2 - x1) / abs(x2 - x1) : 0;
}
#pragma once
#include <imgui.h>
#include <string>
#include "utils.hpp"

using namespace std;

class Board;

class Piece {
public:
    explicit Piece(Colors color)
        : _color(color) {}

    virtual ~Piece() = default;

    Colors get_color() const { return _color; }
    int    distance(int x1, int x2) const;

    virtual Pieces get_type() const                                                = 0;
    virtual string get_label() const                                               = 0;
    virtual string get_name() const                                                = 0;
    virtual bool   get_moves(Coordinates from, Coordinates to, const Board& board) = 0;

protected:
    string _black_label = "undefined";
    string _white_label = "undefined";
    Colors _color;
};
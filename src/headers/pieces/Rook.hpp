#pragma once

#include "../Piece.hpp"

class Rook : public Piece {
public:
    explicit Rook(Colors color)
        : Piece(color)
    {
        _black_label = "t";
        _white_label = "r";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;
};
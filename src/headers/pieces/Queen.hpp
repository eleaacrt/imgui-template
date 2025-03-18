#pragma once

#include "../Piece.hpp"

class Queen : public Piece {
public:
    explicit Queen(Colors color)
        : Piece(color)
    {
        _black_label = "w";
        _white_label = "q";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;
};
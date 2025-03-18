#pragma once

#include "../Piece.hpp"

class King : public Piece {
public:
    explicit King(Colors color)
        : Piece(color)
    {
        _black_label = "l";
        _white_label = "k";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;

    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;};
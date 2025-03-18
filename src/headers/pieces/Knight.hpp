#pragma once

#include "../Piece.hpp"

class Knight : public Piece {
public:
    explicit Knight(Colors color) : Piece(color) {
        _black_label = "j";
        _white_label = "h";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;

    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;
};
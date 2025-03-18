#pragma once

#include "../Piece.hpp"
#include "../utils.hpp"

class Bishop : public Piece {
public:
    explicit Bishop(Colors color) : Piece(color) {
        _black_label = "n";
        _white_label = "b";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;

    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;};
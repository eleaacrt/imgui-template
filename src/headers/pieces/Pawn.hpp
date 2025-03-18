#pragma once

#include "../Piece.hpp"

class Pawn : public Piece {
public:
    explicit Pawn(Colors color)
        : Piece(color), is_first_move(true)
    {
        _black_label = "o";
        _white_label = "p";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool   get_moves(Coordinates from, Coordinates to, const Board& board) override;
    void   set_first_move();

private:
    bool is_first_move = true;
};

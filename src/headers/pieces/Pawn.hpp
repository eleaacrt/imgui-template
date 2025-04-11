#pragma once

#include "../Piece.hpp"

class Pawn : public Piece {
public:
    explicit Pawn(Colors color)
        : Piece(color), is_first_move(true)
    {
        _black_label = "o";
        _white_label = "p";
        _path_white        = "pawn/pawn.obj";
        _path_black        = "pawn/pawn_b.obj";
        _name        = "pawn";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool   get_moves(Coordinates from, Coordinates to, const Board& board) override;
    void   set_first_move();

    /* --------------------------------
        3D
    -------------------------------- */

    void draw(Colors color) override;
    void render(glmax::Shader& shader, Colors color) override;
    void rotate(Colors color) override;

private:
    bool is_first_move = true;
    Model3D _pawn;
};

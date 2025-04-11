#pragma once

#include "../Piece.hpp"

class Rook : public Piece {
public:
    explicit Rook(Colors color)
        : Piece(color)
    {
        _black_label = "t";
        _white_label = "r";
        _path_white        = "rook/rook.obj";
        _path_black        = "rook/rook_b.obj";
        _name        = "rook";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool   get_moves(Coordinates from, Coordinates to, const Board& board) override;

    /* --------------------------------
            3D
    -------------------------------- */

    void draw(Colors color) override;
    void render(glmax::Shader& shader, Colors color) override;
    void rotate(Colors color) override;

private:
    Model3D _rook;
};
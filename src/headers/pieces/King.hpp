#pragma once

#include "../Piece.hpp"
#include "Model3D.hpp"

class King : public Piece {
public:
    explicit King(Colors color)
        : Piece(color)
    {
        _black_label = "l";
        _white_label = "k";
        _path_white        = "king/king.obj";
        _path_black        = "king/king_b.obj";
        _name        = "king";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;

    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;

    /* --------------------------------
            3D
    -------------------------------- */

    void draw(Colors color) override;
    void render(glmax::Shader& shader, Colors color) override;
    void rotate(Colors color) override;

private:
    Model3D _king;
};
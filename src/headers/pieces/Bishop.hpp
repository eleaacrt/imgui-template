#pragma once

#include "../Piece.hpp"
#include "../utils.hpp"

class Bishop : public Piece {
public:
    explicit Bishop(Colors color)
        : Piece(color)
    {
        _black_label = "n";
        _white_label = "b";
        _path_black        = "bishop/bishop_b.obj";
        _path_white        = "bishop/bishop.obj";
        _name        = "bishop";
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
    Model3D _bishop;
};
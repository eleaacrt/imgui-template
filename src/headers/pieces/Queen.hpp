#pragma once

#include "../Piece.hpp"

class Queen : public Piece {
public:
    explicit Queen(Colors color)
        : Piece(color)
    {
        _black_label = "w";
        _white_label = "q";
        _path_white = "queen/queen.obj";
        _path_black = "queen/queen_b.obj";
        _name = "queen";
    }

    Pieces get_type() const override;
    string get_label() const override;
    string get_name() const override;
    bool get_moves(Coordinates from, Coordinates to, const Board& board) override;

    /* --------------------------------
            3D
    -------------------------------- */

    void draw(Colors color) override;
    void render(glmax::Shader& shader) override;

    private:
    Model3D _queen;

};
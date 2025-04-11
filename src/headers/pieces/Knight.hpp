#pragma once

#include "../Piece.hpp"

class Knight : public Piece {
public:
    explicit Knight(Colors color) : Piece(color) {
        _black_label = "j";
        _white_label = "h";
        _path_white = "knight/knight.obj";
        _path_black = "knight/knight_b.obj";
        _name = "knight";
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
    Model3D _knight;

};
#pragma once
#include <imgui.h>
#include <string>
#include "Model3D.hpp"
#include "Shader.hpp"
#include "utils.hpp"

using namespace std;

class Board;

class Piece {
public:
    explicit Piece(Colors color)
        : _color(color) {}

    virtual ~Piece() = default;

    Colors get_color() const { return _color; }
    int    distance(int x1, int x2) const;

    virtual Pieces get_type() const                                                = 0;
    virtual string get_label() const                                               = 0;
    virtual string get_name() const                                                = 0;
    virtual bool   get_moves(Coordinates from, Coordinates to, const Board& board) = 0;

    /* --------------------------------
            3D
    -------------------------------- */

    virtual void draw(Colors color)                          = 0;
    virtual void render(glmax::Shader& shader, Colors color) = 0;
    virtual void rotate(Colors color)                        = 0;

    void set_model_matrix(const glm::mat4& model) { _model_matrix = model; }

    Coordinates get_position() const { return _position; }
    void        set_position(const Coordinates& position) { _position = position; }

protected:
    string _black_label = "undefined";
    string _white_label = "undefined";
    Colors _color;

    /* --------------------------------
            3D
    -------------------------------- */

    string _path_black;
    string _path_white;
    string _name;

    glm::mat4 _model_matrix = glm::mat4(1.0f);

    Coordinates _position;
};
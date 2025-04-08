#include "headers/pieces/King.hpp"

Pieces King::get_type() const
{
    return Pieces::King;
}

string King::get_label() const
{
    return (_color == Colors::Black) ? _black_label : _white_label;
}

string King::get_name() const
{
    return "King";
}

bool King::get_moves(Coordinates from, Coordinates to, const Board& board)
{
    if (from.x == to.x && from.y == to.y)
    {
        return false;
    }
    
    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);
    return (dx <= 1 && dy <= 1);
}

/* --------------------------------
        3D
-------------------------------- */

void King::draw(Colors color)
{
    color == Colors::Black ? _king.load_mesh(_path_black, _name) : _king.load_mesh(_path_white, _name);
    _king.setup_buffers();
}

void King::render(glmax::Shader& shader)
{
    shader.set_uniform_matrix_4fv("model", _model_matrix);
    _king.render(shader);
}
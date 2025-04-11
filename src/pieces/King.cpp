#include "headers/pieces/King.hpp"
#include "glm/ext/matrix_transform.hpp"

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

void King::render(glmax::Shader& shader, Colors color)
{
    rotate(color);
    shader.set_uniform_matrix_4fv("model", _model_matrix);
    _king.render(shader);
}

void King::rotate(Colors color)
{
    // rotation
    if (_color == Colors::White)
    {
        // Rotation de 90° vers la droite (axe Y)
        _model_matrix = glm::rotate(_model_matrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if (_color == Colors::Black)
    {
        // Rotation de 90° vers la gauche (axe Y)
        _model_matrix = glm::rotate(_model_matrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}
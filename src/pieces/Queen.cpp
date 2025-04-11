#include "headers/pieces/Queen.hpp"
#include "headers/Board.hpp"
#include "glm/ext/matrix_transform.hpp"

Pieces Queen::get_type() const
{
    return Pieces::Queen;
}

string Queen::get_label() const
{
    return (_color == Colors::Black) ? _black_label : _white_label;
}

string Queen::get_name() const
{
    return "Queen";
}

bool Queen::get_moves(Coordinates from, Coordinates to, const Board& board)
{
    if (from.x == to.x && from.y == to.y)
    {
        return false;
    }

    int dx = to.x - from.x;
    int dy = to.y - from.y;

    // Vérifiez que le mouvement est en ligne droite ou en diagonale
    if (dx != 0 && dy != 0 && abs(dx) != abs(dy))
    {
        return false;
    }

    // Vérifiez les cases intermédiaires pour les pièces bloquantes
    int step_x = (dx != 0) ? dx / abs(dx) : 0;
    int step_y = (dy != 0) ? dy / abs(dy) : 0;

    for (int i = 1; i < max(abs(dx), abs(dy)); ++i)
    {
        int intermediate_x  = from.x + i * step_x;
        int intermediate_y  = from.y + i * step_y;
        int intermediate_id = board.at(intermediate_x, intermediate_y);

        if (board.get_piece(intermediate_id) != nullptr)
        {
            return false;
        }
    }

    return true;
}

/* --------------------------------
        3D
-------------------------------- */

void Queen::draw(Colors color)
{
    color == Colors::Black ? _queen.load_mesh(_path_black, _name) : _queen.load_mesh(_path_white, _name);
    _queen.setup_buffers();
}

void Queen::render(glmax::Shader& shader, Colors color)
{
    rotate(color);
    shader.set_uniform_matrix_4fv("model", _model_matrix);
    _queen.render(shader);
}


void Queen::rotate(Colors color)
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
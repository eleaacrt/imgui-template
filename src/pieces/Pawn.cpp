#include "headers/pieces/Pawn.hpp"
#include "headers/Board.hpp"
#include "headers/utils.hpp"

Pieces Pawn::get_type() const
{
    return Pieces::Pawn;
}

string Pawn::get_label() const
{
    return (_color == Colors::Black) ? _black_label : _white_label;
}

string Pawn::get_name() const
{
    return "Pawn";
}

void Pawn::set_first_move()
{
    is_first_move = false;
}

bool Pawn::get_moves(Coordinates from, Coordinates to, const Board& board)
{
    if (from.x == to.x && from.y == to.y)
    {
        return false;
    }

    int dy        = to.y - from.y;
    int dx        = to.x - from.x;
    int direction = (_color == Colors::White) ? -1 : 1;

    if (dx == 0)
    {
        // Vérifiez si le pion peut avancer de 2 cases lors de son premier coup
        if (is_first_move)
        {
            if (dy == 2 * direction)
            {
                // Vérifiez que la case intermédiaire est vide
                int intermediate_y = from.y + direction;
                if (board.get_piece(board.at(from.x, intermediate_y)) == nullptr && board.get_piece(board.at(to.x, to.y)) == nullptr)
                {
                    return true;
                }
            }
        }

        // Vérifiez si le pion peut avancer d'une case
        if (dy == direction && board.get_piece(board.at(to.x, to.y)) == nullptr)
        {
            return true;
        }
    }
    else if (abs(dx) == 1 && dy == direction)
    {
        // Vérifiez si le pion peut capturer une pièce en diagonale
        if (board.get_piece(board.at(to.x, to.y)) != nullptr && board.get_piece(board.at(to.x, to.y))->get_color() != _color)
        {
            return true;
        }
    }

    return false;
}

/* --------------------------------
        3D
-------------------------------- */

void Pawn::draw(Colors color)
{
    color == Colors::Black ? _pawn.load_mesh(_path_black, _name) : _pawn.load_mesh(_path_white, _name);
    _pawn.setup_buffers();
}

void Pawn::render(glmax::Shader& shader)
{
    shader.set_uniform_matrix_4fv("model", _model_matrix);
    _pawn.render(shader);
}
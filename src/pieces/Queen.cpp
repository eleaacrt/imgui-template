#include "headers/pieces/Queen.hpp"
#include "headers/Board.hpp"

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
#include "headers/Board.hpp"
#include <imgui.h>
#include <cstddef>
#include <glm/gtc/matrix_transform.hpp>
#include "headers/App.hpp"
#include "headers/utils.hpp"

void Board::draw_box(int id, ImVec4 color, const string& label) const
{
    ImGui::PushStyleColor(ImGuiCol_Button, color);
    ImGui::PushStyleColor(ImGuiCol_Text, {0.f, 0.f, 0.f, 1.f});
    ImGui::PushID(id);
    ImGui::Button(label.c_str(), ImVec2{30.f, 30.f});
    ImGui::PopID();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
}

int Board::at(int x, int y) const
{
    return (y * _board_size + x);
}

Coordinates Board::id_to_coord(int id) const
{
    Coordinates coord;
    coord.x = id % _board_size; // Colonne
    coord.y = id / _board_size; // Ligne
    return coord;
}

int Board::distance(int x1, int x2) const
{
    return (x2 - x1) ? (x2 - x1) / abs(x2 - x1) : 0;
}

void Board::draw_board()
{
    for (int y = 0; y < _board_size; ++y)
    {
        draw_row(y);
    }
}

void Board::draw_row(int y)
{
    for (int x = 0; x < _board_size; ++x)
    {
        draw_cell(x, y);
        if (x != (_board_size - 1))
        {
            ImGui::SameLine();
        }
    }
}

void Board::draw_cell(int x, int y)
{
    int    id    = at(x, y);
    ImVec4 color = ((x + y) % 2 == 0) ? _color_1 : _color_2;

    if (_is_clicked)
    {
        if (id == at(_from.x, _from.y))
        {
            color = ImVec4(0.5f, 0.5f, 0.5f, 1.f);
        }

        if (check_valid_move(x, y))
        {
            highlight_cell(id, color);
        }
    }

    if (_board[id] == nullptr)
    {
        draw_box(id, color, "");
    }
    else
    {
        draw_box(id, color, _board[id]->get_label());
    }

    if (ImGui::IsItemClicked())
    {
        handle_click(x, y);
    }
}

void Board::highlight_cell(int id, ImVec4& color) const
{
    if (check_empty_cell(id))
    {
        color = ImVec4(0.01f, 0.7f, 0.4f, 1.f);
    }
    else
    {
        color = ImVec4(1.f, 0.f, 0.f, 1.f);
    }
}

bool Board::check_valid_move(int x, int y)
{
    int         from = at(_from.x, _from.y);
    int         to   = at(x, y);
    Coordinates path = {.x = x, .y = y};

    // if it's the same color, you cannot eat the piece
    if (_board[to] && (_board[from]->get_color() == _board[to]->get_color()))
    {
        return false;
    }

    return _board[from]->get_moves(_from, path, *this);
}

void Board::set_coordinates(int x, int y, Coordinates& coord)
{
    coord = {.x = x, .y = y};
}

void Board::move_piece(int to)
{
    int from = at(_from.x, _from.y);

    if (_board[from]->get_type() == Pieces::Pawn)
    {
        dynamic_cast<Pawn*>(_board[from].get())->set_first_move();
    }

    _board[to]   = std::move(_board[from]);
    _board[from] = nullptr;
    set_coordinates(-1, -1, _from);
    set_coordinates(-1, -1, _to);
    set_player();
}

Piece* Board::get_piece(int id) const
{
    return _board[id].get();
}

bool Board::check_player(int id) const
{
    Colors clicked_piece = _board[id]->get_color();
    return clicked_piece == _current_player;
}

bool Board::check_empty_cell(int id) const
{
    // check if a cell is empty
    return _board[id] == nullptr;
}

void Board::set_player()
{
    // reset current player (black to white and white to black)
    _current_player == Colors::White ? _current_player = Colors::Black : _current_player = Colors::White;
}

void Board::reset_turn()
{
    // reset turn coordinates to -1
    set_coordinates(-1, -1, _from);
    set_coordinates(-1, -1, _to);
    _is_clicked = false;
}

void Board::handle_click(int x, int y)
{
    // if a cell is NOT selected
    if (!_is_clicked)
    {
        // convert the x,y coord in an id
        int from = at(x, y);

        // check if the right color is playing or if the cell is empty
        if (check_empty_cell(from) || !check_player(from))
        {
            return;
        }

        // init the piece's coordinates 'from'
        set_coordinates(x, y, _from);

        _is_clicked = true;
    }

    // if a cell IS selected
    else
    {
        set_coordinates(x, y, _to);

        int from = at(_from.x, _from.y);
        int to   = at(_to.x, _to.y);

        if (check_valid_move(_to.x, _to.y))
        {
            move_piece(to);
            reset_turn();
        }
    }
}

/* --------------------------------
            3D
-------------------------------- */

void Board::draw_board_3D()
{
    _board3D.load_mesh(_path, _name);
    _board3D.setup_buffers();
}

void Board::render(glmax::Shader& shader)
{
    _board3D.render(shader);
}

void Board::draw_pieces_3D()
{
    // for (const auto& piece : _board)
    for (size_t id = 0; id < _board.size(); id++)
    {
        if (_board[id] != nullptr)
        {
            _board[id]->draw(_board[id]->get_color());
        }
    }
}

void Board::render_pieces_3D(glmax::Shader& shader)
{
    for (size_t id = 0; id < _board.size(); id++)
    {
        if (_board[id] != nullptr)
        {
            Coordinates to    = id_to_coord(id);
            glm::mat4   model = glm::mat4(1.0f);
            float       x     = 2 * to.x - _board_size + 1;
            float       y     = 2 * to.y - _board_size + 1;
            model             = glm::translate(model, glm::vec3(x, 0.0f, y));
            _board[id]->set_model_matrix(model);
            _board[id]->render(shader);
        }
    }
}
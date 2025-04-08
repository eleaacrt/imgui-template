#pragma once

#include <imgui.h>
#include <array>
#include <memory>
#include "Model3D.hpp"
#include "Piece.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "utils.hpp"

using namespace std;

class Board {
public:
    Board()  = default;
    ~Board() = default;

    int at(int x, int y) const;
    Coordinates id_to_coord(int id) const;
    int distance(int x1, int x2) const;

    void draw_board();
    void create_pieces() const;
    void draw_box(int id, ImVec4 color, const string& label) const;
    void handle_click(int x, int y);
    void move_piece(int to);
    void set_player();
    void set_coordinates(int x, int y, Coordinates& coord);
    void reset_turn();
    void highlight_cell(int id, ImVec4& border_color) const;

    bool check_player(int id) const;
    bool check_empty_cell(int id) const;
    bool check_valid_move(int x, int y);

    Piece* get_piece(int id) const;

    /* --------------------------------
                3D
    -------------------------------- */

    void draw_board_3D();
    void render(glmax::Shader& shader);

    void draw_pieces_3D();
    void render_pieces_3D(glmax::Shader& shader);

private:
    void draw_row(int y);
    void draw_cell(int x, int y);

    int    _board_size = 8;
    ImVec4 _color_1    = {0.482353f, 0.407843f, 0.933333f, 1.f};
    ImVec4 _color_2    = {0.9019608f, 0.9019608f, 0.980392f, 1.f};

    Coordinates _from, _to;

    // clang-format off
    std::array<std::unique_ptr<Piece>, 64> _board = {
        make_unique<Rook>(Colors::Black), make_unique<Knight>(Colors::Black), make_unique<Bishop>(Colors::Black), make_unique<Queen>(Colors::Black), make_unique<King>(Colors::Black), make_unique<Bishop>(Colors::Black), make_unique<Knight>(Colors::Black), make_unique<Rook>(Colors::Black),
        make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black), make_unique<Pawn>(Colors::Black),
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White), make_unique<Pawn>(Colors::White),
        make_unique<Rook>(Colors::White), make_unique<Knight>(Colors::White), make_unique<Bishop>(Colors::White), make_unique<Queen>(Colors::White), make_unique<King>(Colors::White), make_unique<Bishop>(Colors::White), make_unique<Knight>(Colors::White), make_unique<Rook>(Colors::White),
    };
    // clang-format on

    bool _is_clicked = false;

    Colors _current_player = Colors::White;

    /* --------------------------------
            3D
    -------------------------------- */

    Model3D _board3D;

    string _path = "board/board.obj";
    string _name = "board";
};

#pragma once

#include <imgui.h>
#include <iostream>

enum class Colors {
    White,
    Black
};

inline std::ostream& operator<<(std::ostream& os, const Colors& color)
{
    switch (color)
    {
    case Colors::White:
        os << "White";
        break;
    case Colors::Black:
        os << "Black";
        break;
    }
    return os;
}

enum class Pieces {
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Pawn
};

struct Coordinates {
    int x = -1;
    int y = -1;
};

inline void load_font(const std::string& path, const float size)
{
    ImGuiIO& io = ImGui::GetIO();
    std::cout << "Trying to load font... " << "\n";
    if (io.Fonts->AddFontFromFileTTF(path.c_str(), size))
        std::cout << "Font successfully loaded : " << path << "\n";
    else
        std::cout << "Failed to load font: " << path << " :(" << "\n";
}
#pragma once

#include <imgui.h>
#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Piece.hpp"
#include "glimac/Program.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "utils.hpp"

using namespace std;

class Board3D {
public:
    Board3D()  = default;
    ~Board3D() = default;

    void initBoard3D();
    void drawBoard3D();
    void deleteBuffers3D();

private:
    int    n_triangles = 100;
    GLuint vao;
    GLuint vbo;

    struct Vertex2DColor {
        glm::vec2 position;
        glm::vec3 color;
        Vertex2DColor() {};
        Vertex2DColor(glm::vec2 position, glm::vec3 color)
            : position(position), color(color) {};
    };

    std::vector<Vertex2DColor> vertices = {};
};

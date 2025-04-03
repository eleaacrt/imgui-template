#pragma once

#include <imgui.h>
#include <glm/glm.hpp>
#include <vector>
#include "glimac/Program.hpp"
#include "headers/Board.hpp"
#include "headers/Board3D.hpp"
#include "headers/utils.hpp"

using namespace std;

class App {
public:
    App()  = default;
    ~App() = default;

    void init() const;
    void update(int argc, char** argv);

    // 3D
    void drawBoard3D();
    void initBoard3D();

private:
    Board   board;
    Board3D board3D;
    Colors  player = Colors::White;
};

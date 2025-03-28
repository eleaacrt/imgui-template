#pragma once

#include <imgui.h>
#include "headers/Board.hpp"
#include "headers/utils.hpp"
#include <vector>

using namespace std;

class App {
public:
    App()  = default;
    ~App() = default;

    void init() const;
    void update(int argc, char** argv);

private:
    Board  board;
    Colors player = Colors::White;
};

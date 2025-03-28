#include <imgui.h>
#include "headers/App.hpp"


int main(int argc, char** argv)
{
    App app;
    app.init();
    app.update( argc, argv);
}
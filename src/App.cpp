#include "headers/App.hpp"
#include <glm/glm.hpp>
#include <optional>
#include <quick_imgui/quick_imgui.hpp>
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"

/* ----------------------

LEARN OPENGL -> WEBSITE

---------------------- */

void App::init() const
{
}

void App::update(int argc, char** argv)
{
    glimac::FilePath               applicationPath(argv[0]);
    std::optional<glimac::Program> program;

    quick_imgui::loop(
        "",
        {
            .init         = [&]() {
                load_font(applicationPath.dirPath() + "assets/font/CHEQ_TT.TTF", 64.0f);
                program =
                    loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl", applicationPath.dirPath() + "shaders/triangle.fs.glsl");
                program->use();
                board3D.initBoard3D(); },
            .loop         = [&]() {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    std::cout << "right click" << '\n';
                    board.reset_turn();
                    // return;
                }
                board.draw_board(); 
                board3D.drawBoard3D(); },
            .key_callback = [](int key, int scancode, int action, int mods) {
                // std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n';
            },
            .mouse_button_callback = [](int button, int action, int mods) {
                // std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n';
            },
            .cursor_position_callback = [](double xpos, double ypos) {
                // std::cout << "Position: " << xpos << ' ' << ypos << '\n';
            },
            .scroll_callback = [](double xoffset, double yoffset) {
                // std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n';
            },
            .window_size_callback = [](int width, int height) {
                // std::cout << "Resized: " << width << ' ' << height << '\n';
            },
        }
    );
    board3D.deleteBuffers3D();
}

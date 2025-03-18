#include "headers/App.hpp"
#include <quick_imgui/quick_imgui.hpp>

void App::init() const
{
}

void App::update()
{
    quick_imgui::loop(
        "chess game",
        {
            .init                     = [&]() {            load_font("../../src/assets/font/CHEQ_TT.TTF", 64.0f);
                ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f); },
            .loop                     = [&]() {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    std::cout << "right click" << '\n';
                    board.reset_turn();
                    // return;
                }
                board.draw_board(); },
            .key_callback             = [](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [](double xpos, double ypos) { std::cout << "Position: " << xpos << ' ' << ypos << '\n'; },
            .scroll_callback          = [](double xoffset, double yoffset) { std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n'; },
            .window_size_callback     = [](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}

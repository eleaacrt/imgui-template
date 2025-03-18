#include "headers/App.hpp"
#include <quick_imgui/quick_imgui.hpp>

void App::init() const
{
}

void App::update()
{
    // update the app
    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {
            load_font("../../src/assets/font/CHEQ_TT.TTF", 64.0f);
            ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f); },
        /* loop: */
        [&]() {
            ImGui::Begin("CHESS GAME");

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                std::cout << "right click" << '\n';
                board.reset_turn();
                // return;
            }

            board.draw_board();

            ImGui::End();
        }
    );
}

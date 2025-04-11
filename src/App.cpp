#include "headers/App.hpp"
#include <imgui.h>
#include <Camera.hpp>
#include <Shader.hpp>
#include <glm/glm.hpp>
#include <optional>
#include <quick_imgui/quick_imgui.hpp>
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"
#include "glm/ext/matrix_clip_space.hpp"

/* ----------------------

LEARN OPENGL -> WEBSITE

---------------------- */

void App::init() const
{
}

// void App::load_mesh(vector<pair<string, string>> model_paths)
// {
//     for (const auto& [path, name] : model_paths)
//     {
//         Model3D model;
//         model.load_mesh(path, name);
//         model.setup_buffers();
//         models.push_back(model);
//     }
// }

// void App::render(glmax::Shader& shader) const
// {
//     for (auto& model : models)
//     {
//         model.render(shader);
//     }
// }

void App::update(int argc, char** argv)
{
    glimac::FilePath               applicationPath(argv[0]);
    std::optional<glimac::Program> program;

    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};

    quick_imgui::loop(
        "",
        {
            .init = [&]() {
                load_font(applicationPath.dirPath() + "assets/font/CHEQ_TT.TTF", 16.0f);
                // program =
                //     loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl", applicationPath.dirPath() + "shaders/triangle.fs.glsl");
                // program->use();
                // board3D.initBoard3D();
                shader.load_shader("model.vs.glsl", "model.fs.glsl");

                board.draw_board_3D();
                board.draw_pieces_3D(); },

            .loop = [&]() {
                //                

                glClearColor(0.f, 0.f, 0.f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //
                glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 200.0f);
                shader.use();

                // MVP
                shader.set_uniform_matrix_4fv("model", glm::mat4(0.7f));
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);

                // LIGHT SETTINGS
                shader.set_uniform_3fv("lightPos", glm::vec3(15.0f, 3.0f, 1.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(0.9f, 0.8f, 0.7f));

                shader.set_uniform_3fv("light2Pos", glm::vec3(-15.0f, 4.0f, 1.0f));
                shader.set_uniform_3fv("light2Color", glm::vec3(0.5f, 0.5f, 1.f));

                // CAMERA SETTINGS
                shader.set_uniform_3fv("viewPos", camera.get_position());

                // MODEL RENDER
                board.draw_board();

                board.render(shader);
                board.render_pieces_3D(shader); },

            .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; 
                if(ImGui::IsKeyDown(ImGuiKey_Space)){
                    camera.toggle_lock();
                } },
            .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; 
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    std::cout << "right click" << '\n';
                    board.reset_turn();
                } },
            .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(-xpos, -ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
        }
    );
}

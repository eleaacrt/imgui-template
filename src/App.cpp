#include "headers/App.hpp"
#include <Camera.hpp>
#include <Shader.hpp>
#include <glm/glm.hpp>
#include <optional>
#include <quick_imgui/quick_imgui.hpp>
#include "Model3D.hpp"
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"
#include "glm/ext/matrix_clip_space.hpp"

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

    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};

    Model3D model;

    quick_imgui::loop(
        "",
        {
            .init         = [&]() {
                load_font(applicationPath.dirPath() + "assets/font/CHEQ_TT.TTF", 64.0f);
                // program =
                //     loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl", applicationPath.dirPath() + "shaders/triangle.fs.glsl");
                // program->use();
                // board3D.initBoard3D(); 
                shader.load_shader("model.vs.glsl", "model.fs.glsl");
                // model.load_mesh("creeper/creeper.obj", "creeper");
                model.load_mesh("board/board.obj", "board");
                model.setup_buffers(); },
            .loop         = [&]() {
                //
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                shader.use();
                
                //MVP
                shader.set_uniform_matrix_4fv("model", glm::mat4(1.0f));
                shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                shader.set_uniform_matrix_4fv("projection", projection);

                //LIGHT SETTINGS
                shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                
                //CAMERA SETTINGS
                shader.set_uniform_3fv("viewPos", camera.get_position());
                
                //MODEL RENDER
                model.render(shader);
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    std::cout << "right click" << '\n';
                    board.reset_turn();
                    // return;
                }
                board.draw_board(); 
                // board3D.drawBoard3D(); 
            },
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

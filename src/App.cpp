#include "headers/App.hpp"
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"
#include <quick_imgui/quick_imgui.hpp>
#include <optional>
#include <glm/glm.hpp>


/* ----------------------

LEARN OPENGL -> WEBSITE 

---------------------- */


void App::init() const
{
}

void App::update(int argc, char** argv)
{
    
  glimac::FilePath applicationPath(argv[0]);
  std::optional<glimac::Program> program ;
  
  GLuint vbo;
  GLuint vao;

  int n_triangles = 100;

  struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;
    Vertex2DColor() {};
    Vertex2DColor(glm::vec2 position, glm::vec3 color)
        : position(position), color(color) {};
};
    quick_imgui::loop(
        "",
        {
            .init         = [&]() { load_font(applicationPath.dirPath() + "assets/font/CHEQ_TT.TTF", 64.0f); 
                program =
                loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
                            applicationPath.dirPath() + "shaders/triangle.fs.glsl");
                            program->use();
                        
                            glGenBuffers(1, &vbo);
                            glBindBuffer(GL_ARRAY_BUFFER, vbo);
                          
                            // coordonates of the triangle
                            std::vector<Vertex2DColor> vertices = {};
                          
                            for (int i = 0; i < n_triangles; i++) {
                              vertices.push_back(
                                  Vertex2DColor(glm::vec2(cos(i * ((2 * M_PI) / (n_triangles))),
                                                          sin(i * ((2 * M_PI) / (n_triangles)))),
                                                glm::vec3(0, 0, 1)));
                              vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(0, 1, 0)));
                              vertices.push_back(
                                  Vertex2DColor(glm::vec2(cos((i + 1) * ((2 * M_PI) / (n_triangles))),
                                                          sin((i + 1) * ((2 * M_PI) / (n_triangles)))),
                                                glm::vec3(0, 0, 1)));
                            }
                          
                            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2DColor),
                                         vertices.data(), GL_STATIC_DRAW);
                          
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                                                    
                            glGenVertexArrays(1, &vao);
                            glBindVertexArray(vao);
                          
                            const GLuint VERTEX_ATTR_POSITION = 3;
                            const GLuint VERTEX_ATTR_COLOR = 8;
                          
                            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                            glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
                          
                            glBindBuffer(GL_ARRAY_BUFFER, vbo);
                          
                            glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE,
                                                  sizeof(Vertex2DColor),
                                                  (const GLvoid *)offsetof(Vertex2DColor, position));
                          
                            glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE,
                                                  sizeof(Vertex2DColor),
                                                  (const GLvoid *)offsetof(Vertex2DColor, color));
                          
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                            glBindVertexArray(0);
                        },
            .loop         = [&]() {
                glClear(GL_COLOR_BUFFER_BIT);
            
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, n_triangles * 3);
                glBindVertexArray(0);

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    std::cout << "right click" << '\n';
                    board.reset_turn();
                    // return;
                }
                board.draw_board(); },
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
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
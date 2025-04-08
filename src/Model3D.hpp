#ifndef MODEL3D_HPP
#define MODEL3D_HPP

#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"

class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3
    void translate(float x, float y, float z);                        

private:
    // single mesh
    glmax::Mesh m_mesh;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};

#endif // MODEL3D_HPP "
#include "headers/Board3D.hpp"
#include <imgui.h>

void Board3D::initBoard3D()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    for (int i = 0; i < n_triangles; i++)
    {
        vertices.push_back(
            Vertex2DColor(glm::vec2(cos(i * ((2 * M_PI) / (n_triangles))), sin(i * ((2 * M_PI) / (n_triangles)))), glm::vec3(0, 0, 1))
        );
        vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(0, 1, 0)));
        vertices.push_back(
            Vertex2DColor(glm::vec2(cos((i + 1) * ((2 * M_PI) / (n_triangles))), sin((i + 1) * ((2 * M_PI) / (n_triangles)))), glm::vec3(0, 0, 1))
        );
    }

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 3;
    const GLuint VERTEX_ATTR_COLOR    = 8;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, position));

    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, color));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Board3D::drawBoard3D()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, n_triangles * 3);
    glBindVertexArray(0);
}

void Board3D::deleteBuffers3D()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
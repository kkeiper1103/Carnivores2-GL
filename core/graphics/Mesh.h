//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_MESH_H
#define OPEN_CAR2_MESH_H

#include <vector>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Texture.h"

#include "sfh/ocarn2.h"

struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
protected:
    GLuint vao, vbo, ebo;
    void unbind();

public:
    std::vector<MeshVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;


    glm::vec3 position;
    glm::vec3 scaling = glm::vec3(1);

    bool drawArrays = true;
    GLenum drawMode = GL_TRIANGLES;

    std::function<void(void)> _renderFn = nullptr;

public:
    Mesh(const OCARN2::Mesh& mesh);
    Mesh(std::vector<MeshVertex> vertices, const std::vector<unsigned int>& indices);
    Mesh();
    ~Mesh();

    void setupMesh();
    void draw(Shader* shader);


    inline void renderFn(const std::function<void(void)>& newRenderFn) {
        _renderFn = newRenderFn;
    }
};


#endif //OPEN_CAR2_MESH_H

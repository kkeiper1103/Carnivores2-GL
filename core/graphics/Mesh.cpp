//
// Created by kkeiper on 4/11/2022.
//

#define STB_IMAGE_IMPLEMENTATION
#define OCARN2_IMPLEMENTATION

#include "Mesh.h"

void Mesh::setupMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    //
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // setup attribute locations
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FLOAT, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FLOAT, sizeof(MeshVertex), (void*)offsetof(MeshVertex, texCoords));

    unbind();
}

void Mesh::unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 *
 * @param shader
 */
void Mesh::draw(Shader* shader) {
    shader->use();

    // bind first texture
    glActiveTexture(GL_TEXTURE0);
    shader->setFloat("texture1", 0);
    textures[0].bind(GL_TEXTURE0);


    glBindVertexArray(vao);

    // for terrain cpp, custom calls to drawElements etc
    if(_renderFn != nullptr) {
        _renderFn();
    }
    else {
        // for car and 3df models
        if(drawArrays) {
            glDrawArrays(drawMode, 0, vertices.size());
        }
            // for customer generated ground model
        else {
            glDrawElements(drawMode, indices.size(), GL_UNSIGNED_INT, 0);
        }
    }



    unbind();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

/**
 *
 * @param mesh
 */
Mesh::Mesh(const OCARN2::Mesh &mesh) {
    vertices.reserve(2048);
    for(auto i=0; i < mesh.numFaces; i++) {
        auto triangle = mesh.faces[i];

        auto vert1 = mesh.vertices[triangle.v1],
             vert2 = mesh.vertices[triangle.v2],
             vert3 = mesh.vertices[triangle.v3];

        auto t1 = glm::vec2( triangle.tax / 256.f, triangle.tay / 256.f ),
            t2 = glm::vec2( triangle.tbx / 256.f, triangle.tby / 256.f ),
            t3 = glm::vec2( triangle.tcx / 256.f, triangle.tcy / 256.f );

        indices.push_back(triangle.v1);
        indices.push_back(triangle.v2);
        indices.push_back(triangle.v3);

        // set the buffer array data
        vertices.push_back(MeshVertex {
            .position = glm::vec3(vert1.x, vert1.y, vert1.z),
            .texCoords = t1
        });
        vertices.push_back(MeshVertex {
            .position = glm::vec3(vert2.x, vert2.y, vert2.z),
            .texCoords = t2
        });
        vertices.push_back(MeshVertex {
            .position = glm::vec3(vert3.x, vert3.y, vert3.z),
            .texCoords = t3
        });

        auto a = &vertices[triangle.v1],
            b = &vertices[triangle.v2],
            c = &vertices[triangle.v3];

        // generate normals
        glm::vec3 normal = glm::cross(b->position - a->position, c->position - a->position);

        a->normal += normal;
        b->normal += normal;
        c->normal += normal;
    }

    for(auto i=0; i < mesh.numVertices; ++i) {
        vertices.at(i).normal = glm::normalize( vertices.at(i).normal );
    }

    // translate raw texture into bgra 5
    for(auto i=0; i < mesh.textureSize / 2; i++) {
        unsigned short pixel = mesh.textureData[i];

        int b = (pixel >> 0) & 31;
        int g = (pixel >> 5) & 31;
        int r = (pixel >> 10) & 31;

        int a = 1;
        if(!b && !g && !r)
            a = 0;

        mesh.textureData[i] = (b) + (g << 5) + (r << 10) + (a << 15);
    }

    int TexH = (mesh.textureSize / 2) / 256;


    textures.emplace_back( (char*) mesh.textureData, 256, int(ceilf(float(TexH) / 256.0f) * 256) );


    setupMesh();
}

Mesh::Mesh(std::vector<MeshVertex> vertices, const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;

    setupMesh();
}

Mesh::Mesh() {}

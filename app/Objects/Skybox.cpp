//
// Created by kkeiper on 4/15/2022.
//

#include <cstdio>
#include "Skybox.h"
#include "globals.h"

#include <stb/stb_image.h>

Skybox::Skybox(const unsigned short *skyTexture) : data(skyTexture) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    int width, height;
    width = height = 256;

    printf("Loading Skybox\n");

    auto texture = new unsigned short[width * height];
    for(auto p=0; p < width * height; p++) {
        auto pixel = data[p];

        int r = (pixel >> 10) & 31,
            g = (pixel >> 5) & 31,
            b = (pixel) & 31;

        int a = 1;
        if(!r && !g && !b)
            a = 0;

        texture[p] = (b) + (g<<5) + (r<<10) + (a<<15);
    }

    int w, h, channels;
    unsigned char* skymap = stbi_load("assets/skybox/front.jpg", &w, &h, &channels, STBI_rgb);


    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB5_A1, width, height, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, texture);

    stbi_image_free(skymap);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    delete[] texture;


    // load vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), &skyboxVertices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);


        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Skybox::update(double dt) {
    glm::mat4 view = glm::mat4(glm::mat3(globalCamera.view));

    shaders.at(SKYBOX_SHADER)->use();
    shaders.at(SKYBOX_SHADER)->setMat4("view", view);
    shaders.at(SKYBOX_SHADER)->setInt("skybox", 0);
}

void Skybox::render() {
    glDepthMask(GL_FALSE);
    shaders.at(SKYBOX_SHADER)->use();

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

void Skybox::handleEvent(const SDL_Event *e) {

}

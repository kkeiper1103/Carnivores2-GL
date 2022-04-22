//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_TEXTURE_H
#define OPEN_CAR2_TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
    GLuint id;

    Texture(char* data, int width, int height);
    ~Texture();

    void bind( GLenum slot ) const {
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }
};


#endif //OPEN_CAR2_TEXTURE_H

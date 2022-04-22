//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_GLOBALS_H
#define OPEN_CAR2_GLOBALS_H

#include <stdio.h>
#include <stdint.h>

#include <memory>
#include <vector>


#include "graphics/Shader.h"
#include "Camera.h"


extern int screen_width, screen_height;
extern glm::mat4 projection;

//
extern Camera globalCamera;


// shaders for the program
enum SHADERS {
    MODEL_SHADER = 0,
    TERRAIN_SHADER,
    SKYBOX_SHADER,

    LAST_INDEX_SHADER
};
extern std::vector<std::unique_ptr<Shader>> shaders;




// utility function
void tga_write(const char *filename, uint32_t width, uint32_t height, uint8_t *dataBGRA, uint8_t bytes, uint8_t dataChannels=4, uint8_t fileChannels=3);

#endif //OPEN_CAR2_GLOBALS_H

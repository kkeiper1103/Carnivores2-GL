//
// Created by kkeiper on 4/11/2022.
//

#include "globals.h"

int screen_width = 1920;
int screen_height = 1080;
glm::mat4 projection;

Camera globalCamera( glm::vec3(0, 0, 0) );


std::vector<std::unique_ptr<Shader>> shaders = std::vector<std::unique_ptr<Shader>>(LAST_INDEX_SHADER);

/**
 *
 * @param filename
 * @param width
 * @param height
 * @param dataBGRA
 * @param dataChannels
 * @param fileChannels
 */
void tga_write(const char *filename, uint32_t width, uint32_t height, uint8_t *dataBGRA, uint8_t bytes, uint8_t dataChannels, uint8_t fileChannels)
{
    FILE *fp = NULL;
    // MSVC prefers fopen_s, but it's not portable
    //fp = fopen(filename, "wb");
    fopen_s(&fp, filename, "wb");
    if (fp == NULL) return;

    // You can find details about TGA headers here: http://www.paulbourke.net/dataformats/tga/
    uint8_t header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0, (uint8_t)(width%256), (uint8_t)(width/256), (uint8_t)(height%256), (uint8_t)(height/256), (uint8_t)(fileChannels*5), 0x20 };
    fwrite(&header, 18, 1, fp);

    fwrite(dataBGRA, bytes, 1, fp);

    fclose(fp);
}
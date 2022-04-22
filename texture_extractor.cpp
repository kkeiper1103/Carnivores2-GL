//
// Created by kkeiper on 4/16/2022.
//

#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#define OCARN2_IMPLEMENTATION
#include "sfh/ocarn2.h"


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    OCARN2::Rsc resources = load_rsc_file("assets/HUNTDAT/AREAS/AREA1.RSC");

    for(auto i=0; i < resources.numTextures; i++) {
        std::stringstream filename;
        filename << "output\\texture" << i << ".bmp";

        unsigned short* data = resources.textures[i].data;

        for(int i=0; i < 128 * 128; i++) {
            int a = data[i] & 0x8000;
            int r = data[i] & 0x7c00;
            int g = data[i] & 0x03E0;
            int b = data[i] & 0x1f;
            int rgb = (r << 9) | (g << 6) | (b << 3);

            data[i] = (a * 0x1FE00) | rgb | ((rgb >> 5) & 0x070707);
        }

        stbi_write_bmp(filename.str().c_str(), 128, 128, 3, data);
    }


    OCARN2::Mesh hunter = load_car_file("assets/HUNTDAT/HUNTER1.CAR");


    std::vector<unsigned char> converted(256 * 1024, 0);
    unsigned char* p = &converted[0];

    for (int i=0; i < hunter.textureSize / 2; i++)
    {
        unsigned short w = hunter.textureData[i];
        int B = ((w>> 0) & 31);
        int G = ((w>> 5) & 31);
        int R = ((w>>10) & 31);
        int A = 1;
        if (!B && !G && !R)
            A = 0;

        *p++ = (int) (R / 31.f) * 255;
        *p++ = (int) (G / 31.f) * 255;
        *p++ = (int) (B / 31.f) * 255;
        *p++ = A * 255;
    }



    stbi_write_png("output\\hunter1.png", 256, 256, 4, &converted[0], 0);

    FILE* f = fopen("output\\hunter1.texture.bin", "wb");
    fwrite(hunter.textureData, 1, hunter.textureSize, f);
    fclose(f);


    free_mesh(hunter);
    free_rsc(resources);

    return 0;
}
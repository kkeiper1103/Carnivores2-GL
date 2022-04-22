//
// Created by kkeiper on 4/19/2022.
//


#include <windef.h>
#include <wingdi.h>
#include "SquareMesh.h"




SquareMesh::SquareMesh() {
    vertices = std::vector<MeshVertex> {
            { .position = {30.f,  30.f, 0.0f}, .normal = {}, .texCoords = {1.0f, 1.0f} },
            { .position = {30.f, -30.f, 0.0f}, .normal = {}, .texCoords = {1.0f, 0.0f} },
            { .position = {-30.f, -30.f, 0.0f}, .normal = {}, .texCoords = {0.0f, 0.0f} },
            { .position = {-30.f,  30.f, 0.0f}, .normal = {}, .texCoords = {0.0f, 1.0f} },
    };
    indices = std::vector<unsigned int> {
            0, 1, 3,
            1, 2, 3
    };

    setupMesh();

    auto mesh = load_car_file("assets/HUNTDAT/HUNTER1.CAR");
    auto rsc = load_rsc_file("assets/HUNTDAT/AREAS/AREA1.RSC");


    std::vector<unsigned short> stitchedTextures(rsc.numTextures * 128 * 128, 0);
    unsigned size = 0;
    for(auto i=0; i < rsc.numTextures; i++) {
        memcpy(&stitchedTextures[i * 128 * 128], rsc.textures[i].data, rsc.textures[i].size);

        size += rsc.textures[i].size;
    }

    bool drawStitchedTexture = true;

    if(drawStitchedTexture) {
        textures.emplace_back((char *) &stitchedTextures[0], 128.f, 128 * rsc.numTextures);
    }
    else {
        for (auto i = 0; i < mesh.textureSize / 2; i++) {
            unsigned short pixel = mesh.textureData[i];

            int b = (pixel >> 0) & 31;
            int g = (pixel >> 5) & 31;
            int r = (pixel >> 10) & 31;

            int a = 1;
            if (!b && !g && !r)
                a = 0;

            mesh.textureData[i] = (b) + (g << 5) + (r << 10) + (a << 15);
        }

        int TexH = (mesh.textureSize / 2) / 256;
        textures.emplace_back((char *) mesh.textureData, 256, int(ceilf(float(TexH) / 256.0f) * 256));
    }


    free_mesh(mesh);
    free_rsc(rsc);
}

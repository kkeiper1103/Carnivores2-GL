//
// Created by kkeiper on 4/14/2022.
//

#include <iostream>

#define OCARN2_IMPLEMENTATION
#include "sfh/ocarn2.h"

int main(int argc, char* argv[]) {
    OCARN2::Mesh allosaurusMesh       = load_car_file("assets/HUNTDAT/ALLO.CAR");
    OCARN2::Mesh binoculars     = load_3df_file("assets/HUNTDAT/BINOCUL.3DF");
    OCARN2::Rsc resources   = load_rsc_file("assets/HUNTDAT/AREAS/AREA2.RSC");
    OCARN2::Map map         = load_map_file("assets/HUNTDAT/AREAS/AREA2.MAP");


    auto restxt = load_res_txt_file("assets/HUNTDAT/_RES.TXT");


    std::cout << resources.numTextures << std::endl;
    std::cout << resources.numModels << std::endl;


    int highest = 0;
    for(int y=0; y < 1024; y++) {
        for( int x=0; x < 1024; x++) {
            int index = y * 1024 + x;

            if( map.textureMap[index] > highest ) highest = map.textureMap[index];
        }
    }

    std::cout << "Highest Texture ID: " << highest << std::endl;

    free_mesh(allosaurusMesh);
    free_rsc(resources);
}
//
// Created by kkeiper on 4/11/2022.
//

#include "CarnivoresApp.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"

void CarnivoresApp::setup() {

    models = {
        {"assets/HUNTDAT/ALLO.CAR"},
        {"assets/HUNTDAT/ANKYLO1.CAR"},
        {"assets/HUNTDAT/BRACHI1.CAR"},
        {"assets/HUNTDAT/CERATO1.CAR"},
        {"assets/HUNTDAT/CHASMOSA.CAR"},
        {"assets/HUNTDAT/DIMET.CAR"},
        {"assets/HUNTDAT/DIMOR2.CAR"},
        {"assets/HUNTDAT/GALL.CAR"},
        {"assets/HUNTDAT/HUNTER1.CAR"},
        {"assets/HUNTDAT/MOSH.CAR"},
        {"assets/HUNTDAT/PAR2.CAR"},
        {"assets/HUNTDAT/PTERA.CAR"},
        {"assets/HUNTDAT/SHIP2A.CAR"},
        {"assets/HUNTDAT/SPINO.CAR"},
        {"assets/HUNTDAT/STEGO.CAR"},
        {"assets/HUNTDAT/TIREX.CAR"},
        {"assets/HUNTDAT/VELO2.CAR"},
        {"assets/HUNTDAT/WCIRCLE2.CAR"},
        {"assets/HUNTDAT/WIND.CAR"},
    };

    for(auto& file: models) {
        meshes.push_back( load_car_file(file.c_str()) );
    }

    /**
     * system.state.register(system.state.PLAY, new PlayState);
     * system.state.register(system.state.MENU, new MenuState);
     */
}

void CarnivoresApp::cleanup() {
    for(auto& mesh: meshes) {
        free_mesh(mesh);
    }
}

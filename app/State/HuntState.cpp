//
// Created by kkeiper on 4/21/2022.
//

#include "HuntState.h"

#include "globals.h"
#include "state/StateMachine.h"
#include "graphics/Model.h"

void HuntState::onEnter() {
    BaseState::onEnter();


    // initialize camera and projection space
    projection = glm::perspective(
            glm::radians(60.f),
            (float)screen_width / (float) screen_height,
            .1f,
            20000.f
    );

    globalCamera = Camera( glm::vec3(500, 50, 500) );
    // globalCamera.lookAt(glm::vec3(0, 0, 0));
    globalCamera.firstPersonMode(SDL_TRUE);



    for(auto& s: shaders) {
        s->use();
        s->setMat4("projection", projection);
        s->setMat4("view", globalCamera.view);
    }

    glm::mat4 model = glm::mat4(1.f);

    shaders.at(MODEL_SHADER)->use();
    shaders.at(MODEL_SHADER)->setMat4("model", model);

    shaders.at(TERRAIN_SHADER)->use();
    shaders.at(TERRAIN_SHADER)->setMat4("model", model);



    //
    auto map = load_map_file("assets/HUNTDAT/AREAS/AREA1.MAP");
    auto rsc = load_rsc_file("assets/HUNTDAT/AREAS/AREA1.RSC");


    std::unique_ptr<Terrain> terrain = std::make_unique<Terrain>(map, rsc);
    items.emplace_back( std::move(terrain) );


    free_rsc(rsc);




    OCARN2::Mesh spinoCar = load_car_file("assets/HUNTDAT/SPINO.CAR");
    Mesh spino(spinoCar);
    std::unique_ptr<Model> object = std::make_unique<Model>(spino, spino.textures[0]);

    object->setPosition(glm::vec3(0, 0, 0));

    items.emplace_back( std::move(object) );

    free_mesh(spinoCar);



    isPaused = false;
}

void HuntState::onExit() {
    BaseState::onExit();

    while(!items.empty())
        items.pop_back();

    items.clear();
}


void HuntState::gui() {
    // draw pause menu
    // @todo extract private method
    if(isPaused) {
        nk_begin(nkCtx, "Pause Menu", nk_rect(300, 300, 300, 300), NK_WINDOW_TITLE | NK_WINDOW_BORDER);

        nk_layout_row_dynamic(nkCtx, 35, 1);
        if(nk_button_label(nkCtx, "Unpause")) {
            isPaused = false;
            globalCamera.firstPersonMode(SDL_TRUE);
        }


        nk_layout_row_dynamic(nkCtx, 35, 1);
        if(nk_button_label(nkCtx, "Exit to Menu")) {
            SDL_Event e; SDL_zero(e);
            e.type = SDL_USEREVENT;
            e.user.code = 101;
            e.user.data1 = (void*) STATE_INTRO;
            SDL_PushEvent(&e);
        }

        nk_end(nkCtx);
    }
    else {

        if(nk_begin(nkCtx, "Hunt Details", nk_rect(10, 10, 150, 250), NK_WINDOW_TITLE)) {

            nk_layout_row_dynamic(nkCtx, 35, 1);

            nk_label(nkCtx, "Guns:", NK_TEXT_ALIGN_LEFT);
            /*for(auto& g: player.guns) {
                nk_label(nkCtx, g.name.c_str(), NK_TEXT_ALIGN_MIDDLE);
            }*/

            nk_label(nkCtx, "Current Dinos:", NK_TEXT_ALIGN_LEFT);
            /*for(auto& d: hunt.dinos) {
                nk_label(nkCtx, d.name.c_str(), NK_TEXT_ALIGN_MIDDLE);
            }*/

        }
        nk_end(nkCtx);
    }
}

void HuntState::input(const SDL_Event *e) {

    // events
    globalCamera.handleEvent(e);

    BaseState::input(e);

    if(e->type == SDL_KEYUP && e->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        isPaused = !isPaused;

        globalCamera.firstPersonMode((SDL_bool) !isPaused);

        printf("Inverting the Pause!\n");
    }
}

void HuntState::update(double dt) {
    if(!isPaused) {
        globalCamera.update(dt);

        BaseState::update(dt);
    }
}

void HuntState::render() {
    shaders.at(MODEL_SHADER)->use();
    shaders.at(MODEL_SHADER)->setMat4("view", globalCamera.view);

    shaders.at(TERRAIN_SHADER)->use();
    shaders.at(TERRAIN_SHADER)->setMat4("view", globalCamera.view);

    shaders.at(MODEL_SHADER)->use();

    BaseState::render();
}

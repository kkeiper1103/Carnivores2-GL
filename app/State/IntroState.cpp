//
// Created by kkeiper on 4/21/2022.
//

#include "IntroState.h"

#include "globals.h"
#include "state/StateMachine.h"
#include "graphics/Mesh.h"
#include "graphics/Model.h"

void IntroState::onEnter() {
    BaseState::onEnter();

    printf("Loading Shaders for Later...\n");
    shaders.at(MODEL_SHADER) = std::make_unique<Shader>("assets/shaders/model.vs.glsl", "assets/shaders/model.fs.glsl");
    shaders.at(TERRAIN_SHADER) = std::make_unique<Shader>("assets/shaders/terrain.vs.glsl", "assets/shaders/terrain.fs.glsl");
    shaders.at(SKYBOX_SHADER) = std::make_unique<Shader>("assets/shaders/skybox.vs.glsl", "assets/shaders/skybox.fs.glsl");


    //
}

void IntroState::onExit() {
    BaseState::onExit();

    items.clear();
}

void IntroState::gui() {
    if( nk_begin(nkCtx, "Info Bar", nk_rect(0, 0, screen_width, 55), NK_WINDOW_BORDER) ) {
        nk_layout_row_begin(nkCtx, NK_STATIC, 40, 3);

        nk_layout_row_push(nkCtx, 50);
        nk_label(nkCtx, "Name: ", NK_TEXT_LEFT);


        nk_layout_row_push(nkCtx, 100);
        nk_label(nkCtx, "Account: ", NK_TEXT_LEFT);


        nk_layout_row_push(nkCtx, 100);
        if( nk_button_label(nkCtx, "Statistics") ) {
            printf("@todo open statistics screen from savedata\n");
        }

        nk_layout_row_end(nkCtx);
    }
    nk_end(nkCtx);



    struct nk_rect centered = nk_rect(0, 0, 200, 300);
    centered.x = (screen_width / 2) - (centered.w / 2);
    centered.y = (screen_height / 2) - (centered.h / 2);

    if(nk_begin(nkCtx, "Intro State", centered, NK_WINDOW_TITLE | NK_WINDOW_BORDER)) {

        nk_layout_row_dynamic(nkCtx, 35, 1);
        if( nk_button_label(nkCtx, "Start Hunt") ) {
            SDL_Event e; SDL_zero(e);
            e.type = SDL_USEREVENT;
            e.user.code = 101;
            e.user.data1 = (void*) STATE_PLAYING;
            SDL_PushEvent(&e);
        }

        if( nk_button_label(nkCtx, "Options") ) {
            SDL_Event e; SDL_zero(e);
            e.type = SDL_USEREVENT;
            e.user.code = 101;
            e.user.data1 = (void*) STATE_MENU;
            SDL_PushEvent(&e);
        }

        if( nk_button_label(nkCtx, "Start Hunt") ) {
            int trophyRoomMapId = 0;

            SDL_Event e; SDL_zero(e);
            e.type = SDL_USEREVENT;
            e.user.code = 101;
            e.user.data1 = (void*) STATE_PLAYING;
            e.user.data2 = &trophyRoomMapId;
            // SDL_PushEvent(&e);

            printf("Disabled PushEvent until we can start trophy room\n");
        }

        if( nk_button_label(nkCtx, "Credits") ) {
            printf("@TODO Create Credits State\n");
        }

        if( nk_button_label(nkCtx, "Exit Game") ) {
            SDL_Event e; SDL_zero(e);
            e.type = SDL_QUIT;
            SDL_PushEvent(&e);
        }
    }
    nk_end(nkCtx);
}
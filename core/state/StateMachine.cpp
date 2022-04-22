//
// Created by kkeiper on 4/21/2022.
//

#include "StateMachine.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

StateMachine::StateMachine(SDL_Window* window) {
    nkCtx = nk_sdl_init( window );

    nk_sdl_font_stash_begin(&nkFontAtlas);
        // .. add customizable way to register fonts?
        // maybe look in fonts folder and register filename as handle
    nk_sdl_font_stash_end();
}

StateMachine::~StateMachine() {
    nk_sdl_shutdown();
}


void StateMachine::input(const SDL_Event *e) {
    current()->input(e);
}

void StateMachine::update(double dt) {
    current()->update(dt);
}

void StateMachine::render() {
    current()->render();


    current()->gui();
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_ELEMENT_MEMORY, MAX_ELEMENT_MEMORY);
}

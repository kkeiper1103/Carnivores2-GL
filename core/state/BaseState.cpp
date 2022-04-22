//
// Created by kkeiper on 4/21/2022.
//

#include "BaseState.h"

void BaseState::input(const SDL_Event *e) {
    for(auto& o: items) {
        o->handleEvent(e);
    }
}

void BaseState::update(double dt) {
    for(auto& o: items) {
        o->update(dt);
    }
}

void BaseState::render() {
    for(auto& o: items) {
        o->render();
    }
}

void BaseState::gui() {

}

BaseState::~BaseState() {

}

//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_HUNTSTATE_H
#define OPEN_CAR2_HUNTSTATE_H

#include "Level/Terrain.h"
#include "Objects/SquareMesh.h"

#include "graphics/Mesh.h"
#include "sfh/ocarn2.h"
#include "state/BaseState.h"

class HuntState : public BaseState {
public:
    void onEnter() override;
    void onExit() override;

    void gui() override;

    void input(const SDL_Event *e) override;
    void update(double dt) override;
    void render() override;

    bool isPaused = false;
};


#endif //OPEN_CAR2_HUNTSTATE_H

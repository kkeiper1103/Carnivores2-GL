//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_STATEINTERFACE_H
#define OPEN_CAR2_STATEINTERFACE_H

#include <memory>

#include <SDL2/SDL.h>

class StateInterface {
public:
    virtual ~StateInterface() = default;

    virtual void onChange() = 0;
    virtual void onReset() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;

    virtual void input(const SDL_Event* e) = 0;
    virtual void update(double dt) = 0;
    virtual void render() = 0;
    virtual void gui() = 0;
};

typedef std::unique_ptr<StateInterface> StateInterfacePtr;

#endif //OPEN_CAR2_STATEINTERFACE_H

//
// Created by kkeiper on 4/10/2022.
//

#ifndef OPEN_CAR2_APP_H
#define OPEN_CAR2_APP_H

#include <ctime>
#include <cstdio>

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "state/StateMachine.h"

class App {
protected:
    SDL_Window* window = nullptr;
    SDL_GLContext gl = nullptr;

    StateMachinePtr stateMachine = nullptr;

    bool running = true;

    void loop();

    virtual void setup() =0;
    virtual void cleanup() =0;

    void clearScreen();

public:
    App();
    ~App();

    int run();
};


#endif //OPEN_CAR2_APP_H

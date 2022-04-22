//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_STATEMACHINE_H
#define OPEN_CAR2_STATEMACHINE_H

#include <map>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "globals.h"
#include "gui/nuklear.h"
#include "state/StateInterface.h"

enum STATES {
    STATE_INTRO = 0,
    STATE_MENU,
    STATE_SETTINGS,
    STATE_PLAYING,
    STATE_GAMEOVER
};

class StateMachine {
protected:
    std::vector<STATES> history;
    std::map<STATES, StateInterfacePtr> allStates;

public:
    explicit StateMachine(SDL_Window* window);
    ~StateMachine();

    void input(const SDL_Event* e);
    void update(double dt);
    void render();


    inline void set(STATES state, StateInterfacePtr newState) {
        allStates[state] = std::move(newState);
    }

    inline void changeTo(STATES state) {
        if(history.size() > 0) current()->onExit();

        history.push_back(state);

        current()->onEnter();
    }

    inline void pop() {
        history.pop_back();
    }

    inline const StateInterfacePtr& current() {
        assert(history.size() > 0 && "You Forgot to Add an Initial State via StateMachine::changeTo()!");

        return allStates[ history.back() ];
    }
};

typedef std::unique_ptr<StateMachine> StateMachinePtr;

#endif //OPEN_CAR2_STATEMACHINE_H

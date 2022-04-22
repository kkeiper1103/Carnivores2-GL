//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_INTROSTATE_H
#define OPEN_CAR2_INTROSTATE_H


#include "state/BaseState.h"

class IntroState : public BaseState {
public:
    void onEnter() override;
    void onExit() override;

    void gui() override;
};


#endif //OPEN_CAR2_INTROSTATE_H

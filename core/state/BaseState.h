//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_BASESTATE_H
#define OPEN_CAR2_BASESTATE_H

#include <memory>
#include <string>
#include <vector>
#include <list>

#include "gui/nuklear.h"

#include "state/StateInterface.h"
#include "entity/Entity.h"

class BaseState : public StateInterface {
protected:
    std::list< std::unique_ptr<Entity> > items;

public:
    ~BaseState() override;

    inline void onChange() override {};
    inline void onReset() override {};
    inline void onEnter() override {};
    inline void onExit() override {};

    void input(const SDL_Event *e) override;
    void update(double dt) override;
    void render() override;

    void gui() override;

};


#endif //OPEN_CAR2_BASESTATE_H

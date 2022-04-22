//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_ENTITY_H
#define OPEN_CAR2_ENTITY_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Entity {
protected:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 direction;

public:
    virtual void handleEvent(const SDL_Event* e)=0;
    virtual void update(double dt)=0;
    virtual void render()=0;
};


#endif //OPEN_CAR2_ENTITY_H

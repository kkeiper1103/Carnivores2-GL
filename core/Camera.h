//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_CAMERA_H
#define OPEN_CAR2_CAMERA_H

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity/Entity.h"

class Camera : public Entity {
protected:
    glm::vec3 position, target, direction, up, right, front = glm::vec3(0, 0, -1.f); // "front" is one z-unit away from current position

    float yaw = 0.f, pitch = 0;

public:
    glm::mat4 view;

public:
    explicit Camera(const glm::vec3& position, const glm::vec3& target = glm::vec3(0, 0, 0));
    void lookAt(const glm::vec3& newTarget);
    void firstPersonMode(SDL_bool fps);


    void handleEvent(const SDL_Event *e) override;
    void update(double dt) override;
    void render() override;
};


#endif //OPEN_CAR2_CAMERA_H

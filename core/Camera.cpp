//
// Created by kkeiper on 4/11/2022.
//

#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& target) : position(position), target(target) {
    direction = glm::normalize(position - target);

    // get absolute up
    glm::vec3 cardinalUp = glm::vec3(0, 1, 0);

    right = glm::normalize(glm::cross(cardinalUp, direction));

    // get camera's vertical up
    up = glm::normalize(glm::cross(direction, right));

    view = glm::lookAt(position, position + front, up);
}


/**
 *
 * @param position
 */
void Camera::lookAt(const glm::vec3 &newTarget) {
    target = newTarget;

    view = glm::lookAt(position, position + front, up);
}

void Camera::firstPersonMode(SDL_bool fps) {
    SDL_SetRelativeMouseMode(fps);
}


void Camera::handleEvent(const SDL_Event *e) {
    const float sensitivity = 0.1;

    if( SDL_GetRelativeMouseMode() == SDL_TRUE ) {

        // update pitch and yaw
        if(e->type == SDL_MOUSEMOTION) {
            yaw += e->motion.xrel * sensitivity;
            pitch -= e->motion.yrel * sensitivity;

            if(pitch > 90.f) pitch = 90.f;
            if(pitch < -90.f) pitch = -90.f;
        }

        // update the lookat when the mouse moves around
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        direction.y = sin(glm::radians(pitch)) ;

        // normalize the front vector
        front = glm::normalize(direction);
    }


}

void Camera::update(double dt) {
    const uint8_t* keys = SDL_GetKeyboardState(0);
    SDL_Keymod mods = SDL_GetModState(); // used for detecting LSHIFT

    const float cameraSpeed = 100.f;

    if(keys[SDL_SCANCODE_W]) {
        position += cameraSpeed * front;
    }
    if(keys[SDL_SCANCODE_S]) {
        position -= cameraSpeed * front;
    }
    if(keys[SDL_SCANCODE_A]) {
        position -= glm::normalize( glm::cross(front, up) ) * cameraSpeed;
    }
    if(keys[SDL_SCANCODE_D]) {
        position += glm::normalize( glm::cross(front, up) ) * cameraSpeed;
    }

    if(keys[SDL_SCANCODE_SPACE]) {
        position.y += 1.0 * cameraSpeed;
    }
    if(mods & KMOD_SHIFT) {
        position.y -= 1.0 * cameraSpeed;
    }


    // keep position.y affected by gravity
    // position.y = 50.f;

    view = glm::lookAt(position, position + front, up);
}

void Camera::render() {

}


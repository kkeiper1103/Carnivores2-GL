//
// Created by kkeiper on 4/21/2022.
//

#ifndef OPEN_CAR2_MODEL_H
#define OPEN_CAR2_MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "entity/Entity.h"

#include "Texture.h"
#include "Mesh.h"

class Model : public Entity {
protected:
    Mesh mesh;
    Texture texture;

    glm::mat4 model;

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 direction;

public:
    Model(const Mesh& mesh, const Texture& texture);
    ~Model();

    void rotate(const glm::vec3& rotation);
    void translate(const glm::vec3& translation);
    void scale(const glm::vec3& scaling);

    inline void setPosition(const glm::vec3& newPosition) {
        position = newPosition;

        model = glm::translate(model, newPosition);
    }

    void handleEvent(const SDL_Event *e) override;
    void update(double dt) override;
    void render() override;


};


#endif //OPEN_CAR2_MODEL_H

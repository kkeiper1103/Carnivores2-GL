//
// Created by kkeiper on 4/21/2022.
//

#include "Model.h"
#include "globals.h"

Model::Model(const Mesh &mesh, const Texture &texture) : mesh(mesh), texture(texture) {
    model = glm::mat4(1);


}

Model::~Model() {

}

void Model::handleEvent(const SDL_Event *e) {

}

void Model::update(double dt) {

}

void Model::render() {
    shaders[MODEL_SHADER]->use();
    shaders[MODEL_SHADER]->setMat4("model", model);

    texture.bind(GL_TEXTURE0);
    mesh.draw( shaders[MODEL_SHADER].get() );
}

void Model::rotate(const glm::vec3 &rotation) {
    auto quaternion = glm::quat(rotation);

    model *= glm::mat4_cast(quaternion);
}

void Model::translate(const glm::vec3 &translation) {
    model *= glm::vec4(translation, 0);
}

void Model::scale(const glm::vec3 &scaling) {
    model *= glm::vec4(scaling, 0);
}

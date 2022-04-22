//
// Created by kkeiper on 4/15/2022.
//

#ifndef OPEN_CAR2_TERRAIN_H
#define OPEN_CAR2_TERRAIN_H

#include <map>
#include <memory>

#include "entity/Entity.h"

#include "sfh/ocarn2.h"

#include "graphics/Mesh.h"
#include "Objects/Skybox.h"



class Terrain : public Entity {
protected:
    std::unique_ptr<Mesh> groundMesh = nullptr;

    std::vector<MeshVertex> vertices;
    std::vector<unsigned int> indices;

    // first is object id, second is list of positions
    std::map<unsigned int, std::vector<glm::vec3>> objectPositions;

    // map of unique objects found on map
    std::map<unsigned int, std::unique_ptr<Mesh>> objects;

    std::unique_ptr<Skybox> sky = nullptr;
    glm::mat4 model = glm::mat4(1);

    unsigned int num_strips;
    unsigned int num_verts_per_strip;

public:
    Terrain(const OCARN2::Map& mapData, const OCARN2::Rsc& rscData);
    ~Terrain();

    void handleEvent(const SDL_Event *e) override;
    void update(double dt) override;
    void render() override;

    void draw();

    bool isInView(glm::vec3 vec1, glm::mat4 mat1, glm::mat4 mat2);
};


#endif //OPEN_CAR2_TERRAIN_H

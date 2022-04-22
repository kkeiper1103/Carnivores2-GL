//
// Created by kkeiper on 4/15/2022.
//

#include "Terrain.h"
#include "glm/ext/matrix_transform.hpp"
#include "globals.h"
#include "Objects/Skybox.h"

#include "FrustumCull.h"

Terrain::Terrain(const OCARN2::Map &mapData, const OCARN2::Rsc& rscData) {
    printf("Starting Terrain Construction\n");

    int mapSize = 1024;

    // generate heightmap of data
    for(auto z=0; z < mapSize; z++) {
        for(auto x=0; x < mapSize; x++) {
            unsigned int index = z * mapSize + x;
            unsigned short height = mapData.heightMap[index];

            MeshVertex v {};
            v.position = glm::vec3(
                    (float) x * 150,
                    height * 64,
                    (float) z * 150
                );

            v.normal = glm::vec3(0);

            // calculate the texCoord based on which vertex we're dealing with 0-5
            // indices ordering for quads
            // 0, 1, 2
            // 2, 1, 3
            float bandHeight = 1.f / rscData.numTextures;
            float row = mapData.textureMap[index];

            switch(index % 6) {
                case 0:
                    v.texCoords = glm::vec2(0, (bandHeight * row) + bandHeight);
                    break;
                case 1:
                case 4:
                    v.texCoords = glm::vec2(0, (bandHeight * row));
                    break;
                case 2:
                case 3:
                    v.texCoords = glm::vec2(1, (bandHeight * row) + bandHeight);
                    break;
                case 5:
                    v.texCoords = glm::vec2(1, (bandHeight * row));
                    break;
            }

            vertices.emplace_back(v);


            // add objects
            if( (int) mapData.objectMap[index] < 255 ) {

                if( mapData.objectMap[index] > rscData.numModels ) {

                }
                else {
                    // if the object hasn't been added previously, create it and add to list of objects
                    if( objectPositions.find( mapData.objectMap[index] ) == objectPositions.end() ) {
                        auto mesh = std::make_unique<Mesh>( rscData.models[ mapData.objectMap[index] ].mesh );

                        objects[ mapData.objectMap[index] ] = std::move(mesh);
                    }

                    // add the current location to the list of positions for this object
                    objectPositions[ mapData.objectMap[index] ].push_back(
                            glm::vec3(v.position)
                    );
                }
            }
        }
    }

    num_strips = mapSize - 1;
    num_verts_per_strip = mapSize * 2;

    // generate indices in second loop
    for(unsigned int z = 0; z < mapSize-1; z++)       // for each row a.k.a. each strip
    {
        for(unsigned int x = 0; x < mapSize; x++)      // for each column
        {
            for(unsigned int t = 0; t < 2; t++)      // for each side of the strip
            {
                indices.push_back(x + mapSize * (z + t));
            }
        }
    }



    // print vertices for testing
    groundMesh = std::make_unique<Mesh>(vertices, indices);
    groundMesh->drawArrays = false; // draw indexed elements instead
    groundMesh->drawMode = GL_TRIANGLE_STRIP;

    printf("%d textures in rsc\n", rscData.numTextures);

    std::vector<unsigned short> stitchedTextures(rscData.numTextures * 128 * 128, 0);
    for(auto i=0; i < rscData.numTextures; i++) {
        memcpy(&stitchedTextures[i * 128 * 128], rscData.textures[i].data, rscData.textures[i].size);
    }

    groundMesh->textures.emplace_back( (char*) &stitchedTextures[0], 128, 128 * rscData.numTextures);
    // groundMesh->textures.emplace_back( (char*) rscData.textures[1].data, 128, 128);


    printf("# Vertices: %d\n# Indices: %d\n", vertices.size(), indices.size());


    // load skybox
    sky = std::make_unique<Skybox>( &rscData.sky[1][0] );
}

Terrain::~Terrain() {

}

void Terrain::handleEvent(const SDL_Event *e) {

}

void Terrain::update(double dt) {
    sky->update(dt);
}

void Terrain::draw() {
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);


    groundMesh->draw( shaders[TERRAIN_SHADER].get() );

    glDisable(GL_CULL_FACE);

    Frustum viewport( projection * globalCamera.view );


    for(auto& kv: objectPositions) {
        auto& mesh = objects[kv.first];

        // loop through positions
        for( auto i=0; i < kv.second.size(); i++ ) {

            // don't draw more than 100 of each item
            if(i > 1000) break;


            // if( viewport.IsBoxVisible(position - glm::vec3(.5, .5, .5), position + glm::vec3(.5, .5, .5)) ) {
                auto position = kv.second[i];
                glm::mat4 model = glm::mat4(1);
                model = glm::translate(model, position);

                shaders[MODEL_SHADER]->use();
                shaders[MODEL_SHADER]->setMat4("model", model);
                mesh->draw(shaders[MODEL_SHADER].get());
           //  }
        }
    }

    sky->render();
}

void Terrain::render() {
    draw();
}

bool Terrain::isInView(glm::vec3 vec1, glm::mat4 mat1, glm::mat4 mat2) {
    return false;
}

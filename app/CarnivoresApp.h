//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_CARNIVORESAPP_H
#define OPEN_CAR2_CARNIVORESAPP_H

#include <string>
#include <vector>

#include "App.h"

#include "globals.h"
#include "sfh/ocarn2.h"

class CarnivoresApp : public App {
protected:
    std::vector<std::string> models;
    std::vector<OCARN2::Mesh> meshes;

    void setup() override;
    void cleanup() override;
};


#endif //OPEN_CAR2_CARNIVORESAPP_H

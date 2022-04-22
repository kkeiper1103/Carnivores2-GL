cmake_minimum_required(VERSION 3.21)
project(open_car2)

set(CMAKE_CXX_STANDARD 20)

include_directories(core)
include_directories(app)


add_executable(open_car2
        main.cpp
        ext/glad/src/glad.c
        core/gui/nuklear.cpp

        core/App.cpp core/Camera.cpp
         app/CarnivoresApp.cpp core/entity/Entity.cpp
        app/globals.cpp core/graphics/Mesh.cpp
        core/graphics/Shader.cpp core/graphics/Texture.cpp
        app/Level/Terrain.cpp app/Objects/Skybox.cpp app/Objects/SquareMesh.cpp
        core/state/StateMachine.cpp core/state/BaseState.cpp app/State/HuntState.cpp  app/State/IntroState.cpp core/graphics/Model.cpp core/graphics/Model.h)

# executable to make sure the stb_ocarn2 file works
add_executable(ocarn2_test ocarn2_test.cpp)

add_executable(extract_textures texture_extractor.cpp)
target_include_directories(extract_textures PRIVATE ext)

target_include_directories(open_car2 PRIVATE ext/glad/include)
target_include_directories(open_car2 PRIVATE ext/SDL2-win/include)
target_include_directories(open_car2 PRIVATE ext)

target_link_directories(open_car2 PRIVATE ext/SDL2-win/lib)

target_link_libraries(open_car2 OpenGL32 SDL2 SDL2main)

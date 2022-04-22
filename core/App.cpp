//
// Created by kkeiper on 4/10/2022.
//

#include "App.h"
#include "Camera.h"
#include "graphics/Mesh.h"
#include "globals.h"
#include "Level/Terrain.h"
#include "Objects/SquareMesh.h"

#include "State/IntroState.h"
#include "State/HuntState.h"

App::App() {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);

    window = SDL_CreateWindow("Open Carnivores2",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screen_width, screen_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
                              );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    gl = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl);


    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Unable to load GladGL\n");
        exit(0);
    }



    printf("Finished Loading GL\n");

    clearScreen();
    SDL_GL_SetSwapInterval(1);


    stateMachine = std::make_unique<StateMachine>(window);

    stateMachine->set(STATE_INTRO, std::make_unique<IntroState>());
    stateMachine->set(STATE_PLAYING, std::make_unique<HuntState>());

    stateMachine->changeTo(STATE_INTRO);

    SDL_GL_SwapWindow(window);
}

App::~App() {
    SDL_GL_DeleteContext(gl);
    SDL_DestroyWindow(window);
}

/**
 *
 */
void App::loop() {
    clock_t now = clock();



    while(running) {
        clock_t dt = clock() - now;
        now = clock();



        SDL_Event e;
        nk_input_begin(nkCtx);
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = false;

            // change state
            if( e.type == SDL_USEREVENT && e.user.code == 101 ) {
                int stateId = *(int*) &e.user.data1;

                printf("Requested State: %d\n", stateId);

                stateMachine->changeTo( (STATES) stateId );
            }

            // pass input to state
            stateMachine->input(&e);

            // handle gui input
            nk_sdl_handle_event(&e);
        }
        nk_input_end(nkCtx);



        // update state
        stateMachine->update(dt);



        // render state
        clearScreen();

        stateMachine->render();

        SDL_GL_SwapWindow(window);
        SDL_Delay(1);
    }
}

int App::run() {
    setup();

    loop();

    cleanup();

    return 0;
}

void App::clearScreen() {

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);

    glViewport(0, 0, screen_width, screen_height);
    glClearColor(.1, .1, .1, 1);
    glClearDepth(10000);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

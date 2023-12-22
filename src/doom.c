#include <stdio.h>
#include <math.h>
#include </usr/include/SDL2/SDL.h>

// 4:3 aspect ratio
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// prepare a window and renderer for global access and initialization
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// initilize SDL with a nice function

int initSDL() {
    // check if the SDL video subsystem init function returned a error (-1)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed; see error: %s\n", SDL_GetError());
        return 0;
    }

    // replace the NULL with an actual window
    window = SDL_CreateWindow("FOOM, the better DOOM",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    // check if the window got created
    if (window == NULL) {
        printf("Window creation failed; see error: %s\n", SDL_GetError());
        return 0;
    }

    // create the render and enable hardware acceleration
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // check if the renderer got created / exists
    if (renderer == NULL) {
        printf("Renderer creation failed; see error; %s\n", SDL_GetError());
    }

    // staright black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    return 1;
}

// de-initialize all SDL stuff from ram 

void deinitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// render logic and stuff

void renderFrame() {
    // clear info
    SDL_RenderClear(renderer);
    
    // render stuff

    // output info
    SDL_RenderPresent(renderer);
}



int main(int argc, char *argv[])
{
    // init SDL
    if (!initSDL()) {
        // close main function and return error (1)
        return 1;
    }

    int is_window_closed = 0;
    SDL_Event event_queue;

    while (!is_window_closed) {
        //for fps purposes
        Uint64 start = SDL_GetPerformanceCounter(); 

        // check if there are any events (event loop)
        while(SDL_PollEvent(&event_queue) > 0) {
            // switch case statement for any events
            switch(event_queue.type)
            {
                case SDL_QUIT:
                    is_window_closed = 1;
                    break;
            }
        }

        // rendering !
        renderFrame();

        //for fps purposes
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        //fps cap
        SDL_Delay(floor(16.666f - elapsedMS));

    }


    return 0;
}
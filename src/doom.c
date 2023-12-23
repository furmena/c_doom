#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include </usr/include/SDL2/SDL.h>

// 4:3 aspect ratio
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// prepare a window and renderer for global access and initialization
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// structs (i just copied and tryed to understand how the code works ill make explation of how i understand in the markdown file once im finished with this project)
static struct sector
{
    float floor_height, ceiling_height; // each sector has a floor and ceiling height so yeah!
    struct xy 
    {
        float x_pos, y_pos;
    } *vertex; // nested struct inside the sector struct
    signed char *neighbors; // look man i need to do research abt this before wiriting more commment
    unsigned vertex_amount; // int tyoe is assumed
} *sectors = NULL; // ok so i think i kinda got it i defined a sturct (sector) and 
static unsigned sector_amount = 0;

// again i copied this most of the sector is just gonna be copied from bisqwits vidoe
static struct player
{
    struct xyz { float x, y, z; } player_position, player_velocity;
    float angle, angle_sin, angle_cos, yaw;
    unsigned sector; // what secotor im in
} player;

static void loadMapData() {
    const char *resource_folder = "../res";
    // const char *resource_folder = "..\\res" for windows users i think
    struct stat sb;
    
    if ((stat(resource_folder, &sb)) == 0 && S_ISDIR(sb.st_mode))
    {
        printf("YIPPE!");
    } else
    {
        perror("Cannot find directory \"..\\res\"; see error: ");
    }
}

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

    int is_window_closed = 1;
    SDL_Event event_queue;
    SDL_GL_SetSwapInterval(1);

    
    while (is_window_closed) {
        Uint64 start = SDL_GetPerformanceCounter(); 

        // check if there are any events (event loop)
        while(SDL_PollEvent(&event_queue) > 0) {
            // switch case statement for any events
            switch(event_queue.type)
            {
                case SDL_QUIT:
                    is_window_closed = 0;
                    break;
            }
        }

        // rendering !
        renderFrame();

        //for fps purposes
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        //fps cap
        if (!floor(16.666f - elapsedMS) < 0.0f)
        {
        SDL_Delay((floor(16.666f - elapsedMS)));
        }
    }
    return 0;
}
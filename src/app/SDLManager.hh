#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class SDLManager {
public:
    SDLManager(int w, int h);
    ~SDLManager();
    SDL_Window* window;
    SDL_Renderer* renderer;
    // Other SDL properties
};
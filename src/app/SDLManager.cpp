#include "SDLManager.hh"
#include <string>
#include <stdexcept>
SDLManager::SDLManager(int w, int h){
    // Initialisation de la fenêtre et du renderer
    window = SDL_CreateWindow("PPM Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!window) {
        std::string errorMsg = "Window could not be created! SDL_Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw std::runtime_error(errorMsg);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        std::string errorMsg = "Renderer could not be created! SDL Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw std::runtime_error(errorMsg);
    }
}

SDLManager::~SDLManager(){
    // Nettoyage de SDL avant de quitter
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


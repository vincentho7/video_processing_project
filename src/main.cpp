#include "Image.hh"
#include "App.hh"
#include "SDLManager.hh"
#include <iostream>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    Application app;
    app.run(argc, argv);
    return 0;
}
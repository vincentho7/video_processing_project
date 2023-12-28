#include "Image.hh"
#include "App.hh"
#include "SDLManager.hh"
#include <iostream>
#include <string>

std::string ensureTrailingSlash(std::string path) {
    if (!path.empty() && path.back() != '/') {
        path += '/';
    }
    return path;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    std::string pgmDir, ppmDir;
    std::cout << "Enter the location for the 'pgm' directory: ";
    std::getline(std::cin, pgmDir);
    std::cout << "Enter the location for the 'ppm' directory: ";
    std::getline(std::cin, ppmDir);

    Application app;
    app.PGMdirname = ensureTrailingSlash(pgmDir);
    app.PPMdirname = ensureTrailingSlash(ppmDir);
    app.run(argc, argv);
    return 0;
}
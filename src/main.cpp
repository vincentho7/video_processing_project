#include "Image.hh"
#include "App.hh"
#include "SDLManager.hh"
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string ensureTrailingSlash(std::string path) {
    if (!path.empty() && path.back() != '/') {
        path += '/';
    }
    return path;
}
int countPGMFiles(const std::string& directory) {
    int count = 0;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".pgm") {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
     std::string pgmDir, ppmDir, nbpgmInput;
    int nb_pgm;

    std::cout << "Enter the location for the 'pgm' directory: ";
    std::getline(std::cin, pgmDir);
    std::cout << "Enter the location for the 'ppm' directory: ";
    std::getline(std::cin, ppmDir);
    std::cout << "Enter the number of frames to process (type 'all' to select all pgm): ";
    std::getline(std::cin, nbpgmInput);

    if (nbpgmInput == "all") {
        nb_pgm = countPGMFiles(pgmDir);
        std::cout << "All files selected. Count: " << nb_pgm << std::endl;
    } else {
        try {
            nb_pgm = std::stoi(nbpgmInput);
            std::cout << "Number of Frames specified: " << nb_pgm << std::endl;
        } catch (std::exception& e) {
            std::cerr << "Invalid input for number of frames. Error: " << e.what() << std::endl;
            return -1;
        }
    }
    Application app;
    app.PGMdirname = ensureTrailingSlash(pgmDir);
    app.PPMdirname = ensureTrailingSlash(ppmDir);
    app.frameCount = nb_pgm;
    app.run(argc, argv);
    return 0;
}
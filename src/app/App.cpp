#include "App.hh"
#include "SDLManager.hh"
#include "Image.hh"
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>  
#include <sstream> 
#include <filesystem>

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Function to create a directory and verify its existence
void createAndVerifyDirectory(const std::string& dirName) {
    // Create the directory if it doesn't exist
    if(!fs::exists(dirName)) {
        if(fs::create_directory(dirName)) {
            std::cout << "Directory '" << dirName << "' created successfully.\n";
        } 
    }
}

void Application::processArguments(int argc, char* argv[]){
    //ARGUMENT PARSING
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--fps") {
            if (i + 1 < argc) { 
                frameRate = std::stoi(argv[i + 1]); // Convertir l'argument suivant en entier
                i++; 
            } else {
                std::cerr << "Expected number after --fps" << std::endl;
                
            }
        }
        else if (arg == "--frame_period") {
            if (i + 1 < argc) {
                framePeriodClocks = static_cast<unsigned int>(std::stoi(argv[i + 1]));
                if(framePeriodClocks > 0) {
                    frameRate = 27000000 / framePeriodClocks; // Calculer le framerate basé sur framePeriod
                }
                i++; // Incrémenter i pour sauter la valeur que nous venons de lire
            } else {
                throw std::runtime_error( "Expected number after --frame_period");
            }
        }

        else if (arg == "--bob") {
            bob = true; // Activer le mode bob
            std::cout << "bOb is true" << std::endl;
        }
        if (arg == "--shake") {
            shake = true;
            frameRate *= 2;
        }
    }
    std::cout << "Frame Rate is set to: " << frameRate << " fps" << std::endl;
}
void Application::run(int argc, char* argv[]){
    processArguments(argc, argv);
    Uint32 frameDelay = 1000 / frameRate;
    SDLManager sdlm(800, 600);
    int img_height = 0;
    int img_width = 0;
    int j = 0;
    createAndVerifyDirectory("ppm");

    for(int i = 0; i < frameCount; ++i){
        Uint32 frameStart = SDL_GetTicks();
        std::string fileName = PGMdirname + std::to_string(i) + ".pgm";
        std::ifstream input(fileName, std::ios::binary);

        if (!input.is_open()) {
            std::cerr << "Erreur lors de l'ouverture de l'image " << fileName << "\n";
            continue; // Passer à l'image suivante si celle-ci ne peut pas être ouverte
        }
        // Ignorer l'entête PGM pour l'instant (Assumons qu'il est correct)
        std::string header;
        std::getline(input, header); // P5
        std::getline(input, header); //Comments
       
        std::istringstream dimensions(header);
        dimensions >> img_width >> img_height;

        int Yheight = img_height * 2 / 3;
        int uv_width = img_width / 2, uv_height = Yheight / 2;
        std::getline(input, header); // Max value
        
        // Reading Image pixels & copy in buffer
        std::vector<unsigned char> image(img_width * Yheight * 3);
        input.read(reinterpret_cast<char*>(image.data()),image.size());
        input.close(); // closing file
        // Y & U & V Component Images
        int Ysize = Yheight * img_width;
        int UVsize = uv_height * uv_width;
        std::vector<unsigned char> U(image.begin() + Ysize, image.begin() + Ysize + UVsize);
        std::vector<unsigned char> V(image.begin() + Ysize + UVsize, image.end());
        
        for (int x = 0; x < uv_height; x++)
        {
            for (int y = 0; y < uv_width; y++)
            {
                int index = x * img_width + y;
                U[x * uv_width + y] = image[Ysize + index];
                V[x * uv_width + y] = image[Ysize + uv_width + index];
            }
        }
        RGBImage rgb_img = RGBImage::yuv_to_rgb(image, U,V, img_width, Yheight);
        
        if (bob) {
            //std::vector<RGBImage> deinterlaced = RGBImage::bobDeinterlace(rgb_img);
            std::vector<std::vector<uint8_t>> deinterlaced = RGBImage::bobDeinterlace(rgb_img.data, img_width, Yheight);
            int f = 0;
            for (auto& frame : deinterlaced) { // Traite chaque image désentrelacée
                if (f % 2 == 0 && shake == true) {
                    f++;
                    continue;
                }
                std::string imagePath = "image_" + std::to_string(j) + ".ppm"; 
                std::ofstream output(imagePath, std::ios::binary);
                // std::cout << frame.data.size() << std::endl;
                // output << "P6\n" << img_width << " " <<  Yheight << "\n255\n";
                // output.write(reinterpret_cast<char*>(&frame.data[0]), frame.data.size());
                // output.close();
                output << "P6\n" << img_width << " " <<  Yheight << "\n255\n";
                output.write(reinterpret_cast<char*>(&frame[0]), frame.size());
                output.close();
                SDL_Surface* ppmImage = IMG_Load(imagePath.c_str());
                SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlm.renderer, ppmImage);
                SDL_FreeSurface(ppmImage);

                SDL_RenderClear(sdlm.renderer);
                SDL_RenderCopy(sdlm.renderer, texture, NULL, NULL);
                SDL_RenderPresent(sdlm.renderer);
                SDL_DestroyTexture(texture); // Libérer la texture après utilisation

                Uint32 frameTime = SDL_GetTicks() - frameStart;
                if (f == 0) {
                    if (frameDelay > frameTime) { 
                        SDL_Delay(frameDelay - frameTime);
                    }
                }
                else {
                    if (2 * frameDelay > frameTime) { 
                        SDL_Delay(2 * frameDelay - frameTime);
                    }
                }
                j = j + 1;
                f = f + 1;
            }
        }
        else {
            std::string imagePath = "image_" + std::to_string(i) + ".ppm"; // Nom unique pour chaque image
            std::ofstream output(imagePath, std::ios::binary);
            output << "P6\n" << img_width << " " << Yheight << "\n255\n";
            output.write(reinterpret_cast<char*>(&rgb_img.data[0]), rgb_img.data.size());
            output.close();

            // Charger l'image convertie en tant que texture et l'afficher
            SDL_Surface* ppmImage = IMG_Load(imagePath.c_str());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlm.renderer, ppmImage);
            SDL_FreeSurface(ppmImage);

            SDL_RenderClear(sdlm.renderer);
            SDL_RenderCopy(sdlm.renderer, texture, NULL, NULL);
            SDL_RenderPresent(sdlm.renderer);

            SDL_DestroyTexture(texture); // Libérer la texture après utilisation

            // Contrôler le framerate
            Uint32 frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
}
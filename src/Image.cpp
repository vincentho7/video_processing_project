#include "Image.hh"
#include <cmath>


RGBImage RGBImage::yuv_to_rgb(const std::vector<unsigned char>& Y, const std::vector<unsigned char>& U,const std::vector<unsigned char>& V, int width, int height){
    RGBImage img(width, height);
    std::vector<uint8_t> r_U(width * height);
    std::vector<uint8_t> r_V(width * height);
    for (int y = 0; y < height ; ++y) {
        for (int x = 0; x < width; ++x) {
            int uvIndex = (y/2) * (width / 2) + (x / 2);
            r_U[y * width + x] = U[uvIndex];
            r_V[y * width + x] = V[uvIndex];
        }
    }

    for (int y = 0; y < height ; ++y) {
        for (int x = 0; x < width; ++x) {
            // Obtenir l'index linéaire pour le pixel (x, y)
            int i = y * width + x;

            // Conversion YUV à RGB
            int Y_val = Y[i];
            
            int U_val = r_U[i] - 128; // Centrer à 0
            int V_val = r_V[i] - 128; // Centrer à 0

            int R = std::max(0, std::min(255, Y_val + (int)(1.402 * V_val)));
            int G = std::max(0, std::min(255, Y_val - (int)(0.344 * U_val + 0.714 * V_val)));
            int B = std::max(0, std::min(255, Y_val + (int)(1.772 * U_val)));
            
            
            img.data[3 * i] = static_cast<uint8_t>(R);
            img.data[3 * i + 1] = static_cast<uint8_t>(G);
            img.data[3 * i + 2] = static_cast<uint8_t>(B);
        }
    }
    return img;
}

std::vector<RGBImage> RGBImage::bobDeinterlace(const RGBImage& interlaced_rgb) {
    // Créer deux vecteurs pour les images désentrelacées de la même taille que l'image entrelacée
    RGBImage evenLines(interlaced_rgb);
    RGBImage oddLines(interlaced_rgb);

    int height = interlaced_rgb.height;
    int width = interlaced_rgb.width;

    for (int y = 0; y < height; y += 2) { // Parcourir chaque ligne
        for (int x = 0; x < width; ++x) {
            for (int color = 0; color < 3; ++color) {
                int index_line = 6 * width * (y / 2) + 3 * x + color;
                int next_line = index_line + 3 * width;
                int even_index = 3 * width * y + 3 * x + color;
                int odd_index = 3 * width * (y + 1) + 3 * x + color;
                // Double chaque ligne paire pour evenLines
                evenLines.data[index_line] = interlaced_rgb.data[even_index];
                evenLines.data[next_line] = interlaced_rgb.data[even_index];
                
                // Double chaque ligne impaire pour oddLines
                oddLines.data[index_line] = interlaced_rgb.data[odd_index];
                oddLines.data[next_line] = interlaced_rgb.data[odd_index];
            }
        }
    }
    return {evenLines, oddLines}; // Retourner les deux images désentrelacées
}
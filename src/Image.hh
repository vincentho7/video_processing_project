#pragma once
#include <vector>
#include <cstdint>
class RGBImage {
public:
    RGBImage() : width(0), height(0) {}
    RGBImage(int w, int h) : width(w), height(h), data(w * h * 3) {}
    RGBImage(const RGBImage& other) : width(other.width), height(other.height), data(other.width * other.height * 3) {}
    int width;
    int height;
    std::vector<uint8_t> data;
    static RGBImage yuv_to_rgb(const std::vector<uint8_t>& Y, const std::vector<unsigned char>& U,const std::vector<unsigned char>& V, int width, int height);
    static std::vector<RGBImage> bobDeinterlace(const RGBImage& interlaced_rgb); 
    static std::vector<std::vector<uint8_t>> bobDeinterlace(const std::vector<uint8_t>& rgb, int width, int height);

};
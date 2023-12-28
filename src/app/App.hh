#pragma once
#include <string>
class Application {
public:
    Application() :  frameCount(60), frameRate(12000), framePeriodClocks(0), bob(false) {}
    int frameCount, frameRate;
    unsigned int framePeriodClocks = 0;
    bool bob;
    bool shake = false;
    std::string PGMdirname;
    std::string PPMdirname;
    void run(int argc, char* argv[]);
private:
    void processArguments(int argc, char* argv[]);
};
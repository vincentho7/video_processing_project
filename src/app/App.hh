#pragma once
#include <string>
class Application {
public:
    Application() :  frameCount(30), frameRate(58), framePeriodClocks(0), bob(false) {}
    Application(int frate, int fcount) :  frameCount(fcount), frameRate(frate),framePeriodClocks(0), bob(false) {}
    int frameCount, frameRate;
    unsigned int framePeriodClocks;
    bool bob;
    std::string PGMdirname;
    std::string PPMdirname;
    void run(int argc, char* argv[]);
private:
    void processArguments(int argc, char* argv[]);
    void mainLoop();  
};
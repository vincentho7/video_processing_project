#pragma once
#include <string>
class Application {
public:
    Application() :  frameCount(30), frameRate(58),PGMdirectory("../TP/videos/"), framePeriodClocks(0), bob(false) {}
    Application(int frate, int fcount, std::string dir) :  frameCount(fcount), frameRate(frate), PGMdirectory(dir),framePeriodClocks(0), bob(false) {}
    int frameCount, frameRate;
    std::string PGMdirectory;
    unsigned int framePeriodClocks;
    bool bob;
    void run(int argc, char* argv[]);
private:
    void processArguments(int argc, char* argv[]);
    void mainLoop();
    
};
#ifndef FRAMEPACER_H

#include <chrono>
#include <thread>
#include <vector>

class Framepacer {
    public:
        // I don't really need a default constructor, for this member function. Compiler wasn't happy so I had to specify to use DMI
        Framepacer() = default;
        void Start();
        void End();
        void targetFramerate(unsigned int fpsTarget);

        float avgFPS = 0;
        float deltatime = 0.f;

    private:
        std::chrono::time_point<std::chrono::steady_clock> frameTimeStart;
        std::chrono::time_point<std::chrono::steady_clock> frameTimeEnd;
        std::chrono::microseconds frametimeTarget;
        std::chrono::microseconds frametimeDuration;

        unsigned int fpsTarget = 0;

        std::chrono::milliseconds avgSampleInterval = std::chrono::milliseconds(500);
        std::chrono::microseconds avgSum = std::chrono::microseconds(0);
        unsigned int avgFramesSampled = 0;
        // std::chrono automatically initilizes with time since epoch
        std::chrono::time_point<std::chrono::steady_clock> avgSampleStart;

};

#endif
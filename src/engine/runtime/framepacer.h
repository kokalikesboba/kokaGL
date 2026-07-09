#ifndef FRAMEPACER_H

#include <chrono>
#include <thread>
#include <vector>

class Framepacer {
public:
    Framepacer();
    void Start();
    void End();

    void SetTargetFramerate(unsigned int fpsTarget);

    float GetAvgFPS() const;
    float GetDeltaTime() const;
    // Returns time since program start in milliseconds.
    unsigned int GetTime() const;
private:
    std::chrono::time_point<std::chrono::steady_clock> programEpoch;
    std::chrono::time_point<std::chrono::steady_clock> frameTimeStart;
    std::chrono::time_point<std::chrono::steady_clock> frameTimeEnd;
    std::chrono::microseconds frametimeTarget;
    std::chrono::microseconds frametimeDuration;

    long long int fpsTarget = 0;
    float avgFPS = 0.f;
    float deltatime = 0.f;

    std::chrono::milliseconds avgSampleInterval = std::chrono::milliseconds(500);
    std::chrono::microseconds avgSum = std::chrono::microseconds(0);
    unsigned int avgFramesSampled = 0;
    // std::chrono automatically initilizes with time since epoch
    std::chrono::time_point<std::chrono::steady_clock> avgSampleStart;
};

#endif
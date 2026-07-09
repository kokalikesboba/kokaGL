#include "framepacer.h"

Framepacer::Framepacer()
{
    programEpoch = std::chrono::steady_clock::now();
}

void Framepacer::Start()
{
    frameTimeStart = std::chrono::steady_clock::now();
}

void Framepacer::End() {
    frameTimeEnd = std::chrono::steady_clock::now();
    frametimeDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameTimeEnd - frameTimeStart);
    deltatime = frametimeDuration.count() / 1000000.f;

    if (fpsTarget != 0 && frametimeDuration < frametimeTarget) {
        std::this_thread::sleep_for(frametimeTarget - frametimeDuration);
        // By definition, setting a frametarget fixes deltatime
        deltatime = frametimeTarget.count() / 1000000.f;
        
        // purely for avgFPS counter
        frametimeDuration = frametimeTarget;
    }

    // FPS stat handling
    avgSum += frametimeDuration;
    ++avgFramesSampled;
    if ((avgSampleStart + avgSampleInterval) < std::chrono::steady_clock::now()) {

        avgFPS = 1000000.f / (avgSum.count() / (float)avgFramesSampled);

        avgSampleStart = std::chrono::steady_clock::now();
        avgSum = std::chrono::microseconds(0);
        avgFramesSampled = 0;
    }

}

float Framepacer::GetAvgFPS() const
{
    return avgFPS;
}

float Framepacer::GetDeltaTime() const
{
    return deltatime;
}

// Returns time since program started in seconds. 
unsigned int Framepacer::GetTime() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - programEpoch).count();
}

void Framepacer::SetTargetFramerate(unsigned int fpsTarget) {
    this->fpsTarget = fpsTarget;
    if (fpsTarget) {
        frametimeTarget = std::chrono::microseconds(1000000 / fpsTarget);
    }
}
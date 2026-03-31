#include "framepacer.h"

Framepacer::Framepacer()
{

}

void Framepacer::Start()
{   
    frameTimeStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

void Framepacer::End()
{
    frameTimeEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    deltatime = std::chrono::duration<float>(frameTimeEnd - frameTimeStart).count();
}

float Framepacer::getDeltatime()
{
    return deltatime;
}

/* void Renderer::fpsStatsStart()
{
    auto frametimeTarget = std::chrono::duration<float, std::milli>(1000.0f / fpsTarget);
}

void Renderer::fpsStatsEnd()
{
    frametimeSum += frametimeActual;
    sampledFrames += 1.f;
    if ((fpsSampleBegin + std::chrono::milliseconds(sampleInterval)) < std::chrono::steady_clock::now()) {
        avgFPS = 1000.f / (std::chrono::duration<float, std::milli>(frametimeSum).count() / sampledFrames); 
        fpsSampleBegin = std::chrono::steady_clock::now();
        frametimeSum = std::chrono::milliseconds(0);
        sampledFrames = 0;
    };
}

auto frametimeEnd = std::chrono::steady_clock::now();
auto frametimeElapsed = frametimeEnd - frametimeStart;

if (limitFPS && frametimeElapsed < frametimeTarget) {
    std::this_thread::sleep_for(frametimeTarget - (frametimeElapsed));
}*/
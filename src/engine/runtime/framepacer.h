#ifndef FRAMEPACER_H

#include <chrono>
#include <thread>

class Framepacer {
    public:
        Framepacer();
        void Start();
        void End();
        float getDeltatime();
        
    private:
        int64_t frameTimeStart = 0;
        int64_t frameTimeEnd = 0;
        float deltatime = 1.f;


        unsigned int fpsTarget = 60;
        /* void fpsStatsStart();
        void fpsStatsEnd();
        std::chrono::milliseconds fpsAvgSampleBegin = std::chrono::milliseconds(0);
        std::chrono::milliseconds fpsAvgFrametimeSum = std::chrono::milliseconds(0);
        unsigned int fpsAvgsampleInterval = 1000;
        unsigned int sampledFrames = 0;
        float avgFPS = 0;
        

    	bool limitFPS = true;*/
};

#endif
#pragma once
#include <SDL3/SDL.h>

class Timer
{
    private:
        Uint64 mStartTicks;

    public:
        Timer();
        void start();
        Uint64 getTicksNS();
};
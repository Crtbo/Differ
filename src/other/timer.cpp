#include "../../include/other/timer.hpp"

Timer::Timer()
{
    mStartTicks = 0;
}

void Timer::start()
{
    mStartTicks = SDL_GetTicksNS();
}

Uint64 Timer::getTicksNS()
{
    Uint64 time = SDL_GetTicksNS() - mStartTicks;
    return time;
}
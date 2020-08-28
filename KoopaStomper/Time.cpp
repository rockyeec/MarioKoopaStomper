#include "Time.h"
#include <SDL.h>

//temp
//using namespace std::chrono;

Time::Time()
{
    mOldTime = (float)SDL_GetTicks();

    
    // temp 
    //last = steady_clock::now();
}

Time& Time::GetInstance()
{
    static Time time;
    return time;
}

const void Time::Update()
{
    const float newTime = (float)SDL_GetTicks();
    float& oldTime = GetInstance().mOldTime;
    GetInstance().mDeltaTime = (newTime - oldTime) / 1000.0f;
    oldTime = newTime;

    // temp
    /*const auto old = GetInstance().last;
    GetInstance().last = steady_clock::now();
    const duration<float> frameTime = GetInstance().last - old;
    GetInstance().mDeltaTime = frameTime.count();*/
}

const float Time::GetDeltaTime()
{
    return GetInstance().mDeltaTime;
}

const float Time::GetFixedDeltaTime()
{
    return GetInstance().mFixedDeltaTime;
}


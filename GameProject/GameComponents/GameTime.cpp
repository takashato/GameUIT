#include "GameTime.h"

GameTime* GameTime::mInstance = NULL;

GameTime::GameTime()
{

}

GameTime::~GameTime()
{
}

GameTime* GameTime::GetInstance()
{
    if (!mInstance)
        mInstance = new GameTime();

    return mInstance;
}

void GameTime::StartCounter()
{
    if (!QueryPerformanceFrequency(&mClockRate))
    {
        return;
    }

    QueryPerformanceCounter(&mStartTime);
    
}

float GameTime::GetCouter()
{
    QueryPerformanceCounter(&mEndTime);
    mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;

    return ((float)mDelta.QuadPart / mClockRate.QuadPart);
}

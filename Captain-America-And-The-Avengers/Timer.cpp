#include "pch.h"
#include "Timer.h"

Timer& Timer::GetInstance()
{
	static Timer timer;
	return timer;
}

void Timer::Update()
{
	previousTime = currentTime;
	currentTime = std::chrono::steady_clock::now();

	std::chrono::duration<float> duration = currentTime - previousTime;
	
	deltaTime = duration.count();

	fps = 1.0F / deltaTime;
}

float Timer::Get()
{
	return deltaTime;
}

float Timer::GetFPS()
{
	static float timePassed = 0.0f;
	static float fps = 0;
	static int nFrame = 0;

	nFrame++;
	timePassed += deltaTime;

	if (timePassed >= 1.0f)
	{
		fps = static_cast<float>(nFrame);
		nFrame = 0;
		timePassed -= 1.0f;
	}

	return fps;
}

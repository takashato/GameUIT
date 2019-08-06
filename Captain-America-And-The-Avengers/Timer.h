#pragma once
#include <chrono>

class Timer : ISingleton {
private:
	std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	float deltaTime = 0.0F;
	float fps = 0.0F;

public:
	static Timer& GetInstance();

	void Update();
	float Get();
	float GetFPS();
	static float Dt() { return GetInstance().deltaTime; }
private:
	Timer() : ISingleton(NULL) {};
};
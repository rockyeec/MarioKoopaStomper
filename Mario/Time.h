#pragma once

//#include <chrono>

class Time
{
public:
	static const void Update();
	static const float GetDeltaTime();
	static const float GetFixedDeltaTime();

private:
	Time();
	static Time& GetInstance();

private:
	float mOldTime = 0.0f;
	float mDeltaTime = 0.0f;
	float mFixedDeltaTime = 0.02f;

	// temp
	//std::chrono::steady_clock::time_point last;
};
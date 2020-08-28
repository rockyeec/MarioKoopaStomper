#pragma once
#include <random>

class Random
{
public:
	static float GetRandomFloat(const float& min, const float& max);
	static int GetRandomInt(const int& min, const int& max);

private:
	Random();
	static Random& GetInstance();

private:
	std::mt19937 mRng;
};
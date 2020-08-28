#include "Random.h"

float Random::GetRandomFloat(const float& min, const float& max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(GetInstance().mRng);
}

int Random::GetRandomInt(const int& min, const int& max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetInstance().mRng);
}

Random::Random()
	:
	mRng(std::random_device()())
{
	
}

Random& Random::GetInstance()
{
	static Random random;
	return random;
}

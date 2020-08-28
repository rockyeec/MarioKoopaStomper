#pragma once


struct Mathf
{
	template<typename T>
	static const T Abs(const T& value)
	{
		return value < 0 ? -value : value;
	}

	template<typename T>
	static void Clamp(const T& a, const T& b, T& value)
	{
		if (value < a)
		{
			value = a;
		}
		else if (value > b)
		{
			value = b;
		}
	}

	template<typename T>
	static const T Clamp(const T& a, const T& b, const T& value)
	{
		if (value < a)
		{
			return a;
		}
		else if (value > b)
		{
			return b;
		}
		return value;
	}
	
	template<typename T>
	static const T Lerp(const T& start, const T& end, const T& percent)
	{
		return start + (percent * (end - start));
	}

	template<typename T>
	static const T MoveTowards(const T& start, const T& end, const T& speed)
	{
		const T distance = Abs(end - start);
		if (distance < speed)
		{
			return end;
		}
		else
		{
			return start + (start < end ? speed : -speed);
		}
	}

	static constexpr float pi = 3.142f;
	static constexpr float deg2rad = pi / 180.0f;
	static constexpr float rad2deg = 180.0f / pi;
};
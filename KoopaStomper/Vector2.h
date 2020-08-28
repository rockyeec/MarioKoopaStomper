#pragma once
#include "Mathf.h"
#include <math.h>

template<typename T>
struct Vector2
{
	T x;
	T y;

	Vector2() : x(0), y(0) {}
	Vector2(const Vector2& value) : x(value.x), y(value.y) {}
	Vector2(const T& x, const T& y) : x(x), y(y) {}
	Vector2(const T& value) : x(value), y(value) {}

	static Vector2 Lerp(const Vector2& a, const Vector2& b, const float& percent)
	{
		return
		{
			Mathf::Lerp<float>(a.x, b.x, percent),
			Mathf::Lerp<float>(a.y, b.y, percent)
		};
	}

	static Vector2 MoveTowards(const Vector2& a, const Vector2& b, const float& speed)
	{
		return
		{
			Mathf::MoveTowards<float>(a.x, b.x, speed),
			Mathf::MoveTowards<float>(a.y, b.y, speed)
		};
	}


	Vector2 operator + (const Vector2& other) const
	{
		return { x + other.x, y + other.y };
	}
	Vector2 operator - (const Vector2& other) const
	{
		return { x - other.x, y - other.y };
	}
	Vector2 operator * (const T& other) const
	{
		return { x * other, y * other };
	}
	Vector2 operator / (const T& other) const
	{
		return { x / other, y / other };
	}
	Vector2 operator / (const Vector2& other) const
	{
		return { x / other.x, y / other.y };
	}
	Vector2& operator += (const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator -= (const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& operator *= (const T& other)
	{
		x *= other;
		y *= other;
		return *this;
	}
	Vector2& operator /= (const T& other)
	{
		x /= other;
		y /= other;
		return *this;
	}
	T GetSquareMagnitude() const
	{
		return x * x + y * y;
	}
	T GetMagnitude() const
	{
		return T(sqrtf((float)GetSquareMagnitude()));
	}
	Vector2 GetNormal() const
	{
		return *this / GetMagnitude();
	}
	Vector2& Normalize()
	{
		return *this /= GetMagnitude();
	}

	T GetDegrees() const
	{
		return GetRadians() * Mathf::rad2deg;
	}
	float GetRadians() const
	{
		return atan2f((float)y, (float)x);
	}

	bool operator == (const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator != (const Vector2& other) const
	{
		return !(x == other.x && y == other.y);
	}

};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
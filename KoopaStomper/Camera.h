#pragma once
#include "Vector2.h"
#include "GameObject.h"

class Camera
{
public:
	~Camera();
	static const Vector2f& GetPosition();
	static const Vector2f& GetCenterPosition();

	static void Update(const Vector2f& focusPoint);
	static void Shake();
	static const bool IsWithinFOV(const Vector2f& centerPoint);

private:
	Camera();
	static Camera& GetInstance();
	static void SetPosition(const Vector2f& position);
	static void SetCenterPosition(const Vector2f& position);

private:
	Vector2f mPosition;
	Vector2f mScreenCenterOffset;
	Vector2f mCenterPosition;
	float mShakeTimer = 1000.0f;
	float mWobble = 0.0f;
};
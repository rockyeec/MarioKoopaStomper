#include "Camera.h"
#include "Mathf.h"
#include "Constants.h"
#include "Mathf.h"
#include "Time.h"

Camera& Camera::GetInstance()
{
    static Camera camera;
    return camera;
}


Camera::Camera()
    :
    mScreenCenterOffset({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }),
    mCenterPosition(mPosition + mScreenCenterOffset)
{
}

Camera::~Camera()
{
}

const Vector2f& Camera::GetPosition()
{
    return GetInstance().mPosition;
}

void Camera::SetPosition(const Vector2f& position)
{
    const float x = Mathf::Clamp<float>(0, (float)(GAME_WIDTH - SCREEN_WIDTH), position.x);
    const float y = Mathf::Clamp<float>(0, (float)(GAME_HEIGHT - SCREEN_HEIGHT), position.y);

    const Vector2f pos(x, y);
    GetInstance().mPosition = pos;
    GetInstance().mCenterPosition = pos + GetInstance().mScreenCenterOffset;
}

const Vector2f& Camera::GetCenterPosition()
{
    return GetInstance().mCenterPosition;
}

void Camera::Update(const Vector2f& focusPoint)
{
    static constexpr float magnitude = 16.9f;
    static constexpr float duration = 0.2f;
    float& wobble = GetInstance().mWobble;
    float& timer = GetInstance().mShakeTimer;
    if (timer < duration)
    {
        timer += Time::GetFixedDeltaTime();
        const float offset = magnitude * sinf(++wobble);

        SetCenterPosition({ focusPoint.x, offset + focusPoint.y });
    }
    else
    {
        SetCenterPosition(focusPoint);
    }
}

void Camera::Shake()
{
    GetInstance().mShakeTimer = 0.0f;
    GetInstance().mWobble = 0.0f;
}

const bool Camera::IsWithinFOV(const Vector2f& centerPoint)
{
    const float& x = centerPoint.x;
    const float& y = centerPoint.y;

    return x >= GetPosition().x - float(TILE_WIDTH) && x <= GetPosition().x + SCREEN_WIDTH  + float(TILE_WIDTH)
        && y >= GetPosition().y - float(TILE_HEIGHT) && y <= GetPosition().y + SCREEN_HEIGHT + float(TILE_HEIGHT);
}

void Camera::SetCenterPosition(const Vector2f& position)
{
    SetPosition(position - GetInstance().mScreenCenterOffset);
}

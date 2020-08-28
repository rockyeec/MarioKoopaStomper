#include "Transform.h"
#include "Mathf.h"
#include "Constants.h"
#include "Collisions.h"

Transform::Transform(GameObject& gameObject)
    :
    mGameObject(gameObject),
    mScale({ 1 }),
    mRotation(0)
{
}

Transform::~Transform()
{
}

const Vector2f& Transform::GetPosition() const
{
    return mPosition;
}

const Vector2f& Transform::GetCenterPosition() const
{
    const Vector2f& halfSize = mGameObject.GetTexture().GetSizeFloat() / 2;
    return mPosition + halfSize;
}

const Vector2f& Transform::GetScale() const
{
    return mScale;
}

const float& Transform::GetRotation() const
{
    return mRotation;
}

void Transform::SetPosition(const Vector2f& newPosition)
{
    mPosition = newPosition;
    mGameObject.GetBox().SetPosition(newPosition);
    Collisions::OccupyCell(mGameObject.GetBox(), mGameObject.GetBox());
}

void Transform::SetCenterPosition(const Vector2f& newPosition)
{
    const Vector2f& halfSize = mGameObject.GetTexture().GetSizeFloat() / 2;
    SetPosition(newPosition - halfSize);
}

void Transform::Translate(const Vector2f& amount)
{
    SetPosition(mPosition + amount);
}

void Transform::SetScale(const Vector2f& newScale)
{
    mScale = newScale;
    mGameObject.GetTexture().SetSizeWithScale(newScale);
    mGameObject.GetBox().SetSize(mGameObject.GetTexture().GetSizeFloat());
}

void Transform::SetScaleCenter(const Vector2f& newScale)
{
    const Vector2f center = GetCenterPosition();
    SetScale(newScale);
    SetCenterPosition(center);
}

void Transform::Grow(const Vector2f& amount)
{
    const float& feetLevel = mPosition.y + mGameObject.GetBox().GetSize().y;
    SetScale(mScale + amount);
    SetPosition(Vector2f(mPosition.x, feetLevel - mGameObject.GetBox().GetSize().y));
}

void Transform::SetRotation(const float& newRotation)
{
    mRotation = newRotation;
    while (mRotation < 0.0f)
    {
        mRotation += 360.0f;
    }
    while (mRotation > 360.0f)
    {
        mRotation -= 360.0f;
    }
}

void Transform::Rotate(const float& degrees)
{
    SetRotation(mRotation + degrees);    
}

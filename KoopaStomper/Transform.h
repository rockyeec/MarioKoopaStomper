#pragma once
#include "Vector2.h"
#include "GameObject.h"

class GameObject;

class Transform
{
public:
	Transform(GameObject& gameObject);
	~Transform();

	const Vector2f& GetPosition() const;
	const Vector2f& GetCenterPosition() const;
	const Vector2f& GetScale() const;
	const float& GetRotation() const;
	void SetPosition(const Vector2f& newPosition);
	void SetCenterPosition(const Vector2f& newPosition);
	void Translate(const Vector2f& amount);
	void SetScale(const Vector2f& newScale);
	void SetScaleCenter(const Vector2f& newScale);
	void Grow(const Vector2f& amount);
	void SetRotation(const float& newRotation);
	void Rotate(const float& degrees);

private:
	GameObject& mGameObject;
	Vector2f mPosition;
	Vector2f mScale;
	float mRotation = 0;

public:
	Vector2f mStartPosition;
};
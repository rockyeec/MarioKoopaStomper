#pragma once
#include "Vector2.h"

class GameObject;

enum class Layer
{
	IGNORE = -1,
	DEFAULT = 0,
	PLAYER = 1,
	ENEMY = 2,
	NEXT_LEVEL = 3
};


class BoxCollider
{
public:
	BoxCollider();
	BoxCollider(const Vector2f& position, const Vector2f& size);
	BoxCollider(const float& x, const float& y, const float& w, const float& h);
	
	const bool IsPointOver(const Vector2f& point) const;
	const bool IsOverlap(const BoxCollider& other) const;
	const Vector2f GetCorner(const int& index) const;
	const Vector2f GetCenter() const;

	const Vector2f& GetPosition() const;
	void SetPosition(const Vector2f newPosition);
	const Vector2f& GetSize() const;
	void SetSize(const Vector2f newSize);

public:
	mutable Layer mLayer = Layer::DEFAULT;
	mutable BoxCollider* mOther = NULL;
	mutable GameObject* mGameObject = NULL;

private:
	Vector2f mPosition;
	Vector2f mSize;
};

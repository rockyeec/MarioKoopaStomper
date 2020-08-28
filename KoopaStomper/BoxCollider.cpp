#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(const Vector2f& position, const Vector2f& size)
	: mPosition(position), mSize(size)
{
}

BoxCollider::BoxCollider(const float& x, const float& y, const float& w, const float& h)
	: BoxCollider({ x, y }, { w, h })
{
}

const bool BoxCollider::IsPointOver(const Vector2f& point) const
{
	if ((int)mLayer < 0)
		return false;

	return point.x < mPosition.x + mSize.x && point.x > mPosition.x
		&& point.y < mPosition.y + mSize.y && point.y > mPosition.y;
}

const bool BoxCollider::IsOverlap(const BoxCollider& other) const
{
	if ((int)mLayer < 0 || (int)other.mLayer < 0)
		return false;

	return other.mPosition.x <= mPosition.x + mSize.x && other.mPosition.x + other.mSize.x >= mPosition.x
		&& other.mPosition.y <= mPosition.y + mSize.y && other.mPosition.y + other.mSize.y >= mPosition.y;
}

const Vector2f BoxCollider::GetCorner(const int& index) const
{
	enum Corner
	{
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	switch (index)
	{
	case TOP_LEFT:
		return mPosition;

	case TOP_RIGHT:
		return { mPosition.x + mSize.x, mPosition.y };

	case BOTTOM_LEFT:
		return { mPosition.x, mPosition.y + mSize.y };

	case BOTTOM_RIGHT:
		return { mPosition.x + mSize.x, mPosition.y + mSize.y };
	}

	return Vector2f();
}

const Vector2f BoxCollider::GetCenter() const
{
	return { mPosition.x + mSize.x / 2, mPosition.y + mSize.y / 2 };
}

const Vector2f& BoxCollider::GetPosition() const
{
	return mPosition;
}

void BoxCollider::SetPosition(const Vector2f newPosition)
{
	mPosition = newPosition;
}

const Vector2f& BoxCollider::GetSize() const
{
	return mSize;
}

void BoxCollider::SetSize(const Vector2f newSize)
{
	mSize = newSize;
}

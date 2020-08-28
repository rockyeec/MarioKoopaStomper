#include "Arrow.h"
#include "Camera.h"
#include "Time.h"

Arrow::Arrow(const Waypoint& waypoint, std::vector<GameObject*>* mpEntities)
	:
	mpWaypoint(waypoint),
	GameObject(mpEntities)
{
	mTexture.LoadFromFile("Resources/Images/Arrow.png");
	mBox.mLayer = Layer::IGNORE;
}

void Arrow::Update()
{
	mpTransform->SetCenterPosition(Camera::GetCenterPosition() + Vector2f(0, -169.0f));
	const Vector2f direction = mpWaypoint.GetTransform().GetCenterPosition() - mpTransform->GetCenterPosition();
	mpTransform->SetRotation(direction.GetDegrees());

	mElapsed += Time::GetDeltaTime();
	if (mElapsed >= mDuration)
	{
		mElapsed -= mDuration;
		std::swap(mCurOri, mCurTarget);
	}

	mpTransform->SetScaleCenter(Vector2f::Lerp(*mCurOri, *mCurTarget, mElapsed / mDuration));

}

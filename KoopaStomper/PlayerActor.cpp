#include "PlayerActor.h"
#include "Camera.h"
#include "Input.h"
#include "Time.h"
#include "Mathf.h"


PlayerActor::PlayerActor(std::vector<GameObject*>* entityList)
    :
    Actor(Layer::PLAYER, entityList)
{
    mTexture.LoadFromFile("Resources/Images/Mario Animated.png", 1, 21);
    mMoveSpeed = 369.69f;
    mIsOutsideScreen = false;
}

PlayerActor::~PlayerActor()
{
}

void PlayerActor::Start()
{
    Actor::Start();
    InitializeAnimations();
    Camera::Update(mpTransform->GetPosition());

    mpTransform->Grow(-0.25f);
}

void PlayerActor::EarlyUpdate()
{    
}

void PlayerActor::LateUpdate()
{
    if (IsWaypoint() && mIsHeadButt)
    {
        mIsHeadButt = false;
        mBox.mOther->mGameObject->Interact();
        mBox.mOther = NULL;
        Camera::Shake();
        return;
    }
}

void PlayerActor::RemoveFromGame()
{
    mIsOutOfMap = false;
    mBox.mLayer = Layer::PLAYER;
    mIsDead = false;
    mCanInput = true;
    ClearHorizontal();
    ClearVertical();
    mJump.mIsJump = true;
    mJump.mIsOnGround = false;
    GetTransform().SetRotation(0);
    GetTransform().SetPosition(GetTransform().mStartPosition);
}

void PlayerActor::Jump()
{
    Actor::Jump();
    mAnimations.curAnimation = &mAnimations.jump;
}

void PlayerActor::Fall()
{
    Actor::Fall();
    if (IsFalling())
        mAnimations.curAnimation = &mAnimations.jump;
}

void PlayerActor::HeadButt()
{
    mIsHeadButt = true;
}

void PlayerActor::Interact()
{
    Die();
}

void PlayerActor::SubClassUpdate(const float& deltaTime)
{
    HandleMovementInput(deltaTime);
}

void PlayerActor::SubClassFixedUPdate(const float& deltaTime)
{
    MakeCameraFollow(deltaTime);
}

const bool PlayerActor::IsStomp() const
{
    if (mBox.mOther == NULL)
        return false;

    return mBox.mOther->mLayer == Layer::ENEMY;
}

const bool PlayerActor::IsHeadButt() const
{
    return IsWaypoint();
}

const bool PlayerActor::IsWaypoint() const
{
    if (mBox.mOther == NULL)
        return false;

    return mBox.mOther->mLayer == Layer::NEXT_LEVEL;
}


void PlayerActor::HandleMovementInput(const float& deltaTime)
{
    SetHorizontal(Input::GetKey(KeyCode::LEFT), Input::GetKey(KeyCode::RIGHT));
    mJump.mJumpButton = Input::GetKey(KeyCode::UP);
}

void PlayerActor::MakeCameraFollow(const float& deltaTime) const
{
    const Vector2f centerPos = mpTransform->GetPosition() + (GetTexture().GetSizeFloat() / 2);
    const float slipperiness =  deltaTime * 2.69f;
    const Vector2f pos = Vector2f::Lerp(Camera::GetCenterPosition(), centerPos, slipperiness);
    Camera::Update(pos);
}

void PlayerActor::InitializeAnimations()
{
    mAnimations.idle.Initialize(&mTexture);
    mAnimations.run.Initialize(&mTexture);
    mAnimations.jump.Initialize(&mTexture);

    // assign idle clip
    mAnimations.idle.AddClip(new Vector2i(0, 0));

    // assign run clips
    for (size_t i = 0; i < 3; i++)
    {
        mAnimations.run.AddClip(new Vector2i(32 * (3 - i), 0));
    }

    // assign jump clip
    mAnimations.jump.AddClip(new Vector2i(5 * 32, 0));
}

void PlayerActor::HandleAnimations(const float& deltaTime)
{
    if (!IsFalling() && mJump.mIsOnGround)
        mAnimations.curAnimation = (mHorizontalInput != 0) ? &mAnimations.run : &mAnimations.idle;

    mAnimations.curAnimation->Update(deltaTime);
}

const bool PlayerActor::IsFalling() const
{
    return mKinematics.mVelocity.y > 0.069f;
}


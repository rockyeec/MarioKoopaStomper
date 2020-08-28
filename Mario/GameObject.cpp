#include "GameObject.h"
#include "Time.h"
#include "Camera.h"
#include <SDL.h>


GameObject::GameObject(std::vector<GameObject*>* entityList)
    :
    mpTransform(new Transform(*this)),
    mpEntities(entityList)
{
    mBox.mGameObject = this;

    if (mpEntities != NULL)
        mpEntities->push_back(this);
}

GameObject::~GameObject()
{
    delete mpTransform;
}

void GameObject::EarlyUpdate()
{
    mIsOutsideScreen = !Camera::IsWithinFOV(mBox.GetCenter());
}

void GameObject::FixedUpdate()
{
    if (mIsOutsideScreen)
        return;
}

void GameObject::LateUpdate()
{
}

void GameObject::Start()
{
    mpTransform->SetScale(mpTransform->GetScale());
}

void GameObject::Update()
{    
    if (mIsOutsideScreen)
        return;
}

void GameObject::Render()
{
    if (mIsOutsideScreen)
        return;

    GetTexture().Render(mpTransform->GetPosition(), mpTransform->GetRotation());

    /*const Vector2f position = mpTransform->GetPosition() - Camera::GetPosition();
    const Vector2f size = mTexture.GetSizeFloat();
    SDL_Rect dstRect = { (int)position.x, (int)position.y, size.x, size.y };

    mTexture.Render(&dstRect, NULL, mpTransform->GetRotation());*/
}

const Texture& GameObject::GetTexture() const
{
    return mTexture;
}

const Transform& GameObject::GetTransform() const
{
    return *mpTransform;
}

const BoxCollider& GameObject::GetBox() const
{
    return mBox;
}

Texture& GameObject::GetTexture()
{
    return mTexture;
}

Transform& GameObject::GetTransform()
{
    return *mpTransform;
}

BoxCollider& GameObject::GetBox()
{
    return mBox;
}

void GameObject::RemoveFromGame()
{
    const size_t& length = mpEntities->size();
    for (size_t i = 0; i < length; i++)
    {
        if ((*mpEntities)[i] == this)
        {
            mpEntities->erase(mpEntities->begin() + i);
            break;
        }
    }

    delete this;
}

void GameObject::Interact()
{
}


#include "Texture.h"
#include "Graphics.h"
#include "Camera.h"

Texture::Texture() 
    :
    mTexture(NULL),
    mFlip((int)SDL_FLIP_NONE),
    mSrcRect{ 0, 0, 0, 0 },
    mDstRect{ 0, 0, 0, 0 }
{
    
}

Texture::~Texture()
{
    Free();
}

void Texture::LoadFromFile(const char* path, const int& slice_rows, const int& slice_cols)
{
    Free();

    SDL_Surface* mSurface = IMG_Load(path);

    if (mSurface != NULL)
    {
        SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface->format, 0xFF, 0xFF, 0xFF));
        mTexture = SDL_CreateTextureFromSurface(Graphics::GetRenderer(), mSurface);
        SetSrcRectSize(mSurface->w / slice_cols, mSurface->h / slice_rows);
        SetSizeWithScale({ 1 });
    }

    SDL_FreeSurface(mSurface);
}

void Texture::Free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }
}

void Texture::Render(const Vector2f& position, const float& angle)
{
    if (mTexture == NULL)
        return;

    SetDstRectPosition(position - Camera::GetPosition());

    SDL_RenderCopyEx(
        Graphics::GetRenderer(),
        mTexture,
        &mSrcRect,
        &mDstRect,
        angle,
        NULL,
        (SDL_RendererFlip)mFlip);
}



const Vector2f Texture::GetSizeFloat() const
{
    return { float(mDstRect.w), float(mDstRect.h) };
}

const Vector2i& Texture::GetOriSize() const
{
    return { mSrcRect.w, mSrcRect.h };
}

void Texture::SetSizeWithScale(const Vector2f& scale)
{
    float x = mSrcRect.w * scale.x;
    float y = mSrcRect.h * scale.y;

    SetSize({ (int)x, (int)y });
}

void Texture::SetSize(const Vector2i& scale)
{
    mDstRect.w = scale.x;
    mDstRect.h = scale.y;
}

void Texture::SetFlip(const int& flip)
{
    mFlip = flip;
}

void Texture::SetSpriteClip(const int& x, const int& y)
{
    mSrcRect.x = x;
    mSrcRect.y = y;
}

void Texture::SetSpriteClip(const Vector2i& v)
{
    SetSpriteClip(v.x, v.y);
}

void Texture::SetSrcRectSize(const int& w, const int& h)
{
    mSrcRect.w = w;
    mSrcRect.h = h;
}

void Texture::SetDstRectPosition(const Vector2f& position)
{
    mDstRect.x = int(position.x);
    mDstRect.y = int(position.y);
}

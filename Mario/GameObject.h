#pragma once

#include "Texture.h"
#include "Vector2.h"
#include "Transform.h"
#include "Collisions.h"
#include "BoxCollider.h"
#include <vector>

class Transform;

class GameObject
{
public:
	GameObject(std::vector<GameObject*>* entityList);
	~GameObject();

	virtual void Start();
	virtual void EarlyUpdate();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void Update();
	virtual void Render();

	const Texture& GetTexture() const;
	const Transform& GetTransform() const;
	const BoxCollider& GetBox() const;
	Texture& GetTexture();
	Transform& GetTransform();
	BoxCollider& GetBox();


public:
	virtual void RemoveFromGame();
	virtual void Interact();

protected:
	Transform* mpTransform;
	Texture mTexture;
	BoxCollider mBox;
	bool mIsOutsideScreen = true;
	std::vector<GameObject*>* mpEntities = NULL;
};
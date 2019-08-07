#pragma once
#include "Entity.h"
#include "SoundManager.h"
#include "GridNode.h"
#include "Animation.h"
#include "AnimationScript.h"

class Explosion : public Entity
{
public:
	Explosion(Entity* source);
	~Explosion();

	void LoadAnimations();
	void Draw(D3DXVECTOR2 transform);
	void Update(float deltaTime);
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;
private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	Animation* mAniExplosing = NULL;
	Animation* mCurrentAni = NULL;
};


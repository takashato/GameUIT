#pragma once
#include "Entity.h"
#include "AnimationScript.h"
#include "Animation.h"

class Item : public Entity
{
	friend class Grid;

public:
	Item(ItemType type, D3DXVECTOR3 position);
	~Item() = default;

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans);

	void Consume(Player &player);

	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;

	void SetType(ItemType type);

	static void LoadAnimation();

private:
	bool isOnGround = false;
	ItemType mType;
	Animation* mCurrentAni;

	static AnimationScript* mAniScript;
	static Sprite* mSprite;
	static Animation *mAniFivePoint, *mAniHeartEnergy, *mAniKeyCrystal, *mAniOneUp, *mAniPowerStone;

	int mState = -1;
};
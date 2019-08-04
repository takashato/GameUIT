#pragma once
#include "Entity.h"
#include "Animation.h"

static constexpr auto DROP_INTERVAL = 0.3f;

class Capsule : public Entity
{
public:
	Capsule(D3DXVECTOR3 position, std::vector<ItemType>& itemList);
	~Capsule() = default;

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 trans);

	void Drop();

	// Inherited via Entity
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;

	static void LoadAnimation();
private:
	Animation* mCurrentAni;
	ItemType mItemPrimary;
	ItemType mITemSecondary;
	bool mDroppedPrimary = false;
	bool mIsJustDrop = false;
	float mCounter = .0f;

	static AnimationScript* mAniScript;
	static Sprite* mSprite;
	static Animation* mAniNormal, *mAniInvoked;
};
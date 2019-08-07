#pragma once
#include "Bullet.h"

class Missile : public Bullet
{
public:
	Missile(D3DXVECTOR3 position, int flyDirection, int flyDirectionY = 0);
	~Missile();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();

	void OnSetPosition();

	BulletType GetBulletType();

	void HitShield();

private:
	static Sprite* mSprite;
	static AnimationScript* mAniScripts;
	static Animation* mAniFlying;

	float mCounter = 0;
	bool isFired = true;

	int mFlyDirection = 0;
	int mFlyDirectionY = 0;

	D3DXVECTOR3 orginalPos;

	static constexpr auto BULLET_SPEED = 100.0f;
	static constexpr auto DELTA_CAM_TO_DESTROY = .0f;
};
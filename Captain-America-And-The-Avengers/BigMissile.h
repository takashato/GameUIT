#pragma once
#include "Bullet.h"

class BigMissile : public Bullet
{
public:
	BigMissile(D3DXVECTOR3 position, Player* player);
	~BigMissile();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();

	void OnSetPosition();

	BulletType GetBulletType();

	void HitShield();

	void CalcLineEqual(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float &a, float &b);
	void CalcVelByPlayerPos(float x, float y);
	void UpdateVelYbyVelX(float x);
	void SetAnimationByVel();

private:
	static Sprite* mSprite;
	static AnimationScript* mAniScripts;
	static Animation* mAniTop, * mAniTopLeft, * mAniLeft, * mAniBottomLeft, *mAniBottom;

	float mCounter = 0;
	bool isFired = true;

	int mFlyDirection = 0;
	int mFlyDirectionY = 0;

	float a, b;

	D3DXVECTOR3 orginalPos;

	Player* mPlayer;

	static constexpr auto RECALC_INTERVAL = 0.5f;

	static constexpr float BULLET_MOVING = 110.0f;
	static constexpr float MIN_CHANGE_VELX_PER_FRAME = 2.5f;
	static constexpr float MAX_TIME_TILL_EXPLODE = 2.5f;

	static constexpr auto DELTA_CAM_TO_DESTROY = .0f;
};
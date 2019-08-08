#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define GUNSTOCK_TOP_DIRECT 0
#define GUNSTOCK_TOPRIGHT_DIRECT 1
#define GUNSTOCK_RIGHT_DIRECT 2
#define GUNSTOCK_BOTTOMRIGHT_DIRECT 3
#define GUNSTOCK_BOTTOM_DIRECT 4
#define GUNSTOCK_BOTTOMLEFT_DIRECT 5
#define GUNSTOCK_LEFT_DIRECT 6
#define GUNSTOCK_TOPLEFT_DIRECT 7
#define GUNSTOCK_ROTATING_STATE 8

class GunStock : public Enemy
{
public:
	GunStock(D3DXVECTOR3 position = D3DXVECTOR3(300.0f, 402.0f, 0.f), int subType = 0);
	~GunStock();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	EnemyType GetEnemyType();
	Bullet* GetBullet();
	void SetBullet(Bullet* Bullet);

	void BeAttacked();

	void TakeDamage(Entity* source, int damage);
	/*void OnDie();

	void SetInvincible(bool val);*/

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniTop= NULL;
	Animation* mAniTopRight = NULL;
	Animation* mAniRight = NULL;
	Animation* mAniBottomRightt = NULL;
	Animation* mAniBottom = NULL;
	Animation* mAniBottomLeft = NULL;
	Animation* mAniLeft = NULL;
	Animation* mAniTopLeft = NULL;
	Animation* mAniRotating = NULL;

	int mState = -1;
	int lastState = 0;
	/*Camera* mCamera;*/
	float mCounter = 0;
	float mIntervalCounter = .0f;
	/*NormalBullet* mBullet;*/

	int mHP = 1000;

	static constexpr auto BULLET_INTERVAL_TIME = 1.5f;
};
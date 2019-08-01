#include "pch.h"
#include "Game.h"
#include "BossCharleston.h"

BossCharleston::BossCharleston(D3DXVECTOR3 position)
{
	mDirection = Left;
	LoadAnimations();
	SetPosition(position);
	mState = BOSS_CHARLESTON_IDLE_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


BossCharleston::~BossCharleston()
{
}

void BossCharleston::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Boss_Wizard.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\Boss_Wizard.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);
	mAniLaugh = new Animation(mSprite, mAniScripts->GetRectList("Laugh", "0"), 0.1F);
	mAniBeHit = new Animation(mSprite, mAniScripts->GetRectList("BeHit", "0"), 0.1F);
	mAniGun = new Animation(mSprite, mAniScripts->GetRectList("Gun", "0"), 0.2F, false);
	mAniKamehameha = new Animation(mSprite, mAniScripts->GetRectList("Kamehameha", "0"), 0.15F);
	mAniHit = new Animation(mSprite, mAniScripts->GetRectList("Hit", "0"), 0.1F);
	mAniFly = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.1F);
	mAniFlyGun = new Animation(mSprite, mAniScripts->GetRectList("FlyGun", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void BossCharleston::Update(float deltaTime, Player* player)
{
	Entity::Update(deltaTime); // Update position

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;

	ModeOne(deltaTime, player);

	mCurrentAni->Update(deltaTime);
}

void BossCharleston::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int BossCharleston::GetState()
{
	return mState;
}

void BossCharleston::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void BossCharleston::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BOSS_CHARLESTON_IDLE_STATE:
		mCurrentAni = mAniStanding;
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		break;
	case BOSS_CHARLESTON_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		if (mDirection == EntityDirection::Left)
		{
			if (mVelocityX > -PLAYER_VELOCITY_X_MAX)
			{
				AddVelocityX(-50);
				if (mVelocityX < -PLAYER_VELOCITY_X_MAX)
					SetVelocityX(-PLAYER_VELOCITY_X_MAX);
			}
		}
		else
		{
			if (mVelocityX < PLAYER_VELOCITY_X_MAX)
			{
				AddVelocityX(50);
				if (mVelocityX > PLAYER_VELOCITY_X_MAX)
					SetVelocityX(PLAYER_VELOCITY_X_MAX);
			}
		}
		break;
	case BOSS_CHARLESTON_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	case BOSS_CHARLESTON_BEHIT_STATE:
		mCurrentAni = mAniBeHit;
		break;
	case BOSS_CHARLESTON_GUN_STATE:
		mCurrentAni = mAniGun;
		SetVelocityX(0.f);
		break;
	case BOSS_CHARLESTON_HIT_STATE:
		mCurrentAni = mAniHit;
		break;
	case BOSS_CHARLESTON_KAMEHAMEHA_STATE:
		mCurrentAni = mAniKamehameha;
		break;
	case BOSS_CHARLESTON_LAUGH_STATE:
		mCurrentAni = mAniLaugh;
		break;
	case BOSS_CHARLESTON_PLYGUN_STATE:
		mCurrentAni = mAniFlyGun;
		break;
	case BOSS_CHARLESTON_PLY_STATE:
		mCurrentAni = mAniFly;
		break;
	}
}

void BossCharleston::OnSetPosition()
{
}

EnemyType BossCharleston::GetEnemyType()
{
	return EnemyType::EBossCharleston;
}
void BossCharleston::SetBullet(Bullet* Bullet)
{

}
void BossCharleston::ModeOne(float deltaTime, Player* player)
{
	if (mState == BOSS_CHARLESTON_IDLE_STATE && mCounter > 0.9f)
	{
		SetState(BOSS_CHARLESTON_RUNNING_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_RUNNING_STATE && mCounter > 0.9f)
	{
		SetState(BOSS_CHARLESTON_GUN_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_GUN_STATE)
	{
		if (mCurrentAni->IsDoneCycle())
		{
			mCurrentAni->Reset();
			if (coutGun == 3) {
				SetState(BOSS_CHARLESTON_KAMEHAMEHA_STATE);
				coutGun = 1;
			}
			else {
				SetState(BOSS_CHARLESTON_GUN_STATE);
				++coutGun;
			}
			mCounter = 0;
		}
	}
	if (mState == BOSS_CHARLESTON_KAMEHAMEHA_STATE)
	{
		if (mCurrentAni->IsDoneCycle())
		{
			mCurrentAni->Reset();
			SetState(BOSS_CHARLESTON_RUNNING_STATE);
		}
	}
	if (player->GetPosition().x > mPosition.x+20)
	{
		mDirection = Right;
	}
	if (player->GetPosition().x< mPosition.x-20)
	{
		mDirection = Left;
	}
	if (mPosition.x < 8) {
		mDirection = Right;
	}
	if (mPosition.x > 180) {
		mDirection = Left;
	}
}
Bullet* BossCharleston::GetBullet()
{
	return mBullet;
}

#include "pch.h"
#include "Game.h"
#include "BossCharleston.h"

BossCharleston::BossCharleston(D3DXVECTOR3 position)
{
	mDirection = Left;
	LoadAnimations();
	SetPosition(position);
	mState = BOSS_CHARLESTON_RUNNING_STATE;
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

	mCurrentAni = mAniRunning;
}

void BossCharleston::Update(float deltaTime, Player* player)
{
	Entity::Update(deltaTime); // Update position

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;

	if (mDirection == EntityDirection::Left)
	{
		if (mVelocityX > -PLAYER_VELOCITY_X_MAX)
		{
			AddVelocityX(-PLAYER_ACC_X * deltaTime);
			if (mVelocityX < -PLAYER_VELOCITY_X_MAX)
				SetVelocityX(-PLAYER_VELOCITY_X_MAX);
		}
	}
	else
	{
		if (mVelocityX < PLAYER_VELOCITY_X_MAX)
		{
			AddVelocityX(PLAYER_ACC_X * deltaTime);
			if (mVelocityX > PLAYER_VELOCITY_X_MAX)
				SetVelocityX(PLAYER_VELOCITY_X_MAX);
		}
	}
	if (mPosition.x < 8)
		mDirection = Right;
	if (mPosition.x > 230)
		mDirection = Left;
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
		break;
	case BOSS_CHARLESTON_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case BOSS_CHARLESTON_DYING_STATE:
		mCurrentAni = mAniDying;
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


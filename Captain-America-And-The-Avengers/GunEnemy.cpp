#include "pch.h"
#include "Game.h"
#include "GunEnemy.h"

GunEnemy::GunEnemy(D3DXVECTOR3 position) : Enemy()
{
	LoadAnimations();
	SetPosition(position);
	mState = GUNENEMY_STANDING_STATE;
}


GunEnemy::~GunEnemy()
{
}

void GunEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\GunEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void GunEnemy::Update(float deltaTime, Player* player)
{
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 gunEnemyPosition = this->GetPosition();

	if (playerPosition.x <= gunEnemyPosition.x)
	{
		mDirection = Right;
	}
	else
	{
		mDirection = Left;
	}

	mCurrentAni->SetFlippedHorizontally(mDirection == Left);
	mCounter += deltaTime;

	if (mCounter >= 0.9f)
	{
		if (mCurrentAni == mAniStanding)
		{
			mCurrentAni = mAniSitting;
			mState = GUNENEMY_SITTING_STATE;
		}
		else
		{
			mCurrentAni = mAniStanding;
			mState = GUNENEMY_STANDING_STATE;
		}
		mCounter = 0;
	}
}

void GunEnemy::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0,0));
	}
}

int GunEnemy::GetState()
{
	return mState;
}

void GunEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void GunEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case GUNENEMY_STANDING_STATE:
		mCurrentAni = mAniStanding;
		break;
	case GUNENEMY_SITTING_STATE:
		mCurrentAni = mAniSitting;
		break;
	case GUNENEMY_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void GunEnemy::OnSetPosition()
{
}

EnemyType GunEnemy::GetEnemyType()
{
	return EnemyType::EGunEnemy;
}


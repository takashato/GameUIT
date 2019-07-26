#include "pch.h"
#include "Game.h"
#include "RunEnemy.h"

RunEnemy::RunEnemy(D3DXVECTOR3 position) : Enemy()
{
	LoadAnimations();
	SetPosition(position);
	mState = RUNENEMY_STANDING_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


RunEnemy::~RunEnemy()
{
}

void RunEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\RunEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void RunEnemy::Update(float deltaTime, Player* player)
{
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 runEnemyPosition = this->GetPosition();
	
	mCurrentAni->SetFlippedHorizontally(mDirection == Left);
	
	if (abs(runEnemyPosition.x - playerPosition.x) < 200)
	{
		mCurrentAni = mAniRunning;
		mState = RUNENEMY_RUNNING_STATE;
		mCounter += deltaTime;
		if (mCounter >= MOVEMENT_UPDATE_TIME)
		{
			if (mDirection == Right)
			{
				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * mCounter);
			}
			else
			{
				if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
					AddVelocityX(PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * mCounter);
			}
			mCounter = 0;
		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
	}
	else
	{
		mCurrentAni = mAniStanding;
		mState = RUNENEMY_STANDING_STATE;
		if (runEnemyPosition.x < playerPosition.x)
			mDirection = Left;
		else
			mDirection = Right;
		SetVelocityX(0.f);
		SetVelocityY(0.f);
	}
	
}

void RunEnemy::Draw(D3DXVECTOR2 transform)
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

int RunEnemy::GetState()
{
	return mState;
}

void RunEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void RunEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case RUNENEMY_STANDING_STATE:
		mCurrentAni = mAniStanding;
		break;
	case RUNENEMY_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case RUNENEMY_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void RunEnemy::OnSetPosition()
{
}


RECT RunEnemy::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();
	RECT rect = mCurrentAni->GetCurrentFrameRect();
	rect.right -= rect.left;
	rect.bottom -= rect.top;
	rect.left = 0;
	rect.top = 0;
	return rect;
}

EnemyType RunEnemy::GetEnemyType()
{
	return EnemyType::ERunEnemy;
}


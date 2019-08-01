#include "pch.h"
#include "Game.h"
#include "RunEnemy.h"

RunEnemy::RunEnemy(D3DXVECTOR3 position, int subTypeID) : Enemy()
{
	mSubTypeID = subTypeID;
	spawnPosition = position;
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
	
	mCurrentAni->SetFlippedHorizontally(mDirection == Right);
	if (mSubTypeID == 0)
	{
		if (abs(runEnemyPosition.x - playerPosition.x) < 200)
		{
			mCurrentAni = mAniRunning;
			mState = RUNENEMY_RUNNING_STATE;
			mCounter += deltaTime;
			if (mCounter >= MOVEMENT_UPDATE_TIME)
			{
				if (mDirection == Left)
				{
					if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
						AddVelocityX(-100);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
				else
				{
					if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
						AddVelocityX(100);
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
				mDirection = Right;
			else
				mDirection = Left;
			SetVelocityX(0.f);
			SetVelocityY(0.f);
		}
	}

	if (mSubTypeID == 1)
	{
		SetDirection(EntityDirection::Right);
		/*if(mCurrentAni == mAniStanding && mState == RUNENEMY_STANDING_STATE)
			lastPosition = this->GetPosition();*/
		if (!isShoot)
		{
			mCurrentAni = mAniRunning;
			mState = RUNENEMY_RUNNING_STATE;

			if (runEnemyPosition.x - spawnPosition.x > 256)
				SetPosition(spawnPosition);
			else
			{
				if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
					AddVelocityX(20);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * deltaTime);
			}
		}

		if ((int)runEnemyPosition.x % 31 > 29)
			isShoot = true;

		if (isShoot)
		{
			mCounter += deltaTime;
			mCurrentAni = mAniStanding;
			mState = RUNENEMY_STANDING_STATE;
			
			if (mCounter > 0.4f)
			{
				isShoot = false;
				mCounter = 0;
			}
		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
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
	Enemy::OnSetPosition();
}

EnemyType RunEnemy::GetEnemyType()
{
	return EnemyType::ERunEnemy;
}

Bullet* RunEnemy::GetBullet()
{
	return mBullet;
}

void RunEnemy::SetBullet(Bullet* bullet)
{
	mBullet = (NormalBullet*)bullet;
}


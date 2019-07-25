#include "pch.h"
#include "Game.h"
#include "MissileEnemy.h"

MissileEnemy::MissileEnemy(D3DXVECTOR3 position) : Entity()
{
	LoadAnimations();
	SetPosition(position);
	mState = MISSILEENEMY_STANDING_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


MissileEnemy::~MissileEnemy()
{
	
}

void MissileEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\MissileEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniJumping = new Animation(mSprite, mAniScripts->GetRectList("Jumping", "0"), 0.1F);
	mAniFalling = new Animation(mSprite, mAniScripts->GetRectList("Falling", "0"), 0.1F);
	mAniTakeDamage = new Animation(mSprite, mAniScripts->GetRectList("TakeDamage", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void MissileEnemy::Update(float deltaTime, Player* player, int id)
{
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 missileEnemyPosition = this->GetPosition();

	if (playerPosition.x <= missileEnemyPosition.x)
	{
		mDirection = Right;
	}
	else
	{
		mDirection = Left;
	}

	mCurrentAni->SetFlippedHorizontally(mDirection == Left);
	
	if (id == 1) // Missile Enemy Stand and Shoot
	{
		mCounter += deltaTime;
		if (mCounter >= 0.9f)
		{
			if (mCurrentAni == mAniStanding)
			{
				mCurrentAni = mAniSitting;
				mState = MISSILEENEMY_SITTING_STATE;
			}
			else
			{
				mCurrentAni = mAniStanding;
				mState = MISSILEENEMY_STANDING_STATE;
			}
			mCounter = 0;
		}
	}

	if (id == 2) // Missile Enemy Run and Shoot
	{
		mCounter += deltaTime;
		if (mDirection == Left)
		{
			if (mCounter < 0.9f)
			{
				mCurrentAni = mAniRunning;
				mState = MISSILEENEMY_RUNNING_STATE;
				if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
					AddVelocityX(PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.01f);
			}
			else if (mCounter >= 0.9f && mCounter < 1.5f)
			{
				mCurrentAni = mAniStanding;
				mState = MISSILEENEMY_STANDING_STATE;
			}
			else if (mCounter >= 1.5f && mCounter < 1.9f)
			{
				mCurrentAni = mAniSitting;
				mState = MISSILEENEMY_SITTING_STATE;
			}
			else
			{
				mCounter = 0;
			}
			if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		}
		else
		{
			if (mCounter < 0.9f)
			{
				mCurrentAni = mAniRunning;
				mState = MISSILEENEMY_RUNNING_STATE;
				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.01f);
			}
			else if (mCounter >= 0.9f && mCounter < 1.5f)
			{
				mCurrentAni = mAniStanding;
				mState = MISSILEENEMY_STANDING_STATE;
			}
			else if (mCounter >= 1.5f && mCounter < 1.9f)
			{
				mCurrentAni = mAniSitting;
				mState = MISSILEENEMY_SITTING_STATE;	
			}
			else
			{
				mCounter = 0;
			}
			if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		}
	}
}

void MissileEnemy::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->Draw(GetPosition(), transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
	}
}

int MissileEnemy::GetState()
{
	return mState;
}

void MissileEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void MissileEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case MISSILEENEMY_STANDING_STATE:
		mCurrentAni = mAniStanding;
		break;
	case MISSILEENEMY_SITTING_STATE:
		mCurrentAni = mAniSitting;
		break;
	case MISSILEENEMY_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case MISSILEENEMY_JUMPING_STATE:
		mCurrentAni = mAniJumping;
		break;
	case MISSILEENEMY_FALLING_STATE:
		mCurrentAni = mAniFalling;
		break;
	case MISSILEENEMY_TAKEDAMAGE_STATE:
		mCurrentAni = mAniTakeDamage;
		break;
	case MISSILEENEMY_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void MissileEnemy::OnSetPosition()
{
}

//void MissileEnemy::SetCamera(Camera* camera)
//{
//	mCamera = camera;
//}

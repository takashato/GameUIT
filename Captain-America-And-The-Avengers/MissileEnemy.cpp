#include "pch.h"
#include "Game.h"
#include "MissileEnemy.h"

MissileEnemy::MissileEnemy(D3DXVECTOR3 position, int subTypeID)
{
	mSubTypeID = subTypeID;
	spawnPosition = position;
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
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.1F);
	mAniJumping = new Animation(mSprite, mAniScripts->GetRectList("Jumping", "0"), 0.1F);
	mAniFalling = new Animation(mSprite, mAniScripts->GetRectList("Falling", "0"), 0.1F);
	mAniTakeDamage = new Animation(mSprite, mAniScripts->GetRectList("TakeDamage", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void MissileEnemy::Update(float deltaTime, Player* player)
{
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 missileEnemyPosition = this->GetPosition();

	if (mSubTypeID != 0)
	{
		if (playerPosition.x <= missileEnemyPosition.x)
		{
			mDirection = Left;
		}
		else
		{
			mDirection = Right;
		}
	}

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);
	
	if (mSubTypeID == 1) // Missile Enemy Stand and Shoot
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
	else if (mSubTypeID == 2) // Missile Enemy Run and Shoot
	{
		if (mDirection == Left)
		{
			if (playerPosition.x > 160 && isMeetPlayer == false)
			{
				
				mCurrentAni = mAniRunning;
				mState = MISSILEENEMY_RUNNING_STATE;
				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.01f);
			}

			if(missileEnemyPosition.x - playerPosition.x <= 50)
			{
				if (isMeetPlayer == false)
				{
					mCurrentAni = mAniStanding;
					mState = MISSILEENEMY_STANDING_STATE;
				}
				isMeetPlayer = true;
				mCounter += deltaTime;
				if (mCounter >= 0.9f)
				{
					if (mCurrentAni == mAniStanding)
					{
						mCurrentAni = mAniSitting;
						mState = MISSILEENEMY_SITTING_STATE;
						this->SetPositionY(missileEnemyPosition.y + this->mAniStanding->GetHeight() - this->mAniSitting->GetHeight());
					}
					else 
					{
						mCurrentAni = mAniStanding;
						mState = MISSILEENEMY_STANDING_STATE;
						this->SetPositionY(missileEnemyPosition.y - this->mAniStanding->GetHeight() + this->mAniSitting->GetHeight());
					}
					mCounter = 0;
				}
			}
		}
		else
		{
			mCounter += deltaTime;
			if (mCounter >= 0.9f)
			{
				if (mCurrentAni == mAniStanding)
				{
					mCurrentAni = mAniSitting;
					mState = MISSILEENEMY_SITTING_STATE;
					this->SetPositionY(missileEnemyPosition.y + this->mAniStanding->GetHeight() - this->mAniSitting->GetHeight());
				}
				else
				{
					mCurrentAni = mAniStanding;
					mState = MISSILEENEMY_STANDING_STATE;
					this->SetPositionY(missileEnemyPosition.y - this->mAniStanding->GetHeight() + this->mAniSitting->GetHeight());
				}
				mCounter = 0;
			}

		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
	}
	else if (mSubTypeID == 0) // Only Run and Jump Not Shoot
	{
		
		SetDirection(EntityDirection::Left);
		if (!isJump)
		{
			mCurrentAni = mAniRunning;
			mState = MISSILEENEMY_RUNNING_STATE;

			if (spawnPosition.x - GetPosition().x > 256)
				SetPosition(spawnPosition);
			else
			{
				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.005f);
			}
		}

		if (missileEnemyPosition.x - player->GetShield()->GetPosition().x < 50 && player->GetShield()->GetState() == ShieldState::EShieldHigh)
			isJump = true;

		if (isJump)
		{
			mCounter += deltaTime;
			if (mCounter < 0.4f)
			{
				mCurrentAni = mAniJumping;
				mState = MISSILEENEMY_JUMPING_STATE;

				AddPositionY(-120 * deltaTime);

				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.005f);
			}
			else
			{
				mCurrentAni = mAniFalling;
				mState = MISSILEENEMY_FALLING_STATE;

				AddPositionY(120 * deltaTime);

				if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
					AddVelocityX(-PLAYER_ACC_X);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * 0.005f);

				if (missileEnemyPosition.y > 402.0f)
				{
					isJump = false;
					SetPositionY(402.0f);
					mCounter = 0;
				}
			}
		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
	}
}

void MissileEnemy::Draw(D3DXVECTOR2 transform)
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
	Enemy::OnSetPosition();
}

EnemyType MissileEnemy::GetEnemyType()
{
	return EnemyType::EMissileEnemy;
}

Bullet* MissileEnemy::GetBullet()
{
	return mBullet;
}

void MissileEnemy::SetBullet(Bullet* bullet)
{
	mBullet = (NormalBullet*)bullet;
}


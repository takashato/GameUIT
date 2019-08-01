#include "pch.h"
#include "Game.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet(Enemy* Enemy) : Bullet()
{
	if (Enemy->GetEnemyType() == EnemyType::EGunEnemy)
		mGunEnemy = (GunEnemy*)Enemy;
	else
		mRunEnemy = (RunEnemy*)Enemy;
	LoadAnimations();
	D3DXVECTOR3 position = Enemy->GetPosition();
	position.y = position.y + 4;
	SetPosition(position);
	mState = NORMALBULLET_FLYING_STATE;
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\NormalBullet.xml");

	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.1F);

	mCurrentAni = mAniFlying;
}

void NormalBullet::Update(float deltaTime)
{
	if (mGunEnemy != NULL)
	{
		D3DXVECTOR3 gunEnemyPosition = mGunEnemy->GetPosition();

		if (mGunEnemy->GetState() == GUNENEMY_STANDING_STATE || mGunEnemy->GetState() == GUNENEMY_SITTING_STATE)
		{
			if (mGunEnemy->GetState() == GUNENEMY_STANDING_STATE)
			{
				if (mFlyDirection == 0)
				{
					if (mGunEnemy->GetDirection() == Left)
					{
						mFlyDirection = -1;
					}
					else
					{
						mFlyDirection = 1;
					}
				}
			}
			isFired = true;
			if (mFlyDirection == -1)
			{
				if (GetVelocityX() < 100)
					AddVelocityX(15);
			}
			else if (mFlyDirection == 1)
			{
				if (GetVelocityX() > -100)
					AddVelocityX(-15);

			}

			if (!mIsHitShield)
			{
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * deltaTime);
			}
			else
			{
				if (GetVelocityX() != 0.f)
					AddPositionY(-abs(GetVelocityX()) * deltaTime);
			}

			if (mGunEnemy->GetState() == GUNENEMY_SITTING_STATE)
			{
				mIsHitShield = false;
				SetVelocityX(0.0f);
				SetVelocityY(0.0f);
				mFlyDirection = 0;
				gunEnemyPosition.y = gunEnemyPosition.y - 10;
				SetPosition(gunEnemyPosition);
				isFired = false;
			}
		}
		else
		{
			mFlyDirection = 0;
			gunEnemyPosition.y = gunEnemyPosition.y - 10;
			SetPosition(gunEnemyPosition);
			isFired = false;
		}
	}
	
	if (mRunEnemy != NULL)
	{
		D3DXVECTOR3 runEnemyPosition = mRunEnemy->GetPosition();

		if (mRunEnemy->GetState() == RUNENEMY_STANDING_STATE || mRunEnemy->GetState() == RUNENEMY_RUNNING_STATE)
		{
			if (mRunEnemy->GetState() == RUNENEMY_STANDING_STATE)
			{
				if (mFlyDirection == 0)
				{
					if (mRunEnemy->GetDirection() == Right)
					{
						mFlyDirection = -1;
					}
					else
					{
						mFlyDirection = 1;
					}
				}
			}
			isFired = true;
			if (mFlyDirection == -1)
			{
				if (GetVelocityX() < 150)
					AddVelocityX(15);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX()* deltaTime);
			}
			else if (mFlyDirection == 1)
			{
				if (GetVelocityX() > -150)
					AddVelocityX(-15);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX() * deltaTime);
			}

			if (mRunEnemy->GetState() == RUNENEMY_RUNNING_STATE)
			{
				SetVelocityX(0.0f);
				mFlyDirection = 0;
				SetPosition(runEnemyPosition);
				isFired = false;
			}
		}
		else
		{
			mFlyDirection = 0;
			SetPosition(runEnemyPosition);
			isFired = false;
		}
	}
}

void NormalBullet::Draw(D3DXVECTOR2 transform)
{
	if (isFired)
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
}

int NormalBullet::GetState()
{
	return mState;
}

void NormalBullet::OnSetPosition()
{
	Bullet::OnSetPosition();
}

BulletType NormalBullet::GetBulletType()
{
	return BulletType::BNormalBullet;
}

void NormalBullet::HitShield()
{
	mIsHitShield = true;
}

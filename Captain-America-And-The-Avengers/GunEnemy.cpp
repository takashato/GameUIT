#include "pch.h"
#include "Game.h"
#include "GunEnemy.h"

GunEnemy::GunEnemy(D3DXVECTOR3 position, int subTypeID) : Enemy()
{
	mSubTypeID = subTypeID;
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
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F, false);

	mCurrentAni = mAniStanding;
}

void GunEnemy::Update(float deltaTime, Player* player)
{
	Enemy::Update(deltaTime, player);

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
	if (mSubTypeID == 0) // Normal
	{
		mCounter += deltaTime;

		if (mIsInvincible)
		{
			if (mCurrentAni != mAniDying)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
				}
				SetState(GUNENEMY_DYING_STATE);
			}
			mCounter = .0f;
		}
		else
		{
			if (mCounter >= 0.9f && mCounter <= 1.8f)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniSitting->GetHeight());
				}
				else if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniSitting->GetHeight());
				}

				if (mCurrentAni != mAniSitting) SetState(GUNENEMY_SITTING_STATE);
			}
			else if (mCounter < 0.9f)
			{
				if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
				}
				if (mCurrentAni != mAniStanding) SetState(GUNENEMY_STANDING_STATE);
			}
			else
			{
				mCounter = .0f;
			}
		}
	}
	else if (mSubTypeID == 1) // Shoot Fast
	{
		mCounter += deltaTime;

		if (mIsInvincible)
		{
			if (mCurrentAni != mAniDying)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
				}
				SetState(GUNENEMY_DYING_STATE);
			}
			mCounter = .0f;
		}
		else
		{
			if (mCounter >= 0.3f && mCounter <= 0.6f)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniSitting->GetHeight());
				}
				else if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniSitting->GetHeight());
				}

				if (mCurrentAni != mAniSitting) SetState(GUNENEMY_SITTING_STATE);
			}
			else if (mCounter < 0.3f)
			{
				if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
				}
				if (mCurrentAni != mAniStanding) SetState(GUNENEMY_STANDING_STATE);
			}
			else
			{
				mCounter = .0f;
			}
		}
	}

	if (mBullet != nullptr) mBullet->Update(deltaTime);
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
	Enemy::OnSetPosition();
}

EnemyType GunEnemy::GetEnemyType()
{
	return EnemyType::EGunEnemy;
}

Bullet* GunEnemy::GetBullet()
{
	return mBullet;
}

void GunEnemy::SetBullet(Bullet* bullet)
{
	mBullet = (NormalBullet*)bullet;
}

void GunEnemy::OnAttacked()
{
	SetInvincible(true);
}

void GunEnemy::OnDie()
{
	ChangeAnimationByState(GUNENEMY_DYING_STATE);
	mCurrentAni->Reset();
}

void GunEnemy::SetInvincible(bool val)
{
	Enemy::SetInvincible(val);
	if (val)
	{
		mAniStanding->SetBlink(true);
		mAniSitting->SetBlink(true);
		mAniDying->SetBlink(true);
		std::cout << "Blink on\n";
	}
	else
	{
		mAniStanding->SetBlink(false);
		mAniSitting->SetBlink(false);
		mAniDying->SetBlink(false);
		std::cout << "Blink off\n";
	}
}


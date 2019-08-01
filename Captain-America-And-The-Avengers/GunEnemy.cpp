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
	mCounter += deltaTime;

	if (mIsInvincible)
	{
		if (mCurrentAni == mAniStanding)
		{
			this->SetPositionY(gunEnemyPosition.y + this->mCurrentAni->GetHeight() - this->mAniDying->GetHeight());
		}
		else if (mCurrentAni == mAniSitting)
		{
			this->SetPositionY(gunEnemyPosition.y + this->mAniDying->GetHeight() - this->mCurrentAni->GetHeight());
		}
		mCurrentAni = mAniDying;
		mState = GUNENEMY_DYING_STATE;
	}
	else
	{
		if (mCounter >= 0.9f)
		{
			if (mCurrentAni == mAniStanding)
			{
				mCurrentAni = mAniSitting;
				mState = GUNENEMY_SITTING_STATE;
				this->SetPositionY(gunEnemyPosition.y + this->mAniStanding->GetHeight() - this->mAniSitting->GetHeight());
			}
			else
			{
				mCurrentAni = mAniStanding;
				mState = GUNENEMY_STANDING_STATE;
				this->SetPositionY(gunEnemyPosition.y - this->mAniStanding->GetHeight() + this->mAniSitting->GetHeight());
			}
			mCounter = 0;
		}
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


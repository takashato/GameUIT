#include "pch.h"
#include "Game.h"
#include "FlyRocketEnemy.h"
#include "BigMissile.h"
#include <cmath>

FlyRocketEnemy::FlyRocketEnemy(D3DXVECTOR3 position) 
{
	mHP = 2;
	mDirection = Right;
	LoadAnimations();
	spawnPos = position;
	SetPosition(position);
	mState = FLYROCKETENEMY_IDLE_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
	//calculate ellipse //Mac dinh truc lon = 180 truc be = 52
	mCenterEllipse = D3DXVECTOR2(mPosition.x + 90, mPosition.y);
	mTransformEllipse = mCenterEllipse;
}


FlyRocketEnemy::~FlyRocketEnemy()
{
}

void FlyRocketEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\FlyRocketEnemy.xml");

	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.1F);
	mAniGunning = new Animation(mSprite, mAniScripts->GetRectList("Flying", "0"), 0.11F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniFlying;
}

void FlyRocketEnemy::Update(float deltaTime, Player* player)
{
	mPlayer = player;

	Entity::Update(deltaTime);
	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	if (mIsInvincible)
	{
		mInvincibleCounter += deltaTime;
		if (mInvincibleCounter >= 1.0f)
		{
			mInvincibleCounter = .0f;
			mIsInvincible = false;
		}
	}

	if (mState == FLYROCKETENEMY_DYING_STATE)
	{
		mCounterDie += deltaTime;
		if (mCounterDie > 0.2f)
		{
			SetDirection(GetDirection() == Left ? Right : Left);
			mCounterDie = 0;
		}
		if (spawnPos.y == 755)
		{
			AddPositionY(50*deltaTime);
			if (mPosition.y > 900)
			{
				if (SceneManager::GetInstance().GetScene() != nullptr
					&& SceneManager::GetInstance().GetScene()->GetGrid() != nullptr)
				{
					Explosion* explosion;
					explosion = new Explosion(this);
					SceneManager::GetInstance().GetScene()->GetGrid()->Add(explosion);
				}
				pendingDelete = true;
			}	
		}
		if (spawnPos.y == 39)
		{
			AddPositionY(50*deltaTime);
			if (mPosition.x > 638 && mPosition.x < 673)
			{
				if (mPosition.y > 180)
				{
					if (SceneManager::GetInstance().GetScene() != nullptr
						&& SceneManager::GetInstance().GetScene()->GetGrid() != nullptr)
					{
						Explosion* explosion;
						explosion = new Explosion(this);
						SceneManager::GetInstance().GetScene()->GetGrid()->Add(explosion);
					}
					pendingDelete = true;
				}
			}
			else
			{
				if (mPosition.y > 90)
				{
					if (SceneManager::GetInstance().GetScene() != nullptr
						&& SceneManager::GetInstance().GetScene()->GetGrid() != nullptr)
					{
						Explosion* explosion;
						explosion = new Explosion(this);
						SceneManager::GetInstance().GetScene()->GetGrid()->Add(explosion);
					}
					pendingDelete = true;
				}
			}
		}
		return;
	}

	mCounter += deltaTime;
	CheckDirection(player);
	if (mState == FLYROCKETENEMY_IDLE_STATE)
	{
		if (mCounter > 0.9f) {
			SetState(FLYROCKETENEMY_FLY_STATE);
			mCounter = 0;
		}
	}
	if (mPosition.x > (mCenterEllipse.x) + 10 && isShootOke == true &&mFlagMove==1) {
		isShootOke = false;
		SetState(FLYROCKETENEMY_GUN_STATE);
		mCounter = 0;
	}
	if (mPosition.x < (mCenterEllipse.x) + 30 && isShootOke == true && mFlagMove == -1) {
		isShootOke = false;
		SetState(FLYROCKETENEMY_GUN_STATE);
		mCounter = 0;
	}
	if (mState == FLYROCKETENEMY_GUN_STATE)
	{
		CheckDirection(player);
		if (mCounter > 0.7f)
		{
			SetState(FLYROCKETENEMY_FLY_STATE);
			mCounter = 0;
		}
	}
	if (mState == FLYROCKETENEMY_FLY_STATE)
	{
		//Mac dinh truc lon = 180 truc be = 52 
		//Ta se co elip (x-trans.x)^2/(180/2)^2+ (y-trans.y)^2/(52/2)^2
		//Khai trien y theo x tao dc phuong trinh y = sqrt(26*26*(1-(((x-trans.x)*(x-trans.x))/(90*90)))) + tran.y
		if (mFlagMove == -1)
		{
			if ((mPosition.x + (-50 * deltaTime)) < mCenterEllipse.x - 90)
			{
				isShootOke = true;
				SetVelocityX((-(mCenterEllipse.x - 90)+mPosition.x)/deltaTime);
				mFlagMove = -mFlagMove;

			}
			else if(mPosition.x< mCenterEllipse.x - 85)
				SetVelocityX(-25);
			else
				SetVelocityX(-50);
			mPosition.y = (sqrt(26 * 26 * (1 - (((mPosition.x - mTransformEllipse.x)*(mPosition.x - mTransformEllipse.x)) / (90 * 90)))) + mTransformEllipse.y);
		}
		else
		{
			if ((mPosition.x + (50 * deltaTime)) > mCenterEllipse.x + 90)
			{
				isShootOke = true;
				SetVelocityX(((mCenterEllipse.x + 90) - mPosition.x) / deltaTime);
				mFlagMove = -mFlagMove;
			}
			else if (mPosition.x > mCenterEllipse.x + 85)
				SetVelocityX(25);
			else SetVelocityX(50);
			mPosition.y = (-1 * sqrt(26 * 26 * (1 - (((mPosition.x - mTransformEllipse.x)*(mPosition.x - mTransformEllipse.x)) / (90 * 90)))) + mTransformEllipse.y);
		}
	}

	mCurrentAni->Update(deltaTime);
}

void FlyRocketEnemy::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetBlink(mIsInvincible);
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0, 0));
	}
}

int FlyRocketEnemy::GetState()
{
	return mState;
}

void FlyRocketEnemy::SetState(int state)
{
	if (state == FLYROCKETENEMY_GUN_STATE)
	{
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(new BigMissile(mPosition, mPlayer));
	}
	mState = state;
	ChangeAnimationByState(mState);
}

void FlyRocketEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case FLYROCKETENEMY_FLY_STATE:
		mCurrentAni = mAniFlying;
		break;
	case FLYROCKETENEMY_GUN_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniGunning;
		break;
	case BOSS_CHARLESTON_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	case FLYROCKETENEMY_IDLE_STATE:
		mCurrentAni = mAniFlying;
		break;
	}
}

void FlyRocketEnemy::OnSetPosition()
{
}


void FlyRocketEnemy::CheckDirection(Player* player)
{
	if (player->GetPosition().x > mPosition.x + 20 && mDirection == Left)
	{
		mDirection = Right;
	}
	if (player->GetPosition().x < mPosition.x - 20 && mDirection == Right)
	{
		mDirection = Left;
	}

}
EnemyType FlyRocketEnemy::GetEnemyType()
{
	return EnemyType::EFlyEnemy;
}

void FlyRocketEnemy::TakeDamage(Entity* source, int damage)
{
	if (mIsInvincible) return;
	mLastState = mState;
	mHP -= damage;

	if (mHP <= 0)
	{
		SetState(FLYROCKETENEMY_DYING_STATE);
		SetVelocityX(0.f);
	}
	else
	{
		SetInvincible(true);
	}
}

void FlyRocketEnemy::SetInvincible(bool val)
{
	mIsInvincible = val;
}
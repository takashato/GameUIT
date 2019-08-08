#include "pch.h"
#include "Game.h"
#include "Bat.h"
#include <cmath>

Bat::Bat(D3DXVECTOR3 position, int subTypeID)
{
	mHP = 2;
	mSubTypeID = subTypeID;
	mDirection = Right;
	LoadAnimations();
	SetPosition(position);
	mState = BAT_COCOON_SATTE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
	mCenter = position;
	mCenter.y = mCenter.y + 15;
}


Bat::~Bat()
{
}

void Bat::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\Bat.xml");

	mAniCocoon = new Animation(mSprite, mAniScripts->GetRectList("Cocoon", "0"), 0.15F);
	mAniSwing = new Animation(mSprite, mAniScripts->GetRectList("Swing", "0"), 0.5F);
	mAniFlying = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.15F);
	mAniFlyWithShock = new Animation(mSprite, mAniScripts->GetRectList("FlyWithShock", "0"), 0.1F);

	mCurrentAni = mAniCocoon;
}

void Bat::Update(float deltaTime, Player* player)
{
	Entity::Update(deltaTime);
	mCurrentAni->SetFlippedHorizontally(true);

	if (mIsInvincible)
	{
		mInvincibleCounter += deltaTime;
		if (mInvincibleCounter >= 1.0f)
		{
			mInvincibleCounter = .0f;
			mIsInvincible = false;
		}
	}

	mCounter += deltaTime;
	if (mSubTypeID == 0) {
		if (mState == BAT_COCOON_SATTE)
		{
			isDown = true;
			if (mCounter > 0.9f)
			{
				SetState(BAT_SWING_STATE);
				mCounter = 0;
			}
		}
		if (mState == BAT_SWING_STATE)
		{
			if (!isDown)
			{
				if (mCounter > 0.3f)
				{
					SetState(BAT_COCOON_SATTE);
					mCounter = 0;
				}
			}
			if (mCurrentAni->IsDoneCycle() && isDown)
			{
				mCurrentAni->Reset();
				SetState(BAT_FLY_STATE);
				mCounter = 0;
			}

		}
		if (mState == BAT_FLY_STATE)
		{
			if (isDown)
				mPosition.y++;
			else mPosition.y--;
			if (mPosition.y == mCenter.y)
			{
				SetState(BAT_FLYWITHSHOCK_STATE);
				mCounter = 0;
			}
			if (mPosition.y == mCenter.y - 15)
			{
				SetState(BAT_SWING_STATE);
				mCounter = 0;
			}
		}
		if (mState == BAT_FLYWITHSHOCK_STATE) {
			if (mDirection == Right)
				mPosition.x -= 1.5;
			else mPosition.x += 1.5;
			if (mPosition.x < mCenter.x - amplitudeA || mPosition.x>mCenter.x + amplitudeA)
			{
				if (mDirection == Left)
					mDirection = Right;
				else mDirection = Left;

				if (isDown)
					mPosition.y += 0.5;
				else mPosition.y -= 0.5;

			}
			else
			{
				if (isDown)
					mPosition.y += 0.3;
				else mPosition.y -= 0.3;
			}
			if ((mPosition.y > mCenter.y + amplitudeB * 2 && mPosition.x < mCenter.x))
			{
				if (mPosition.y > mCenter.y + amplitudeB * 2)
					mPosition.y--;
				isDown = !isDown;
			}
			if ((mPosition.y < mCenter.y) && mPosition.x < mCenter.x)
			{
				SetPositionX(mCenter.x);
				SetPositionY(mCenter.y);
				SetVelocityX(0.f);
				SetVelocityY(0.f);
				SetState(BAT_FLY_STATE);
				mCounter = 0;
			}
		}
	}
	mCurrentAni->Update(deltaTime);
}

void Bat::Draw(D3DXVECTOR2 transform)
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

int Bat::GetState()
{
	return mState;
}

void Bat::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void Bat::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BAT_COCOON_SATTE:
		mCurrentAni = mAniCocoon;
		break;
	case BAT_SWING_STATE:
		mCurrentAni = mAniSwing;
		break;
	case BAT_FLY_STATE:
		mCurrentAni = mAniFlying;
		break;
	case BAT_FLYWITHSHOCK_STATE:
		mCurrentAni = mAniFlyWithShock;
		break;
	}
}

void Bat::OnSetPosition()
{
}

void Bat::CheckDirection(Player* player)
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

EnemyType Bat::GetEnemyType()
{
	return EnemyType::EBatEnemy;
}

void Bat::TakeDamage(Entity* source, int damage)
{
	if (mIsInvincible) return;
	mHP -= damage;
	if (mHP <= 0)
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
	else
	{
		SetInvincible(true);
	}
}

void Bat::SetInvincible(bool val)
{
	mIsInvincible = val;
}
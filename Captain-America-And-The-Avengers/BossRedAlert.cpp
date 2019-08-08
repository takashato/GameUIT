#include "pch.h"
#include "Game.h"
#include "BossRedAlert.h"
#include <cmath>

BossRedAlert::BossRedAlert(D3DXVECTOR3 position)
{
	mDirection = Left;
	LoadAnimations();
	SetPosition(position);
	mState = BOSSREDALERT_IDLE_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


BossRedAlert::~BossRedAlert()
{
}

void BossRedAlert::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\BossRedAlert.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniTossTheBarrel = new Animation(mSprite, mAniScripts->GetRectList("TossTheBarrel", "0"), 1.5F, false);
	mAniGun = new Animation(mSprite, mAniScripts->GetRectList("Gun", "0"), 0.9F, false);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.1F);
	mAniCrazy = new Animation(mSprite, mAniScripts->GetRectList("Crazy", "0"), 0.1F);
	mAniHurt = new Animation(mSprite, mAniScripts->GetRectList("Hurt", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Die", "0"), 0.1F);

	mCurrentAni = mAniIdle;
}

void BossRedAlert::Update(float deltaTime, Player* player)
{
	playerPos = player->GetPosition();

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
	if (mState == BOSSREDALERT_IDLE_STATE)
	{

		CheckDirection(player);
		if (mCounter > 0.5f)
		{
			SetState(BOSSREDALERT_TOSS_THE_BARREL_STATE);
			mCounter = 0;
		}
	}
	if (mState == BOSSREDALERT_TOSS_THE_BARREL_STATE)
	{
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		if (mCurrentAni->GetCurrentFrame() == 1 && !thrownDynamite) // Create 
		{
			thrownDynamite = true;
			auto pos = mPosition;
			if (mDirection == Left)
				pos.x += 10;
			this->dynamite = new Dynamite(pos, mDirection);
			this->dynamite->boss = this;
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(
				this->dynamite
			);
		}
		else if (mCurrentAni->GetCurrentFrame() == 2 && dynamite != nullptr && !dynamite->isThrown)
		{
			dynamite->Throw();
		}
		else if (mCurrentAni->IsDoneCycle())//Neu thung thung no roi
		{
			mCurrentAni->Reset();
			SetState(BOSSREDALERT_GUN_STATE);
			mCounter = 0;
			thrownDynamite = false;
			dynamite = nullptr;
		}
	}
	if (mState == BOSSREDALERT_GUN_STATE)
	{
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		if (mCurrentAni->IsDoneCycle())
		{
			CheckDirection(player);
			mCountGun++;
			mCurrentAni->Reset();
			if (mCountGun == 2)
			{
				mCountGun = 0;
				SetState(BOSSREDALERT_RUNNING_STATE);
				mCounter = 0;
			}
			else
			{
				SetState(BOSSREDALERT_GUN_STATE);
				mCounter = 0;
			}
		}
	}
	if (mState == BOSSREDALERT_RUNNING_STATE)
	{
		if (mCounter > 4.f)
		{
			CheckDirection(player);
			SetState(BOSSREDALERT_TOSS_THE_BARREL_STATE);
			mCounter = 0;
		}
		if (mDirection == EntityDirection::Left)
		{
			if (mVelocityX > -100)
			{
				AddVelocityX(-20);
				if (mVelocityX < -100)
					SetVelocityX(-100);
			}
		}
		else
		{
			if (mVelocityX < 100)
			{
				AddVelocityX(20);
				if (mVelocityX > 100)
					SetVelocityX(100);
			}
		}
	}
	if (mState == BOSSREDALERT_CRAZY_STATE)
	{
		if (mCounter > 1.f)
		{
			auto pos = mPosition;
			auto bb = GetBoundingBox();
			pos.y += 25;
			if (mDirection == Left) pos.x = bb.left;
			else pos.x = bb.right;
			SceneManager::GetInstance().GetScene()->GetGrid()->Add(
				new RedAlertBullet(pos, mDirection)
			);
			mCounter = 0;
		}
		if (mDirection == EntityDirection::Left)
		{
			if (mVelocityX > -60)
			{
				AddVelocityX(-20);
				if (mVelocityX < -60)
					SetVelocityX(-60);
			}
		}
		else
		{
			if (mVelocityX < 60)
			{
				AddVelocityX(20);
				if (mVelocityX > 60)
					SetVelocityX(60);
			}
		}
	}
	if (mState == BOSSREDALERT_HURT_STATE)
	{
		if (mCounter > 2.f) {
			thrownDynamite = false;
			SetState(BOSSREDALERT_GUN_STATE);
			mCounter = 0;
		}
	}
	if (mState == BOSSREDALERT_DYING_STATE)
	{
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCounterDie += deltaTime;
		if (mCounterDie > 0.2f)
		{
			SetDirection(GetDirection() == Left ? Right : Left);
			mCounterDie = 0;
		}
		if (mCounter > 1.f)
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
	if (mPosition.x < 14.f)
	{
		mPosition.x = 14;
		mDirection = Right;
	}
	if (mPosition.x > 213.f)
	{
		mPosition.x = 213;
		mDirection = Left;
	}

	mCounter += deltaTime;

	mCurrentAni->Update(deltaTime);
}
void BossRedAlert::Draw(D3DXVECTOR2 transform)
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

int BossRedAlert::GetState()
{
	return mState;
}

void BossRedAlert::SetState(int state)
{
	if (state == BOSSREDALERT_GUN_STATE)
	{
		auto pos = mPosition;
		auto bb = GetBoundingBox();
		pos.y += 20;
		if (mDirection == Left) pos.x = bb.left;
		else pos.x = bb.right;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new RedAlertBullet(pos, mDirection)
		);
	}
	mState = state;
	ChangeAnimationByState(mState);
}

void BossRedAlert::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BOSSREDALERT_IDLE_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniIdle;
		break;
	case BOSSREDALERT_TOSS_THE_BARREL_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniTossTheBarrel;
		break;
	case BOSSREDALERT_GUN_STATE:
		mCurrentAni = mAniGun;
		break;
	case BOSSREDALERT_CRAZY_STATE:
		mCurrentAni = mAniCrazy;
		break;
	case BOSSREDALERT_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case BOSSREDALERT_HURT_STATE:
		mCurrentAni = mAniHurt;
		break;
	case BOSSREDALERT_DYING_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniDying;
		break;
	case BOSSREDALERT_CHANGE_STATUS_STATE:
		mCurrentAni = mAniDying;
		break;

	}
}

void BossRedAlert::OnSetPosition()
{
}

void BossRedAlert::CheckDirection(Player* player)
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
void BossRedAlert::TakeDamageBossRedAlertNotCrazy(Entity* source, int damage)
{
	if (mIsInvincible) return;
	SetState(BOSSREDALERT_HURT_STATE);
	mCounter = 0;
	mHP -= damage;
	std::cout << "Boss take " << damage << "\n";
	if (damage == 2)
	{
		std::cout << "Found 2!\n";
	}
	if (mHP < 5)
	{
		SetState(BOSSREDALERT_CRAZY_STATE);
	}
	SetInvincible(true);

}
void BossRedAlert::TakeDamage(Entity* source, int damage)
{
	if (mState == BOSSREDALERT_CRAZY_STATE)
	{
		if (mIsInvincible) return;
		mHP -= damage;
		std::cout << "Boss take " << damage << "\n";
		if (damage == 2)
		{
			std::cout << "Found 2!\n";
		}
		if (mHP <= 0)
		{
			SetState(BOSSREDALERT_DYING_STATE);
			mCounter = 0;
		}
		else
		{
			SetInvincible(true);
		}
	}
}
void BossRedAlert::SetInvincible(bool val)
{
	mIsInvincible = val;
}
RECT BossRedAlert::GetBoundingBox()
{
	if (mCurrentAni == nullptr) {
		return RECT();
	}

	RECT bb;
	bb.left = mPosition.x + 5;
	bb.top = mPosition.y + 20;
	bb.right = mPosition.x + mCurrentAni->GetWidth() - 10;
	bb.bottom = mPosition.y + mCurrentAni->GetHeight();
	return bb;
}
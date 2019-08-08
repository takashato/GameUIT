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
	mCenter = position;
	mCenter.y = mCenter.y + 15;
}


BossRedAlert::~BossRedAlert()
{
}

void BossRedAlert::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\BossRedAlert.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\BossRedAlert.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniTossTheBarrel = new Animation(mSprite, mAniScripts->GetRectList("TossTheBarrel", "0"), 1.F, false);
	mAniGun = new Animation(mSprite, mAniScripts->GetRectList("Gun", "0"), 0.9F, false);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.1F);
	mAniCrazy = new Animation(mSprite, mAniScripts->GetRectList("Crazy", "0"), 0.1F);

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
	if (mHP > 13)
	{
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
			if (mCurrentAni->IsDoneCycle())//Neu thung thung no roi
			{
				mCurrentAni->Reset();
				SetState(BOSSREDALERT_GUN_STATE);
				mCounter = 0;
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
			if (mCounter > 5.f)
			{
				CheckDirection(player);
				SetState(BOSSREDALERT_GUN_STATE);
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
	}
	else if (mHP > 0 && mHP < 13)
	{
		if (mState != BOSSREDALERT_CRAZY_STATE)
		{
			SetState(BOSSREDALERT_CRAZY_STATE);
			mCounter = 0;
		}
		if (mState == BOSSREDALERT_CRAZY_STATE)
		{
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
	}
	else if (mHP == 0)
	{
		/*SetState(Boss);*///Die
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
void BossRedAlert::TakeDamageBossRedAlert(Entity* source, int damage)
{
	if (mIsInvincible) return;
	/*SetState(BOSS_CHARLESTON_BEHIT_STATE);*/
	mHP -= damage;
	std::cout << "Boss take " << damage << "\n";
	if (damage == 2)
	{
		std::cout << "Found 2!\n";
	}
	if (mHP <= 0)
	{
		SceneManager::GetInstance().GetScene()->mCanTransport = true;
		SetState(BOSS_CHARLESTON_DYING_STATE);
	}
	else
	{
		SetInvincible(true);
	}
}

void BossRedAlert::SetInvincible(bool val)
{
	mIsInvincible = val;
}
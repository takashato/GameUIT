#include "pch.h"
#include "Game.h"
#include "BossCharleston.h"

BossCharleston::BossCharleston(D3DXVECTOR3 position)
{
	mDirection = Left;
	LoadAnimations();
	SetPosition(position);
	mState = BOSS_CHARLESTON_IDLE_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


BossCharleston::~BossCharleston()
{
}

void BossCharleston::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Boss_Wizard.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\Boss_Wizard.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);
	mAniLaugh = new Animation(mSprite, mAniScripts->GetRectList("Laugh", "0"), 0.1F);
	mAniBeHit = new Animation(mSprite, mAniScripts->GetRectList("BeHit", "0"), 0.1F);
	mAniGun = new Animation(mSprite, mAniScripts->GetRectList("Gun", "0"), 0.2F, false);
	mAniKamehameha = new Animation(mSprite, mAniScripts->GetRectList("Kamehameha", "0"), 0.15F);
	mAniHit = new Animation(mSprite, mAniScripts->GetRectList("Hit", "0"), 0.1F);
	mAniFly = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.1F);
	mAniFlyGun = new Animation(mSprite, mAniScripts->GetRectList("FlyGun", "0"), 0.1F, false);

	mCurrentAni = mAniStanding;
}

void BossCharleston::Update(float deltaTime, Player* player)
{

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	mCounter += deltaTime;
	if (player->GetPosition().y < 60 && mPosition.y == 145) {
		SetState(BOSS_CHARLESTON_LAUGH_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_LAUGH_STATE)
	{
		if (player->GetPosition().y > 60)
		{
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCounter = 0;
		}

	}
		if (BOSS_CHARLESTON_IDLE_STATE)
		{
			SetVelocityX(0.f);
			SetVelocityY(0.f);
		}
		switch (mNumChangeMode)
		{
		case 1:
			ModeOne(deltaTime, player);
			break;
		case 2:
			ModeTwo(deltaTime, player);
			break;
		case 3:
			ModeThree(deltaTime, player);
			break;
		default:
			break;
		}
		if (mCountMisc == 2)
		{
			if (mNumChangeMode == 1)
				mNumChangeMode = 2;
			else if(mNumChangeMode==2)
				mNumChangeMode = 3;
			else mNumChangeMode = 1;
			mCountMisc = 0;
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCounter = 0;
		}

	mCurrentAni->Update(deltaTime);
}

void BossCharleston::Draw(D3DXVECTOR2 transform)
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

int BossCharleston::GetState()
{
	return mState;
}

void BossCharleston::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void BossCharleston::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case BOSS_CHARLESTON_IDLE_STATE:
		mCurrentAni = mAniStanding;
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		break;
	case BOSS_CHARLESTON_RUNNING_STATE:
		SetVelocityY(0.f);
		mCurrentAni = mAniRunning;
		break;
	case BOSS_CHARLESTON_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	case BOSS_CHARLESTON_BEHIT_STATE:
		mCurrentAni = mAniBeHit;
		break;
	case BOSS_CHARLESTON_GUN_STATE:
		mCurrentAni = mAniGun;
		break;
	case BOSS_CHARLESTON_HIT_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniHit;
		break;
	case BOSS_CHARLESTON_KAMEHAMEHA_STATE:
		mCurrentAni = mAniKamehameha;
		break;
	case BOSS_CHARLESTON_LAUGH_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniLaugh;
		break;
	case BOSS_CHARLESTON_PLYGUN_STATE:
		mCurrentAni = mAniFlyGun;
		break;
	case BOSS_CHARLESTON_PLY_STATE:
		mCurrentAni = mAniFly;
		break;
	case BOSS_CHARLESTON_JUMP_STATE:
		mCurrentAni = mAniFly;
		bool mIsJump = true;
		bool mIsFalling = false;
		break;
	}
}

void BossCharleston::OnSetPosition()
{
}

EnemyType BossCharleston::GetEnemyType()
{
	return EnemyType::EBossCharleston;
}
void BossCharleston::SetBullet(Bullet* Bullet)
{

}
void BossCharleston::ModeOne(float deltaTime, Player* player)
{
	if (mState == BOSS_CHARLESTON_IDLE_STATE && mCounter > 0.9f)
	{
		SetState(BOSS_CHARLESTON_RUNNING_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_GUN_STATE)
	{
		SetVelocityX(0.f);
		SetVelocityY(0.f);
	}
	if (mState == BOSS_CHARLESTON_RUNNING_STATE)
	{
		if (mDirection == EntityDirection::Left)
		{
			if (mVelocityX > -PLAYER_VELOCITY_X_MAX)
			{
				AddVelocityX(-50);
				if (mVelocityX < -PLAYER_VELOCITY_X_MAX)
					SetVelocityX(-PLAYER_VELOCITY_X_MAX);
			}
		}
		else
		{
			if (mVelocityX < PLAYER_VELOCITY_X_MAX)
			{
				AddVelocityX(50);
				if (mVelocityX > PLAYER_VELOCITY_X_MAX)
					SetVelocityX(PLAYER_VELOCITY_X_MAX);
			}
		}
	}
	if (mState == BOSS_CHARLESTON_RUNNING_STATE && mCounter > 0.9f)
	{
		SetState(BOSS_CHARLESTON_GUN_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_GUN_STATE)
	{
		if (mCurrentAni->IsDoneCycle())
		{
			mCurrentAni->Reset();
			if (coutGun == 3) {
				SetState(BOSS_CHARLESTON_KAMEHAMEHA_STATE);
				coutGun = 1;
				mCountMisc++;
			}
			else {
				SetState(BOSS_CHARLESTON_GUN_STATE);
				mCounter = 0;
				++coutGun;
			}
			mCounter = 0;
		}
	}
	if (mState == BOSS_CHARLESTON_KAMEHAMEHA_STATE)
	{
		if (mCurrentAni->IsDoneCycle())
		{
			mCurrentAni->Reset();
			SetState(BOSS_CHARLESTON_RUNNING_STATE);
			mCounter = 0;
		}
	}
	CheckDirection(player);
	if (mPosition.x < 0) {
		mPosition.x = 0;
		mDirection = Right;
	}
	if (mPosition.x > 216) {
		mPosition.x = 216;
		mDirection = Left;
	}

}
void BossCharleston::ModeTwo(float deltaTime, Player* player)
{
	if (mState == BOSS_CHARLESTON_PLY_STATE || mState == BOSS_CHARLESTON_PLYGUN_STATE)
	{
		if (player->GetPosition().x - mPosition.x <= 10 && player->GetPosition().x - mPosition.x >= -10) {
			SetState(BOSS_CHARLESTON_PLYGUN_STATE);
			mCounter = 0;
		}
		if (mState == BOSS_CHARLESTON_PLYGUN_STATE)
		{
			if (mCurrentAni->IsDoneCycle())
			{
				mCurrentAni->Reset();
				SetState(BOSS_CHARLESTON_PLY_STATE);
				mCounter = 0;
			}

		}
		if (mFlyHorizontal)
		{
			if (mDirection == EntityDirection::Left)
			{

				if (mVelocityX > -PLAYER_VELOCITY_X_MAX)
				{
					AddVelocityX(-150);
					if (mVelocityX < -PLAYER_VELOCITY_X_MAX)
						SetVelocityX(-PLAYER_VELOCITY_X_MAX);
				}
			}
			else
			{

				if (mVelocityX < PLAYER_VELOCITY_X_MAX)
				{
					AddVelocityX(150);
					if (mVelocityX > PLAYER_VELOCITY_X_MAX)
						SetVelocityX(PLAYER_VELOCITY_X_MAX);
				}


			}
		}
		if (mFlyUp)
		{
			if (mVelocityY > -PLAYER_VELOCITY_Y_MAX)
			{
				AddVelocityY(-100);
				if (mVelocityY < -PLAYER_VELOCITY_Y_MAX)
					SetVelocityY(-PLAYER_VELOCITY_Y_MAX);
			}
		}
		if (mFlyDown)
		{
			if (mVelocityY < PLAYER_VELOCITY_Y_MAX)
			{
				AddVelocityY(100);
				if (mVelocityY > PLAYER_VELOCITY_Y_MAX)
					SetVelocityY(PLAYER_VELOCITY_Y_MAX);
			}
		}

		if (mPosition.y < 30.f)
		{
			mFlyUp = false;
			mFlyHorizontal = true;
			mFlyDown = false;
			SetVelocityY(0.f);
		}
		if (mPosition.x < 5.f)
		{
			mFlyUp = false;
			mFlyHorizontal = false;
			mFlyDown = true;
			SetVelocityX(0.f);
		}
		if (mPosition.y > 145.f&&mPosition.x == 5.f&&mDirection == Left)
		{
			mDirection = Right;
			mFlyUp = true;
			mFlyHorizontal = false;
			mFlyDown = false;
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCountMisc++;
			mCounter = 0;

		}
		if (mPosition.x > 189)
		{
			mFlyUp = false;
			mFlyHorizontal = false;
			mFlyDown = true;
			SetVelocityX(0.f);
		}
		if (mPosition.y > 145.f&&mPosition.x == 189.f&&mDirection == Right)
		{
			mDirection = Left;
			mFlyUp = true;
			mFlyHorizontal = false;
			mFlyDown = false;
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCountMisc++;
			mCounter = 0;

		}



	}
	if (mPosition.y < 30.f)
		mPosition.y = 30.f;
	if (mPosition.x < 5.f)
		mPosition.x = 5.f;
	if (mPosition.y > 145.f)
		mPosition.y = 145.f;
	if (mPosition.x > 189.f)
		mPosition.x = 189.f;
	if (mState == BOSS_CHARLESTON_IDLE_STATE && mCounter > 2.f)
	{
		SetState(BOSS_CHARLESTON_PLY_STATE);
		mCounter = 0;
	}

}
Bullet* BossCharleston::GetBullet()
{
	return mBullet;
}
void BossCharleston::CheckDirection(Player* player)
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
void BossCharleston::ModeThree(float deltaTime, Player* player)
{
	if (mState == BOSS_CHARLESTON_IDLE_STATE && mCounter > 1.f)
	{
		SetState(BOSS_CHARLESTON_JUMP_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_JUMP_STATE)
	{
		if (mDirection == EntityDirection::Left)
		{

			if (mVelocityX > -90)
			{
				AddVelocityX(-30);
				if (mVelocityX < -90)
					SetVelocityX(-90);
			}
		}
		else
		{

			if (mVelocityX < 90)
			{
				AddVelocityX(30);
				if (mVelocityX > 90)
					SetVelocityX(90);
			}


		}
		if (mIsJump)
		{
			if (mVelocityY > -90)
			{
				AddVelocityY(-30);
				if (mVelocityY < -90)
					SetVelocityY(-90);
			}
		}
		if (mIsFalling)
		{
			if (mVelocityY < 90)
			{
				AddVelocityY(30);
				if (mVelocityY > 90)
					SetVelocityY(90);
			}
		}
		if (mPosition.y < 110)
		{
			mIsJump = false;
			mIsFalling = true;
		}
		if (mPosition.y > 145)
		{
			mPosition.y = 145;
			mIsJump = true;
			mIsFalling = false;
			mCountMisc++;
			SetState(BOSS_CHARLESTON_RUNNING_STATE);
			mCounter = 0;

		}
		if (mPosition.x < 0 && mDirection == Left)
		{
			mDirection = Right;
		}
		if (mPosition.x > 240 && mDirection == Right)
		{
			mDirection = Left;
		}
	}
	if (mState == BOSS_CHARLESTON_RUNNING_STATE)
	{
		if ((mPosition.x - player->GetPosition().x) <= 90 && (mPosition.x - player->GetPosition().x) >= -90)
		{
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCounter = 0;
		}
		else
		{
			if (mDirection == EntityDirection::Left)
			{
				SetVelocityX(-150);
			}
			else
			{
				SetVelocityX(150);
			}
			CheckDirection(player);
			if (mPosition.x < 0) {
				mPosition.x = 0;
				mDirection = Right;
			}
			if (mPosition.x > 216) {
				mPosition.x = 216;
				mDirection = Left;
			}
		}
	}
}


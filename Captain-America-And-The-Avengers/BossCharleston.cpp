#include "pch.h"
#include "Game.h"
#include "BossSmallBullet.h"
#include "BossVipBullet.h"
#include "BossCharleston.h"

BossCharleston::BossCharleston(D3DXVECTOR3 position)
{
	mHP = 20;
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
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.5F, false);
	mAniLaugh = new Animation(mSprite, mAniScripts->GetRectList("Laugh", "0"), 0.1F);
	mAniBeHit = new Animation(mSprite, mAniScripts->GetRectList("BeHit", "0"), 0.1F);
	mAniGun = new Animation(mSprite, mAniScripts->GetRectList("Gun", "0"), 0.3F, false);
	mAniKamehameha = new Animation(mSprite, mAniScripts->GetRectList("Kamehameha", "0"), 0.15F);
	mAniHit = new Animation(mSprite, mAniScripts->GetRectList("Hit", "0"), 0.2F);
	mAniFly = new Animation(mSprite, mAniScripts->GetRectList("Fly", "0"), 0.1F);
	mAniFlyGun = new Animation(mSprite, mAniScripts->GetRectList("FlyGun", "0"), 0.1F, false);
	mAniTurnOffTheLight = new Animation(mSprite, mAniScripts->GetRectList("TurnOffTheLight", "0"), 0.2F);

	mCurrentAni = mAniStanding;
}

void BossCharleston::Update(float deltaTime, Player* player)
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

	mCounter += deltaTime;

	if (mState == BOSS_CHARLESTON_DYING_STATE)
	{
		SetVelocityX(.0f);
		SetVelocityY(.0f);
		return;
	}

	if (mState == BOSS_CHARLESTON_BEHIT_STATE)
	{
		mCounterBeHit += deltaTime;
		if (mCounterBeHit > 0.2f)
		{
			SetState(mLastState);
			mCounterBeHit = 0;
		}
	}

	if (mPosition.y == 145 && player->GetPosition().x > mPosition.x - 5 && player->GetPosition().x < mPosition.x + 28 && player->GetPosition().y>145)
	{
		SetState(BOSS_CHARLESTON_HIT_STATE);
		mCounter = 0;
	}
	if (mState == BOSS_CHARLESTON_HIT_STATE)
	{
		CheckDirection(player);
		if (mCurrentAni->IsDoneCycle())
		{
			mCurrentAni->Reset();
			if (mChangeLight)
			{
				if (auto scene = dynamic_cast<CharlestonBossScene*>(SceneManager::GetInstance().GetScene()))
				{
					scene->ToggleLight();
				}
				mChangeLight = false;
			}
			SetState(BOSS_CHARLESTON_IDLE_STATE);
			mCounter = 0;
		}

	}
	if (player->GetPosition().y <= 57 && mPosition.y == 145) {
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
	case 4:
		ModeFour(deltaTime, player);//
	default:
		break;
	}
	if (mCountMisc == 2)
	{
		if (mNumChangeMode == 1)
			mNumChangeMode = 2;
		else if (mNumChangeMode == 2)
			mNumChangeMode = 3;
		else if (mNumChangeMode == 3)
			mNumChangeMode = 4;
		else mNumChangeMode = 1;
		mCountMisc = 0;
		if (mNumChangeMode == 4)
		{
			if (mPosition.x < 96 || mDirection == Right)
				mNumChangeMode = 3;
		}
		SetState(BOSS_CHARLESTON_IDLE_STATE);
		mCounter = 0;
	}
	mCurrentAni->Update(deltaTime);
}

void BossCharleston::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetBlink(mIsInvincible);
		if (auto scene = dynamic_cast<CharlestonBossScene*>(SceneManager::GetInstance().GetScene()))
		{
			if (!scene->isLightOn)
			{
				mCurrentAni->Draw(GetPosition(), transform, D3DCOLOR_RGBA(0, 0, 0, 255));
			}
			else
			{
				if (mCurrentAni == mAniBeHit)
				{
					AddPositionX(mDirection*(-1));
				}
				mCurrentAni->Draw(GetPosition(), transform);
			}
		}
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
	if (state == BOSS_CHARLESTON_GUN_STATE)
	{
		auto pos = mPosition;
		auto bb = GetBoundingBox();
		pos.y += 15;
		if (mDirection == Left) pos.x = bb.left;
		else pos.x = bb.right;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new BossSmallBullet(pos, mDirection, playerPos.y < mPosition.y ? -1 : 0)
		);
	}
	else if (state == BOSS_CHARLESTON_KAMEHAMEHA_STATE)
	{
		auto pos = mPosition;
		auto bb = GetBoundingBox();
		pos.y += 13;
		if (mDirection == Left) pos.x = bb.left;
		else pos.x = bb.right;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new BossVipBullet(pos, mDirection)
		);
	}
	else if (state == BOSS_CHARLESTON_PLYGUN_STATE)
	{
		auto pos = mPosition;
		auto bb = GetBoundingBox();
		pos.y = (bb.bottom + bb.top) / 2;
		pos.x = mDirection == Left ? bb.left : bb.right;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new BossVipBullet(pos, 0, 1)
		);
	}
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
		mFlyUp = true;
		mFlyDown = false;
		mFlyHorizontal = false;
		mCurrentAni = mAniFly;
		break;
	case BOSS_CHARLESTON_TURN_OFF_THE_LIGHT_STATE:
		SetVelocityX(0.f);
		SetVelocityY(0.f);
		mCurrentAni = mAniHit;
	case BOSS_CHARLESTON_JUMP_STATE:
		mCurrentAni = mAniFly;
		mIsJump = true;
		mIsFalling = false;
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
		if (player->GetPosition().x - mPosition.x <= 10 && player->GetPosition().x - mPosition.x >= -10
			&& mState != BOSS_CHARLESTON_PLYGUN_STATE) {
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
void BossCharleston::TakeDamage(Entity* source, int damage)
{
	if (mIsInvincible) return;
	mLastState = mState;
	SetState(BOSS_CHARLESTON_BEHIT_STATE);
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

void BossCharleston::SetInvincible(bool val)
{
	mIsInvincible = val;
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
void BossCharleston::ModeFour(float deltaTime, Player* player)
{
	
	if (mState == BOSS_CHARLESTON_PLY_STATE)
	{
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
		if (mPosition.x < 65.f)
		{
			mFlyUp = false;
			mFlyHorizontal = false;
			mFlyDown = true;
			SetVelocityX(0.f);
		}
		if (mPosition.y > 48.f&&mPosition.x == 65.f&&mDirection == Left)
		{
			mDirection = Right;
			mFlyUp = true;
			mFlyHorizontal = false;
			mFlyDown = false;
			mChangeLight = true;
			SetState(BOSS_CHARLESTON_HIT_STATE);
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
	if (mPosition.x < 65.f)
		mPosition.x = 65.f;
	if (mPosition.y > 145.f)
		mPosition.y = 145.f;
	if (mPosition.x > 189.f)
		mPosition.x = 189.f;
	if (mState == BOSS_CHARLESTON_IDLE_STATE && mCounter > 1.f)
	{
		SetState(BOSS_CHARLESTON_PLY_STATE);
		mCounter = 0;
	}
}


#include "pch.h"
#include "Game.h"
#include "RunEnemy.h"

RunEnemy::RunEnemy(D3DXVECTOR3 position, int subTypeID) : Enemy()
{
	mHP = 2;
	mSubTypeID = subTypeID;
	spawnPosition = position;
	LoadAnimations();
	SetPosition(position);
	mState = RUNENEMY_STANDING_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


RunEnemy::~RunEnemy()
{
}

void RunEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\RunEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void RunEnemy::Update(float deltaTime, Player* player)
{
	Enemy::Update(deltaTime, player);

	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 runEnemyPosition = this->GetPosition();
	
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

	if (mState == RUNENEMY_DYING_STATE)
	{
		mCounterDie += deltaTime;
		if (mCounterDie > 0.2f)
		{
			if (SceneManager::GetInstance().GetScene() != nullptr
				&& SceneManager::GetInstance().GetScene()->GetGrid() != nullptr)
			{
				Explosion* explosion;
				explosion = new Explosion(this);
				SceneManager::GetInstance().GetScene()->GetGrid()->Add(explosion);
			}

			mGridNode->Remove(this);
			delete this;
		}
		return;
	}
	
	if (mSubTypeID == 0) // Only Run
	{
		/*if (mIsInvincible)
		{
			if (mCurrentAni != mAniDying)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniRunning)
				{
					SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
				}
				SetState(RUNENEMY_DYING_STATE);
				SetVelocityX(0.f);
				SetVelocityY(0.f);
			}
			mCounter = .0f;
		}
		else
		{*/
		if (abs(runEnemyPosition.x - playerPosition.x) < 200)
		{
			if (mCurrentAni == mAniStanding)
			{
				SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniRunning->GetHeight());
			}
			else if (mCurrentAni == mAniDying)
			{
				SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniRunning->GetHeight());
			}
			SetState(RUNENEMY_RUNNING_STATE);

			mCounter += deltaTime;
			if (mCounter >= MOVEMENT_UPDATE_TIME)
			{
				if (mDirection == Left)
				{
					if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
						AddVelocityX(-100);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
				else
				{
					if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
						AddVelocityX(100);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
				mCounter = 0;
			}
			if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		}
		else
		{
			if (mCurrentAni == mAniDying)
			{
				SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
			}
			else if (mCurrentAni == mAniRunning)
			{
				SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
			}
			SetState(RUNENEMY_STANDING_STATE);

			if (runEnemyPosition.x < playerPosition.x)
				SetDirection(EntityDirection::Right);
			else
				SetDirection(EntityDirection::Left);
			SetVelocityX(0.f);
			SetVelocityY(0.f);
		}
		//}
	}

	if (mSubTypeID == 1) // Run and Shoot
	{
		SetDirection(EntityDirection::Right);
		/*if(mCurrentAni == mAniStanding && mState == RUNENEMY_STANDING_STATE)
			lastPosition = this->GetPosition();*/
			/*if (mIsInvincible)
			{
				if (mCurrentAni != mAniDying)
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
					}
					else if (mCurrentAni == mAniRunning)
					{
						SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
					}
					SetState(RUNENEMY_DYING_STATE);
					SetVelocityX(0.f);
					SetVelocityY(0.f);
				}
				mCounter = .0f;
			}
			else
			{*/
		if (!isShoot)
		{
			if (mCurrentAni == mAniStanding)
			{
				SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniRunning->GetHeight());
			}
			else if (mCurrentAni == mAniDying)
			{
				SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniRunning->GetHeight());
			}
			SetState(RUNENEMY_RUNNING_STATE);

			if (runEnemyPosition.x - spawnPosition.x > 256)
			{
				SetPosition(spawnPosition);
				SetState(RUNENEMY_STANDING_STATE);
			}
			else
			{
				SetVelocityX(GetDirection()*RUN_SPEED);
				AddPositionX(GetVelocityX() * deltaTime);
			}
		}

		if ((int)runEnemyPosition.x % 31 > 29)
			isShoot = true;

		if (isShoot)
		{
			mCounter += deltaTime;

			if (mCurrentAni == mAniDying)
			{
				SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
			}
			else if (mCurrentAni == mAniRunning)
			{
				SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
			}
			SetState(RUNENEMY_STANDING_STATE);

			SetVelocityX(0.f);
			SetVelocityY(0.f);
			if (mCounter > 0.4f)
			{
				isShoot = false;
				mCounter = .0f;
			}
		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		//}
	}
}

void RunEnemy::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAni != nullptr && mState != -1)
	{
		mCurrentAni->SetBlink(mIsInvincible);
		if (mCurrentAni == mAniDying)
		{
			AddPositionX(mDirection*(-1));
		}
		mCurrentAni->Draw(GetPosition(), transform);
		this->RenderBoundingBox(transform);
	}
	else
	{
		mCurrentAni->Draw(GetPosition());
		this->RenderBoundingBox(D3DXVECTOR2(0,0));
	}
}

int RunEnemy::GetState()
{
	return mState;
}

void RunEnemy::SetState(int state)
{
	if (state == RUNENEMY_RUNNING_STATE && mState == RUNENEMY_STANDING_STATE)
	{
		auto position = mPosition;
		position.x += mDirection == Right ? 5 : -5;
		SceneManager::GetInstance().GetScene()->GetGrid()->Add(
			new NormalBullet(position, mDirection)
		);
	}
	mState = state;
	ChangeAnimationByState(mState);
}

void RunEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case RUNENEMY_STANDING_STATE:
		mCurrentAni = mAniStanding;
		break;
	case RUNENEMY_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case RUNENEMY_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void RunEnemy::OnSetPosition()
{
	Enemy::OnSetPosition();
}

EnemyType RunEnemy::GetEnemyType()
{
	return EnemyType::ERunEnemy;
}

void RunEnemy::OnAttacked()
{
	SetInvincible(true);
}

void RunEnemy::OnDie()
{
	SetState(RUNENEMY_DYING_STATE);
}

void RunEnemy::TakeDamage(Entity* source, int hp)
{
	if (!mIsInvincible)
	{
		if (source->GetCollidableObjectType() == EWeapon || source->GetCollidableObjectType() == EPlayer)
		{
			mHP -= hp;
			if (mHP <= 0)
			{
				OnDie();
			}
			else
			{
				OnAttacked();
			}
		}
	}
}

void RunEnemy::SetInvincible(bool val)
{
	Enemy::SetInvincible(val);
}
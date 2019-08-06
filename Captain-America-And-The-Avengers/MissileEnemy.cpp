#include "pch.h"
#include "Game.h"
#include "MissileEnemy.h"

MissileEnemy::MissileEnemy(D3DXVECTOR3 position, int subTypeID)
{
	mHP = 3;
	mSubTypeID = subTypeID;
	spawnPosition = position;
	LoadAnimations();
	SetPosition(position);
	mState = MISSILEENEMY_STANDING_STATE;
	SetVelocityX(0.f);
	SetVelocityY(0.f);
}


MissileEnemy::~MissileEnemy()
{
	
}

void MissileEnemy::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Enemies\\Enemies.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Enemies\\MissileEnemy.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.1F);
	mAniJumping = new Animation(mSprite, mAniScripts->GetRectList("Jumping", "0"), 0.1F);
	mAniFalling = new Animation(mSprite, mAniScripts->GetRectList("Falling", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniDying = new Animation(mSprite, mAniScripts->GetRectList("Dying", "0"), 0.1F);

	mCurrentAni = mAniStanding;
}

void MissileEnemy::Update(float deltaTime, Player* player)
{
	Enemy::Update(deltaTime, player);

	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 missileEnemyPosition = this->GetPosition();

	if (mSubTypeID != 0 && mSubTypeID != 3)
	{
		if (playerPosition.x <= missileEnemyPosition.x)
		{
			mDirection = Left;
		}
		else
		{
			mDirection = Right;
		}
	}

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);
	
	if (mSubTypeID == 1) // Missile Enemy Stand, Sit and Shoot
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
				/*else if (mCurrentAni == mAniRunning)
				{
					SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
				}*/
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
				}
				SetState(MISSILEENEMY_DYING_STATE);
			}
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
				/*else if (mCurrentAni == mAniRunning)
				{
					SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniSitting->GetHeight());
				}*/

				if (mCurrentAni != mAniSitting)
					SetState(MISSILEENEMY_SITTING_STATE);
			}
			else if (mCounter < 0.9f)
			{
				if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
				}
				else if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
				}
				/*else if (mCurrentAni == mAniRunning)
				{
					SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
				}*/

				if (mCurrentAni != mAniStanding)
					SetState(MISSILEENEMY_STANDING_STATE);
			}
			else
			{
				mCounter = 0;
			}
		}
	}
	else if (mSubTypeID == 2) // Missile Enemy Run and Shoot
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
				else if (mCurrentAni == mAniRunning)
				{
					SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
				}
				SetState(MISSILEENEMY_DYING_STATE);
				SetVelocityX(0.f);
				SetVelocityY(0.f);
			}
		}
		else
		{
			if (mDirection == Left)
			{
				if (playerPosition.x > 160 && isMeetPlayer == false)
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniRunning->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniRunning->GetHeight());
					}
					else if (mCurrentAni == mAniSitting)
					{
						SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniRunning->GetHeight());
					}
					SetState(MISSILEENEMY_RUNNING_STATE);
					SetVelocityX(GetDirection()*RUN_SPEED);
					AddPositionX(GetVelocityX() * deltaTime);
				}

				if (missileEnemyPosition.x - playerPosition.x <= 50)
				{
					if (isMeetPlayer == false)
					{
						if (mCurrentAni == mAniSitting)
						{
							SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
						}
						else if (mCurrentAni == mAniDying)
						{
							SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
						}
						else if (mCurrentAni == mAniRunning)
						{
							SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
						}
						SetState(MISSILEENEMY_STANDING_STATE);
						SetVelocityX(0.f);
						SetVelocityY(0.f);
					}
					isMeetPlayer = true;
					
					if (mCounter >= 0.9f)
					{
						if (mCurrentAni == mAniStanding)
						{
							SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniSitting->GetHeight());
							SetState(MISSILEENEMY_SITTING_STATE);
						}
						else
						{
							if (mCurrentAni == mAniSitting)
							{
								SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
							}
							else if (mCurrentAni == mAniDying)
							{
								SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
							}
							else if (mCurrentAni == mAniRunning)
							{
								SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
							}
							SetState(MISSILEENEMY_STANDING_STATE);
						}
						mCounter = 0;
					}
				}
			}
			else
			{
				if (mCounter >= 0.9f)
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniSitting->GetHeight());
						SetState(MISSILEENEMY_SITTING_STATE);
					}
					else
					{
						if (mCurrentAni == mAniSitting)
						{
							SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
						}
						else if (mCurrentAni == mAniDying)
						{
							SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
						}
						else if (mCurrentAni == mAniRunning)
						{
							SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
						}
						SetState(MISSILEENEMY_STANDING_STATE);
					}
					mCounter = 0;
				}
			}
			if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		}
	}
	else if (mSubTypeID == 0) // Only Run and Jump Not Shoot
	{
		SetDirection(EntityDirection::Left);
		if (mIsInvincible)
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
				else if (mCurrentAni == mAniFalling)
				{
					SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniJumping)
				{
					SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniDying->GetHeight());
				}
				SetState(MISSILEENEMY_DYING_STATE);
				SetVelocityX(0.f);
				SetVelocityY(0.f);
			}
		}
		else
		{
			if (!isJump)
			{
				if (mCurrentAni == mAniStanding)
				{
					SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniRunning->GetHeight());
				}
				else if (mCurrentAni == mAniDying)
				{
					SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniRunning->GetHeight());
				}
				else if (mCurrentAni == mAniFalling)
				{
					SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniRunning->GetHeight());
				}
				else if (mCurrentAni == mAniJumping)
				{
					SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniRunning->GetHeight());
				}
				SetState(MISSILEENEMY_RUNNING_STATE);

				if (spawnPosition.x - GetPosition().x > 256)
				{
					SetPosition(spawnPosition);
					SetState(MISSILEENEMY_STANDING_STATE);
				}
				else
				{
					SetVelocityX(GetDirection()*RUN_SPEED);
					AddPositionX(GetVelocityX() * deltaTime);
				}
			}

			if (missileEnemyPosition.x - player->GetShield()->GetPosition().x < 70 && player->GetShield()->GetState() == ShieldState::EShieldHigh)
				isJump = true;

			if (isJump)
			{
				mCounter += deltaTime;
				if (mCounter < 0.4f)
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniJumping->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniJumping->GetHeight());
					}
					else if (mCurrentAni == mAniFalling)
					{
						SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniJumping->GetHeight());
					}
					else if (mCurrentAni == mAniRunning)
					{
						SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniJumping->GetHeight());
					}
					SetState(MISSILEENEMY_JUMPING_STATE);
					
					AddPositionY(-200 * deltaTime);

					SetVelocityX(GetDirection()*RUN_SPEED);
					AddPositionX(GetVelocityX() * deltaTime);
				}
				else
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniFalling->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniFalling->GetHeight());
					}
					else if (mCurrentAni == mAniJumping)
					{
						SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniFalling->GetHeight());
					}
					else if (mCurrentAni == mAniRunning)
					{
						SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniFalling->GetHeight());
					}
					SetState(MISSILEENEMY_FALLING_STATE);

					AddPositionY(150 * deltaTime);

					SetVelocityX(GetDirection()*RUN_SPEED);
					AddPositionX(GetVelocityX() * deltaTime);

					if (missileEnemyPosition.y > 401.0f)
					{
						isJump = false;
						SetPositionY(401.0f);
						SetState(MISSILEENEMY_RUNNING_STATE);
						mCounter = 0;
					}
				}
			}
			if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
		}
	}
	else if (mSubTypeID == 3) // Run, Stand, Sit Shoot. If Stand on Step, Jump and Fall to Ground
	{
		SetDirection(EntityDirection::Left);

		if (mPosition.x - playerPosition.x < 100)
			isMeetPlayer = true;

		if (mIsInvincible)
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
				else if (mCurrentAni == mAniFalling)
				{
					SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniJumping)
				{
					SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniDying->GetHeight());
				}
				else if (mCurrentAni == mAniSitting)
				{
					SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
				}
				SetState(MISSILEENEMY_DYING_STATE);
				SetVelocityX(0.f);
				SetVelocityY(0.f);
			}
		}
		else
		{
			if (missileEnemyPosition.y < 401.0f)
			{
				if (isMeetPlayer)
				{
					mCounter += deltaTime;
					if (mCounter < 0.4f)
					{
						if (mCurrentAni == mAniStanding)
						{
							SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniJumping->GetHeight());
						}
						else if (mCurrentAni == mAniDying)
						{
							SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniJumping->GetHeight());
						}
						SetState(MISSILEENEMY_JUMPING_STATE);

						AddPositionY(-100 * deltaTime);

						SetVelocityX(GetDirection()*(RUN_SPEED - 10));
						AddPositionX(GetVelocityX() * deltaTime);
					}
					else
					{
						
						if (mCurrentAni == mAniDying)
						{
							SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniFalling->GetHeight());
						}
						else if (mCurrentAni == mAniJumping)
						{
							SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniFalling->GetHeight());
						}
						SetState(MISSILEENEMY_FALLING_STATE);

						AddPositionY(150 * deltaTime);

						SetVelocityX(GetDirection()*(RUN_SPEED - 10));
						AddPositionX(GetVelocityX() * deltaTime);

						if (GetPosition().y > 401.0f)
						{
							SetPositionY(401.0f);
							SetState(MISSILEENEMY_STANDING_STATE);
							SetVelocityX(0.f);
							SetVelocityY(0.f);
							mCounter = 0;
						}
					}
				}
				else 
				{
					SetState(MISSILEENEMY_STANDING_STATE);
					SetVelocityX(0.f);
					SetVelocityY(0.f);
				}
			}
			else 
			{
				mCounter += deltaTime;
				if (mCounter < 0.5f)
				{
					if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniSitting->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniSitting->GetHeight());
					}
					else if (mCurrentAni == mAniRunning)
					{
						SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniSitting->GetHeight());
					}
					SetState(MISSILEENEMY_SITTING_STATE);
					SetVelocityX(0.f);
					SetVelocityY(0.f);
				}
				else if (mCounter >= 0.5f && mCounter < 1.0f)
				{
					if (mCurrentAni == mAniSitting)
					{
						SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniStanding->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniStanding->GetHeight());
					}
					else if (mCurrentAni == mAniRunning)
					{
						SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniStanding->GetHeight());
					}
					SetState(MISSILEENEMY_STANDING_STATE);
					SetVelocityX(0.f);
					SetVelocityY(0.f);
				}
				else if (mCounter >= 1.0f && mCounter < 2.0f)
				{
					if (mCurrentAni == mAniSitting)
					{
						SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniRunning->GetHeight());
					}
					else if (mCurrentAni == mAniDying)
					{
						SetPositionY(mPosition.y + mAniDying->GetHeight() - mAniRunning->GetHeight());
					}
					else if (mCurrentAni == mAniStanding)
					{
						SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniRunning->GetHeight());
					}
					SetState(MISSILEENEMY_RUNNING_STATE);

					
					SetVelocityX(changeDirection*GetDirection()*RUN_SPEED);
					AddPositionX(GetVelocityX() * deltaTime);
				}
				else
				{
					mCounter = 0;
					changeDirection = -changeDirection;
				}
			}
		}
		if (mCurrentAni != NULL) mCurrentAni->Update(deltaTime);
	}
}

void MissileEnemy::Draw(D3DXVECTOR2 transform)
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

int MissileEnemy::GetState()
{
	return mState;
}

void MissileEnemy::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void MissileEnemy::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case MISSILEENEMY_STANDING_STATE:
		mCurrentAni = mAniStanding;
		break;
	case MISSILEENEMY_SITTING_STATE:
		mCurrentAni = mAniSitting;
		break;
	case MISSILEENEMY_RUNNING_STATE:
		mCurrentAni = mAniRunning;
		break;
	case MISSILEENEMY_JUMPING_STATE:
		mCurrentAni = mAniJumping;
		break;
	case MISSILEENEMY_FALLING_STATE:
		mCurrentAni = mAniFalling;
		break;
	case MISSILEENEMY_DYING_STATE:
		mCurrentAni = mAniDying;
		break;
	}
}

void MissileEnemy::OnSetPosition()
{
	Enemy::OnSetPosition();
}

EnemyType MissileEnemy::GetEnemyType()
{
	return EnemyType::EMissileEnemy;
}

Bullet* MissileEnemy::GetBullet()
{
	return mBullet;
}

void MissileEnemy::SetBullet(Bullet* bullet)
{
	mBullet = (NormalBullet*)bullet;
}

void MissileEnemy::OnAttacked()
{
	if (mCurrentAni == mAniStanding)
	{
		SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniRunning)
	{
		SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniFalling)
	{
		SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniJumping)
	{
		SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniSitting)
	{
		SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
	}
	SetState(MISSILEENEMY_DYING_STATE);
	//mCurrentAni->Reset();
	SetInvincible(true);
}

void MissileEnemy::OnDie()
{
	/*SetPositionX(mPosition.x + mDirection * 5);
	if (mCurrentAni == mAniStanding)
	{
		SetPositionY(mPosition.y + mAniStanding->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniRunning)
	{
		SetPositionY(mPosition.y + mAniRunning->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniFalling)
	{
		SetPositionY(mPosition.y + mAniFalling->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniJumping)
	{
		SetPositionY(mPosition.y + mAniJumping->GetHeight() - mAniDying->GetHeight());
	}
	else if (mCurrentAni == mAniSitting)
	{
		SetPositionY(mPosition.y + mAniSitting->GetHeight() - mAniDying->GetHeight());
	}
	SetState(MISSILEENEMY_DYING_STATE);*/

	mGridNode->Remove(this);
	delete this;
}

void MissileEnemy::TakeDamage(Entity* source, int hp)
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

void MissileEnemy::SetInvincible(bool val)
{
	Enemy::SetInvincible(val);
	if (val)
	{
		mAniStanding->SetBlink(true);
		mAniRunning->SetBlink(true);
		mAniDying->SetBlink(true);
		mAniFalling->SetBlink(true);
		mAniJumping->SetBlink(true);
		mAniSitting->SetBlink(true);
		std::cout << "Blink on\n";
	}
	else
	{
		mAniStanding->SetBlink(false);
		mAniRunning->SetBlink(false);
		mAniDying->SetBlink(false);
		mAniFalling->SetBlink(false);
		mAniJumping->SetBlink(false);
		mAniSitting->SetBlink(false);
		std::cout << "Blink off\n";
	}
}
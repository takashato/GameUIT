#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"

Player::Player() : Entity()
{	
	mIsCollectKeyCrystal = false;
	LoadAnimations();
	SetState(EPlayerState::Standing);
}

void Player::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Animation Captain America And Shield.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniPunching = new Animation(mSprite, mAniScripts->GetRectList("Punching", "0"), 0.1F);
	mAniThrowingShield = new Animation(mSprite, mAniScripts->GetRectList("ThrowingShield", "0"), 0.1F, false);
	mAniHighShielding = new Animation(mSprite, mAniScripts->GetRectList("HighShielding", "0"), 0.1F);
	mAniSitting = new Animation(mSprite, mAniScripts->GetRectList("Sitting", "0"), 0.1F);
	mAniLowPunching = new Animation(mSprite, mAniScripts->GetRectList("LowPunching", "0"), 0.15F);
	mAniRunning = new Animation(mSprite, mAniScripts->GetRectList("Running", "0"), 0.15F);
	mAniLowJumping = new Animation(mSprite, mAniScripts->GetRectList("LowJump", "0"), 0.15F);
	mAniHighJumping = new Animation(mSprite, mAniScripts->GetRectList("HighJump", "0"), 0.05F);
	mAniKicking = new Animation(mSprite, mAniScripts->GetRectList("Kicking", "0"), 0.1F);
	mAniTakeDamage = new Animation(mSprite, mAniScripts->GetRectList("TakeDamage", "0"), 0.1F);
	mAniTakeDown = new Animation(mSprite, mAniScripts->GetRectList("TakeDown", "0"), 1.0F, false);
	mAniInvincibleStand = new Animation(mSprite, mAniScripts->GetRectList("InvincibleStand", "0"), 0.05F);
	mAniSurfing = new Animation(mSprite, mAniScripts->GetRectList("Surfing", "0"), 0.1F);
	mAniSittingOnShield = new Animation(mSprite, mAniScripts->GetRectList("SittingOnShield", "0"), 0.1F);
	mAniSwimming = new Animation(mSprite, mAniScripts->GetRectList("Swimming", "0"), 0.1F);
	mAniCling = new Animation(mSprite, mAniScripts->GetRectList("Cling", "0"), 0.2F);
	mAniDiving = new Animation(mSprite, mAniScripts->GetRectList("Diving", "0"), 0.2F);

	mAniHealth = new Animation(mSprite, mAniScripts->GetRectList("Health", "0"), .1F, false);
	mAniExitSignal = new Animation(mSprite, mAniScripts->GetRectList("ExitSignal", "0"), .1F, false);

	mHealth.mAni = mAniHealth;
	mExitSignal.mAni = mAniExitSignal;
	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (mIsInvincible)
	{
		mInvincibleCounter += deltaTime;
		if (mInvincibleCounter >= INVINCIBLE_DURATION)
		{
			mIsInvincible = false;
			mInvincibleCounter = .0f;
		}
	}

	if (!mIsCollisionLeftRightSide && mState->GetState() != EPlayerState::TakeDown)
	{
		this->AddPositionX(deltaTime * mVelocityX);
	}

	if (mState->GetState() != EPlayerState::Standing 
		&& mState->GetState() != EPlayerState::Running
		&& mState->GetState() != EPlayerState::Sitting
		&& mState->GetState() != EPlayerState::ThrowingShield
		&& mState->GetState() != EPlayerState::HighShielding
		&& mState->GetState() != EPlayerState::LowPunching
		&& mState->GetState() != EPlayerState::Punching
		&& mState->GetState() != EPlayerState::Swimming
		&& mState->GetState() != EPlayerState::Cling
		//&& mState->GetState() != EPlayerState::TakeDown
		&& mState->GetState() != EPlayerState::Surfing
		) // vY not affect when standing
	{
		this->AddPositionY(deltaTime * mVelocityY);
	}

	if (mCurrentAni != NULL)
	{
		mCurrentAni->SetFlippedHorizontally(mDirection == Right);

		if (mCurrentAni == mAniSurfing)
		{
			if (mCurrentAni->GetCurrentFrame() != 1)
				mCurrentAni->Update(deltaTime);
		}
		else
			mCurrentAni->Update(deltaTime);

		UpdateSize();
	}

	if (mState != nullptr) mState->Update(*this, deltaTime);
}

void Player::Draw(D3DXVECTOR2 trans)
{
	mCurrentAni->SetBlink(mIsInvincible && mState->GetState() != EPlayerState::TakeDown);
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	this->RenderBoundingBox(trans);
	mExitSignal.CollectKeyCrystal(canTransport);
	mHealth.Draw();
	mExitSignal.Draw();
}

void Player::HandleKeyboard(Keyboard* keyboard)
{
	if (mState != nullptr)
	{
		mState->HandleKeyboard(*this, keyboard);
	}
}

void Player::OnKeyDown(BYTE code)
{
	if (mState != nullptr) mState->OnKeyDown(*this, code);
	if (code == VK_LEFT || code == VK_RIGHT || code == VK_UP || code == VK_DOWN
		|| code == (BYTE)'X' 
		|| code == (BYTE)'Z')
	{
		lastKeyDown = code;
		lastKeyDownTimePoint = std::chrono::steady_clock::now();
	}
}

void Player::OnKeyUp(BYTE code)
{
	if (mState != nullptr) mState->OnKeyUp(*this, code);
	if (code == VK_LEFT || code == VK_RIGHT || code == VK_UP || code == VK_DOWN
		|| code == (BYTE)'X'
		|| code == (BYTE)'Z')
	{
		lastKeyUp = code;
		lastKeyUpTimePoint = std::chrono::steady_clock::now();
	}
}

PlayerState* Player::GetState()
{
	return mState;
}

void Player::SetState(EPlayerState state)
{
	if (state == EPlayerState::Falling && collideWithMovingGround) return;

	mLastState = mState == nullptr ? state : mState->GetState();
	Data exitData;
	if (mState != nullptr) exitData = mState->Exit(*this, state);

	switch (state)
	{
	case Standing:		    mState = &mStateStanding; break;
	case Running:		    mState = &mStateRunning; break;
	case Jumping:		    mState = &mStateJumping; break;
	case HighJumping:	    mState = &mStateHighJumping; break;
	case Falling:		    mState = &mStateFalling; break;
	case Sitting:		    mState = &mStateSitting; break;
	case ThrowingShield:    mState = &mStateThrowing; break;
	case HighShielding:	    mState = &mStateHighShielding; break;
	case LowPunching:	    mState = &mStateLowPunching; break;
	case Punching:		    mState = &mStatePunching; break;
	case SittingOnShield:   mState = &mStateSitOnShield; break;
	case Swimming:			mState = &mStateSwimming; break;
	case Kicking:			mState = &mStateKicking; break;
	case EPlayerState::TakeDamage: mState = &mStateTakeDamage; break;
	case TakeDown:			mState = &mStateTakeDown; break;
	case Surfing:			mState = &mStateSurfing; break;
	case Cling:				mState = &mStateCling; break;
	}

	mState->Enter(*this, mLastState, std::move(exitData));
	ChangeAnimationByState(state);
}

EPlayerState Player::GetLastState()
{
	return mLastState;
}

Animation* Player::StateToAnimation(EPlayerState state)
{
	switch (state)
	{
	case EPlayerState::Standing:
		return mAniStanding;
	case EPlayerState::Jumping:
	case EPlayerState::Falling:
		return mAniLowJumping;
	case EPlayerState::HighJumping:
		return mAniHighJumping;
	case EPlayerState::Sitting:
		return mAniSitting;
	case EPlayerState::HighShielding:
		return mAniHighShielding;
	case EPlayerState::Punching:
		return mAniPunching;
	case EPlayerState::LowPunching:
		return mAniLowPunching;
	case EPlayerState::ThrowingShield:
		return mAniThrowingShield;
	case EPlayerState::Kicking:
		return mAniKicking;
	case EPlayerState::TakeDamage:
		return mAniTakeDamage;
	case EPlayerState::TakeDown:
		return mAniTakeDown;
	case EPlayerState::InvincibleStand:
		return mAniInvincibleStand;
	case EPlayerState::Surfing:
		return mAniSurfing;
	case EPlayerState::SittingOnShield:
		return mAniSittingOnShield;
	case EPlayerState::Swimming:
		return mAniSwimming;
	case EPlayerState::Cling:
		return mAniCling;
	case EPlayerState::Diving:
		return mAniDiving;
	case EPlayerState::Running:
	default:
		return mAniRunning;
	}
}

void Player::ChangeAnimationByState(EPlayerState state)
{
	const auto oldHeight = GetHeight();
	const auto oldWidth = GetWidth();

	mCurrentAni = StateToAnimation(state);
	mCurrentAni->Reset();
	UpdateSize();

	if ((state == EPlayerState::Punching
		|| state == EPlayerState::LowPunching)
		&& (mLastState == EPlayerState::Punching
			|| mLastState == EPlayerState::LowPunching))
	{
		mPosition.x += float(mDirection == Right ? 0 : oldWidth - GetWidth());
	}
	else
	{
		mPosition.x += float(oldWidth - GetWidth()) / 2.0f;
	}

	if (mState->GetState() != EPlayerState::HighJumping)
		mPosition.y += float(oldHeight - GetHeight()); //Lam giat man hinh => xu li lai camera sau
}

Animation* Player::GetCurrentAnimation()
{
	return mCurrentAni;
}

void Player::OnSetPosition()
{
}

void Player::UpdateSize()
{
	// Dynamically set width, height
	SetWidth((float)mCurrentAni->GetWidth());
	SetHeight((float)mCurrentAni->GetHeight());
}

RECT Player::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();

	RECT rect;
	if (mState->GetState() != EPlayerState::Punching
		&& mState->GetState() != EPlayerState::LowPunching
		&& mState->GetState() != EPlayerState::Kicking
		&& mState->GetState() != EPlayerState::Surfing
		)
	{
		rect.left = (long)(mPosition.x + GetWidth() / 2) - PLAYER_HITBOX_HALF;
		rect.top = (long)mPosition.y;
		rect.right = (long)(rect.left + PLAYER_HITBOX_HALF * 2);
		rect.bottom = (long)(rect.top + GetHeight());
	}
	else
	{
		rect.left = (long)mPosition.x;
		rect.top = (long)mPosition.y;
		rect.right = (long)(rect.left + GetWidth());
		rect.bottom = (long)(rect.top + GetHeight());
	}
	return rect;
	
}

CollidableObjectType Player::GetCollidableObjectType()
{
	return EPlayer;
}

bool Player::OnCollision(std::vector<CollisionEvent*>& cEvent)
{
	for (size_t i = 0; i < cEvent.size(); ++i)
	{
		if (cEvent[i]->entity->GetCollidableObjectType() == EItem)
		{
			((Item*)cEvent[i]->entity)->Consume(*this);
		}
		else if (cEvent[i]->entity->GetCollidableObjectType() == EBullet)
		{
			auto bullet = (Bullet*)cEvent[i]->entity;
			if (bullet->GetBulletType() == BulletType::BNormalBullet || bullet->GetBulletType() == BulletType::BBossNormalBullet)
			{
				this->TakeDamage(1);
				bullet->SetState(1); // Pending remove
			}
			else if (bullet->GetBulletType() == BulletType::BLittleMissile)
			{
				this->TakeDamage(1);
				SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(bullet));
				bullet->SetState(1);
			}
			else if (bullet->GetBulletType() == BulletType::BBossVipBullet)
			{
				this->TakeDamage(3);
				bullet->SetState(1);
			}
			else if (bullet->GetBulletType() == BulletType::BBigMissile)
			{
				this->TakeDamage(1);
				SceneManager::GetInstance().GetScene()->GetGrid()->Add(new Explosion(bullet));
				bullet->SetState(1);
			}
		}
		else if (cEvent[i]->entity->GetCollidableObjectType() == ETransportArea && canTransport)
		{
			SceneManager::GetInstance().GetScene()->Transport();
			return false;
		}
	}

	if (mState != nullptr) mState->OnCollision(*this, cEvent);

	for (CollisionEvent* ce : cEvent) // Avoid memory leak
	{
		delete ce;
	}

	return true;
}

bool Player::CheckAABB(std::set<Entity*> &entities)
{
	collideWithMovingGround = false;
	auto pbb = GetBoundingBox();
	for (auto entity : entities)
	{
		auto ebb = entity->GetBoundingBox();
		if (GeoUtils::IsIntersect(pbb, ebb))
		{
			if (mState->GetState() == EPlayerState::Kicking
				|| mState->GetState() == EPlayerState::LowPunching
				|| mState->GetState() == EPlayerState::Punching)
			{
				if (mDirection == Right && ebb.left > pbb.left
					|| mDirection == Left && ebb.right < pbb.right)
				{
					if (auto enemy = dynamic_cast<Enemy*>(entity))
					{
						enemy->TakeDamage(this, 1);
						continue;
					}
					else if (auto capsule = dynamic_cast<Capsule*>(entity))
					{
						capsule->Drop();
						continue;
					}
					else if (auto button = dynamic_cast<LightButton*>(entity))
					{
						if (auto scene = dynamic_cast<CharlestonBossScene*>(SceneManager::GetInstance().GetScene()))
						{
							scene->ToggleLight();
						}
						continue;
					}
				}
			}

			if (auto enemy = dynamic_cast<Enemy*>(entity))
			{
				if (mState->GetState() != EPlayerState::Surfing
					&& mState->GetState() != EPlayerState::SittingOnShield)
				{
					if (enemy->GetEnemyType() == EGunStockEnemy)
					{
						if (((GunStock*)enemy)->GetState() != GUNSTOCK_ROTATING_STATE)
							((GunStock*)enemy)->BeAttacked();
					}
					else
						enemy->TakeDamage(this, 1);
					this->TakeDamage(1);
					if (mState->GetState() == EPlayerState::ElectricShock) return true;
				}
				else if (mState->GetState() == EPlayerState::Surfing)
				{
					if (enemy->GetEnemyType() == EnemyType::EBossCharleston)
					{
						enemy->TakeDamage(this, 2);
					}
					else
					{
						enemy->TakeDamage(this, 3);
					}
				}
			}
			else if (auto dynamicGround = dynamic_cast<DynamicGround*>(entity))
			{
				collideWithMovingGround = true;
				SetPositionY(dynamicGround->GetPosition().y - GetHeight() + 5);
			}
		}
	}
	return true;
}

Shield* Player::GetShield()
{
	return mShield;
}

void Player::SetShield(Shield* shield)
{
	mShield = shield;
}

void Player::TakeDamage(int modifier)
{
	if (mIsInvincible 
		|| mState->GetState() == EPlayerState::TakeDown
		|| mState->GetState() == EPlayerState::ElectricShock) return; // Invincible can't take damage
	std::cout << "Take " << modifier << " damage.\n";
	mHealth.Subtract(modifier);
	mIsInvincible = true;
	mInvincibleCounter = .0f;
	if (mState->GetState() != EPlayerState::Jumping
		&& mState->GetState() != EPlayerState::Falling
		&& mState->GetState() != EPlayerState::SittingOnShield
		)
		SetState(EPlayerState::TakeDamage);
	else if (mHealth.Get() <= 0)
	{
		SetState(EPlayerState::TakeDown);
	}
}

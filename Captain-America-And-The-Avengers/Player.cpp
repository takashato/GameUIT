#include "pch.h"
#include "Game.h"
#include "Player.h"

Player::Player() : Entity()
{	
	ExitIsOke = true; //Chua xu lí an cuc exit
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
	mAniTakeDown = new Animation(mSprite, mAniScripts->GetRectList("TakeDown", "0"), 0.2F);
	mAniInvincibleStand = new Animation(mSprite, mAniScripts->GetRectList("InvincibleStand", "0"), 0.05F);
	mAniSurfing = new Animation(mSprite, mAniScripts->GetRectList("Surfing", "0"), 0.2F);
	mAniSittingOnShield = new Animation(mSprite, mAniScripts->GetRectList("SittingOnShield", "0"), 0.1F);
	mAniSwimming = new Animation(mSprite, mAniScripts->GetRectList("Swimming", "0"), 0.1F);
	mAniCling = new Animation(mSprite, mAniScripts->GetRectList("Cling", "0"), 0.2F);


	mCurrentAni = mAniStanding;
}

void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (!mIsCollisionLeftRightSide)
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
	if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
	this->RenderBoundingBox(trans);
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
}

void Player::OnKeyUp(BYTE code)
{
	if (mState != nullptr) mState->OnKeyUp(*this, code);
}

PlayerState* Player::GetState()
{
	return mState;
}

void Player::SetState(EPlayerState state)
{
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
	mPosition.x += float(mDirection == Right ? 0 : oldWidth - GetWidth());
	mPosition.y += float(oldHeight - GetHeight());
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
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(rect.left + GetWidth());
	rect.bottom = (long)(rect.top + GetHeight());

	return rect;
}

CollidableObjectType Player::GetCollidableObjectType()
{
	return EPlayer;
}

void Player::OnCollision(std::vector<CollisionEvent*>& cEvent)
{
	mIsCollisionLeftRightSide = false;
	bool collisionWithGround = false;
	for (CollisionEvent* ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			GroundType type = ((Ground*)ce->entity)->GetGroundType();
			if (ce->ny == -1.0f && skipGround != ce->entity)
			{
				if (jumpThrough)
				{
					jumpThrough = false;
					if (type != EGroundHard)
					{
						skipGround = ce->entity;
					}
				}
				else
				{
					collisionWithGround = true;
					if (mState->GetState() == EPlayerState::Falling 
						|| mState->GetState() == EPlayerState::HighJumping)
					{
						skipGround = nullptr;
						SetState(EPlayerState::Sitting);
						SetPositionY(ce->entity->GetPosition().y - GetHeight());
					}
				}
			}

			if (type == EGroundHard)
			{
				RECT pB = GetBoundingBox();
				RECT eB = ce->entity->GetBoundingBox();

				if (ce->nx == -1.0f)
				{
					mIsCollisionLeftRightSide = true;
					SetVelocityX(.0);
					SetPositionX(eB.left - GetWidth());
				}
				else if (ce->nx == 1.0f)
				{
					mIsCollisionLeftRightSide = true;
					SetVelocityX(.0);
					SetPositionX(eB.right);
				}

				if (mState->GetState() != Falling)
				{
					if (ce->ny == 1.0f && (pB.left >= eB.left && pB.left <= eB.right || pB.right >= eB.left && pB.right <= eB.right))
					{
						SetPositionY(eB.bottom);
						SetState(EPlayerState::Falling);
					}
				}
			}
		}
	}

	if (mState->GetState() == EPlayerState::Running && !collisionWithGround)
	{
		SetState(EPlayerState::Falling);
	}

	if (mState != nullptr) mState->OnCollision(*this, cEvent);

	for (CollisionEvent* ce : cEvent) // Avoid memory leak
	{
		delete ce;
	}
}

Shield* Player::GetShield()
{
	return mShield;
}

void Player::SetShield(Shield* shield)
{
	mShield = shield;
}

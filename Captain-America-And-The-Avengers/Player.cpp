#include "pch.h"
#include "Game.h"
#include "Player.h"

Player::Player() : Entity()
{	
	ExitIsOke = true; //Chua xu lí an cuc exit
	LoadAnimations();
	mState = new PlayerStandingState(this);
}

void Player::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Animation Captain America And Shield.xml");

	mAniStanding = new Animation(mSprite, mAniScripts->GetRectList("Standing", "0"), 0.1F);
	mAniPunching = new Animation(mSprite, mAniScripts->GetRectList("Punching", "0"), 0.15F);
	mAniThrowingShield = new Animation(mSprite, mAniScripts->GetRectList("ThrowingShield", "0"), 0.15F);
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
	if (mState != nullptr) mState->Update(deltaTime);

	mCurrentAni->SetFlippedHorizontally(mDirection == Right);

	if (GetVelocityX() != .0f) {
		AddPositionX(GetVelocityX() * deltaTime);
	}
	if (GetVelocityY() != .0f) {
		AddPositionY(GetVelocityY() * deltaTime);
	}

	if (mCurrentAni != NULL)
	{
		if (mCurrentAni == mAniSurfing)
		{
			if (mCurrentAni->GetCurrentFrame() != 1)
				mCurrentAni->Update(deltaTime);
		}
		else
			mCurrentAni->Update(deltaTime);
	}
}

void Player::Draw()
{
	if (mCamera)
	{
		D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x,
			Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);
		if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition(), trans);
		//Test bouding box
		this->RenderBoundingBox(trans);
	}
	else
	{
		if (mCurrentAni != NULL) mCurrentAni->Draw(GetPosition());
		//Test bouding box
		D3DXVECTOR2 trans(0.f,0.f);
		this->RenderBoundingBox(trans);
	}
	
}

void Player::HandleKeyboard(Keyboard* keyboard)
{
	if (mState != nullptr)
	{
		mState->HandleKeyboard(keyboard);
	}
}

PlayerState* Player::GetState()
{
	return mState;
}

void Player::SetState(PlayerState *state)
{
	if (state == nullptr || this == (void*)0xDDDDDDDD) return;

	delete mState;
	mState = state;
	ChangeAnimationByState(mState->GetState());
}

void Player::ChangeAnimationByState(EPlayerState state)
{
	switch (state)
	{
	case EPlayerState::Standing:
		mCurrentAni = mAniStanding;
		break;
	case EPlayerState::Jumping:
	case EPlayerState::Falling:
		mCurrentAni = mAniLowJumping;
		break;
	case EPlayerState::HighJumping:
		mCurrentAni = mAniHighJumping;
		break;
	case EPlayerState::Sitting:
		mCurrentAni = mAniSitting;
		break;
	case EPlayerState::HighShielding:
		mCurrentAni = mAniHighShielding;
		break;
	case EPlayerState::Punching:
		mCurrentAni = mAniPunching;
		break;
	case EPlayerState::LowPunching:
		mCurrentAni = mAniLowPunching;
		break;
	case EPlayerState::ThrowingShield:
		mCurrentAni = mAniThrowingShield;
		break;
	case EPlayerState::Kicking:
		mCurrentAni = mAniKicking;
		break;
	case EPlayerState::TakeDamage:
		mCurrentAni = mAniTakeDamage;
		break;
	case EPlayerState::TakeDown:
		mCurrentAni = mAniTakeDown;
		break;
	case EPlayerState::InvincibleStand:
		mCurrentAni = mAniInvincibleStand;
		break;
	case EPlayerState::Surfing:
		mCurrentAni = mAniSurfing;
		break;
	case EPlayerState::SittingOnShield:
		mCurrentAni = mAniSittingOnShield;
		break;
	case EPlayerState::Swimming:
		mCurrentAni = mAniSwimming;
		break;
	case EPlayerState::Cling:
		mCurrentAni = mAniCling;
		break;
	case EPlayerState::Running:
	default:
		mCurrentAni = mAniRunning;
		break;
	}
}

void Player::OnSetPosition()
{
}

void Player::SetCamera(Camera* camera)
{
	mCamera = camera;
}

RECT Player::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();
	RECT rect = mCurrentAni->GetCurrentFrameRect();
	rect.right -= rect.left;
	rect.bottom -= rect.top;
	rect.left = 0;
	rect.top = 0;
	return rect;
}

CollidableObjectType Player::GetCollidableType()
{
	return EPlayer;
}

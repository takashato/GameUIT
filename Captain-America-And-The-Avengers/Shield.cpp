#include "pch.h"
#include "Shield.h"

Shield::Shield() : Weapon()
{
	LoadAnimations();
	mState = SHIELD_RUNSHIELD_STATE;
}


Shield::~Shield()
{
}

void Shield::LoadAnimations()
{
	mSprite = new Sprite(L"Resources\\Sprites\\Players\\Cap\\Captain America.png");
	mAniScripts = new AnimationScript("Resources\\Sprites\\Players\\Cap\\Shield.xml");

	mAniIdle = new Animation(mSprite, mAniScripts->GetRectList("Idle", "0"), 0.1F);
	mAniHighShield = new Animation(mSprite, mAniScripts->GetRectList("HighShield", "0"), 0.1F);
	mAniRunShield = new Animation(mSprite, mAniScripts->GetRectList("RunShield", "0"), 0.1F);
	mAniSitShield = new Animation(mSprite, mAniScripts->GetRectList("SitShield", "0"), 0.1F);

	mCurrentAni = mAniIdle;
}

void Shield::Update(float deltaTime, Player* player)
{
	D3DXVECTOR3 playerPosition = player->GetPosition();
	D3DXVECTOR3 shieldPosition;
	shieldPosition.z = 0.f;

	if (player->GetDirection() == Left)
		SetDirection(EntityDirection::Left);
	else
		SetDirection(EntityDirection::Right);


	mCurrentAni->SetFlippedHorizontally(mDirection == Right);
	mCounter += deltaTime;

	if (player->GetState()->GetState() == EPlayerState::Standing)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::Running)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 6;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 6;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::Falling || player->GetState()->GetState() == EPlayerState::Jumping)
	{
		mCurrentAni = mAniIdle;
		mState = SHIELD_IDLE_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + 2;
			shieldPosition.y = playerPosition.y + 2;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x + 5;
			shieldPosition.y = playerPosition.y + 2;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::HighShielding)
	{
		mCurrentAni = mAniHighShield;
		mState = SHIELD_HIGHSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + 6;
			shieldPosition.y = playerPosition.y - 1;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x;
			shieldPosition.y = playerPosition.y - 1;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::Cling)
	{

	}
	else if (player->GetState()->GetState() == EPlayerState::InvincibleStand)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;
		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}

	}
	else if (player->GetState()->GetState() == EPlayerState::Kicking)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			SetDirection(EntityDirection::Left);
			shieldPosition.x = playerPosition.x - 2;
			shieldPosition.y = playerPosition.y + 5;
			SetPosition(shieldPosition);
		}
		else
		{
			SetDirection(EntityDirection::Right);
			shieldPosition.x = playerPosition.x + player->GetWidth() - 5;
			shieldPosition.y = playerPosition.y + 5;
			SetPosition(shieldPosition);
		}
		mCurrentAni->SetFlippedHorizontally(mDirection == Right);
	}
	else if (player->GetState()->GetState() == EPlayerState::Sitting)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x - 3;
			shieldPosition.y = playerPosition.y + 8;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::LowPunching)
	{
		mCurrentAni = mAniIdle;
		mState = SHIELD_IDLE_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + 8;
			shieldPosition.y = playerPosition.y + 6;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x + 5;
			shieldPosition.y = playerPosition.y + 6;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::SittingOnShield)
	{
		mCurrentAni = mAniSitShield;
		mState = SHIELD_SITSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x - 2;
			shieldPosition.y = playerPosition.y + player->GetHeight() - 2;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x;
			shieldPosition.y = playerPosition.y + player->GetHeight() - 2;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::Surfing)
	{
		mCurrentAni = mAniRunShield;
		mState = SHIELD_RUNSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			shieldPosition.x = playerPosition.x + player->GetWidth() - 3;
			shieldPosition.y = playerPosition.y;
			SetPosition(shieldPosition);
		}
		else
		{
			shieldPosition.x = playerPosition.x - 4;
			shieldPosition.y = playerPosition.y;
			SetPosition(shieldPosition);
		}
	}
	else if (player->GetState()->GetState() == EPlayerState::ThrowingShield)
	{
		mCurrentAni = mAniHighShield;
		mState = SHIELD_HIGHSHIELD_STATE;

		if (player->GetDirection() == Right)
		{
			/*shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
			shieldPosition.y = playerPosition.y + 9;
			SetPosition(shieldPosition);*/

			if (mCounter >= MOVEMENT_UPDATE_TIME)
			{
				if (shieldPosition.x + GetWidth() < 200.0f)
				{
					if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
						AddVelocityX(-PLAYER_ACC_X);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
				else
				{
					if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
						AddVelocityX(PLAYER_ACC_X);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
			}
		}
		else
		{
			/*shieldPosition.x = playerPosition.x - 11;
			shieldPosition.y = playerPosition.y + 9;
			SetPosition(shieldPosition);*/

			if (mCounter >= MOVEMENT_UPDATE_TIME)
			{
				if (shieldPosition.x + GetWidth() < 200.0f)
				{
					if (GetVelocityX() < PLAYER_VELOCITY_X_MAX)
						AddVelocityX(PLAYER_ACC_X);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
				else
				{
					if (GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
						AddVelocityX(-PLAYER_ACC_X);
					if (GetVelocityX() != 0.f)
						AddPositionX(GetVelocityX() * mCounter);
				}
			}
		}
		mCounter = 0;
	}

}

void Shield::Draw(D3DXVECTOR2 transform)
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

int Shield::GetState()
{
	return mState;
}

void Shield::SetState(int state)
{
	mState = state;
	ChangeAnimationByState(mState);
}

void Shield::ChangeAnimationByState(int state)
{
	switch (state)
	{
	case SHIELD_IDLE_STATE:
		mCurrentAni = mAniIdle;
		break;
	case SHIELD_HIGHSHIELD_STATE:
		mCurrentAni = mAniHighShield;
		break;
	case SHIELD_RUNSHIELD_STATE:
		mCurrentAni = mAniRunShield;
		break;
	case SHIELD_SITSHIELD_STATE:
		mCurrentAni = mAniSitShield;
		break;
	}
}

void Shield::OnSetPosition()
{

}

RECT Shield::GetBoundingBox()
{
	if (mCurrentAni == nullptr) return RECT();

	RECT rect;
	rect.left = (long)mPosition.x;
	rect.top = (long)mPosition.y;
	rect.right = (long)(rect.left + GetWidth());
	rect.bottom = (long)(rect.top + GetHeight());

	return rect;
}
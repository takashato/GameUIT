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

	if (player->GetState()->GetState() == EPlayerState::Standing && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::Running && isThrown == false)
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
	else if ((player->GetState()->GetState() == EPlayerState::Falling || player->GetState()->GetState() == EPlayerState::Jumping) && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::HighShielding && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::Cling && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::Kicking && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::Sitting && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::LowPunching && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::Surfing && isThrown == false)
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
	else if (player->GetState()->GetState() == EPlayerState::ThrowingShield && isThrown == false)
	{
		mCurrentAni = mAniHighShield;
		mState = SHIELD_HIGHSHIELD_STATE;
		

		if (player->GetDirection() == Right)
		{
			flyDirection = 1;
			throwingStateDirection = Right;
			if (player->mAniThrowingShield->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x - 14;
				shieldPosition.y = playerPosition.y - 2;
				SetPosition(shieldPosition);
			}
			else
			{
				shieldPosition.x = playerPosition.x + player->GetWidth() - 4;
				shieldPosition.y = playerPosition.y + 9;
				SetPosition(shieldPosition);
				throwPos = shieldPosition;
			}
			SetPosition(D3DXVECTOR3(playerPosition.x + 10, playerPosition.y + 9, 0.f));
		}
		else
		{
			flyDirection = 0;
			throwingStateDirection = Left;
			if (player->mAniThrowingShield->GetCurrentFrame() == 0)
			{
				shieldPosition.x = playerPosition.x + player->GetWidth() - 6;
				shieldPosition.y = playerPosition.y - 2;
				SetPosition(shieldPosition);
			}
			else
			{
				shieldPosition.x = playerPosition.x - 12;
				shieldPosition.y = playerPosition.y + 9;
				SetPosition(shieldPosition);
				throwPos = shieldPosition;
			}
			SetPosition(D3DXVECTOR3(playerPosition.x - 12, playerPosition.y + 9, 0.f));
		}
		isThrown = true;
	}

	// Shield fly
	if (isThrown)
	{
		mCurrentAni = mAniHighShield;
		mState = SHIELD_HIGHSHIELD_STATE;

		if (throwingStateDirection == Left)
		{
			if (flyDirection == 0)
			{
				if (GetVelocityX() > -100)
					AddVelocityX(-15);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX()*0.08);
				if (this->GetPosition().x - playerPosition.x < -50 - player->GetWidth())
					flyDirection = 1;
			}
			else
			{
				if (this->GetPosition().x >= playerPosition.x && abs(this->GetPosition().y - playerPosition.y) < player->GetHeight())
				{
					isThrown = false;
				}
				else
				{
					if (this->GetPosition().x < playerPosition.x)
					{
						if (GetVelocityX() < 100)
							AddVelocityX(15);
						if (GetVelocityX() != 0.f)
							AddPositionX(GetVelocityX()*0.08);
					}

					if (this->GetPosition().y - playerPosition.y > player->GetHeight())
					{
						if (GetVelocityY() > -100)
							AddVelocityY(-playerPosition.y / 15);
						if (GetVelocityY() != 0.f)
							AddPositionY(GetVelocityY()*0.08);
					}

					if (playerPosition.y - this->GetPosition().y > player->GetHeight())
					{
						if (GetVelocityY() > 100)
							AddVelocityY(playerPosition.y / 15);
						if (GetVelocityY() != 0.f)
							AddPositionY(GetVelocityY()*0.08);
					}
				}
			}
		}
		else
		{
			if (flyDirection == 1)
			{
				if (GetVelocityX() < 100)
					AddVelocityX(15);
				if (GetVelocityX() != 0.f)
					AddPositionX(GetVelocityX()*0.08);
				if (this->GetPosition().x - playerPosition.x - player->GetWidth() > 50)
				{
					flyDirection = 0;
					maxLengthFly = this->GetPosition().x;
					YChangeDirection = this->GetPosition().x;
				}
			}
			else
			{
				if (this->GetPosition().x <= playerPosition.x + player->GetWidth() && abs(this->GetPosition().y - playerPosition.y) < player->GetHeight())
				{
					isThrown = false;
				}
				else
				{
					if (this->GetPosition().x > playerPosition.x + player->GetWidth())
					{
						if (GetVelocityX() > -100)
							AddVelocityX(-15);
						if (GetVelocityX() != 0.f)
							AddPositionX(GetVelocityX()*0.08);
					}

					if (this->GetPosition().y - playerPosition.y > player->GetHeight())
					{
						if (GetVelocityY() > -100)
							AddVelocityY(-playerPosition.y / 15);
						if (GetVelocityY() != 0.f)
							AddPositionY(GetVelocityY()*0.08);
					}

					if (playerPosition.y - this->GetPosition().y > player->GetHeight())
					{
						if (GetVelocityY() > 100)
							AddVelocityY(playerPosition.y / 15);
						if (GetVelocityY() != 0.f)
							AddPositionY(GetVelocityY()*0.08);
					}
				}
			}
		}
	}
}

float Shield::CalYOfLinearEquation(float x1, float y1, float x2, float y2, float posX)
{
	float a = (y1 - y2) / (x1 - x2);
	float b = y1 - a * x1;

	return a*posX + b;
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
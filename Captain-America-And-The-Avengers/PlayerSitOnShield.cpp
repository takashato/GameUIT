#include "pch.h"
#include "Player.h"
#include "PlayerSitOnShield.h"
#include "Ground.h"

void PlayerSitOnShield::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	assert(fromState == EPlayerState::HighJumping);
	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
	bool isOnGround = false;
}

Data PlayerSitOnShield::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSitOnShield::Update(Player& player, float deltaTime)
{
	
}

void PlayerSitOnShield::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Left)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(-MOVING_HOR);
			player.SetDirection((EntityDirection)-1);
		}
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Right)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(MOVING_HOR);
			player.SetDirection((EntityDirection)1);
		}
	}
}

void PlayerSitOnShield::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_ATTACK)
	{
		if (isOnGround)
			player.SetState(EPlayerState::LowPunching);
		else
			player.SetState(EPlayerState::Kicking);
	}
}

void PlayerSitOnShield::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_DOWN)
	{
		if(isOnGround)
			player.SetState(EPlayerState::Standing);
		else
			player.SetState(EPlayerState::Falling);
	}
}

void PlayerSitOnShield::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	CollisionEvent* groundCe = nullptr;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			if (ce->ny == -1.0f)
			{
				collisionWithGround = true;
				groundCe = ce;
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->nx == -1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Left;
					player.SetPositionX(ce->entity->GetPosition().x - player.GetWidth());
				}
				else if (ce->nx == 1.0f)
				{
					player.mIsCollisionLeftRightSide = true;
					player.mDirectionUnblock = Right;
					player.SetPositionX(ce->entity->GetBoundingBox().right);
				}
			}
		}
	}
	if (collisionWithGround)
	{
		SoundManager::GetInstance().CPlaySound(SoundType::SmallBulletsHitShields);
		player.SetVelocityY(.0f);
		player.SetPositionY(groundCe->entity->GetPosition().y - player.GetHeight());
	}
}

EPlayerState PlayerSitOnShield::GetState()
{
	return EPlayerState::SittingOnShield;
}
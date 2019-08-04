#include "pch.h"
#include "PlayerRunning.h"
#include "Player.h"
#include "Ground.h"

void PlayerRunning::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(GRAVITY);
}

Data PlayerRunning::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerRunning::Update(Player& player, float deltaTime)
{
	player.SetVelocityX(player.GetDirection() * WALKING_SPEED);
	player.SetVelocityY(GRAVITY);
}

void PlayerRunning::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Left)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		player.SetDirection(EntityDirection::Left);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.mIsCollisionLeftRightSide && player.mDirectionUnblock == Right)
		{
			player.mIsCollisionLeftRightSide = false;
		}

		player.SetDirection(EntityDirection::Right);
	}
}

void PlayerRunning::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
	else if (code == VK_KEY_ATTACK)
	{
		if (!player.GetShield()->IsThrown())
		{
			player.SetState(EPlayerState::ThrowingShield);
		}
	}
}

void PlayerRunning::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerRunning::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			if (ce->ny == -1.0f)
			{
				collisionWithGround = true;
			}
			
			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->nx == -1.0f)
				{
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetPosition().x - player.GetWidth());
				}
				else if (ce->nx == 1.0f)
				{
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetBoundingBox().right);
				}
			}
		}

	}
	if (!collisionWithGround)
	{
		player.SetState(EPlayerState::Falling);
	}
}

EPlayerState PlayerRunning::GetState()
{
	return EPlayerState::Running;
}

#include "pch.h"
#include "Player.h"
#include "Ground.h"
#include "PlayerSurfing.h"

void PlayerSurfing::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	assert(fromState == EPlayerState::Standing);
	player.SetVelocityX(player.mDirection * TACKLE_SPEED);
	player.SetVelocityY(JUMP_SPEED_VER);
	SoundManager::GetInstance().CPlaySound(SoundType::SurfingSound);

	mCounter = .0f;
}

Data PlayerSurfing::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSurfing::Update(Player& player, float deltaTime)
{
	mCounter += deltaTime;
	if (mCounter > 0.5f)
	{
		player.SetState(EPlayerState::Standing);
		mCounter = .0f;
	}
}

void PlayerSurfing::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_LEFT) && !keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		std::chrono::duration<float> duration = std::chrono::steady_clock::now() - player.lastKeyUpTimePoint;
		if (duration.count() > 0.1f) {
			player.SetState(EPlayerState::Standing);
		}
	}
}

void PlayerSurfing::OnKeyDown(Player& player, BYTE code)
{
}

void PlayerSurfing::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerSurfing::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
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

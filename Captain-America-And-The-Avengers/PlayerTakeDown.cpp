#include "pch.h"
#include "Player.h"
#include "Ground.h"
#include "BreakGround.h"
#include "PlayerTakeDown.h"

void PlayerTakeDown::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(FALL_SPEED_VER_MAX);
	player.mCurrentAni->Reset();
	SoundManager::GetInstance().CPlaySound(SoundType::Death);
	player.SetVelocityX(.0f);
}

Data PlayerTakeDown::Exit(Player& player, EPlayerState toState)
{
	return std::move(data);
}

void PlayerTakeDown::Update(Player& player, float deltaTime)
{
}

void PlayerTakeDown::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerTakeDown::OnKeyDown(Player& player, BYTE code)
{
	if (code == (BYTE)'R')
	{
		player.mHealth.Set(12);
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerTakeDown::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerTakeDown::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	player.mIsCollisionLeftRightSide = false;
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
		}
	}
	if (collisionWithGround)
	{
		player.SetVelocityY(.0f);
		player.SetPositionY(groundCe->entity->GetPosition().y - player.GetHeight());
	}
}

#include "pch.h"
#include "PlayerStanding.h"
#include "Ground.h"
#include "SceneManager.h"
#include "Player.h"

void PlayerStanding::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	if (fromState == EPlayerState::Falling || fromState == EPlayerState::HighJumping)
	{
		SoundManager::GetInstance().CPlaySound(SoundType::TouchTheGround);
	}

	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerStanding::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerStanding::Update(Player& player, float deltaTime)
{
}

void PlayerStanding::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetState(EPlayerState::Running);
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		player.SetState(EPlayerState::Sitting);
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		player.SetState(EPlayerState::HighShielding);
	}
}

void PlayerStanding::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
	{
		if (player.lastKeyDown == code && player.lastKeyUp == code) {
			std::chrono::duration<float> duration = std::chrono::steady_clock::now() - player.lastKeyDownTimePoint;
			if (duration.count() < 0.3f)
			{
				player.SetState(EPlayerState::Surfing);
			}
			else
			{
				player.SetState(EPlayerState::Running);
			}
		}
		else
		{
			player.SetState(EPlayerState::Running);
		}
	}
	else if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
	else if (code == VK_DOWN)
	{
		player.SetState(EPlayerState::Sitting);
	}
	else if (code == VK_KEY_ATTACK)
	{
		if (!player.GetShield()->IsThrown())
		{
			player.SetState(EPlayerState::ThrowingShield);
		}
		else
		{
			player.SetState(EPlayerState::Punching);
		}
	}
	else if (code == VK_UP)
	{
		if (player.collideWithDoor != nullptr)
		{
			if (player.collideWithDoor->doorName == "extra1")
			{
				SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra1);
			}
			else if (player.collideWithDoor->doorName == "extra2")
			{
				SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra2);
			}
			else
			{
				SceneManager::GetInstance().ChangeScene(MapID::Pittsburgh);
			}
		}
		else
		{
			player.SetState(EPlayerState::HighShielding);
		}
	}
}

void PlayerStanding::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerStanding::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	CollisionEvent* groundCe = nullptr;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform && ce->ny == -1.0f) 
		{
			collisionWithGround = true;
			groundCe = ce;
		}
	}
	if (collisionWithGround)
	{
		if (((Ground*)groundCe->entity)->GetGroundType() == EGroundThorns && player.mState->GetState() != EPlayerState::SittingOnShield)
		{
			player.TakeDamage(1);
		}
	}
	else if (player.mLastState == EPlayerState::Running
		|| player.mLastState == EPlayerState::Jumping
		|| player.mLastState == EPlayerState::Falling
		|| player.mLastState == EPlayerState::HighJumping
		|| player.mLastState == EPlayerState::Sitting)
	{
		player.SetState(EPlayerState::Falling);
	}
}

EPlayerState PlayerStanding::GetState()
{
	return EPlayerState::Standing;
}

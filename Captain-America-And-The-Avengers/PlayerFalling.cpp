#include "pch.h"
#include "PlayerFalling.h"
#include "Player.h"

void PlayerFalling::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(FALL_SPEED_VER_MIN);
	/*if (fromState == State::Captain_Tackle)
		cap.vel.x = 0.0f;
	key = KeyControls::Default;*/
	if (fromState == EPlayerState::HighJumping || fromState == EPlayerState::Jumping || fromState == EPlayerState::Kicking) {
		isKicked = data.Get<bool>(IS_KICKED);
	}
}

Data PlayerFalling::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerFalling::Update(Player& player, float deltaTime)
{
	if (player.GetVelocityY() < FALL_SPEED_VER_MAX)
	{
		player.AddVelocityY(GRAVITY * 2.5 * deltaTime);
	}
}

void PlayerFalling::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(-MOVING_HOR);
			player.SetDirection((EntityDirection)-1);
		}
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(MOVING_HOR);
			player.SetDirection((EntityDirection)1);
		}
	}

	//case KeyControls::Attack:
	//	isKicked = true;
	//	cap.SetState(State::Captain_Kicking);
	//	return;
}

void PlayerFalling::OnKeyDown(Player& player, BYTE code)
{
}

void PlayerFalling::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerFalling::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerFalling::GetState()
{
	return EPlayerState::Falling;
}

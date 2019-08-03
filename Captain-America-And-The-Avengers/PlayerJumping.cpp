#include "pch.h"
#include "PlayerJumping.h"
#include "Player.h"

void PlayerJumping::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	if (fromState != EPlayerState::Kicking) { JumpSpeed = JUMP_SPEED_VER_MAX; }

	if (fromState == EPlayerState::Kicking)
	{
		JumpHeightRealCounter = data.Get<float>(JUMP_HEIGHT_RealCounter);
		JumpHeightNeedCounter = data.Get<float>(JUMP_HEIGHT_NeedCounter);
		isJumpReleased = data.Get<bool>(IS_JUMP_RELEASED);
	}
	else {
		isKicked = false;
		isJumpReleased = false;
		JumpHeightRealCounter = 0;
		JumpHeightNeedCounter = MIN_JUMP_HEIGHT;
	}
}

Data PlayerJumping::Exit(Player& player, EPlayerState toState)
{
	data.Add(IS_JUMP_RELEASED, isJumpReleased);
	data.Add(JUMP_HEIGHT_RealCounter, JumpHeightRealCounter);
	data.Add(JUMP_HEIGHT_NeedCounter, JumpHeightNeedCounter);
	data.Add(IS_KICKED, isKicked);
	data.Add(SPIN_TIME_DOWN, 0.0f);
	data.Add(SPIN_TIME_UP, 0.0f);
	return std::move(data);
}

void PlayerJumping::Update(Player& player, float deltaTime)
{
	if (JumpHeightNeedCounter < MAX_JUMP_HEIGHT) {
		if (!isJumpReleased) {
			JumpHeightNeedCounter += (JumpSpeed - 30) * deltaTime;
			player.SetVelocityY(-JumpSpeed);
			JumpHeightRealCounter += JumpSpeed * deltaTime;
		}
		else {
			if (JumpHeightRealCounter < JumpHeightNeedCounter * 8.5f / 10.0f)
			{
				player.SetVelocityY(-JumpSpeed);
				JumpHeightRealCounter += JumpSpeed * deltaTime;
			}
			else if (JumpHeightRealCounter < JumpHeightNeedCounter * 14 / 15)
			{
				player.SetVelocityY(-JumpSpeed / 2);
				JumpHeightRealCounter += JumpSpeed / 2 * deltaTime;
			}
			else if (JumpHeightRealCounter < JumpHeightNeedCounter * 19 / 20)
			{
				player.SetVelocityY(-JumpSpeed / 3);
				JumpHeightRealCounter += JumpSpeed / 3 * deltaTime;
			}
			else if (JumpHeightRealCounter < JumpHeightNeedCounter) {
				player.SetVelocityY(-JumpSpeed / 4);
				JumpHeightRealCounter += JumpSpeed / 4 * deltaTime;
			}
			else
			{
				player.SetState(EPlayerState::Falling);
				return;
			}
		}
	}
	else {
		if (JumpHeightRealCounter < JumpHeightNeedCounter)
		{
			player.SetVelocityY(-JumpSpeed);
			JumpHeightRealCounter += JumpSpeed * deltaTime;
		}
		else
		{
			player.SetState(EPlayerState::HighJumping);
			return;
		}
	}
}

void PlayerJumping::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		player.SetDirection(EntityDirection::Left);
		player.SetVelocityX(-MOVING_HOR);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetDirection(EntityDirection::Right);
		player.SetVelocityX(MOVING_HOR);
	}
}

void PlayerJumping::OnKeyDown(Player& player, BYTE code)
{

}

void PlayerJumping::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
		isJumpReleased = true;
	else if (code == VK_RIGHT || code == VK_LEFT)
		player.SetVelocityX(.0f);
}

void PlayerJumping::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerJumping::GetState()
{
	return EPlayerState::Jumping;
}

#pragma once
#include "Keyboard.h"
#include "Timer.h"

class Entity;
class Player;
struct CollisionEvent;

enum EPlayerState {
	Standing,
	Running,
	Jumping,
	HighJumping,
	Falling,
	Sitting,
	HighShielding,
	Punching,
	ThrowingShield,
	LowPunching,
	Kicking,
	TakeDamage,
	TakeDown,
	InvincibleStand,
	Surfing,
	SittingOnShield,
	Swimming,
	Cling,
	Diving
};

class PlayerState
{
public:
	PlayerState();

	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) = 0;
	virtual Data Exit(Player& player, EPlayerState toState) = 0;
	virtual void Update(Player& player, float deltaTime) = 0;

	virtual EPlayerState GetState();
	virtual void HandleKeyboard(Player& player, Keyboard* keyboard) = 0;

	virtual void OnKeyDown(Player& player, BYTE code) = 0;
	virtual void OnKeyUp(Player& player, BYTE code) = 0;

	virtual void OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent) = 0;
protected:
	Data data;

	static constexpr BYTE VK_KEY_JUMP = 0x58;
	static constexpr BYTE VK_KEY_ATTACK = 0x5A;

	static constexpr auto IS_JUMP_RELEASED = "is-jump-released";
	static constexpr auto IS_KICKED = "is-jump-kicked-once-at-jumping-and-falling";
	static constexpr auto JUMP_HEIGHT_RealCounter = "JumpHeightRealCounter";
	static constexpr auto JUMP_HEIGHT_NeedCounter = "JumpHeightNeedCounter";
	static constexpr auto IS_TO_SIT_TACKLE = "is-to-sit-tackle";
	static constexpr auto SPIN_TIME_UP = "spin-up-time-counter";
	static constexpr auto SPIN_TIME_DOWN = "spin-down-time-counter";

	static constexpr auto MOVING_HOR = 60.0f;
	static constexpr auto JUMP_SPEED_VER = 180.0f;
	static constexpr auto JUMP_SPEED_VER_MAX = 210.0f;
	static constexpr auto JUMP_SPEED_VER_MIN = 120.0f;

	static constexpr auto GRAVITY = 550.0f;
	static constexpr auto JUMP_SPEED_HOR = MOVING_HOR;

	static constexpr auto MAX_JUMP_HEIGHT = 83.0f;
	static constexpr auto MIN_JUMP_HEIGHT = 35.0f;

	static constexpr auto FALL_SPEED_VER = 190.0f;
	static constexpr auto FALL_SPEED_VER_MAX = 210.0f;
	static constexpr auto FALL_SPEED_VER_MIN = 20.0f;
	static constexpr auto FALL_SPEED_HOR = MOVING_HOR;

	static constexpr auto SPIN_SPEED_VER = 120.0f;
	static constexpr auto SPIN_SPEED_HOR = JUMP_SPEED_HOR;
	static constexpr auto TIME_KEEP_SPIN = 0.16f;

	static constexpr auto FALL_LANDING_TIME = 0.1f;

	static constexpr float WATER_FLOW_SPEED = -20.0f;
	static constexpr float SWIMMING_SPEED = 50.0f;
	static constexpr float MAX_JUMP_TIME_FROM_WATER = 0.3f;
};
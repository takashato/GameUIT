#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
    PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    float acceleratorY;
    float acceleratorX;
    bool noPressed;
    bool allowMoveRight, allowMoveLeft;
};


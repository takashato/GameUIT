#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float dt)
{

}

void PlayerState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
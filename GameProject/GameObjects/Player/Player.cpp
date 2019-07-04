#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "../../GameComponents/GameCollision.h"

Player::Player()
{
    mAnimationStanding = new Animation("Resources/mario/standingright.png", 1, 1, 1, 0);
    mAnimationJumping = new Animation("Resources/mario/jumpingright.png", 1, 1, 1, 0);
    mAnimationRunning = new Animation("Resources/mario/runningright.png", 2, 1, 2, 0.15f);

    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerFallingState(this->mPlayerData));

    allowJump = true;
}

Player::~Player()
{
}

void Player::Update(float dt)
{    
    mCurrentAnimation->Update(dt);

    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->Update(dt);
    }

    Entity::Update(dt);
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->HandleKeyboard(keys);
    }
}

void Player::OnKeyPressed(int key)
{
    if (key == VK_SPACE)
    {
        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }

            allowJump = false;
        }
    }
}

void Player::OnKeyUp(int key)
{
    if (key == VK_SPACE)
        allowJump = true;
}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
    this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

    if (mCamera)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
    }
    else
    {
        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
    }        
}

void Player::SetState(PlayerState *newState)
{
    allowMoveLeft = true;
    allowMoveRight = true;

    delete this->mPlayerData->state;

    this->mPlayerData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    this->mPlayerData->state->OnCollision(impactor, side, data);
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
        case PlayerState::Running:
            mCurrentAnimation = mAnimationRunning;
            break;

        case PlayerState::Standing:
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
            break;

        case PlayerState::Jumping:
            mCurrentAnimation = mAnimationJumping;
            break;

        default:
            break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

void Player::OnNoCollisionWithBottom()
{
    if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling)
    {
        this->SetState(new PlayerFallingState(this->mPlayerData));
    }    
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}
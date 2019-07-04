#include "Brick.h"
#include "../../GameComponents/GameGlobal.h"


Brick::Brick()
{
    
}

Brick::~Brick()
{

}

bool Brick::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Brick::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void Brick::Update(float dt)
{
    mAnimation->Update(dt);
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Brick::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(D3DXVECTOR2(transform));
}

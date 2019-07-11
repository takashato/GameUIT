#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw()
{
}

D3DXVECTOR3 Entity::GetPosition()
{
	return mPosition;
}

void Entity::SetPosition(D3DXVECTOR3 position)
{
	mPosition = position;
	OnSetPosition();
}

void Entity::AddPosition(D3DXVECTOR2 vector)
{
	SetPosition(mPosition + D3DXVECTOR3(vector.x, vector.y, 0.0F));
}

D3DXVECTOR2 Entity::GetVelocity()
{
	return mVelocity;
}

void Entity::SetVelocity(D3DXVECTOR2 velocity)
{
	mVelocity = velocity;
}

void Entity::AddVelocity(D3DXVECTOR2 deltaVelocity)
{
	mVelocity += deltaVelocity;
}

int Entity::GetWidth()
{
	return mWidth;
}

void Entity::SetWidth(int width)
{
	mWidth = width;
}

int Entity::GetHeight()
{
	return mHeight;
}

void Entity::SetHeight(int height)
{
	mHeight = height;
}

void Entity::OnSetPosition()
{

}


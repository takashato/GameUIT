#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	mDirection = Left;
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

float Entity::GetVelocityX()
{
	return mVelocityX;
}

float Entity::GetVelocityY()
{
	return mVelocityY;
}

void Entity::SetVelocityX(float velocity)
{
	mVelocityX = velocity;
}

void Entity::SetVelocityY(float velocity)
{
	mVelocityY = velocity;
}

void Entity::AddVelocityX(float deltaVelocity)
{
	mVelocityX += deltaVelocity;
}

void Entity::AddVelocityY(float deltaVelocity)
{
	mVelocityY += deltaVelocity;
}

float Entity::GetWidth()
{
	return mWidth;
}

void Entity::SetWidth(float width)
{
	mWidth = width;
}

float Entity::GetHeight()
{
	return mHeight;
}

void Entity::SetHeight(float height)
{
	mHeight = height;
}

EntityDirection Entity::GetDirection()
{
	return mDirection;
}

void Entity::SetDirection(EntityDirection direction)
{
	mDirection = direction;
}

void Entity::OnSetPosition()
{

}


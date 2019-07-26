#pragma once
#include"Sprite.h"

enum EntityDirection
{
	Left,
	Right
};

enum CollidableType
{
	EPlayer,
	EEnemy,
	EPlatform,
	EDefault
};

class Entity 
{
public:
	Entity();
	~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 position);
	void SetPositionX(float value);
	void SetPositionY(float value);
	void AddPosition(D3DXVECTOR2 vector);
	void AddPositionX(float value);
	void AddPositionY(float value);

	float GetVelocityX();
	float GetVelocityY();
	void SetVelocityX(float velocity);
	void SetVelocityY(float velocity);
	void AddVelocityX(float deltaVelocity);
	void AddVelocityY(float deltaVelocity);

	float GetWidth();
	void SetWidth(float width);
	float GetHeight();
	void SetHeight(float height);

	EntityDirection GetDirection();
	void SetDirection(EntityDirection direction);

	virtual void OnSetPosition();
	
	//Get box de xu li va cham 
	virtual RECT GetBoundingBox() = 0;
	virtual CollidableType GetCollidableType();

	void RenderBoundingBox(D3DXVECTOR2 transform);


protected:
	D3DXVECTOR3 mPosition; // Position (x, y)
	float mWidth, mHeight; // Size
	float mVelocityX, mVelocityY;
	EntityDirection mDirection;

	static Sprite* mSpriteBB;
};
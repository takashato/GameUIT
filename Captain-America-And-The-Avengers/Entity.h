#pragma once

enum EntityDirection
{
	Left,
	Right
};

class Entity 
{
public:
	Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 position);
	void AddPosition(D3DXVECTOR2 vector);

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
protected:
	D3DXVECTOR3 mPosition; // Position (x, y)
	float mWidth, mHeight; // Size
	float mVelocityX, mVelocityY;
	EntityDirection mDirection;
};
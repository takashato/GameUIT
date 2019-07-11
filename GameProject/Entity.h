#pragma once
class Entity 
{
public:
	Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 position);
	void AddPosition(D3DXVECTOR2 vector);

	D3DXVECTOR2 GetVelocity();
	void SetVelocity(D3DXVECTOR2 velocity);
	void AddVelocity(D3DXVECTOR2 deltaVelocity);

	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);

	virtual void OnSetPosition();
protected:
	D3DXVECTOR3 mPosition; // Position (x, y)
	int mWidth, mHeight; // Size
	D3DXVECTOR2 mVelocity; // Velocity (Vx, Vy)
};
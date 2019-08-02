#pragma once

class Camera
{
public:
	Camera(int width, int height);

	void Update(D3DXVECTOR3 position);

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 position);
	void SetPositionX(float val);
	void SetPositionY(float val);
	void AddPositionX(float val);
	void AddPositionY(float val);

	int GetWidth();
	int GetHeight();

	void SetLock(bool lock);

	void SetWorldBoundary(RECT boundary);

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	D3DXVECTOR2 GetTransform();

	~Camera();

private:
	int mWidth, mHeight;
	D3DXVECTOR3 mPosition;

	RECT mWorldBoundary;
	bool mIsLocked = false;
};
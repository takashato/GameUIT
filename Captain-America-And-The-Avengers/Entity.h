#pragma once
#include "CollisionEvent.h"
#include "Sprite.h"
#include "ExtraDrawer.h"

class GridNode;

enum EntityDirection
{
	Left = -1,
	Right = 1
}; 

enum CollidableObjectType
{
	EPlayer,
	EEnemy,
	EWeapon,
	EPlatform,
	EDefault,
	EBullet
};

class Entity 
{
public:
	Entity();
	~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw(D3DXVECTOR2 trans = D3DXVECTOR2(.0f, .0f));

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
	
	virtual RECT GetBoundingBox() = 0;
	virtual CollidableObjectType GetCollidableObjectType() = 0;

	D3DXVECTOR3 GetCenterPoint();

	CollisionEvent* SweptAABBEx(Entity* other);
	void CalcCollision(std::set<Entity*> *entities, std::vector<CollisionEvent*>& cEvent);

	virtual void OnCollision(std::vector<CollisionEvent*>& cEvent);

	void RenderBoundingBox(D3DXVECTOR2 transform);

	void SetGridNode(GridNode* gridNode);
	GridNode* GetGridNode();

	static bool shouldRenderBoundingBox;

protected:
	D3DXVECTOR3 mPosition; // Position (x, y)
	float mWidth, mHeight; // Size
	float mVelocityX, mVelocityY;
	EntityDirection mDirection;
	
	float deltaTime;

	GridNode* mGridNode;

	static Sprite* mSpriteBB;
};
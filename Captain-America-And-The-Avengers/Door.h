#pragma once
#include "Entity.h"

class Door : public Entity
{
public:
	Door(D3DXVECTOR3 position, std::string name = "default");
	~Door();
	void Draw(D3DXVECTOR2 trans);
	virtual RECT GetBoundingBox() override;
	virtual CollidableObjectType GetCollidableObjectType() override;
	
	std::string doorName;
};
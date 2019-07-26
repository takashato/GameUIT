#pragma once
#include "Entity.h"

class GridNode
{
public:
	GridNode();

	void Add(Entity* collidable);
	void Remove(Entity* entity);

	std::list<Entity*> GetAll();

private:
	std::list<Entity*> mList;
};
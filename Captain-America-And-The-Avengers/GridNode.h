#pragma once
#include "Entity.h"

class GridNode
{
public:
	GridNode();
	~GridNode();

	void Add(Entity* collidable);
	void Remove(Entity* entity);

	bool Has(Entity* entity);

	std::list<Entity*> GetAll();

private:
	std::list<Entity*> mList;
};
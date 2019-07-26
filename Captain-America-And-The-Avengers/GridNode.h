#pragma once
#include "Collidable.h"

class GridNode
{
public:
	GridNode();

	void Add(Collidable* collidable);
	void Remove(Collidable* collidable);

	std::list<Collidable*> GetAll();

private:
	std::list<Collidable*> mList;
};
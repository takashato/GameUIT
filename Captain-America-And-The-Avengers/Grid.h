#pragma once
#include "Entity.h"
#include "Camera.h"
#include "GridNode.h"

class Grid
{
public:
	static Grid* instance;

	Grid(int colNum, int rowNum, int cellSize);
	~Grid();
	
	void InitNodes();
	GridNode* GetNode(int col, int row);

	void Add(Entity* entity);
	void Move(Entity* entity);

	std::vector<GridNode*> GetByViewPort(Camera* camera);
	
	void GetEntities(Camera* camera, std::vector<Entity*> &entities);

private:
	int mColNum, mRowNum;
	int mCellSize;

	GridNode*** mCells = NULL;
};
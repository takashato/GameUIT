#pragma once
#include "Entity.h"
#include "Camera.h"
#include "GridNode.h"

class Grid
{
public:
	Grid(int colNum, int rowNum, int cellSize);
	~Grid();
	
	void InitNodes();
	GridNode* GetNode(int col, int row);

	void Add(Entity* entity);
	void Move(Entity* entity, D3DXVECTOR3 oldPosition);

	std::vector<GridNode*> GetByViewPort(Camera* camera);

private:
	int mColNum, mRowNum;
	int mCellSize;

	GridNode*** mCells = NULL;
};
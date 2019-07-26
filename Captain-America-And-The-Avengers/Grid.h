#pragma once
#include "Camera.h"
#include "GridNode.h"
#include "Collidable.h"

class Grid
{
public:
	Grid(int colNum, int rowNum, int cellSize);
	~Grid();
	
	void InitNodes();
	GridNode* GetNode(int col, int row);

	void Add(Collidable* collidable);
	void Move(Collidable* collidable, D3DXVECTOR3 oldPosition);

	std::vector<GridNode*> GetByViewPort(Camera* camera);

private:
	int mColNum, mRowNum;
	int mCellSize;

	GridNode*** mCells = NULL;
};
#pragma once
#include "Entity.h"
#include "GridNode.h"

class Player;

class Grid
{
public:
	static Grid* instance;

	Grid(int totalWidth, int totalHeight);
	Grid(int colNum, int rowNum, int cellSize);
	~Grid();
	
	void Update(float deltaTime, RECT rect, Player* player);
	void Draw(D3DXVECTOR2 trans);

	void InitNodes();
	GridNode* GetNode(int col, int row);

	void Add(Entity* entity);
	void Move(Entity* entity);

	std::vector<GridNode*> GetByViewPort(RECT bound);
	
	void GetEntities(RECT rect, std::set<Entity*> &entities);

	std::set<Entity*> mTemp;

private:
	int mColNum, mRowNum;
	int mCellSize;

	GridNode*** mCells = NULL;
};
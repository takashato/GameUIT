#pragma once
#include "./MapReader/tinyxml2.h"
#include "Grid.h"
#include "Ground.h"

class MapObjectReader
{
public:
	static void LoadFromFile(const char* filePath, Grid* grid);
};
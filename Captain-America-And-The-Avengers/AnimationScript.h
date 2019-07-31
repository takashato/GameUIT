#pragma once
#include "./MapReader/tinyxml2.h"
#include <Windows.h>
#include <vector>

class AnimationScript
{
public:
	AnimationScript(const char* filePath);

	std::vector<RECT> GetRectList(const char* animationName, const char* type);

private:
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLElement* pRoot = NULL;

	std::vector<RECT> GetSpriteRects(tinyxml2::XMLElement* ele);
};
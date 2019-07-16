#pragma once
#include "Keyboard.h"

class Scene {
public:
	Scene();

	virtual void Setup();
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
};
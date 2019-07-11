#pragma once
#include "Keyboard.h"

class Scene {
public:
	Scene();

	virtual void Setup();
	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void OnKeyDown(BYTE keyCode);
	virtual void OnKeyUp(BYTE keyCode);

	Keyboard& GetKeyboard();

protected:
	Keyboard mKeyboard;
};
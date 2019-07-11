#pragma once
#include "Scene.h"
#include "Animation.h"

class SceneDemo : public Scene
{
public:
	SceneDemo();
	
	void Setup();

	void Update(float deltaTime);
	void Draw();

	void OnKeyUp(BYTE keyCode);
	void OnKeyDown(BYTE keyCode);

protected:
	Animation* aladdin;
};
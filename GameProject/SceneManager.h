#pragma once
class SceneManager : ISingleton
{
public:
	static SceneManager& GetInstance();

private:
	SceneManager() : ISingleton(NULL) {}

};
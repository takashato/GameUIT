#pragma once
class Game : ISingleton {
private:
	void InitDevice();
	void Render();

public:
	~Game();
};
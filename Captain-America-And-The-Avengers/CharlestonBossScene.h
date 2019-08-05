#pragma once
#include "Scene.h"

class CharlestonBossScene : public Scene
{
public:
	CharlestonBossScene();
	~CharlestonBossScene();

	virtual void Setup() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual SoundType GetBgMusic() override;
	virtual void OnKeyUp(BYTE key) override;
	virtual void OnKeyDown(BYTE key) override;
	virtual MapID GetMapID() override;

private:
	std::unique_ptr<Player> mPlayer;


};
#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Map.h"

class GameScene {

public:

	~GameScene();
	void Initialize();
	void Update();
	void Draw();

private:

	KamataEngine::Camera* camera_ = nullptr;
	Player player_;
	Map map_;
};
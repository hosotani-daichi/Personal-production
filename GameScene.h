#pragma once
#include "KamataEngine.h"
#include "Player.h"

class GameScene {

public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

private:

	Model* model_ = nullptr;
};
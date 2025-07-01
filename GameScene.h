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
	//自キャラ
	Player* player_ = nullptr;
	Model* model_ = nullptr;
};
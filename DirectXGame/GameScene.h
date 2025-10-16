#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Player.h"
#include "Sphere.h"

// シーンの種類
enum class SceneState {
	Title,
	Game,
	Clear,
};

class GameScene {

public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* Spheremodel_ = nullptr;
	Player player_;
	Fade fade_;
	Sphere sphere_;

	// シーン管理
	SceneState sceneState_ = SceneState::Title; // 現在のシーン
	SceneState nextScene_ = SceneState::Title;  // フェード後に移行するシーン
};
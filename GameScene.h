#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Player.h"

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
	Player player_;

	// シーン管理
	SceneState sceneState_ = SceneState::Title; // 現在のシーン
	SceneState nextScene_ = SceneState::Title;  // フェード後に移行するシーン

	// フェード管理
	Fade fade_;
};
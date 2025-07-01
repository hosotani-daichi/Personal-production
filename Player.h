#include "KamataEngine.h"
#pragma once

class Player {

public:
	void Initialize(Model* model, Camera* camera);
	void Update();
	void Draw();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// ビュープロジェクション
	KamataEngine::Camera* camera_;
};

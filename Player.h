#pragma once
#include "KamataEngine.h"

class Player {
public:

	void Initialize();
	void Update();
	void Draw(const KamataEngine::Camera& camera);

private:

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	float velocityY_ = 0.0f;
	bool isJumping_ = false;
	float targetAngleY_ = 90.0f; // ← 初期は右向き
};
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
};
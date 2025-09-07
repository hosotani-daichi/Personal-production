#pragma once
#include "KamataEngine.h"

enum class FadeState {

	None,
	IrisIn,
	IrisOut,
};

class Fade {

public:
	void Initialize();
	void Start(FadeState state);
	void Update();
	void Draw();

	bool IsFinished() const;
	void ResetFinished();

private:
	// 内部描画用
	void DrawIris(float cx, float cy, float r, float screenW, float screenH);

private:
	FadeState state_ = FadeState::None;
	float radius_ = 0.0f;
	float maxRadius_ = 0.0f;
	float speed_ = 0.0f;
	bool finished_ = false;

	uint32_t blackTex_ = 0;
};

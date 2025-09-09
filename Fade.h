#pragma once
#include "KamataEngine.h"

enum class FadeState {
	None,
	FadeIn,
	FadeOut,
};

class Fade {
public:
	void Initialize();
	void Update();
	void Draw();

	void Start(FadeState state); // フェード開始
	bool IsFinished() const { return finished_; }

	FadeState GetState() const { return state_; }

private:
	FadeState state_ = FadeState::None;
	float alpha_ = 0.0f;
	float speed_ = 0.02f;
	bool finished_ = true;

	KamataEngine::Sprite* blackSprite_ = nullptr;
};

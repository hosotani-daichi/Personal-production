#include "Fade.h"

using namespace KamataEngine;

void Fade::Initialize() {
	uint32_t tex = TextureManager::Load("Fade/black.png");
	blackSprite_ = Sprite::Create(tex, {0, 0});
	blackSprite_->SetSize({1280, 720});
	alpha_ = 1.0f; // 最初は真っ黒から始めてもOK
	state_ = FadeState::None;
	finished_ = true;
}

void Fade::Start(FadeState state) {
	state_ = state;
	finished_ = false;

	if (state == FadeState::FadeIn) {
		alpha_ = 1.0f; // 黒から透明へ
	} else if (state == FadeState::FadeOut) {
		alpha_ = 0.0f; // 透明から黒へ
	}
}

void Fade::Update() {
	if (finished_)
		return;

	switch (state_) {
	case FadeState::FadeIn:
		alpha_ -= speed_;
		if (alpha_ <= 0.0f) {
			alpha_ = 0.0f;
			state_ = FadeState::None;
			finished_ = true;
		}
		break;

	case FadeState::FadeOut:
		alpha_ += speed_;
		if (alpha_ >= 1.0f) {
			alpha_ = 1.0f;
			state_ = FadeState::None;
			finished_ = true;
		}
		break;

	default:
		break;
	}
}

void Fade::Draw() {
	if (state_ == FadeState::None && finished_)
		return;

	blackSprite_->SetColor({1.0f, 1.0f, 1.0f, alpha_});
	blackSprite_->Draw();
}

#define NOMINMAX
#include <windows.h>
#include "Fade.h"

using namespace KamataEngine;

void Fade::Initialize() {
	state_ = FadeState::None;
	radius_ = 0.0f;

	// 画面サイズを取得（仮に1280x720固定ならここは固定値でもOK）
	float screenW = 1280.0f;
	float screenH = 720.0f;
	maxRadius_ = sqrtf(screenW * screenW + screenH * screenH) * 0.5f; // 対角線の半分
	speed_ = 20.0f;
	finished_ = false;

	// 1x1 黒テクスチャをロード
	blackTex_ = TextureManager::Load("Fade/black.png");
}

void Fade::Start(FadeState state) {
	state_ = state;
	finished_ = false;

	if (state == FadeState::IrisIn) {
		radius_ = 0.0f; // 中心から外へ広がる（黒が消える）
	} else if (state == FadeState::IrisOut) {
		radius_ = maxRadius_; // 黒が画面外に広がった状態
	}
}

void Fade::Update() {
	if (state_ == FadeState::IrisIn) {
		radius_ += speed_;
		if (radius_ >= maxRadius_) {
			radius_ = maxRadius_;
			state_ = FadeState::None;
			finished_ = true;
		}
	} else if (state_ == FadeState::IrisOut) {
		radius_ -= speed_;
		if (radius_ <= 0.0f) {
			radius_ = 0.0f;
			state_ = FadeState::None;
			finished_ = true;
		}
	}
}

void Fade::Draw() {
	if (state_ == FadeState::None)
		return;

	float screenW = 1280.0f;
	float screenH = 720.0f;
	float centerX = screenW / 2.0f;
	float centerY = screenH / 2.0f;

	if (state_ == FadeState::IrisIn) {
		// 中心から黒が消えていく（従来と同じ）
		DrawIris(centerX, centerY, radius_, screenW, screenH);
	} else if (state_ == FadeState::IrisOut) {
		// 外側から中心に黒が閉じる → radius_ を反転して描画
		DrawIris(centerX, centerY, maxRadius_ - radius_, screenW, screenH);
	}
}

void Fade::DrawIris(float cx, float cy, float r, float w, float h) {
	float radius = r;

	// 上
	float topH = std::max(cy - radius, 0.0f);
	if (topH > 0)
		Sprite::Create(blackTex_, {0, 0}, {w, topH})->Draw();

	// 下
	float bottomY = cy + radius;
	float bottomH = std::max(h - bottomY, 0.0f);
	if (bottomH > 0)
		Sprite::Create(blackTex_, {0, bottomY}, {w, bottomH})->Draw();

	// 左（高さは画面全体）
	float leftW = std::max(cx - radius, 0.0f);
	if (leftW > 0)
		Sprite::Create(blackTex_, {0, 0}, {leftW, h})->Draw();

	// 右（高さは画面全体）
	float rightX = cx + radius;
	float rightW = std::max(w - rightX, 0.0f);
	if (rightW > 0)
		Sprite::Create(blackTex_, {rightX, 0}, {rightW, h})->Draw();
}

bool Fade::IsFinished() const { return finished_; }
void Fade::ResetFinished() { finished_ = false; }

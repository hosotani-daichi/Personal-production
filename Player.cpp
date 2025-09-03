#include "Player.h"
#include "Map.h"
#include "input/Input.h"
#include <DirectXMath.h>

using namespace KamataEngine;
using namespace DirectX;

void Player::Initialize() {

	model_ = Model::CreateFromOBJ("player");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -5.0f, -30.0f};

	// Y軸を +90度回転して右向きにする
	worldTransform_.rotation_.y = XMConvertToRadians(90.0f);
}

void Player::Update(Map& map) {

	Input* input = Input::GetInstance();

	const float speed = 0.1f;         // キャラのスピード
	const float gravity = 0.015f;     // 重力加速度
	//const float groundY = -5.0f;      // 地面Y座標
	const float rotationSpeed = 0.1f; // 補間係数（滑らかさ）

	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= speed;
		targetAngleY_ = -90.0f; // 左向き
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x += speed;
		targetAngleY_ = 90.0f; // 右向き
	}

	// 現在の角度（度）
	float currentAngle = XMConvertToDegrees(worldTransform_.rotation_.y);

	// 差分（度）
	float delta = targetAngleY_ - currentAngle;

	// 最初の方向転換かどうかを判定するフラグ
	bool firstTurnDone_ = false;

	// 正規化（-180° ～ 180°に収める）
	if (delta > 180.0f) {
		delta -= 360.0f;
	} else if (delta < -180.0f) {
		delta += 360.0f;
	}

	// 左(-90) → 右(90) は必ず反時計回り
	if (currentAngle > -135.0f && currentAngle < -45.0f && targetAngleY_ == 90.0f) {
		delta = -270.0f;
	}

	// 最初の右(90) → 左(-90) だけは時計回り
	if (!firstTurnDone_ && currentAngle > 45.0f && currentAngle < 135.0f && targetAngleY_ == -90.0f) {
		delta = +270.0f;       // 時計回り
		firstTurnDone_ = true; // 以降は通常処理
	}

	// 新しい角度を計算
	float newAngle = currentAngle + delta * rotationSpeed;

	// ラジアンにして反映
	worldTransform_.rotation_.y = XMConvertToRadians(newAngle);

	bool spaceNow = input->PushKey(DIK_SPACE);
	bool spaceTriggered = input->TriggerKey(DIK_SPACE);
	bool spaceReleased = prevSpace_ && !spaceNow;

	// ジャンプ開始
	if (spaceTriggered && jumpCount_ < maxJumpCount_) {
		velocityY_ = 0.3f;
		isJumping_ = true;
		isHoldingJump_ = true;
		holdTimer_ = 0.0f;
		jumpCount_++;
	}

	// ジャンプホールド
	if (isHoldingJump_ && spaceNow) {
		holdTimer_ += 1.0f / 60.0f; // 60FPS想定
		if (holdTimer_ < maxHoldTime_) {
			velocityY_ += holdJumpBoost_;
		} else {
			isHoldingJump_ = false;
		}
	}

	// 離したらホールド終了
	if (spaceReleased) {
		isHoldingJump_ = false;
	}

// --- 縦方向の移動 ---
	velocityY_ -= gravity; // 重力
	float nextY = worldTransform_.translation_.y + velocityY_;

	// 移動先がブロックかどうか調べる
	if (map.IsBlockAt(worldTransform_.translation_.x, nextY)) {
		// 下に着地した場合
		if (velocityY_ < 0) {
			nextY = static_cast<float>((int)(nextY / map.GetTileSize())) * map.GetTileSize();
			velocityY_ = 0;
			isJumping_ = false;
			jumpCount_ = 0;
		} else {
			// 上にぶつかった（天井）
			velocityY_ = 0;
		}
	}

	worldTransform_.translation_.y = nextY;


	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}
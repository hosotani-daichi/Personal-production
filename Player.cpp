#include "Player.h"
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

void Player::Update() {

	Input* input = Input::GetInstance();

	const float speed = 0.1f;         // キャラのスピード
	const float gravity = 0.015f;     // 重力加速度
	const float jumpPower = 0.3f;     // ジャンプの初速度
	const float groundY = -5.0f;      // 地面Y座標
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

	//最初の方向転換かどうかを判定するフラグ
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

	// ジャンプ入力（スペースキー）
	if (input->TriggerKey(DIK_SPACE) && jumpCount_ < maxJumpCount_) {
		velocityY_ = jumpPower;
		isJumping_ = true;
		jumpCount_++; // ジャンプ回数を加算
	}

	// 重力・落下処理
	if (isJumping_) {
		velocityY_ -= gravity;
		worldTransform_.translation_.y += velocityY_;

		// 着地判定
		if (worldTransform_.translation_.y <= groundY) {
			worldTransform_.translation_.y = groundY;
			isJumping_ = false;
			velocityY_ = 0.0f;
			jumpCount_ = 0; // 着地したらジャンプ回数リセット
		}
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}
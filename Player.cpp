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

	const float speed = 0.1f;
	const float gravity = 0.01f;      // 重力加速度
	const float jumpPower = 0.3f;     // ジャンプの初速度
	const float groundY = -5.0f;      // 地面Y座標
	const float rotationSpeed = 0.1f; // ← 補間速度（小さいほどゆっくり）

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

	// 差分
	float delta = targetAngleY_ - currentAngle;

	// ここで補正：常に +方向に（時計回り）回るように補正
	if (delta < 0) {
		delta += 360.0f;
	}

	// 補間
	float newAngle = currentAngle + delta * rotationSpeed;

	// 0～360度に正規化
	if (newAngle >= 360.0f)
		newAngle -= 360.0f;

	// ラジアンに変換してセット
	worldTransform_.rotation_.y = XMConvertToRadians(newAngle);

	// ジャンプ入力（スペースキー）
	if (!isJumping_ && input->TriggerKey(DIK_SPACE)) {
		velocityY_ = jumpPower;
		isJumping_ = true;
	}

	// 重力の適用a
	if (isJumping_) {
		velocityY_ -= gravity;
		worldTransform_.translation_.y += velocityY_;

		// 仮の着地判定（Y=0で着地）
		if (worldTransform_.translation_.y <= groundY) {
			worldTransform_.translation_.y = groundY;
			isJumping_ = false;
			velocityY_ = 0.0f;
		}
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}
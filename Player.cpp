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

	const float speed = 2.0f;
	const float gravity = 0.015f;     // 重力加速度
	const float jumpPower = 0.3f;     // ジャンプの初速度
	const float groundY = -5.0f;      // 地面Y座標
	const float rotationSpeed = 0.1f; // 補間係数（滑らかさ）

	float nextX = worldTransform_.translation_.x;
	float nextY = worldTransform_.translation_.y;

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

	// ここで補正：常に +方向に（時計回り）回るように補正
	if (delta < 0) {
		delta += 360.0f;
	}

	// 新しい角度を計算
	float newAngle = currentAngle + delta * rotationSpeed;

	// 強制的に反時計回り（左回り）になるように補正
	if (newAngle >= 360.0f) {
		newAngle -= 360.0f; // 反時計回りで回るように補正
	}

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

	// マップの当たり判定
	if (map_) {
		// 足元判定（32ピクセルのタイルを前提）
		float footX = nextX;
		float footY = nextY - 1; // 足元

		if (map_->IsBlockAtPixel(footX, footY)) {
			// 足元がブロック → 着地
			isJumping_ = false;
			velocityY_ = 0.0f;
			jumpCount_ = 0;

			// タイル境界に揃える
			float tileSize = 32.0f;
			nextY = ((int)(footY / tileSize) + 1) * tileSize;
		}

		// 横移動の衝突
		float headY = nextY + 16; // プレイヤーの頭位置（キャラサイズ次第で調整）
		if (map_->IsBlockAtPixel(nextX, nextY) || map_->IsBlockAtPixel(nextX, headY)) {
			// 衝突したらX移動キャンセル
			nextX = worldTransform_.translation_.x;
		}

		// 位置更新
		worldTransform_.translation_.x = nextX;
		worldTransform_.translation_.y = nextY;
		worldTransform_.UpdateMatrix();
	}
}


void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}
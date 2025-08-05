#include "Player.h"
#include "input/Input.h"
#include <DirectXMath.h>

using namespace KamataEngine;
using namespace DirectX;

void Player::Initialize() {

	model_ = Model::CreateFromOBJ("player");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, -40.0f};

	// Y軸を +90度回転して右向きにする
	worldTransform_.rotation_.y = XMConvertToRadians(90.0f);
}

void Player::Update() {

	Input* input = Input::GetInstance();

	const float speed = 0.1f;

	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= speed;
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x += speed;
	}
	if (input->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= speed;
	}
	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.y += speed;
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}
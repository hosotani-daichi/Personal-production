#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {

	//NULLポインタをチェック
	assert(model);
	// 引数の内容をメンバ変数に記録
	model_ = model;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {}

void Player::Draw() {}

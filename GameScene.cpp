#include "GameScene.h"
#include <cmath>

using namespace KamataEngine;

GameScene::~GameScene() {

	delete camera_;
	camera_ = nullptr;
}

void GameScene::Initialize() {

	Model::StaticInitialize();
	// プレイヤーの初期化
	player_.Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	map_.Initialize("./Resources/Map/map.csv", TextureManager::Load("./Resources/tileset.png"), 32);

	player_.SetMap(&map_);
}

void GameScene::Update() { player_.Update(); }

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	player_.Draw(*camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する
	map_.Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}
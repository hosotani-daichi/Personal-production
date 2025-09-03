#include "GameScene.h"
#include "Map.h"
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

	// マップ初期化
	map_.Initialize(2);                      // 1タイル=2ユニット
	map_.LoadFromCSV("resources/Map/map.csv"); // CSV読み込み

}

void GameScene::Update() { player_.Update(map_); }

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	Sprite::PreDraw();


	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	player_.Draw(*camera_);
	map_.Draw(*camera_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ここに2Dスプライトの描画処理を記述する

	// スプライト描画後処理
	Sprite::PostDraw();
}
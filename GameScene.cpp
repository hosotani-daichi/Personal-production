#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {

	//自キャラの解放
	delete player_;
}

void GameScene::Initialize() {

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize();
}

void GameScene::Update() {

	//自キャラの更新
	player_->Update();
}

void GameScene::Draw() {

	//自キャラの描画
	player_->Draw();
}
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

	sceneState_ = SceneState::Title;
	fade_.Initialize();
	fade_.Start(FadeState::IrisIn); // タイトルはフェードインで開始
}

void GameScene::Update() {

	Input* input = Input::GetInstance();

	fade_.Update();

	switch (sceneState_) {

	case SceneState::Title:

		if (input->TriggerKey(DIK_RETURN)) {
			fade_.Start(FadeState::IrisOut);
			nextScene_ = SceneState::Play;
		}
		break;

	case SceneState::Play:

		player_.Update();
		if (input->TriggerKey(DIK_RETURN)) {
			fade_.Start(FadeState::IrisOut);
			nextScene_ = SceneState::Clear;
		}
		break;

	case SceneState::Clear:

		if (input->TriggerKey(DIK_RETURN)) {
			fade_.Start(FadeState::IrisOut);
			nextScene_ = SceneState::Title;
		}
		break;
	}

	// フェードアウトが終わったら次のシーンに移行
	if (fade_.IsFinished()) {
		sceneState_ = nextScene_;
		fade_.Start(FadeState::IrisIn); // 新シーンをフェードイン
		fade_.ResetFinished();
	}
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dスプライト（UIなど）描画
	Sprite::PreDraw(dxCommon->GetCommandList());

	switch (sceneState_) {
	case SceneState::Title:
		// titleSprite->Draw();
		break;
	case SceneState::Play:
		break;
	case SceneState::Clear:
		// clearSprite->Draw();
		break;
	}

	// フェードは最前面に描画
	fade_.Draw();

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画
	Model::PreDraw();
	if (sceneState_ == SceneState::Play) {
		player_.Draw(*camera_);
	}
	Model::PostDraw();
}

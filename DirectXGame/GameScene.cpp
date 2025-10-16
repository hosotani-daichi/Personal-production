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

	// 天球の3Dモデルの生成
	Spheremodel_ = Model::CreateFromOBJ("Sphere");

	camera_ = new Camera();
	camera_->Initialize();

	// 天球の初期化
	sphere_.Initialize(Spheremodel_, camera_);

	sceneState_ = SceneState::Title;
	fade_.Initialize();
	fade_.Start(FadeState::FadeIn); // タイトルはフェードインで開始
}

void GameScene::Update() {
	fade_.Update();

	// フェード中は入力を受け付けない
	if (!fade_.IsFinished())
		return;

	switch (sceneState_) {
	case SceneState::Title:
		sphere_.Update();
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			fade_.Start(FadeState::FadeOut);
			nextScene_ = SceneState::Game;
		}
		break;

	case SceneState::Game:
		sphere_.Update();
		player_.Update();
		// 例: Enter でクリア画面に遷移
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			fade_.Start(FadeState::FadeOut);
			nextScene_ = SceneState::Clear;
		}
		break;

	case SceneState::Clear:
		sphere_.Update();
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			fade_.Start(FadeState::FadeOut);
			nextScene_ = SceneState::Title;
		}
		break;
	}

	// フェードアウト終了後にシーン切り替え
	if (fade_.IsFinished() && fade_.GetState() == FadeState::None) {
		if (sceneState_ != nextScene_) {
			sceneState_ = nextScene_;
			fade_.Start(FadeState::FadeIn);
		}
	}
}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3D描画
	Model::PreDraw();

	// 天球
	sphere_.Draw();

	if (sceneState_ == SceneState::Game) {
		player_.Draw(*camera_);
	}
	Model::PostDraw();

	// 2D描画（UI, フェードなど）
	Sprite::PreDraw(dxCommon->GetCommandList());

	switch (sceneState_) {
	case SceneState::Title:
		break;
	case SceneState::Clear:
		break;
	default:
		break;
	}

	// フェードを一番上に
	fade_.Draw();

	Sprite::PostDraw();
}

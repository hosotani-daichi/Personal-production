#include "CameraController.h"
#include "Player.h"

using namespace KamataEngine;

Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
	Vector3 result;
	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return result;
}

void CameraController::Initialize() {
	// 引数の内容をメンバ変数に記録
	camera_.Initialize();
}

void CameraController::Update() {
	const Vector3& targetVelocity = target_->GetVelocity();
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	cameraTarget_ = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	// Lerp を使って補間
	camera_.translation_ = Lerp(camera_.translation_, cameraTarget_, kInterpolationRate);

	// 移動範囲制限（必要に応じて）
	camera_.translation_.x = max(camera_.translation_.x, targetWorldTransform.translation_.x + targetmargin.left);
	camera_.translation_.x = min(camera_.translation_.x, targetWorldTransform.translation_.x + targetmargin.right);
	camera_.translation_.y = max(camera_.translation_.y, targetWorldTransform.translation_.y + targetmargin.bottom);
	camera_.translation_.y = min(camera_.translation_.y, targetWorldTransform.translation_.y + targetmargin.top);

	camera_.UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

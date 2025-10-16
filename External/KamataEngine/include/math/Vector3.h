#pragma once

namespace KamataEngine {

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 {
	float x, y, z;

	// 加算
	Vector3 operator+(const Vector3& other) const { return {x + other.x, y + other.y, z + other.z}; }

	// 減算
	Vector3 operator-(const Vector3& other) const { return {x - other.x, y - other.y, z - other.z}; }

	// スカラー倍
	Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

	// スカラー割り算（必要なら）
	Vector3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }
};

} // namespace KamataEngine

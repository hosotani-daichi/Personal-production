#include "Map.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace KamataEngine;

void Map::Initialize(int tileSize) { tileSize_ = tileSize; }

void Map::LoadFromCSV(const std::string& filename) {
	std::ifstream file(filename); // CSVを開く
	std::string line;
	mapData_.clear();

	// 1行ずつ読み込み
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		// カンマ区切りで分割
		while (std::getline(ss, cell, ',')) {
			row.push_back(std::stoi(cell));
		}
		mapData_.push_back(row);
	}

	// サイズ更新
	height_ = (int)mapData_.size();
	width_ = (height_ > 0) ? (int)mapData_[0].size() : 0;
}

bool Map::IsBlockAt(float worldX, float worldY) const {
	int tileX = static_cast<int>(worldX / tileSize_);
	int tileY = static_cast<int>(worldY / tileSize_);

	// 範囲外はブロックなし
	if (tileX < 0 || tileX >= width_ || tileY < 0 || tileY >= height_) {
		return false;
	}
	return mapData_[tileY][tileX] == 1; // 1ならブロック
}

void Map::Draw(Camera& camera) {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			if (mapData_[y][x] == 1) { // ブロックだけ描画
				auto block = Model::CreateFromOBJ("block");
				WorldTransform wt;
				wt.Initialize();
				wt.translation_ = {(float)(x * tileSize_), (float)(y * tileSize_), 0.0f};
				wt.UpdateMatrix();
				block->Draw(wt, camera);
			}
		}
	}
}

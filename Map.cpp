#include "Map.h"
#include <fstream>
#include <sstream>
using namespace KamataEngine;

void Map::Initialize(const std::string& csvPath, uint32_t tilesetTex, int tileSize) {
	tilesetTex_ = tilesetTex;
	tileSize_ = static_cast<float>(tileSize);

	if (!LoadCSV(csvPath)) {
		// 読み込み失敗したら何もしない
		return;
	}

	// CSVの内容からSprite生成
	for (int y = 0; y < (int)mapData_.size(); ++y) {
		for (int x = 0; x < (int)mapData_[y].size(); ++x) {
			int id = mapData_[y][x];
			if (id == 0) {
				sprites_.push_back(nullptr);
				continue;
			}

			auto sp = Sprite::Create(tilesetTex_, {(float)(x * tileSize_), (float)(y * tileSize_)});
			sp->SetSize({(float)tileSize_, (float)tileSize_});
			sprites_.push_back(sp);
		}
	}
}

bool Map::LoadCSV(const std::string& csvPath) {
	std::ifstream file(csvPath);
	if (!file.is_open()) {
		return false;
	}

	mapData_.clear();
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string cell;
		std::vector<int> row;
		while (std::getline(ss, cell, ',')) {
			try {
				row.push_back(std::stoi(cell));
			} catch (...) {
				row.push_back(0);
			}
		}
		mapData_.push_back(row);
	}
	return true;
}

void Map::Draw() {
	for (auto sp : sprites_) {
		if (sp)
			sp->Draw();
	}
}

int Map::GetTileIdAtPixel(float px, float py) const {
	int tx = (int)(px / tileSize_);
	int ty = (int)(py / tileSize_);
	if (ty < 0 || ty >= (int)mapData_.size())
		return 0;
	if (tx < 0 || tx >= (int)mapData_[ty].size())
		return 0;
	return mapData_[ty][tx];
}

bool Map::IsBlockAtPixel(float px, float py) const { return GetTileIdAtPixel(px, py) == 1; }
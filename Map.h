#pragma once
#include "KamataEngine.h"
#include <string>
#include <vector>

class Map {
public:
	// csvPath … マップデータのCSVファイルパス
	// tilesetTex … タイルセットのテクスチャハンドル
	// tileSize … 1タイルのピクセルサイズ
	void Initialize(const std::string& csvPath, uint32_t tilesetTex, int tileSize);

	void Draw();

private:
	bool LoadCSV(const std::string& csvPath);

private:
	uint32_t tilesetTex_ = 0;
	int tileSize_ = 32;

	int GetTileIdAtPixel(float px, float py) const;
	bool IsBlockAtPixel(float px, float py) const;

	std::vector<std::vector<int>> mapData_;      // CSVから読み込んだタイルID
	std::vector<KamataEngine::Sprite*> sprites_; // タイルごとのスプライト
};

#pragma once
#include "KamataEngine.h"
#include <string>
#include <vector>

class Map {
public:

	void Initialize(const std::string& csvPath, uint32_t tilesetTex, int tileSize);

	void Draw();

	int GetTileIdAtPixel(float px, float py) const;
	bool IsBlockAtPixel(float px, float py) const;

private:
	bool LoadCSV(const std::string& csvPath);

private:
	uint32_t tilesetTex_ = 0;
	float tileSize_ = 32.0f;


	std::vector<std::vector<int>> mapData_;      // CSVから読み込んだタイルID
	std::vector<KamataEngine::Sprite*> sprites_; // タイルごとのスプライト
};

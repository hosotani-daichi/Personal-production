#pragma once
#include <KamataEngine.h>
#include <string>
#include <vector>

class Map {
public:
	// 初期化（タイルサイズを指定）
	void Initialize(int tileSize);

	// CSVからマップを読み込む
	void LoadFromCSV(const std::string& filename);

	// 指定座標がブロックかどうかを判定
	bool IsBlockAt(float worldX, float worldY) const;

	// マップを描画
	void Draw(KamataEngine::Camera& camera);

	int GetTileSize() const { return tileSize_; }

private:
	std::vector<std::vector<int>> mapData_; // 2Dマップデータ（0=空,1=ブロック）
	int width_ = 0;                         // 横マス数
	int height_ = 0;                        // 縦マス数
	int tileSize_ = 1;                      // 1タイルの大きさ（ワールド座標単位）
};

#pragma once
#include "../SceneBase.h"
class RankingInput:
	public SceneBase
{
private:
	int backgrouond_image;   // 背景画像
	int result_time;         // 残り時間
	char result_name[1][15];           // 名前
	int name_num;            // 名前入力数
	int cursor_x;            // カーソルx座標
	int cursor_y;            // カーソルy座標

public:
	RankingInput();
	~RankingInput();

	void Initialize() override;
	eSceneType Update() override;
	void Draw() const override;
	void Finalize() override;

	eSceneType GetNowSceneType() const override;

private:
	//名前入力処理
	bool InputName();
};
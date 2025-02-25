#pragma once
#include "../SceneBase.h"
class RankingInput:
	public SceneBase
{
private:
	int backgrouond_image;   // 背景画像
	int remain_time;         // 残り時間
	char name[15];           // 名前
	int name_num;            // 名前入力数
	int cursor_x;            // カーソルx座標
	int cursor_y;            // カーソルy座標

public:
	RankingInput();
	virtual ~RankingInput();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowSceneType() const override;

private:
	//名前入力処理
	bool InputName();
};
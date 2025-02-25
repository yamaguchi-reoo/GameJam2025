#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
private:
	//ゲームシーンに必要な変数を定義
	int time_count;  // 制限時間を減らすためのカウント  60count = 1秒
	int create_span_item; // アイテムを生成する間隔
	int create_span_enemy;  // 敵を生成する間隔

	int in_game_image;

	int shake_timer;  // 針が揺れる時間
	float shake_amount;  // 針の揺れ幅
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;
public:
	void DecTime(int dectime);
	void WriteData();

	void DrawTimer()const;
};
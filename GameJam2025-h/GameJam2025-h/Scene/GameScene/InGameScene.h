#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
private:
	//ゲームシーンに必要な変数を定義
	int time_limit;  // 制限時間
	int time_count;  // 制限時間を減らすためのカウント  60count = 1秒
	int create_time; // オブジェクトを生成する間隔

public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;
public:
	//必要に応じて追加する関数をここに定義
	void DecQuantity();
};
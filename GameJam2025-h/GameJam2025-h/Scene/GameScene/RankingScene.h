#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//シーンに必要な変数を定義
	int remain_time[6];
	int result_time;

public:
	RankingScene();
	~RankingScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;

public:
	//必要に応じて追加する関数をここに定義
	void SortData();  // 残り時間の多い順にソート
};


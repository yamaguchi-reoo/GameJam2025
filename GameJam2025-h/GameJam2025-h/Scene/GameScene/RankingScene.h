#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//シーンに必要な変数を定義
	int remain_time[6];  // タイムデータ
	char player_name[6][15];  // 名前データ
	int result_time;     // 前回の記録を入れる
	char result_name[1][15];     // 今回の入力される名前

	int cursor;   // 選択されているボタンの位置

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


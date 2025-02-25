#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//シーンに必要な変数を定義
	int remain_time[6];  // 今までの残り時間をまとめる
	int player_name[6];  // 今までの名前をまとめる
	int result_time;     // 前回の記録を入れる
	int result_name;     // 今回の入力される名前

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


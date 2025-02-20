#include "RankingScene.h"

RankingScene::RankingScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
}

eSceneType RankingScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	//Zキーが押されたらTitleシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	//描画処理
	DrawString(0, 24, "Ranking", GetColor(255, 255, 255));
}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

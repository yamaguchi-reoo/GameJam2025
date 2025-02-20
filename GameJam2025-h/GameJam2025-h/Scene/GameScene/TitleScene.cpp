#include "TitleScene.h"

TitleScene::TitleScene()//この関数の後ろに定義した変数を連ねて書く（例 : TitleScene() : a()）
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
}

eSceneType TitleScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	//Zキーが押されたらGameMainシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eGameMain;
	}
	//Xキーが押されたらHelpシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_X))
	{
		return eSceneType::eHelp;
	}
	//Cキーが押されたらHelpシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_C))
	{
		return eSceneType::eRanking;
	}

	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	//描画処理
	DrawString(0, 24, "Title", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

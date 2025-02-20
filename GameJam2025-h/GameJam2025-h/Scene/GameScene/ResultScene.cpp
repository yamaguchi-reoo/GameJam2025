#include "ResultScene.h"

ResultScene::ResultScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
}

eSceneType ResultScene::Update()
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

void ResultScene::Draw() const
{
	//描画処理
	DrawString(0, 24, "Result", GetColor(255, 255, 255));
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

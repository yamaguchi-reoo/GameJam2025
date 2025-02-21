#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"

InGameScene::InGameScene()//この関数の後ろに定義した変数を連ねて書く（例 : InGameScene() : a()）
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
	CreateObject<Apple>(Vector2D(30.0f, 40.0f), Vector2D(64.0f));
}

eSceneType InGameScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	//Zキーが押されたらResultシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eResult;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{
	__super::Draw();
	//描画処理
	DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

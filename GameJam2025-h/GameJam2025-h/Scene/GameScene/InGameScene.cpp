#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"
#include "../../Object/Enemy/WeekEnemy.h"
#include "../../common.h"

InGameScene::InGameScene()//この関数の後ろに定義した変数を連ねて書く（例 : InGameScene() : a()）
	:time_limit(),
	time_count()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
	CreateObject<Apple>(Vector2D(30.0f, 40.0f), Vector2D(64.0f));
	CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));

	time_count = 0;
	time_limit = 60;
}

eSceneType InGameScene::Update()
{
	//更新処理
	
	// 制限時間更新
	time_count++;
	if (time_count > 60)
	{
		time_limit--;
		time_count = 0;
	}

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	// 制限時間が０になったらリザルトに遷移
	if (time_limit <= 0)
	{
		return eSceneType::eResult;
	}
	//Zキーが押されたらResultシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eGameMain;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{
	__super::Draw();
	//描画処理
	DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
	DrawFormatString(620, 24, GetColor(255, 255, 255), "%d", time_limit);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

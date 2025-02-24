#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"
#include "../../Object/Item/ItemBase.h"
#include "../../Object/Enemy/WeekEnemy.h"
#include "../../Object/Enemy/NomalEnemy.h"
#include "../../Object/Enemy/HardEnemy.h"
#include "../../Object/Enemy/BossEnemy.h"
#include "../../Object/Player/Player.h"
#include "../../common.h"

#define OBJECT_MAX 10

InGameScene::InGameScene()//この関数の後ろに定義した変数を連ねて書く（例 : InGameScene() : a()）
	:time_limit(),
	time_count(),
	create_span_item(),
	create_span_enemy()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	CreateObject<Player>(Vector2D(290.0f, 520.0f), Vector2D(115.0f,115.0f));

	//CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));

	// 制限時間設定
	time_count = 0;
	time_limit = 60;

	// オブジェクト生成設定
	create_span_item = 0;
	create_span_enemy = 0;
	create_enemy_max = 3;
	create_enemy = true;
	create_boss = true;
	is_boss = true;
}

eSceneType InGameScene::Update()
{
	//更新処理
	
	// 制限時間更新
	time_count++;
	if (time_count > (int)FRAMERATE)
	{
		time_limit--;
		time_count = 0;
	}

	// 敵を生成する
	if (create_enemy == true)
	{
		if (create_enemy_max > 0)
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(200.0f,150.0f));
				create_enemy = false;
				create_span_enemy = 0;
			}
		}
		else
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				if (create_boss == true)
				{
					CreateObject<BossEnemy>(Vector2D(1000.0f, 450.0f), Vector2D(200.f,319.f));
					create_boss = false;
					create_span_enemy = 0;
				}
			}
		}
	}

	// アイテムを生成する
	create_span_item++;
	if (create_span_item >= 30)
	{
		if (create_quantity_item < OBJECT_MAX)
		{
			CreateObject<ItemBase>(Vector2D(140 * (rand() % 5) + 300, 80), Vector2D(95.0f));
		}
		create_span_item = 0;
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
		return eSceneType::eResult;
	}
	// ボスが倒されたらリザルトに遷移
	if (is_boss = false)
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
	DrawFormatString(620, 24, GetColor(255, 255, 255), "%d", time_limit);
	DrawString(200, 24, "item", GetColor(255, 255, 255));
	DrawFormatString(300, 24, GetColor(255, 255, 255), "%d", create_quantity_item);
	DrawString(200, 34, "enemy", GetColor(255, 255, 255));
	DrawFormatString(300, 34, GetColor(255, 255, 255), "%d", create_enemy_max);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

void InGameScene::DecTime(int dectime)
{
	time_limit = time_limit - dectime;
}
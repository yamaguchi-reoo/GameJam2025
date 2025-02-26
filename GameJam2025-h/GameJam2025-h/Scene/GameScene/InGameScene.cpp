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

#include <cmath>

#define OBJECT_MAX 10

InGameScene::InGameScene()//この関数の後ろに定義した変数を連ねて書く（例 : InGameScene() : a()）
	:time_count(),
	create_span_item(),
	create_span_enemy(),
	in_game_image(),
	shake_timer(),
	shake_amount(),
	Fight_BGM()
{
}

InGameScene::~InGameScene()
{ 
}

void InGameScene::Initialize()
{
	CreateObject<Player>(Vector2D(290.0f, 520.0f), Vector2D(115.0f, 115.0f));

	// 制限時間設定
	time_count = 0;
	limit_time = 60;

	// オブジェクト生成設定
	create_span_item = 0;
	create_span_enemy = 0;
	create_enemy_max = 10;
	create_enemy = true;
	create_boss = true;
	is_boss = true;

	in_game_image = LoadGraph("Resource/Images/GameMain04.png");

	shake_timer = 0;
	shake_amount = 0.0f;

	Fight_BGM = LoadSoundMem("Resource/Sounds/MusMus-BGM-172.mp3");

	// 音量の設定
	ChangeVolumeSoundMem(255 * 60 / 100, Fight_BGM);

	PlaySoundMem(Fight_BGM, DX_PLAYTYPE_BACK);
}

eSceneType InGameScene::Update()
{
	//更新処理

	// 制限時間更新
	time_count++;
	if (time_count > (int)FRAMERATE)
	{
		limit_time--;
		time_count = 0;
	}

	//時計の針の揺れを計算**
	if (shake_timer > 0)
	{
		shake_timer--;
		shake_amount *= 0.9f;  // 徐々に揺れを小さくする
	}

	// 敵を生成する
	if (create_enemy == true)
	{
		if (create_enemy_max > 0)
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				if (create_enemy_max >= 7)
				{
					CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(200.0f,142.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
				else if (create_enemy_max >= 3)
				{
					CreateObject<NomalEnemy>(Vector2D(1000.0f, 540.0f), Vector2D(200.0f,223.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
				else if (create_enemy_max >= 1)
				{
					CreateObject<HardEnemy>(Vector2D(1000.0f, 540.0f), Vector2D(200.0f,200.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
			}
		}
		else
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				if (create_boss == true)
				{
					// 再生を止めます
					StopSoundMem(Fight_BGM);
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
	if (limit_time <= 0)
	{
		limit_time = 0;
		WriteData();
		return eSceneType::eResult;
	}
	//Zキーが押されたらResultシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		WriteData();
		return eSceneType::eResult;
	}
	// ボスが倒されたらリザルトに遷移
	if (is_boss == false)
	{
		WriteData();
		return eSceneType::eResult;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{

	DrawGraph(0, 0, in_game_image, TRUE);

	// アイテム生成レーンを描画 (レーンの位置にボックスを表示)
	DrawItemGenerationLanes();

	__super::Draw();

	//時計の描画
	SetFontSize(30);
	DrawTimer();

	SetFontSize(12);
	//描画処理
	//DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
	//DrawFormatString(620, 24, GetColor(255, 255, 255), "%d", limit_time);
	//DrawString(200, 24, "item", GetColor(255, 255, 255));
	//DrawFormatString(300, 24, GetColor(255, 255, 255), "%d", create_quantity_item);
	//DrawString(200, 34, "enemy", GetColor(255, 255, 255));
	//DrawFormatString(300, 34, GetColor(255, 255, 255), "%d", create_enemy_max);
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
	limit_time = limit_time - dectime;

	//針を揺らすための値をセット
	shake_timer = 60;
	shake_amount = 10.0f;  //最初は10度くらい大きく揺れる
}

void InGameScene::WriteData()
{
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "w");

	if (result != 0)
	{
		throw("Resource/Data/Result.csvが開けません\n");
	}

	fprintf(fp, "%d,\n", limit_time);

	fclose(fp);
}

void InGameScene::DrawTimer() const
{
	//時計の位置とサイズ
	int clock_center_x = 1200;  // 時計の中心 X
	int clock_center_y = 60;  // 時計の中心 Y
	int clock_radius = 50;     // 時計の半径

	//時計の円を描画
	DrawCircle(clock_center_x, clock_center_y, clock_radius, GetColor(0, 0, 0), TRUE);
	DrawCircle(clock_center_x, clock_center_y, clock_radius + 1, GetColor(255, 255, 255), FALSE);


	//秒針の計算
	float angle = ((float)limit_time / 60.0f) * 360.0f + 90;  // 60秒で一周（360度）
	angle += (shake_timer > 0) ? ((rand() % 5 - 2) * shake_amount) : 0.0f;  // ランダムにブレる

	//角度をラジアンに変換
	float rad = angle * (3.1415926535f / 180.0f);  // 角度をラジアンに変換

	//秒針の座標を計算
	int hand_x = clock_center_x + cos(rad) * (clock_radius - 5);
	int hand_y = clock_center_y - sin(rad) * (clock_radius - 5);  // Y軸は逆方向

	//秒針を描画
	DrawLine(clock_center_x, clock_center_y, hand_x, hand_y, GetColor(255, 0, 0), 3);

	//デジタル時計（アナログ時計の下に表示
	int minutes = limit_time / 60;  // 分
	int seconds = limit_time % 60;  // 秒

	//デジタル時計をアナログ時計の下に描画
	DrawFormatString(clock_center_x - 40, clock_center_y + clock_radius + 10, GetColor(255, 255, 255), "%02d:%02d", minutes, seconds);

}

void InGameScene::DrawItemGenerationLanes() const
{
	// アイテム生成レーンを示すためにボックスを描画
	int lane_y = 0;  // Y座標 (全てのレーンの高さをここで設定)
	int lane_height = 450;  // 高さ
	int lane_spacing = 140; // 各レーンの間隔

	//黒い背景ボックスの描画（透明度を設定）
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(275, lane_y, 285 + (lane_spacing * 5), lane_height, GetColor(0, 0, 0), TRUE);

	for (int i = 0; i < 6; ++i) 
	{
		int lane_x = 285 + i * lane_spacing; // X座標（各レーンの横位置をずらす）
		DrawBox(lane_x - 10, lane_y, lane_x, lane_height, GetColor(255, 255, 255), TRUE); // ブレンド付きの青色
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ブレンドモードを戻す

}

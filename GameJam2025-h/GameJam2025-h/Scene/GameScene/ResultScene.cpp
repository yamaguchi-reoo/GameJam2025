#include "ResultScene.h"
#include "DxLib.h"
#include <string>
#include <fstream>

ResultScene::ResultScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
	:result_time()
	/*remain_time()*/
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
	/*for (int i = 0; i <= 5; i++)
	{
		remain_time[i] = 0;
	}*/

	LoadData();
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

	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", result_time);

	if (result_time > 30)
	{
		DrawString(100, 120,"☆PERFECT☆", GetColor(255, 255, 255));
	}
	else if (result_time > 15)
	{
		DrawString(100, 120, "GOOD!!", GetColor(255, 255, 255));
	}
	else if (result_time >= 1)
	{
		DrawString(100, 120, "NICE", GetColor(255, 255, 255));
	}
	else if (result_time == 0)
	{
		DrawString(100, 120, "DEFEAT", GetColor(255, 255, 255));
	}
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

void ResultScene::LoadData()
{
	// ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

	// エラーチェック
	if (result != 0)
	{
		throw("Resource/Data/Result.csvが開けませんでした。");
	}

	// 今回の記録を取得
	fscanf_s(fp, "%d,\n", &result_time);

	// ファイルクローズ
	fclose(fp);

	if (result_time < 0)
	{
		result_time = 0;
	}

	//// ファイルオープン
	//FILE* fp = nullptr;
	//errno_t result = fopen_s(&fp, "Resource/Data/TimeData.csv", "r");

	//// エラーチェック
	//if (result != 0)
	//{
	//	throw("Resource/Data/TimeData.csvが開けませんでした。");
	//}

	//// 今までの記録を取得
	//for (int i = 0; i < 5; i++)
	//{
	//	fscanf_s(fp, "%d,\n", &remain_time[i]);
	//}

	//// ファイルクローズ
	//fclose(fp);
}
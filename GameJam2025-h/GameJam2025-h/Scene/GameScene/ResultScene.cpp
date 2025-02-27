#include "ResultScene.h"
#include "DxLib.h"
#include <string>
#include <fstream>

ResultScene::ResultScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
	:bgi(),
	result_time()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	LoadData();

	bgi = LoadGraph("Resource/Images/Result_bgi.png");
}

eSceneType ResultScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	if (input->GetButtonDown(XINPUT_BUTTON_B)) {
		return eSceneType::eInput;
	}

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
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 210, 210), TRUE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgi, TRUE);

	ChangeFontType(DX_FONTTYPE_EDGE);
	int init_font_size = GetFontSize();

	SetFontSize(50);
	//描画処理
	DrawString(SCREEN_WIDTH / 2 - 100, 24, "Result", GetColor(255, 255, 255));

	SetFontSize(36);
	DrawString(100, 100, "残り時間", 0xffffff);

	SetFontSize(350);
	DrawFormatString(200, 150, GetColor(255, 255, 255), "%d", result_time);

	SetFontSize(36);
	DrawString(600, 420, "秒", 0xffffff);

	SetFontSize(80);
	if (result_time > 30)
	{
		DrawString(700, 500,"☆PERFECT☆", GetColor(255, 255, 0));
	}
	else if (result_time > 15)
	{
		DrawString(700, 500, "GREAT!!", GetColor(0, 255, 0));
	}
	else if (result_time >= 1)
	{
		DrawString(700, 500, "GOOD", GetColor(255, 0, 0));
	}
	else if (result_time == 0)
	{
		DrawString(700, 500, "DEFEAT", GetColor(0, 0, 255));
	}

	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(init_font_size);
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
}
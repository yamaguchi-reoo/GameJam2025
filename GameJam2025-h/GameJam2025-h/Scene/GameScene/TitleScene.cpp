#include "TitleScene.h"
#include "DxLib.h"
#include "../../common.h"

TitleScene::TitleScene()://この関数の後ろに定義した変数を連ねて書く（例 : TitleScene() : a()）
	cursor(),
	in_title_image()
{
}

TitleScene::~TitleScene()
{
}


void TitleScene::Initialize()
{
	PlaySoundFile("Resource/Sounds/maou_bgm_acoustic10.mp3アコースティック.mp3", DX_PLAYTYPE_BACK);

	//ここで変数の初期化して（例：a = 0;）
	cursor = 0;

	in_title_image = LoadGraph("Resource/Images/grassland-dot1.jpg");
}

eSceneType TitleScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	//負の値にならないように
	//上キーで移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))cursor = (cursor - 1 + 4) % 4;
	//下キーで移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))cursor = (cursor + 1) % 4;

	//決定
	if (input->GetButtonDown(XINPUT_BUTTON_B)) {
		if (cursor == 0)
		{
			StopSoundFile();
			return eSceneType::eGameMain;
		}
		else if (cursor == 1)
		{
			StopSoundFile();
			return eSceneType::eRanking;
		}
		else if (cursor == 2)
		{
			StopSoundFile();
			return eSceneType::eHelp;
		}
	}
	if (input->GetKeyDown(KEY_INPUT_R))
	{
		StopSoundFile();
		return eSceneType::eGameMain;
	}
	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawGraph(0, 0, in_title_image, TRUE);
	// 描画処理
	SetFontSize(60);
	DrawString((SCREEN_WIDTH / 2) - 190, 150, "Butting Apple", GetColor(255, 255, 255));
	
	
	// 一時的にフォントサイズを変更する
	int old_font_size = GetFontSize();
	SetFontSize(24);

	// メニュー項目のリスト
	const char* menu_items[] = { "START", "RANKING", "HELP", "END" };

	// 四角形のサイズと間隔の定義
	Vector2D box = { 160.0f,80.0f };
	int box_spacing = 3;
	int start_y = (SCREEN_HEIGHT / 2) + 50;

	for (int i = 0; i < 4; i++)
	{
		int y = start_y + i * (box.y + box_spacing) - 100;

		// 選択中の項目は黄色、それ以外は赤
		int color = (i == cursor) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

		// 四角形の描画
		DrawBox(box.x, y, box.x * 2, y + box.y, color, FALSE);

		// テキスト描画
		DrawFormatString(box.x + 10, y + 7, GetColor(255, 255, 255), menu_items[i]);
	}

	//Aボタン描画
	DrawCircleAA(145.5f, 670, 12, 12, GetColor(255, 255, 255), FALSE);
	DrawCircleAA(145.5f, 670, 11, 12, GetColor(255, 20, 20), TRUE);
	SetFontSize(16);
	DrawString(170, 665, "決定", 0xffffff);
	DrawString(142, 662, "B", 0xffffff);

	//DPad描画
	DrawDPad();

	// 元のフォントサイズに戻す
	SetFontSize(old_font_size);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

void TitleScene::DrawDPad() const
{
	// 十字キーの中心座標
	int d_pad_x = 240;
	int d_pad_y = 670;
	int d_pad_size = 5;

	// 縦・横のボタンの背景（黒枠）
	DrawBox(d_pad_x - d_pad_size, d_pad_y - d_pad_size * 3, d_pad_x + d_pad_size, d_pad_y + d_pad_size * 3, GetColor(100, 100, 100), TRUE);
	DrawBox(d_pad_x - d_pad_size * 3, d_pad_y - d_pad_size, d_pad_x + d_pad_size * 3, d_pad_y + d_pad_size, GetColor(100, 100, 100), TRUE);

	// 上ボタン（↑）
	DrawTriangle(d_pad_x, d_pad_y - d_pad_size * 2, d_pad_x - d_pad_size, d_pad_y - d_pad_size,  d_pad_x + d_pad_size, d_pad_y - d_pad_size,  GetColor(255, 255, 255), TRUE);

	// 下ボタン（↓）
	DrawTriangle(d_pad_x, d_pad_y + d_pad_size * 2,  d_pad_x - d_pad_size, d_pad_y + d_pad_size,  d_pad_x + d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	// 左ボタン（←）
	DrawTriangle(d_pad_x - d_pad_size * 2, d_pad_y,  d_pad_x - d_pad_size, d_pad_y - d_pad_size,  d_pad_x - d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	// 右ボタン（→）
	DrawTriangle(d_pad_x + d_pad_size * 2, d_pad_y,  d_pad_x + d_pad_size, d_pad_y - d_pad_size,  d_pad_x + d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	DrawString(265, 665, "移動", GetColor(255, 255, 255));
}

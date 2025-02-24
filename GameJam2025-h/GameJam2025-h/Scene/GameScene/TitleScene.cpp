#include "TitleScene.h"
#include "DxLib.h"
#include "../../common.h"

TitleScene::TitleScene()://この関数の後ろに定義した変数を連ねて書く（例 : TitleScene() : a()）
	cursor()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
	cursor = 0;
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
			return eSceneType::eGameMain;
		}
		else if (cursor == 1)
		{
			return eSceneType::eRanking;
		}
		else if (cursor == 2)
		{
			return eSceneType::eHelp;
		}
	}
	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
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
		//DrawBox((SCREEN_WIDTH / 2) - (box.x / 2), y, (SCREEN_WIDTH / 2) + (box.x / 2), y + box.y, color, FALSE);
		DrawBox(box.x, y, box.x * 2, y + box.y, color, FALSE);

		// テキスト描画
		DrawFormatString(box.x + 10, y + 7, GetColor(255, 255, 255), menu_items[i]);
	}

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

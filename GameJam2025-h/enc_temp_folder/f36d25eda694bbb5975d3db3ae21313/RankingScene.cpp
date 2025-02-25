#include "RankingScene.h"

RankingScene::RankingScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
	:remain_time(),
	result_time(),
	cursor()
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
	cursor = 0;

	for (int i = 0; i < 5; i++)
	{
		remain_time[i] = 0;
	}

	//ランキングデータの読み込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/Data/TimeData.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/Data/TimeData.scvが開けませんでした\n");
	}

	//対象ファイルから読み込む
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,\n", &remain_time[i]);
	}

	//ファイルクローズ
	fclose(fp);

	//ファイルオープン
	result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/Data/Result.scvが開けませんでした\n");
	}
	fscanf_s(fp, "%6d,\n", &result_time);

	//ファイルクローズ
	fclose(fp);

	SortData();
}

eSceneType RankingScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		cursor = 0;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		cursor = 1;
	}

	//Zキーが押されたらTitleシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_B))
	{
		if (cursor == 0)
		{
			return eSceneType::eGameMain;
		}
		if (cursor == 1)
		{
			return eSceneType::eTitle;
		}
	}

	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// フォントサイズの変更
	int init_font_size = GetFontSize();
	SetFontSize(36);

	// 遷移リスト
	const char* menu_items[] = { "RESTART","TITLE" };

	// 四角・テキストの描画位置、サイズの設定
	Vector2D box = Vector2D(160.0f, 80.0f);
	int start_x = (SCREEN_WIDTH / 4);
	int y = (SCREEN_HEIGHT - (int)box.y * 2);
	int box_spacing = 20;

	//描画処理
	DrawString(0, 24, "Ranking", GetColor(255, 255, 255));

	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(100, (GetFontSize() + 30) * i + 100, GetColor(255, 255, 255), "%d 位　　残り時間　%d 秒", i + 1, remain_time[i]);
		DrawLine(100, (GetFontSize() + 30) * i + 100 + GetFontSize(), 600, (GetFontSize() + 30) * i + 100 + GetFontSize(), GetColor(255, 255, 255));
	}

	// シーン遷移ボタン描画
	for (int i = 0; i < 2; i++)
	{
		// 描画位置決定
		int x = start_x + i * (box.x + box_spacing);

		// カラー指定
		int color = (i == cursor) ? GetColor(255, 225, 0) : GetColor(255, 0, 0);

		// 四角の描画
		DrawBox(x, y, x + box.x, y + box.y, color, FALSE);

		// テキスト表示
		DrawFormatString(x + 10, y + 10, GetColor(255, 255, 255), menu_items[i]);
	}

	// フォントサイズを元に戻す
	SetFontSize(init_font_size);
}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

void RankingScene::SortData()
{
	remain_time[5] = result_time;
	//選択法ソートを使用し、降順で入れ替える
	for (int i = 0; i < 6; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (remain_time[i] <= remain_time[j])
			{
				int tmp = remain_time[i];
				remain_time[i] = remain_time[j];
				remain_time[j] = tmp;
			}
		}
	}
	//ランキングデータの書き込み
	FILE* fp = nullptr;

	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/Data/TimaData.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/Data/TimeData.csvが開けませんでした\n");
	}

	//対象ファイルに書き込み
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,\n", remain_time[i]);
	}

	//ファイルクローズ
	fclose(fp);
}
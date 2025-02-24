#include "RankingScene.h"

RankingScene::RankingScene()//この関数の後ろに定義した変数を連ねて書く（例 : ResultScene() : a()）
	:remain_time(),
	result_time()
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）
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

	//Zキーが押されたらTitleシーンへ遷移
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	//描画処理
	DrawString(0, 24, "Ranking", GetColor(255, 255, 255));

	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(100, 25 * i + 100, GetColor(255, 255, 255), "%d", remain_time[i]);
	}
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
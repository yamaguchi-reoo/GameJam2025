#include "DxLib.h"
#include "SceneManager.h"
#include "GameScene/SceneList.h"

//静的メンバ変数定義
SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	//インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}

	//自分自身でポインタを返却する
	return instance;
}

void SceneManager::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

SceneManager::SceneManager() :current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
	this->Finalize();
}

void SceneManager::Initialize()
{
	// 最初に表示するシーンをタイトルシーンに設定
	ChangeScene(eSceneType::eTitle);		//TitlrScene
}

void SceneManager::Update()
{
	//現在のシーンの更新処理を実行し、次のシーンの種類を取得
	eSceneType next_scene_type = current_scene->Update();

	//現在のシーンの描画処理を実行
	current_scene->Draw();

	//シーンが変更される場合は新しいシーンに切り替える
	if (next_scene_type != current_scene->GetNowSceneType())
	{
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	//現在のシーンが存在すれば、終了処理を行い、メモリを解放する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Draw() const
{
}

void SceneManager::ChangeScene(eSceneType type)
{
	//新しいシーンのインスタンスを作成
	SceneBase* new_scene = CreateScene(type);

	//エラーチェック
	if (new_scene == nullptr)
	{
		throw("\n新しいシーンの生成が出来ませんでした\n");
	}

	//現在のシーンの終了処理を実行し、メモリを解放する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//新しいシーンの初期化
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(eSceneType type)
{
	switch (type)
	{
	case eSceneType::eTitle:
		//TitleScene生成
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eGameMain:
		//GameScene生成
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eResult:
		//ResultScene生成
		return dynamic_cast<SceneBase*>(new ResultScene());
	case eSceneType::eHelp:
		//HelpScene生成
		return dynamic_cast<SceneBase*>(new HelpScene());
	case eSceneType::eRanking:
		//HelpScene生成
		return dynamic_cast<SceneBase*>(new RankingScene());
	case eSceneType::eInput:
		//RankingInput生成
		return dynamic_cast<SceneBase*>(new RankingInput());
	case eSceneType::eCredit:
		//CreditScene生成
		return dynamic_cast<CreditScene*>(new CreditScene());
	default:
		//該当するシーンがない場合はnullptrを返す
		return nullptr;
	}
}

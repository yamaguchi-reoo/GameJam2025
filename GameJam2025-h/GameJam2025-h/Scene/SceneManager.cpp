#include "DxLib.h"
#include "SceneManager.h"
#include "GameScene/InGameScene.h"
#include "GameScene/TitleScene.h"


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
	//ChangeScene(eSceneType::eGameMain);
	ChangeScene(eSceneType::eTitle);
}

void SceneManager::Update()
{

	//デバッグ表示の更新
	//DebugInfomation::Update();
	eSceneType next_scene_type = current_scene->Update();

	current_scene->Draw();

	if (next_scene_type != current_scene->GetNowSceneType())
	{
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

SceneBase* SceneManager::GetCurrentScene() const
{
	return current_scene;
}

void SceneManager::Draw() const
{
}

void SceneManager::ChangeScene(eSceneType type)
{
	SceneBase* new_scene = CreateScene(type);

	//エラーチェック
	if (new_scene == nullptr)
	{
		throw("\n新しいシーンの生成が出来ませんでした\n");
	}

	//現在のシーンの終了処理
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
	case eSceneType::eGameMain:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());
	default:
		return nullptr;
	}
}

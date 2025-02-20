#include "DxLib.h"
#include "SceneManager.h"
#include "GameScene/InGameScene.h"
#include "GameScene/TitleScene.h"


//�ÓI�����o�ϐ���`
SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	//�C���X�^���X��������΁A��������
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}

	//�������g�Ń|�C���^��ԋp����
	return instance;
}

void SceneManager::DeleteInstance()
{
	//�C���X�^���X�����݂��Ă���΁A�폜����
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

	//�f�o�b�O�\���̍X�V
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

	//�G���[�`�F�b�N
	if (new_scene == nullptr)
	{
		throw("\n�V�����V�[���̐������o���܂���ł���\n");
	}

	//���݂̃V�[���̏I������
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//�V�����V�[���̏�����
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

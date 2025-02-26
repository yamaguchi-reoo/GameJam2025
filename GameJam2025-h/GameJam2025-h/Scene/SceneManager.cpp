#include "DxLib.h"
#include "SceneManager.h"
#include "GameScene/SceneList.h"

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
	// �ŏ��ɕ\������V�[�����^�C�g���V�[���ɐݒ�
	ChangeScene(eSceneType::eTitle);		//TitlrScene
}

void SceneManager::Update()
{
	//���݂̃V�[���̍X�V���������s���A���̃V�[���̎�ނ��擾
	eSceneType next_scene_type = current_scene->Update();

	//���݂̃V�[���̕`�揈�������s
	current_scene->Draw();

	//�V�[�����ύX�����ꍇ�͐V�����V�[���ɐ؂�ւ���
	if (next_scene_type != current_scene->GetNowSceneType())
	{
		ChangeScene(next_scene_type);
	}
}

void SceneManager::Finalize()
{
	//���݂̃V�[�������݂���΁A�I���������s���A���������������
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
	//�V�����V�[���̃C���X�^���X���쐬
	SceneBase* new_scene = CreateScene(type);

	//�G���[�`�F�b�N
	if (new_scene == nullptr)
	{
		throw("\n�V�����V�[���̐������o���܂���ł���\n");
	}

	//���݂̃V�[���̏I�����������s���A���������������
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
	case eSceneType::eTitle:
		//TitleScene����
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eGameMain:
		//GameScene����
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eResult:
		//ResultScene����
		return dynamic_cast<SceneBase*>(new ResultScene());
	case eSceneType::eHelp:
		//HelpScene����
		return dynamic_cast<SceneBase*>(new HelpScene());
	case eSceneType::eRanking:
		//HelpScene����
		return dynamic_cast<SceneBase*>(new RankingScene());
	case eSceneType::eInput:
		//RankingInput����
		return dynamic_cast<SceneBase*>(new RankingInput());
	case eSceneType::eCredit:
		//CreditScene����
		return dynamic_cast<CreditScene*>(new CreditScene());
	default:
		//�Y������V�[�����Ȃ��ꍇ��nullptr��Ԃ�
		return nullptr;
	}
}

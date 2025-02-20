#include "HelpScene.h"

HelpScene::HelpScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : HelpScene() : a()�j
{
}

HelpScene::~HelpScene()
{
}

void HelpScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
}

eSceneType HelpScene::Update()
{
	//�X�V����

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	//Z�L�[�������ꂽ��Title�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	//�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void HelpScene::Draw() const
{
	//�`�揈��
	DrawString(0, 24, "Help", GetColor(255, 255, 255));
}

void HelpScene::Finalize()
{
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}

#include "ResultScene.h"

ResultScene::ResultScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
}

eSceneType ResultScene::Update()
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

void ResultScene::Draw() const
{
	//�`�揈��
	DrawString(0, 24, "Result", GetColor(255, 255, 255));
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

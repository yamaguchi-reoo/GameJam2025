#include "TitleScene.h"

TitleScene::TitleScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : TitleScene() : a()�j
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
}

eSceneType TitleScene::Update()
{
	//�X�V����

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	//Z�L�[�������ꂽ��GameMain�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eGameMain;
	}
	//X�L�[�������ꂽ��Help�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_X))
	{
		return eSceneType::eHelp;
	}
	//C�L�[�������ꂽ��Help�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_C))
	{
		return eSceneType::eRanking;
	}

	//�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	//�`�揈��
	DrawString(0, 24, "Title", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

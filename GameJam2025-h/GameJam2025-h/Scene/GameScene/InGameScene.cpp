#include "InGameScene.h"
#include <DxLib.h>

InGameScene::InGameScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : InGameScene() : a()�j
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
}

eSceneType InGameScene::Update()
{
	//�X�V����

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	//Z�L�[�������ꂽ��Result�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eResult;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{
	//�`�揈��
	DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

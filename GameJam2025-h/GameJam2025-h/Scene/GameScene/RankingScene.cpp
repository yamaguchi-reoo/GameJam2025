#include "RankingScene.h"

RankingScene::RankingScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
}

eSceneType RankingScene::Update()
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

void RankingScene::Draw() const
{
	//�`�揈��
	DrawString(0, 24, "Ranking", GetColor(255, 255, 255));
}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowSceneType() const
{
	return eSceneType::eRanking;
}

#include "RankingScene.h"

RankingScene::RankingScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
	:remain_time(),
	result_time()
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
	for (int i = 0; i < 5; i++)
	{
		remain_time[i] = 0;
	}

	//�����L���O�f�[�^�̓ǂݍ���
	FILE* fp = nullptr;

	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/Data/TimeData.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/TimeData.scv���J���܂���ł���\n");
	}

	//�Ώۃt�@�C������ǂݍ���
	for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,\n", &remain_time[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//�t�@�C���I�[�v��
	result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/Result.scv���J���܂���ł���\n");
	}
	fscanf_s(fp, "%6d,\n", &result_time);

	//�t�@�C���N���[�Y
	fclose(fp);

	SortData();
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
	//�I��@�\�[�g���g�p���A�~���œ���ւ���
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
	//�����L���O�f�[�^�̏�������
	FILE* fp = nullptr;

	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/Data/TimaData.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/TimeData.csv���J���܂���ł���\n");
	}

	//�Ώۃt�@�C���ɏ�������
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%d,\n", remain_time[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}
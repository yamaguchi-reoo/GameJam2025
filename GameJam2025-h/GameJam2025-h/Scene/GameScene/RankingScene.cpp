#include "RankingScene.h"

RankingScene::RankingScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
	:remain_time(),
	result_time(),
	cursor()
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
	cursor = 0;

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

	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		cursor = 0;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		cursor = 1;
	}

	//Z�L�[�������ꂽ��Title�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_B))
	{
		if (cursor == 0)
		{
			return eSceneType::eGameMain;
		}
		if (cursor == 1)
		{
			return eSceneType::eTitle;
		}
	}

	//�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void RankingScene::Draw() const
{
	// �t�H���g�T�C�Y�̕ύX
	int init_font_size = GetFontSize();
	SetFontSize(36);

	// �J�ڃ��X�g
	const char* menu_items[] = { "RESTART","TITLE" };

	// �l�p�E�e�L�X�g�̕`��ʒu�A�T�C�Y�̐ݒ�
	Vector2D box = Vector2D(160.0f, 80.0f);
	int start_x = (SCREEN_WIDTH / 4);
	int y = (SCREEN_HEIGHT - (int)box.y * 2);
	int box_spacing = 20;

	//�`�揈��
	DrawString(0, 24, "Ranking", GetColor(255, 255, 255));

	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(100, (GetFontSize() + 30) * i + 100, GetColor(255, 255, 255), "%d �ʁ@�@�c�莞�ԁ@%d �b", i + 1, remain_time[i]);
		DrawLine(100, (GetFontSize() + 30) * i + 100 + GetFontSize(), 600, (GetFontSize() + 30) * i + 100 + GetFontSize(), GetColor(255, 255, 255));
	}

	// �V�[���J�ڃ{�^���`��
	for (int i = 0; i < 2; i++)
	{
		// �`��ʒu����
		int x = start_x + i * (box.x + box_spacing);

		// �J���[�w��
		int color = (i == cursor) ? GetColor(255, 225, 0) : GetColor(255, 0, 0);

		// �l�p�̕`��
		DrawBox(x, y, x + box.x, y + box.y, color, FALSE);

		// �e�L�X�g�\��
		DrawFormatString(x + 10, y + 10, GetColor(255, 255, 255), menu_items[i]);
	}

	// �t�H���g�T�C�Y�����ɖ߂�
	SetFontSize(init_font_size);
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
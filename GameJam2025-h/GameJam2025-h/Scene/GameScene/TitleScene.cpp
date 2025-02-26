#include "TitleScene.h"
#include "DxLib.h"
#include "../../common.h"

TitleScene::TitleScene()://���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : TitleScene() : a()�j
	cursor(),
	in_title_image()
{
}

TitleScene::~TitleScene()
{
}


void TitleScene::Initialize()
{
	PlaySoundFile("Resource/Sounds/maou_bgm_acoustic10.mp3�A�R�[�X�e�B�b�N.mp3", DX_PLAYTYPE_BACK);

	//�����ŕϐ��̏��������āi��Fa = 0;�j
	cursor = 0;

	in_title_image = LoadGraph("Resource/Images/grassland-dot1.jpg");
}

eSceneType TitleScene::Update()
{
	//�X�V����

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	//���̒l�ɂȂ�Ȃ��悤��
	//��L�[�ňړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))cursor = (cursor - 1 + 4) % 4;
	//���L�[�ňړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))cursor = (cursor + 1) % 4;

	//����
	if (input->GetButtonDown(XINPUT_BUTTON_B)) {
		if (cursor == 0)
		{
			StopSoundFile();
			return eSceneType::eGameMain;
		}
		else if (cursor == 1)
		{
			StopSoundFile();
			return eSceneType::eRanking;
		}
		else if (cursor == 2)
		{
			StopSoundFile();
			return eSceneType::eHelp;
		}
	}
	if (input->GetKeyDown(KEY_INPUT_R))
	{
		StopSoundFile();
		return eSceneType::eGameMain;
	}
	//�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawGraph(0, 0, in_title_image, TRUE);
	// �`�揈��
	SetFontSize(60);
	DrawString((SCREEN_WIDTH / 2) - 190, 150, "Butting Apple", GetColor(255, 255, 255));
	
	
	// �ꎞ�I�Ƀt�H���g�T�C�Y��ύX����
	int old_font_size = GetFontSize();
	SetFontSize(24);

	// ���j���[���ڂ̃��X�g
	const char* menu_items[] = { "START", "RANKING", "HELP", "END" };

	// �l�p�`�̃T�C�Y�ƊԊu�̒�`
	Vector2D box = { 160.0f,80.0f };
	int box_spacing = 3;
	int start_y = (SCREEN_HEIGHT / 2) + 50;

	for (int i = 0; i < 4; i++)
	{
		int y = start_y + i * (box.y + box_spacing) - 100;

		// �I�𒆂̍��ڂ͉��F�A����ȊO�͐�
		int color = (i == cursor) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

		// �l�p�`�̕`��
		DrawBox(box.x, y, box.x * 2, y + box.y, color, FALSE);

		// �e�L�X�g�`��
		DrawFormatString(box.x + 10, y + 7, GetColor(255, 255, 255), menu_items[i]);
	}

	//A�{�^���`��
	DrawCircleAA(145.5f, 670, 12, 12, GetColor(255, 255, 255), FALSE);
	DrawCircleAA(145.5f, 670, 11, 12, GetColor(255, 20, 20), TRUE);
	SetFontSize(16);
	DrawString(170, 665, "����", 0xffffff);
	DrawString(142, 662, "B", 0xffffff);

	//DPad�`��
	DrawDPad();

	// ���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(old_font_size);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

void TitleScene::DrawDPad() const
{
	// �\���L�[�̒��S���W
	int d_pad_x = 240;
	int d_pad_y = 670;
	int d_pad_size = 5;

	// �c�E���̃{�^���̔w�i�i���g�j
	DrawBox(d_pad_x - d_pad_size, d_pad_y - d_pad_size * 3, d_pad_x + d_pad_size, d_pad_y + d_pad_size * 3, GetColor(100, 100, 100), TRUE);
	DrawBox(d_pad_x - d_pad_size * 3, d_pad_y - d_pad_size, d_pad_x + d_pad_size * 3, d_pad_y + d_pad_size, GetColor(100, 100, 100), TRUE);

	// ��{�^���i���j
	DrawTriangle(d_pad_x, d_pad_y - d_pad_size * 2, d_pad_x - d_pad_size, d_pad_y - d_pad_size,  d_pad_x + d_pad_size, d_pad_y - d_pad_size,  GetColor(255, 255, 255), TRUE);

	// ���{�^���i���j
	DrawTriangle(d_pad_x, d_pad_y + d_pad_size * 2,  d_pad_x - d_pad_size, d_pad_y + d_pad_size,  d_pad_x + d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	// ���{�^���i���j
	DrawTriangle(d_pad_x - d_pad_size * 2, d_pad_y,  d_pad_x - d_pad_size, d_pad_y - d_pad_size,  d_pad_x - d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	// �E�{�^���i���j
	DrawTriangle(d_pad_x + d_pad_size * 2, d_pad_y,  d_pad_x + d_pad_size, d_pad_y - d_pad_size,  d_pad_x + d_pad_size, d_pad_y + d_pad_size,  GetColor(255, 255, 255), TRUE);

	DrawString(265, 665, "�ړ�", GetColor(255, 255, 255));
}

#include "TitleScene.h"
#include "DxLib.h"
#include "../../common.h"

TitleScene::TitleScene()://���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : TitleScene() : a()�j
	cursor()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
	cursor = 0;
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
			return eSceneType::eGameMain;
		}
		else if (cursor == 1)
		{
			return eSceneType::eRanking;
		}
		else if (cursor == 2)
		{
			return eSceneType::eHelp;
		}
	}
	//�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	return GetNowSceneType();
}

void TitleScene::Draw() const
{
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
		//DrawBox((SCREEN_WIDTH / 2) - (box.x / 2), y, (SCREEN_WIDTH / 2) + (box.x / 2), y + box.y, color, FALSE);
		DrawBox(box.x, y, box.x * 2, y + box.y, color, FALSE);

		// �e�L�X�g�`��
		DrawFormatString(box.x + 10, y + 7, GetColor(255, 255, 255), menu_items[i]);
	}

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

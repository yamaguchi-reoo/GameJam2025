#include "ResultScene.h"
#include "DxLib.h"
#include <string>
#include <fstream>

ResultScene::ResultScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
	:bgi(),
	result_time()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	LoadData();

	bgi = LoadGraph("Resource/Images/Result_bgi.png");
}

eSceneType ResultScene::Update()
{
	//�X�V����

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	if (input->GetButtonDown(XINPUT_BUTTON_B)) {
		return eSceneType::eInput;
	}

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
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 210, 210), TRUE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgi, TRUE);

	ChangeFontType(DX_FONTTYPE_EDGE);
	int init_font_size = GetFontSize();

	SetFontSize(50);
	//�`�揈��
	DrawString(SCREEN_WIDTH / 2 - 100, 24, "Result", GetColor(255, 255, 255));

	SetFontSize(36);
	DrawString(100, 100, "�c�莞��", 0xffffff);

	SetFontSize(350);
	DrawFormatString(200, 150, GetColor(255, 255, 255), "%d", result_time);

	SetFontSize(36);
	DrawString(600, 420, "�b", 0xffffff);

	SetFontSize(80);
	if (result_time > 30)
	{
		DrawString(700, 500,"��PERFECT��", GetColor(255, 255, 0));
	}
	else if (result_time > 15)
	{
		DrawString(700, 500, "GREAT!!", GetColor(0, 255, 0));
	}
	else if (result_time >= 1)
	{
		DrawString(700, 500, "GOOD", GetColor(255, 0, 0));
	}
	else if (result_time == 0)
	{
		DrawString(700, 500, "DEFEAT", GetColor(0, 0, 255));
	}

	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(init_font_size);
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}

void ResultScene::LoadData()
{
	// �t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/Data/Result.csv���J���܂���ł����B");
	}

	// ����̋L�^���擾
	fscanf_s(fp, "%d,\n", &result_time);

	// �t�@�C���N���[�Y
	fclose(fp);

	if (result_time < 0)
	{
		result_time = 0;
	}
}
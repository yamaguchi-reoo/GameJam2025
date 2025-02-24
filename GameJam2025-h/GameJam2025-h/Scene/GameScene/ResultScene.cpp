#include "ResultScene.h"
#include "DxLib.h"
#include <string>
#include <fstream>

ResultScene::ResultScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : ResultScene() : a()�j
	:result_time()
	/*remain_time()*/
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
	/*for (int i = 0; i <= 5; i++)
	{
		remain_time[i] = 0;
	}*/

	LoadData();
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

	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", result_time);

	if (result_time > 30)
	{
		DrawString(100, 120,"��PERFECT��", GetColor(255, 255, 255));
	}
	else if (result_time > 15)
	{
		DrawString(100, 120, "GOOD!!", GetColor(255, 255, 255));
	}
	else if (result_time >= 1)
	{
		DrawString(100, 120, "NICE", GetColor(255, 255, 255));
	}
	else if (result_time == 0)
	{
		DrawString(100, 120, "DEFEAT", GetColor(255, 255, 255));
	}
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

	//// �t�@�C���I�[�v��
	//FILE* fp = nullptr;
	//errno_t result = fopen_s(&fp, "Resource/Data/TimeData.csv", "r");

	//// �G���[�`�F�b�N
	//if (result != 0)
	//{
	//	throw("Resource/Data/TimeData.csv���J���܂���ł����B");
	//}

	//// ���܂ł̋L�^���擾
	//for (int i = 0; i < 5; i++)
	//{
	//	fscanf_s(fp, "%d,\n", &remain_time[i]);
	//}

	//// �t�@�C���N���[�Y
	//fclose(fp);
}
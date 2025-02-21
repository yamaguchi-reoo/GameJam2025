#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"
#include "../../Object/Enemy/WeekEnemy.h"
#include "../../common.h"

InGameScene::InGameScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : InGameScene() : a()�j
	:time_limit(),
	time_count()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	//�����ŕϐ��̏��������āi��Fa = 0;�j
	CreateObject<Apple>(Vector2D(30.0f, 40.0f), Vector2D(64.0f));
	CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));

	time_count = 0;
	time_limit = 60;
}

eSceneType InGameScene::Update()
{
	//�X�V����
	
	// �������ԍX�V
	time_count++;
	if (time_count > 60)
	{
		time_limit--;
		time_count = 0;
	}

	//���͊Ǘ��N���X�̃C���X�^���X���擾
	InputControl* input = InputControl::GetInstance();

	// �������Ԃ��O�ɂȂ����烊�U���g�ɑJ��
	if (time_limit <= 0)
	{
		return eSceneType::eResult;
	}
	//Z�L�[�������ꂽ��Result�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eGameMain;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{
	__super::Draw();
	//�`�揈��
	DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
	DrawFormatString(620, 24, GetColor(255, 255, 255), "%d", time_limit);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

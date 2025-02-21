#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"
#include "../../Object/Item/ItemBase.h"
#include "../../Object/Enemy/WeekEnemy.h"
#include "../../Object/Player/Player.h"
#include "../../common.h"

#define OBJECT_MAX 10

InGameScene::InGameScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : InGameScene() : a()�j
	:time_limit(),
	time_count(),
	create_time()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	CreateObject<Player>(Vector2D(60.0f, 500.0f), Vector2D(130.0f,200.0f));

	CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));

	// �������Ԑݒ�
	time_count = 0;
	time_limit = 60;

	// �I�u�W�F�N�g�����ݒ�
	create_time = 0;
}

eSceneType InGameScene::Update()
{
	//�X�V����
	
	// �������ԍX�V
	time_count++;
	if (time_count > (int)FRAMERATE)
	{
		time_limit--;
		time_count = 0;
	}

	// �I�u�W�F�N�g�𐶐�����
	create_time++;
	if (create_time >= 30)
	{
		if (create_quantity < OBJECT_MAX)
		{
			CreateObject<ItemBase>(Vector2D(140 * (rand() % 5) + 300, 80), Vector2D(64.0f));
			create_time = 0;
		}
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
	DrawFormatString(300, 24, GetColor(255, 255, 255), "%d", create_quantity);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

void InGameScene::DecQuantity()
{
	create_quantity--;
}

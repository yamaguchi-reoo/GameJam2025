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
	create_span_item(),
	create_span_enemy()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	CreateObject<Player>(Vector2D(290.0f, 520.0f), Vector2D(115.0f,115.0f));

	//CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));

	// �������Ԑݒ�
	time_count = 0;
	time_limit = 60;

	// �I�u�W�F�N�g�����ݒ�
	create_span_item = 0;
	create_span_enemy = 0;
	create_enemy_max = 10;
	create_enemy = true;
	create_boss = false;
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

	// �G�𐶐�����
	if (create_enemy == true)
	{
		if (create_enemy_max > 0)
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(64.0f));
				create_enemy = false;
				create_span_enemy = 0;
			}
		}
		else
		{
			create_boss = true;
		}
	}

	// �A�C�e���𐶐�����
	create_span_item++;
	if (create_span_item >= 30)
	{
		if (create_quantity_item < OBJECT_MAX)
		{
			CreateObject<ItemBase>(Vector2D(140 * (rand() % 5) + 300, 80), Vector2D(95.0f));
		}
		create_span_item = 0;
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
	DrawString(200, 24, "item", GetColor(255, 255, 255));
	DrawFormatString(300, 24, GetColor(255, 255, 255), "%d", create_quantity_item);
	DrawString(200, 34, "enemy", GetColor(255, 255, 255));
	DrawFormatString(300, 34, GetColor(255, 255, 255), "%d", create_enemy_max);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}
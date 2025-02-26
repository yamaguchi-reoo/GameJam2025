#include "InGameScene.h"
#include <DxLib.h>
#include "../../Object/Item/Apple.h"
#include "../../Object/Item/ItemBase.h"
#include "../../Object/Enemy/WeekEnemy.h"
#include "../../Object/Enemy/NomalEnemy.h"
#include "../../Object/Enemy/HardEnemy.h"
#include "../../Object/Enemy/BossEnemy.h"
#include "../../Object/Player/Player.h"
#include "../../common.h"

#include <cmath>

#define OBJECT_MAX 10

InGameScene::InGameScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : InGameScene() : a()�j
	:time_count(),
	create_span_item(),
	create_span_enemy(),
	in_game_image(),
	shake_timer(),
	shake_amount(),
	Fight_BGM()
{
}

InGameScene::~InGameScene()
{ 
}

void InGameScene::Initialize()
{
	CreateObject<Player>(Vector2D(290.0f, 520.0f), Vector2D(115.0f, 115.0f));

	// �������Ԑݒ�
	time_count = 0;
	limit_time = 60;

	// �I�u�W�F�N�g�����ݒ�
	create_span_item = 0;
	create_span_enemy = 0;
	create_enemy_max = 10;
	create_enemy = true;
	create_boss = true;
	is_boss = true;

	in_game_image = LoadGraph("Resource/Images/GameMain04.png");

	shake_timer = 0;
	shake_amount = 0.0f;

	Fight_BGM = LoadSoundMem("Resource/Sounds/MusMus-BGM-172.mp3");

	// ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 * 60 / 100, Fight_BGM);

	PlaySoundMem(Fight_BGM, DX_PLAYTYPE_BACK);
}

eSceneType InGameScene::Update()
{
	//�X�V����

	// �������ԍX�V
	time_count++;
	if (time_count > (int)FRAMERATE)
	{
		limit_time--;
		time_count = 0;
	}

	//���v�̐j�̗h����v�Z**
	if (shake_timer > 0)
	{
		shake_timer--;
		shake_amount *= 0.9f;  // ���X�ɗh�������������
	}

	// �G�𐶐�����
	if (create_enemy == true)
	{
		if (create_enemy_max > 0)
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				if (create_enemy_max >= 7)
				{
					CreateObject<WeekEnemy>(Vector2D(1000.0f, 640.0f), Vector2D(200.0f,142.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
				else if (create_enemy_max >= 3)
				{
					CreateObject<NomalEnemy>(Vector2D(1000.0f, 540.0f), Vector2D(200.0f,223.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
				else if (create_enemy_max >= 1)
				{
					CreateObject<HardEnemy>(Vector2D(1000.0f, 540.0f), Vector2D(200.0f,200.0f));
					create_enemy = false;
					create_span_enemy = 0;
				}
			}
		}
		else
		{
			create_span_enemy++;
			if (create_span_enemy >= 30)
			{
				if (create_boss == true)
				{
					// �Đ����~�߂܂�
					StopSoundMem(Fight_BGM);
					CreateObject<BossEnemy>(Vector2D(1000.0f, 450.0f), Vector2D(200.f,319.f));
					create_boss = false;
					create_span_enemy = 0;
				}
			}
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
	if (limit_time <= 0)
	{
		limit_time = 0;
		WriteData();
		return eSceneType::eResult;
	}
	//Z�L�[�������ꂽ��Result�V�[���֑J��
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		WriteData();
		return eSceneType::eResult;
	}
	// �{�X���|���ꂽ�烊�U���g�ɑJ��
	if (is_boss == false)
	{
		WriteData();
		return eSceneType::eResult;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{

	DrawGraph(0, 0, in_game_image, TRUE);

	// �A�C�e���������[����`�� (���[���̈ʒu�Ƀ{�b�N�X��\��)
	DrawItemGenerationLanes();

	__super::Draw();

	//���v�̕`��
	SetFontSize(30);
	DrawTimer();

	SetFontSize(12);
	//�`�揈��
	//DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
	//DrawFormatString(620, 24, GetColor(255, 255, 255), "%d", limit_time);
	//DrawString(200, 24, "item", GetColor(255, 255, 255));
	//DrawFormatString(300, 24, GetColor(255, 255, 255), "%d", create_quantity_item);
	//DrawString(200, 34, "enemy", GetColor(255, 255, 255));
	//DrawFormatString(300, 34, GetColor(255, 255, 255), "%d", create_enemy_max);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

void InGameScene::DecTime(int dectime)
{
	limit_time = limit_time - dectime;

	//�j��h�炷���߂̒l���Z�b�g
	shake_timer = 60;
	shake_amount = 10.0f;  //�ŏ���10�x���炢�傫���h���
}

void InGameScene::WriteData()
{
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "w");

	if (result != 0)
	{
		throw("Resource/Data/Result.csv���J���܂���\n");
	}

	fprintf(fp, "%d,\n", limit_time);

	fclose(fp);
}

void InGameScene::DrawTimer() const
{
	//���v�̈ʒu�ƃT�C�Y
	int clock_center_x = 1200;  // ���v�̒��S X
	int clock_center_y = 60;  // ���v�̒��S Y
	int clock_radius = 50;     // ���v�̔��a

	//���v�̉~��`��
	DrawCircle(clock_center_x, clock_center_y, clock_radius, GetColor(0, 0, 0), TRUE);
	DrawCircle(clock_center_x, clock_center_y, clock_radius + 1, GetColor(255, 255, 255), FALSE);


	//�b�j�̌v�Z
	float angle = ((float)limit_time / 60.0f) * 360.0f + 90;  // 60�b�ň���i360�x�j
	angle += (shake_timer > 0) ? ((rand() % 5 - 2) * shake_amount) : 0.0f;  // �����_���Ƀu����

	//�p�x�����W�A���ɕϊ�
	float rad = angle * (3.1415926535f / 180.0f);  // �p�x�����W�A���ɕϊ�

	//�b�j�̍��W���v�Z
	int hand_x = clock_center_x + cos(rad) * (clock_radius - 5);
	int hand_y = clock_center_y - sin(rad) * (clock_radius - 5);  // Y���͋t����

	//�b�j��`��
	DrawLine(clock_center_x, clock_center_y, hand_x, hand_y, GetColor(255, 0, 0), 3);

	//�f�W�^�����v�i�A�i���O���v�̉��ɕ\��
	int minutes = limit_time / 60;  // ��
	int seconds = limit_time % 60;  // �b

	//�f�W�^�����v���A�i���O���v�̉��ɕ`��
	DrawFormatString(clock_center_x - 40, clock_center_y + clock_radius + 10, GetColor(255, 255, 255), "%02d:%02d", minutes, seconds);

}

void InGameScene::DrawItemGenerationLanes() const
{
	// �A�C�e���������[�����������߂Ƀ{�b�N�X��`��
	int lane_y = 0;  // Y���W (�S�Ẵ��[���̍����������Őݒ�)
	int lane_height = 450;  // ����
	int lane_spacing = 140; // �e���[���̊Ԋu

	//�����w�i�{�b�N�X�̕`��i�����x��ݒ�j
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(275, lane_y, 285 + (lane_spacing * 5), lane_height, GetColor(0, 0, 0), TRUE);

	for (int i = 0; i < 6; ++i) 
	{
		int lane_x = 285 + i * lane_spacing; // X���W�i�e���[���̉��ʒu�����炷�j
		DrawBox(lane_x - 10, lane_y, lane_x, lane_height, GetColor(255, 255, 255), TRUE); // �u�����h�t���̐F
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �u�����h���[�h��߂�

}

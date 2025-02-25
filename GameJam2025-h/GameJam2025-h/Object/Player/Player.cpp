#include "Player.h"
#include <DxLib.h>
#include "../../Utility/InputControl.h"
#include "../Item/ItemBase.h"
#include "../../Scene/GameScene/InGameScene.h"
#include "../../Scene/SceneManager.h"
#include <algorithm>
#include <iostream>

#define MOVEMENT 92.0f + 47.5f


Player::Player() :
	move_count(),
	is_attack(),
	attack_timer(),
	is_power(),
	power_time(),
	cool_time(),
	hit_se(),
	miss_se(),
	is_hit(),
	explosion_se(),
	power_se()
{

}

Player::~Player()
{
}

void Player::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);

	move_count = 0;
	is_attack = false;
	attack_timer = 0;
	cool_time = 0;

	is_hit = false;

	/*player_pos = { 160.0f,500.0f };
	player_box = { 130.0f,200.0f };*/

	player_pos = { _location.x - 130.0f,_location.y - 20.0f };
	player_box = { _box_size.x + 15.0f,_box_size.y + 85.0f};

	is_power = false; 
	image = LoadGraph("Resource/Images/image.png");

	hit_se = LoadSoundMem("Resource/Sounds/�ؐ��o�b�g�őł�1.mp3");
	miss_se = LoadSoundMem("Resource/Sounds/se_swing13-1.mp3");

	explosion_se = LoadSoundMem("Resource/Sounds/se_explode_zun.mp3");
}

void Player::Update()
{
	__super::Update();

	//�ړ�����
	Movement();

	//�U������
	Attack();

	//�������
	if (is_power)
	{
		power_time++;
		if (power_time > 60 * 10)
		{
			is_power = false;
			power_time = 0;
		}
	}

	//�N�[���^�C�����͉摜�ύX
	if (cool_time <= 0)
	{
		image = LoadGraph("Resource/Images/image.png");
	}
	else
	{
		image = LoadGraph("Resource/Images/image(3).png");
	}


	//���ʒ���
	ChangeVolumeSoundMem(150, hit_se);
	ChangeVolumeSoundMem(150, explosion_se);
}

void Player::Draw() const
{
	//__super::Draw();
	//DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "%d", is_attack ? "false","true"));
	DrawGraph(player_pos.x, player_pos.y-15, image, TRUE);

	//�f�o�b�O�\��
#ifdef _DEBUG
	DrawFormatString((int)location.x, (int)location.y + 12, GetColor(255, 255, 255), !is_attack ? "false" : "true");
	DrawFormatString((int)location.x, (int)location.y + 24, GetColor(255, 255, 255), "%f", location.x);
	DrawFormatString((int)location.x, (int)location.y + 36, GetColor(255, 255, 255), "%f", location.y);
	DrawFormatString((int)location.x, (int)location.y + 48, GetColor(255, 255, 255), "%f", location.x + box_size.x);
	DrawFormatString((int)location.x, (int)location.y + 60, GetColor(255, 255, 255), "%f", location.y + box_size.y);

	//�v���C���[�`��	
	//DrawBoxAA(player_pos.x, player_pos.y, player_pos.x + player_box.x, player_pos.y + player_box.y, GetColor(255, 255, 255), FALSE);
	DrawFormatString(player_pos.x, player_pos.y, GetColor(255, 255, 255), "%f", player_pos.x);
	DrawFormatString(player_pos.x, player_pos.y + 12, GetColor(255, 255, 255), "%d", power_time);
	DrawFormatString(player_pos.x, player_pos.y + 24, GetColor(255, 255, 255), "%d", cool_time);

	//�Փ˔͈͂̐ݒ�
	float left = location.x;
	float right = location.x + box_size.x;
	float top = location.y;
	float bottom = location.y + box_size.y;
	DrawBoxAA(left, top, right, bottom, GetColor(0, 255, 255), FALSE);
#endif // 

	
	//�o�b�g�̍U���͈͂�`��
	DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 60, 50, GetColor(0, 0, 255), FALSE);
	DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 55, 50, GetColor(0, 0, 255), FALSE);

}

void Player::Finalize()
{
}

void Player::OnHitCollision(ObjectBase* hit_object)
{
	//�A�C�e���ƏՓ˂��A�U�����̏ꍇ
	if (hit_object->GetObjectType() == eItem && is_attack)
	{
		//dynamic_cast��ItemBase�^�ɕύX
		ItemBase* item = dynamic_cast<ItemBase*>(hit_object);
		if (!item) return;


		//�Փ˔͈͂̐ݒ�
		Vector2D my_location = location;
		Vector2D my_size = location + box_size;;

		//�A�C�e���͈͎̔擾
		Vector2D item_location = hit_object->GetLocation();
		Vector2D item_size = hit_object->GetLocation() + hit_object->GetBoxSize();

		//�A�C�e�����͈͓��ɂ��邩����
		if (item_location.x >= my_location.x && item_size.x <= my_size.x &&
			item_location.y >= my_location.y && item_size.y <= my_size.y)
		{
			is_hit = true;
			//���e��ł�
			if (item->GetItemType() == eBomb && !is_power)
			{
				//GameMain�擾
				SceneManager* manager = SceneManager::GetInstance();
				InGameScene* in_game = manager->GetGameMainScene();

				
				//�����I�I�I�I�I
				item->SetImage("Resource/Images/BombAfter.png");
				item->SetVelocity({ 0.0f, 0.0f });
				PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK);
				//Object�폜
				if (attack_timer <= 1) {
					//�������Ԃ�����
					in_game->DecTime(10);

					hit_object->SetDeleteFlg();
				}
			}
			//�����A�C�e����ł�
			else if (item->GetItemType() == ePowerup)
			{
				is_power = true;
				hit_object->SetDeleteFlg();
			}
			else 
			{
				PlaySoundMem(hit_se, DX_PLAYTYPE_BACK);
				// Item���΂�����
				item->BlowAway({ 30.0f, -10.0f });
				//������Ԃ̂Ƃ�
				if (is_power)
				{
					//�A�C�e���̃_���[�W�A�b�v
					item->DamageUp();
				}
			}
		}
	}
}

void Player::Movement()
{
	InputControl* input = InputControl::GetInstance();

	//�\���L�[�i�E�j�ŉE�ړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move_count++;
		//PlaySoundFile("Resource/Sounds/Hit08-1.mp3", DX_PLAYTYPE_BACK);
		if (move_count > 4)
		{
			move_count = 4;
			//�ړ��ł��Ȃ��悤�Ɉړ���0.0f��
			velocity = 0.0f;
		}

	}
	//�\���L�[�i���j�ō��ړ�
	else if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		move_count--;
		//PlaySound("Resource/Sounds/Hit08-1.mp3", DX_PLAYTYPE_NORMAL);
		if (move_count < 0)
		{
			move_count = 0;
			//�ړ��ł��Ȃ��悤�Ɉړ���0.0f��
			velocity = 0.0f;

			//PlaySound("Resource/Sounds/Hit08-1.mp3", DX_PLAYTYPE_NORMAL);
		}
	}

	location.x = (139.5f * move_count) + 290.0f;
	player_pos.x = (139.5f * move_count) + 160.0f;

}

void Player::Attack()
{
	InputControl* input = InputControl::GetInstance();

	if (cool_time > 0)
	{
		cool_time--;
		return;
	}

	//�U���{�^���iB�{�^���j�������ꂽ��U���J�n
	if (input->GetButtonDown(XINPUT_BUTTON_B) && !is_attack)
	{
		is_attack = true;
		attack_timer = 5;

	}

	//�U�����Ȃ�^�C�}�[������
	if (is_attack)
	{
		attack_timer--;
		if (attack_timer <= 0)
		{
			if (!is_hit)
			{
				PlaySoundMem(miss_se, DX_PLAYTYPE_BACK);

			}
			is_attack = false;
			is_hit = false;
			cool_time = 20;
		}
	}

}

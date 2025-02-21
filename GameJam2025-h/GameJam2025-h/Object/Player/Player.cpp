#include "Player.h"
#include <DxLib.h>
#include "../../Utility/InputControl.h"

#include <algorithm>
#include <iostream>

Player::Player():
	move_count()
{

}

Player::~Player()
{
}

void Player::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
}

void Player::Update()
{
	__super::Update();

	//�ړ�����
	Movement();

}

void Player::Draw() const
{
	__super::Draw();
}

void Player::Finalize()
{
}

void Player::OnHitCollision(ObjectBase* hit_object)
{
}

void Player::Movement()
{
	InputControl* input = InputControl::GetInstance();

	//�\���L�[�i�E�j�ŉE�ړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		/*velocity.x = 300.0f;
		location.x += velocity.x;*/
		move_count++;
		if (move_count > 4)
		{
			move_count = 4;
		}
	}
	//�\���L�[�i���j�ō��ړ�
	else if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		/*velocity.x = 300.0f;
		location.x -= velocity.x;*/
		move_count--;
		if (move_count < 0)
		{
			move_count = 0;
		}
	}
	location.x = (120.0f * move_count) + 60.0f;
}

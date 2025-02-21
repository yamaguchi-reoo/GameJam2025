#include "Player.h"
#include <DxLib.h>
#include "../../Utility/InputControl.h"

#include <algorithm>
#include <iostream>

Player::Player():
	move_count(),
	is_attack(),
	attack_timer()
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
}

void Player::Update()
{
	__super::Update();

	//移動処理
	Movement();

	Attack();

}

void Player::Draw() const
{
	__super::Draw();
	//DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "%d", is_attack ? "false","true"));

	DrawFormatString(location.x, location.y + 12 , GetColor(255, 255, 255), !is_attack ? "false" : "true");
	if (is_attack)
	{
		DrawBox(location.x + box_size.x, location.y + box_size.y, location.x + box_size.x + 98, location.y + box_size.y - 98, GetColor(255, 255, 255), FALSE);
	}
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

	//十字キー（右）で右移動
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
	//十字キー（左）で左移動
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

void Player::Attack()
{
	InputControl* input = InputControl::GetInstance();

	if (input->GetButtonDown(XINPUT_BUTTON_B))
	{
		is_attack = true;
		attack_timer = 10;
	}

	if (is_attack)
	{
		attack_timer--;
		if (attack_timer <= 0)
		{
			is_attack = false;
		}
	}

}

#include "Player.h"
#include <DxLib.h>
#include "../../Utility/InputControl.h"

#include <algorithm>
#include <iostream>

Player::Player()
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

	//移動処理
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

	//十字キー（右）で右移動
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity.x = 300.0f;
		location.x += velocity.x;

	}
	//十字キー（左）で左移動
	else if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x = 300.0f;
		location.x -= velocity.x;
	}




}

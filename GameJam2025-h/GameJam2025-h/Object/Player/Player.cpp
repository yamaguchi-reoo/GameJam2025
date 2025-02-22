#include "Player.h"
#include <DxLib.h>
#include "../../Utility/InputControl.h"
#include "../Item/ItemBase.h"

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

	player_pos = { 60.0f,500.0f };
	player_box = { 130.0f,200.0f };
}

void Player::Update()
{
	__super::Update();

	//移動処理
	Movement();

	//攻撃処理
	Attack();

}

void Player::Draw() const
{
	//__super::Draw();
	//DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "%d", is_attack ? "false","true"));

	//デバッグ表示
	DrawFormatString((int)location.x, (int)location.y + 12 , GetColor(255, 255, 255), !is_attack ? "false" : "true");
	DrawFormatString((int)location.x, (int)location.y + 24, GetColor(255, 255, 255), "%f", location.x);
	DrawFormatString((int)location.x, (int)location.y + 36, GetColor(255, 255, 255), "%f", location.y);
	DrawFormatString((int)location.x, (int)location.y + 48, GetColor(255, 255, 255), "%f", location.x + box_size.x);
	DrawFormatString((int)location.x, (int)location.y + 60, GetColor(255, 255, 255), "%f", location.y + box_size.y);
	//プレイヤー描画	
	DrawBoxAA(player_pos.x, player_pos.y, player_pos.x + player_box.x, player_pos.y + player_box.y, GetColor(255, 255, 255), FALSE);

	//バットの攻撃範囲を描画
	if (!is_attack) 
	{
		DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 65, 50, GetColor(255, 255, 255), FALSE);
		DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 60, 50, GetColor(255, 255, 255), FALSE);
	}
	else
	{
		DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 65, 50, GetColor(0, 0, 255), FALSE);
		DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 60, 50, GetColor(0, 0, 255), FALSE);
	}

	//衝突範囲の設定
	float left = location.x;
	float right = location.x + box_size.x;
	float top = location.y;
	float bottom = location.y + box_size.y;
	DrawBoxAA(left, top, right, bottom, GetColor(0, 255, 255), FALSE);
}

void Player::Finalize()
{
}

void Player::OnHitCollision(ObjectBase* hit_object)
{
	//アイテムと衝突し、攻撃中の場合
	if (hit_object->GetObjectType() == eItem && is_attack)
	{
		//dynamic_castでItemBase型に変更
		ItemBase* item = dynamic_cast<ItemBase*>(hit_object);


		//衝突範囲の設定
		Vector2D my_location = location;
		Vector2D my_size = location + box_size;;

		//アイテムの範囲取得
		Vector2D item_location = hit_object->GetLocation();
		Vector2D item_size = hit_object->GetLocation()+ hit_object->GetBoxSize();

		//アイテムが範囲内にあるか判定
		if (item_location.x >= my_location.x && item_size.x <= my_size.x &&
			item_location.y >= my_location.y && item_size.y <= my_size.y)
		{
			// Itemを飛ばす処理
			item->BlowAway({ 30.0f, -10.0f });
		}
	}
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

	//移動位置の更新
	location.x = (120.0f * move_count) + 190.0f;
	player_pos.x = (120.0f * move_count) + 60.0f;

}

void Player::Attack()
{
	InputControl* input = InputControl::GetInstance();

	//攻撃ボタン（Bボタン）が押されたら攻撃開始
	if (input->GetButtonDown(XINPUT_BUTTON_B))
	{
		is_attack = true;
		attack_timer = 10;
	}

	//攻撃中ならタイマーを減少
	if (is_attack)
	{
		attack_timer--;
		if (attack_timer <= 0)
		{
			is_attack = false;
		}
	}

}

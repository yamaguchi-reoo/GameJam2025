#include "ItemBase.h"
#include <DxLib.h>
#include "../Player/Player.h"

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
	object_type = eItem;

	//アイテムをスポーン
	ItemSpawn();
}

void ItemBase::Update()
{
	__super::Update();

	//画面外に出たら削除
	if (location.y > SCREEN_HEIGHT + box_size.y)
	{
		//Object削除
		this->SetDeleteFlg();
	}

	//落下
	location.y += velocity.y;
	location.x += velocity.x;

	// 空気抵抗的な減速処理
	if (is_blowing)
	{
		velocity.x *= 0.98f;
		velocity.y += 0.5f; // 重力で落下
	}

	// 一定の速度以下になったら通常状態に戻す
	if (fabs(velocity.x) < 0.5f && fabs(velocity.y) < 0.5f)
	{
		is_blowing = false;
	}

	if (animation_time > 0)
	{
		animation_time--;
		image = LoadGraph("Resource/Images/BombAfter.png");
		if (animation_time < 0)
		{
			animation_time = 0;
		}
	}
	
}

void ItemBase::Draw() const
{
	__super::Draw();
	switch (item_type)
	{
	case eApple:
		DrawFormatString(location.x, location.y + 12, color, "type: apple");
		DrawFormatString(location.x, location.y + 24, color, "damage: %d", damage);
		break;
	case eRock:
		DrawFormatString(location.x, location.y + 12, color, "type: rock");
		DrawFormatString(location.x, location.y + 24, color, "damage: %d", damage);
		break;
	case eBomb:
		DrawFormatString(location.x, location.y + 12, color, "type: bomb");
		DrawFormatString(location.x, location.y + 24, color, "damage: %d", damage);
		break;
	case eHeal:
		DrawFormatString(location.x, location.y + 12, color, "type: heal");
		DrawFormatString(location.x, location.y + 24, color, "damage: %d", damage);
		break;
	case ePowerup:
		DrawFormatString(location.x, location.y + 12, color, "type: power");
		DrawFormatString(location.x, location.y + 24, color, "damage: %d", damage);
		break;
	default:
		break;
	}

	DrawGraph(location.x + offset.x, location.y + offset.y, image, TRUE);

	//DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 50.0f, 50, GetColor(0, 255, 0), TRUE);
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(ObjectBase* hit_object)
{
	if (hit_object->GetObjectType() == eEnemy || hit_object->GetObjectType() == eBoss)
	{
		//Object削除
		this->SetDeleteFlg();

		//当たったObjectにダメージを与える
		hit_object->ApplyDamage(damage);
	}

	if (hit_object->GetObjectType() == ePlayer && this->GetItemType() == eBomb)
	{

	}
}

void ItemBase::ItemSpawn()
{
	//velocity = 落ちてくる速度
	//damage = 与えるダメージ
	//offset = 画像のずらし
	//image = 画像
	switch (ItemRand())
	{
	case eApple:
		velocity.y = 1.5f;
		damage = 1;
		color = GetColor(255, 0, 0);
		offset = { 5.0f, -5.0f };
		image = LoadGraph("Resource/Images/Apple.png");
		break;
	case eRock:
		velocity.y = 2.5f;
		damage = 2;
		color = GetColor(0, 0, 255);
		offset = { -4.0f,6.0f };
		image = LoadGraph("Resource/Images/Rock.png");
		break;
	case eBomb:
		velocity.y = 2.0f;
		damage = 3;
		color = GetColor(255, 255, 0);
		offset = { 7.0f,0.0f };
		image = LoadGraph("Resource/Images/Bomb.png");
		break;
	case eHeal:
		velocity.y = 2.0f;
		damage = -5;
		color = GetColor(0, 255, 0);
		offset = { 11.5f,2.0f };
		image = LoadGraph("Resource/Images/Heal.png");
		break;
	case ePowerup:
		velocity.y = 3.5f;
		damage = 0;
		color = GetColor(255, 0, 255);
		offset = { 11.5f,2.0f };
		image = LoadGraph("Resource/Images/PowerUp.png");
		break;
	default:
		break;
	}
}

int ItemBase::ItemRand()
{
	//ランダムな値（0 ～ 99）を入れる
	int rand = GetRand(99);

	// りんご (40%)
	if (rand >= 0 && rand <= 39)
	{
		SetItemType(eApple);
		return GetItemType();
	}
	// 岩 (25%)
	else if (rand > 39 && rand <= 64)
	{
		SetItemType(eRock);
		return GetItemType();
	}
	// 爆弾 (20%)
	else if (rand > 64 && rand <= 84)
	{
		SetItemType(eBomb);
		return GetItemType();
	}
	// 回復アイテム (8%)
	else if (rand > 84 && rand <= 92)
	{
		SetItemType(eHeal);
		return GetItemType();
	}
	// パワーアップ (7%)
	else if (rand > 91 && rand <= 99)
	{
		SetItemType(ePowerup);
		return GetItemType();
	}

	return 0;
}

void ItemBase::BlowAway(Vector2D _force)
{
	velocity = _force;
	is_blowing = true;
}

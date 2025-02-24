#include "ItemBase.h"
#include <DxLib.h>

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

	//DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 50.0f, 50, GetColor(0, 255, 0), TRUE);
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(ObjectBase* hit_object)
{
	if (hit_object->GetObjectType() == eEnemy)
	{
		//Object削除
		this->SetDeleteFlg();

		//当たったObjectにダメージを与える
		hit_object->ApplyDamage(damage);
	}
}

void ItemBase::ItemSpawn()
{
	switch (ItemRand())
	{
	case eApple:
		velocity.y = 1.5f;
		damage = 1;
		color = GetColor(255, 0, 0);
		break;
	case eRock:
		velocity.y = 2.5f;
		damage = 2;
		color = GetColor(0, 0, 255);
		break;
	case eBomb:
		velocity.y = 2.0f;
		damage = 2;
		color = GetColor(255, 255, 0);
		break;
	case eHeal:
		velocity.y = 2.0f;
		damage = -5;
		color = GetColor(0, 255, 0);
		break;
	case ePowerup:
		velocity.y = 3.5f;
		damage = 0;
		color = GetColor(255, 0, 255);
		break;
	default:
		break;
	}
}

int ItemBase::ItemRand()
{
	//ランダムな値（0 ～ 9）を入れる
	//int rand = GetRand(9);
	int rand = GetRand(99);

	// りんご (40%)
	if (rand >= 0 && rand <= 39)
	{
		SetItemType(eApple);
		return GetItemType();
	}
	// 岩 (30%)
	else if (rand > 39 && rand <= 69)
	{
		SetItemType(eRock);
		return GetItemType();
	}
	// 爆弾 (15%)
	else if (rand > 69 && rand <= 84)
	{
		SetItemType(eBomb);
		return GetItemType();
	}
	// 回復アイテム (7%)
	else if (rand > 84 && rand <= 91)
	{
		SetItemType(eHeal);
		return GetItemType();
	}
	// パワーアップ (7%)
	else
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

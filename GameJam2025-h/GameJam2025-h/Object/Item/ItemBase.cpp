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
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "type: apple");
		DrawFormatString(location.x, location.y + 24, GetColor(255, 255, 255), "damage: %d", damage);
		break;
	case eRock:
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "type: rock");
		DrawFormatString(location.x, location.y + 24, GetColor(255, 255, 255), "damage: %d", damage);

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
		velocity.y = 1.0f;
		damage = 1;
		break;
	case eRock:
		velocity.y = 2.0f;
		damage = 2;
		break;
	default:
		break;
	}
}

int ItemBase::ItemRand()
{
	//ランダムな値（0 ～ 9）を入れる
	int rand = GetRand(9);

	//りんご
	if (rand >= 0 && rand <= 5)
	{
		SetItemType(eApple);
		return GetItemType();
	}
	//岩
	else if (rand > 5 && rand <= 10)
	{
		SetItemType(eRock);
		return GetItemType();
	}

	return 0;
}

void ItemBase::BlowAway(Vector2D _force)
{
	velocity = _force;
	is_blowing = true;
}

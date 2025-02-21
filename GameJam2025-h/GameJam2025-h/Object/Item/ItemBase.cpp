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
}

void ItemBase::Draw() const
{
	__super::Draw();
	switch (item_type)
	{
	case eApple:
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "apple");
		break;
	case eRock:
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "rock");
		break;
	default:
		break;
	}
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
	//ランダムな値（0 〜 9）を入れる
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

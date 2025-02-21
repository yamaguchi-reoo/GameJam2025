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
	__super::Initialize(location, _box_size);
	object_type = eItem;
}

void ItemBase::Update()
{
	__super::Update();

	//‰æ–ÊŠO‚Éo‚½‚çíœ
	if (location.y > SCREEN_HEIGHT + box_size.y)
	{
		this->SetDeleteFlg();
	}
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
}

void ItemBase::ItemSpawn()
{
	/*switch (ItemRand())
	{
	case eApple:
		break;
	case eRock:
		break;
	default:
		break;
	}*/
}

int ItemBase::ItemRand()
{
	int rand = GetRand(9);

	if (rand >= 0 && rand <= 5)
	{
		SetItemType(eApple);
		return GetItemType();
	}
	else if (rand > 5 && rand <= 10)
	{
		SetItemType(eRock);
		return GetItemType();
	}

	return 0;
}

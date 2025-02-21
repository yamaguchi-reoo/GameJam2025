#include "Item.h"
#include <DxLib.h>

Item::Item()
{
}

Item::~Item()
{
}

void Item::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);

	//タイプ追加
	item_type = {};

	//速度代入
	velocity.y = 0.0f;
}

void Item::Update()
{
	__super::Update();
}

void Item::Draw() const
{
	__super::Draw();
	
}

void Item::Finalize()
{
}

void Item::OnHitCollision(ObjectBase* hit_object)
{
}

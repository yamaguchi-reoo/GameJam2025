#include "ItemBase.h"

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
}

void ItemBase::Draw() const
{
	__super::Draw();
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(ObjectBase* hit_object)
{
}

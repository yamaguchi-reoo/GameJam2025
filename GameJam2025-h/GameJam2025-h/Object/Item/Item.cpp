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

	//�^�C�v�ǉ�
	item_type = {};

	//���x���
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

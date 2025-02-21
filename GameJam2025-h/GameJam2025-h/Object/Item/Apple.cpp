#include "Apple.h"
#include <DxLib.h>

#define DROP_SPEED 1.5f

Apple::Apple()
{
}

Apple::~Apple()
{
}

void Apple::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);

	//�^�C�v�ǉ�
	item_type = eApple;

	//���x���
	velocity.y = DROP_SPEED;

}

void Apple::Update()
{
	__super::Update();
	//���x���Z
	location.y += velocity.y;
}

void Apple::Draw() const
{
	__super::Draw();
}

void Apple::Finalize()
{
}

void Apple::OnHitCollision(ObjectBase* hit_object)
{
}

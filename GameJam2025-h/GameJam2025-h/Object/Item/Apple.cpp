#include "Apple.h"

Apple::Apple()
{
}

Apple::~Apple()
{
}

void Apple::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);
}

void Apple::Update()
{
	__super::Update();

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

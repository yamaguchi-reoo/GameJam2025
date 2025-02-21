#include "WeekEnemy.h"
#include <DxLib.h>

WeekEnemy::WeekEnemy()
{
}

WeekEnemy::~WeekEnemy()
{
}

void WeekEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);
}

void WeekEnemy::Update()
{
	__super::Update();
}

void WeekEnemy::Draw() const
{
	__super::Draw();
}

void WeekEnemy::Finalize()
{
}

void WeekEnemy::OnHitCollision(ObjectBase* hit_object)
{
}

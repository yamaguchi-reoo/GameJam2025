#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);
	object_type = eEnemy;
}

void EnemyBase::Update()
{
	__super::Update();
}

void EnemyBase::Draw() const
{
	__super::Draw();
}

void EnemyBase::Finalize()
{
}

void EnemyBase::OnHitCollision(ObjectBase* hit_object)
{
}

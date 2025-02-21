#include "WeekEnemy.h"
#include <DxLib.h>

WeekEnemy::WeekEnemy()
{
	Hp = 3;
}

WeekEnemy::~WeekEnemy()
{
}

void WeekEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);
	location.x -= 500;
}

void WeekEnemy::Update()
{
	__super::Update();
}

void WeekEnemy::Draw() const
{
	__super::Draw();
	DrawBox(location.x+90,location.y+30,location.x + 90 + Hp*20,location.y+50,GetColor(255,255,255),true);
}

void WeekEnemy::Finalize()
{
}

void WeekEnemy::OnHitCollision(ObjectBase* hit_object)
{
	Hp -= 1;
	
	if (Hp == 0)
	{
		delete_flg = true;
	}
}

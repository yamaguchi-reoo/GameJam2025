#include "WeekEnemy.h"
#include <DxLib.h>

WeekEnemy::WeekEnemy()
{
	//初期値は1
	EnemyChange = 1;
}

WeekEnemy::~WeekEnemy()
{
}

void WeekEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);

	//ランダムに敵の見た目を変える
	EnemyChange = GetRand(3);

	if (EnemyChange == 0)
	{
		image = LoadGraph("Resource/Images/slime_purple_re.png");
	}
	else if (EnemyChange == 1)
	{
		image = LoadGraph("Resource/Images/teki.png");
		box_size.x = 200.0f;
		box_size.y = 246.0f;
	}
	else if (EnemyChange == 2)
	{
		image = LoadGraph("Resource/Images/zombi.png");
		box_size.x = 150.0f;
		box_size.y = 184.0f;
	}
	else if (EnemyChange == 3)
	{
		image = LoadGraph("Resource/Images/skeleton.png");
		box_size.x = 200.0f;
		box_size.y = 210.0f;
	}
	location.y -= 200;

	hp = 1;
}

void WeekEnemy::Update()
{
	__super::Update();
}

void WeekEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image,TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y -20, location.x + 90 + hp * 80, location.y - 40, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void WeekEnemy::Finalize()
{
}

void WeekEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
	__super::OnHitCollision(hit_object);
}

#include "NomalEnemy.h"
#include <DxLib.h>

NomalEnemy::NomalEnemy()
{
	//初期値は1
	EnemyChange = 1;
}

NomalEnemy::~NomalEnemy()
{
}

void NomalEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);

	//ランダムに敵の見た目を変える
	EnemyChange = GetRand(3);

	if (EnemyChange == 0)
	{
		image = LoadGraph("Resource/Images/elf_man.png");
	}
	else if (EnemyChange == 1)
	{
		image = LoadGraph("Resource/Images/uranaishi.png");
		box_size.x = 180.0f;
		box_size.y = 221.0f;
	}
	else if (EnemyChange == 2)
	{
		image = LoadGraph("Resource/Images/mummy.png");
		box_size.x = 170.0f;
		box_size.y = 209.0f;
	}
	else if (EnemyChange == 3)
	{
		image = LoadGraph("Resource/Images/devil.png");
		box_size.x = 200.0f;
		box_size.y = 200.0f;
	}
	location.y -= 100;

	hp = 2;
}

void NomalEnemy::Update()
{
	__super::Update();
}

void NomalEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image, TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y - 20, location.x + 90 + hp * 40, location.y - 40, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void NomalEnemy::Finalize()
{
}

void NomalEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
	__super::OnHitCollision(hit_object);
}

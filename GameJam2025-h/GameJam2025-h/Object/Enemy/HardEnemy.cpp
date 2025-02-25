#include "HardEnemy.h"
#include <DxLib.h>

HardEnemy::HardEnemy()
{
	//初期値は1
	EnemyChange = 1;
}

HardEnemy::~HardEnemy()
{
}

void HardEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);

	//ランダムに敵の見た目を変える
	EnemyChange = GetRand(1);

	if (EnemyChange == 0)
	{
		image = LoadGraph("Resource/Images/akuma.png");
	}
	else if (EnemyChange == 1)
	{
		image = LoadGraph("Resource/Images/shinigami.png");
		box_size.x = 212.0f;
		box_size.y = 200.0f;
	}
	location.y -= 100;

	hp = 8;
}

void HardEnemy::Update()
{
	__super::Update();

	//hpが0になったら
	if (hp <= 0)
	{
		//削除
		this->SetDeleteFlg();
	}
}

void HardEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image, TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 5, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void HardEnemy::Finalize()
{
}

void HardEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
}

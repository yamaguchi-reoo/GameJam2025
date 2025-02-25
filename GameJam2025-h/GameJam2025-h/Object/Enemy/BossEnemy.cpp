#include "BossEnemy.h"
#include <DxLib.h>

BossEnemy::BossEnemy()
{

}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
	object_type = eBoss;
	image = LoadGraph("Resource/Images/monster_mao.png");
	location.y -= 100;

	hp = 20;
}

void BossEnemy::Update()
{
	__super::Update();

	//hpが0になったら
	if (hp <= 0)
	{
		//削除
		this->SetDeleteFlg();
	}
}

void BossEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image, TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y - 20, location.x + 90 + hp * 4, location.y - 40, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void BossEnemy::Finalize()
{
}

void BossEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
	__super::OnHitCollision(hit_object);
}

#include "NomalEnemy.h"
#include <DxLib.h>

NomalEnemy::NomalEnemy()
{

}

NomalEnemy::~NomalEnemy()
{
}

void NomalEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
	location.x -= 500;

	hp = 5;
}

void NomalEnemy::Update()
{
	__super::Update();

	//hpが0になったら
	if (hp <= 0)
	{
		//削除
		this->SetDeleteFlg();
	}
}

void NomalEnemy::Draw() const
{
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 8, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void NomalEnemy::Finalize()
{
}

void NomalEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
}

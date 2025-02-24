#include "HardEnemy.h"
#include <DxLib.h>

HardEnemy::HardEnemy()
{

}

HardEnemy::~HardEnemy()
{
}

void HardEnemy::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
	location.x -= 500;

	hp = 9;
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
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 20, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void HardEnemy::Finalize()
{
}

void HardEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
}

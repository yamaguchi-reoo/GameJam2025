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
	__super::Initialize(_location, _box_size);
	image = LoadGraph("Resource/Images/slime_purple_re.png");
	location.y -= 100;

	hp = 2;
}

void WeekEnemy::Update()
{
	__super::Update();

	//hpが0になったら
	if (hp <= 0)
	{
		//削除
		this->SetDeleteFlg();
	}
}

void WeekEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image,TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 20, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void WeekEnemy::Finalize()
{
}

void WeekEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//エネミーにダメージを与える処理はItem側やっておきます
}

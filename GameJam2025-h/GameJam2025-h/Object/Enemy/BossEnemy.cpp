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
	location.x -= 500;

	hp = 20;
}

void BossEnemy::Update()
{
	__super::Update();

	//hp��0�ɂȂ�����
	if (hp <= 0)
	{
		//�폜
		this->SetDeleteFlg();
	}
}

void BossEnemy::Draw() const
{
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 20, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void BossEnemy::Finalize()
{
}

void BossEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//�G�l�~�[�Ƀ_���[�W��^���鏈����Item������Ă����܂�
}

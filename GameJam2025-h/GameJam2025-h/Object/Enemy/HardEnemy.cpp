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
	image = LoadGraph("Resource/Images/akuma.png");
	location.y -= 100;

	hp = 8;
}

void HardEnemy::Update()
{
	__super::Update();

	//hp��0�ɂȂ�����
	if (hp <= 0)
	{
		//�폜
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
	//�G�l�~�[�Ƀ_���[�W��^���鏈����Item������Ă����܂�
}

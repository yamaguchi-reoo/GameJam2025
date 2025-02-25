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
	image = LoadGraph("Resource/Images/elf_man.png");
	location.y -= 100;

	hp = 5;
}

void NomalEnemy::Update()
{
	__super::Update();

	//hp��0�ɂȂ�����
	if (hp <= 0)
	{
		//�폜
		this->SetDeleteFlg();
	}
}

void NomalEnemy::Draw() const
{
	DrawGraph(location.x, location.y, image, TRUE);
	__super::Draw();
	DrawBox(location.x + 90, location.y + 30, location.x + 90 + hp * 8, location.y + 50, GetColor(255, 255, 255), true);
	DrawFormatString(location.x, location.y + 20, GetColor(255, 255, 255), "%d", hp);
}

void NomalEnemy::Finalize()
{
}

void NomalEnemy::OnHitCollision(ObjectBase* hit_object)
{
	//�G�l�~�[�Ƀ_���[�W��^���鏈����Item������Ă����܂�
}

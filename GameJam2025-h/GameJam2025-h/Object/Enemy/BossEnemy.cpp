#include "BossEnemy.h"
#include <DxLib.h>

BossEnemy::BossEnemy():BossSound()
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

	BossSound = LoadSoundMem("Resource/Sounds/MusMus-BGM-171.mp3�{�X�P.mp3");
	// �ǂ݂��񂾉����o�b�N�O���E���h�Đ����܂�(�wPlaySoundMem�x�֐��g�p)

	 // ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 * 60 / 100, BossSound);

	PlaySoundMem(BossSound, DX_PLAYTYPE_BACK);
}

void BossEnemy::Update()
{
	//hp��0�ɂȂ�����
	if (hp <= 0)
	{
		// �Đ����~�߂܂�
		StopSoundMem(BossSound);
	}
	__super::Update();
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
	//�G�l�~�[�Ƀ_���[�W��^���鏈����Item������Ă����܂�
	__super::OnHitCollision(hit_object);
}

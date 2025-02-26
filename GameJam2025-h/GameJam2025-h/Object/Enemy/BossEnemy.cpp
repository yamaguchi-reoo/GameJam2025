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

	BossSound = LoadSoundMem("Resource/Sounds/MusMus-BGM-171.mp3ボス１.mp3");
	// 読みこんだ音をバックグラウンド再生します(『PlaySoundMem』関数使用)

	 // 音量の設定
	ChangeVolumeSoundMem(255 * 60 / 100, BossSound);

	PlaySoundMem(BossSound, DX_PLAYTYPE_BACK);
}

void BossEnemy::Update()
{
	//hpが0になったら
	if (hp <= 0)
	{
		// 再生を止めます
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
	//エネミーにダメージを与える処理はItem側やっておきます
	__super::OnHitCollision(hit_object);
}

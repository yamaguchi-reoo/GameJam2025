#include "EnemyBase.h"
#include "DxLib.h"

EnemyBase::EnemyBase() :DamageSound(0)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);

	/*DamageSound = LoadSoundMem("Resource/Sounds/Hit08-1.mp3");

	if (LoadSoundMem("Resource/Sounds/Hit08-1.mp3") == -1)
	{
		throw ("音声ファイルが開けません");
	}*/


	//ChangeVolumeSoundMem(250, DamageSound);
	object_type = eEnemy;
}

void EnemyBase::Update()
{
	__super::Update();
}

void EnemyBase::Draw() const
{
	__super::Draw();
}

void EnemyBase::Finalize()
{
}

void EnemyBase::OnHitCollision(ObjectBase* hit_object)
{
	PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK);
}

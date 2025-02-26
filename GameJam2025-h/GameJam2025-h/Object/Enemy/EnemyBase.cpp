#include "EnemyBase.h"
#include "DxLib.h"
#include "../Item/ItemBase.h"

EnemyBase::EnemyBase() :DamageSound(),ExplosionSound(),HealSound(),DethSound()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);

	DamageSound = LoadSoundMem("Resource/Sounds/Hit08-1.mp3");
	DethSound = LoadSoundMem("Resource/Sounds/se_duwaiwaiwai (1).mp3");

	if (LoadSoundMem("Resource/Sounds/Hit08-1.mp3") == -1)
	{
		throw ("�����t�@�C�����J���܂���");
	}


	ChangeVolumeSoundMem(250, DamageSound);
	object_type = eEnemy;
}

void EnemyBase::Update()
{
	__super::Update();

	//hp��0�ɂȂ�����
	if (hp <= 0)
	{
		PlaySoundMem(DethSound, DX_PLAYTYPE_BACK);
		//�폜
		this->SetDeleteFlg();
	}
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
	if (hit_object->GetObjectType() == eItem)
	{
		ItemBase* item = dynamic_cast<ItemBase*>(hit_object);

		//���e�Ȃ�
		if (item->GetItemType() == eBomb)
		{
			PlaySoundMem(ExplosionSound, DX_PLAYTYPE_BACK);
		}
		//�񕜃A�C�e���Ȃ�
		else if (item->GetItemType() == eHeal)
		{
			PlaySoundMem(HealSound, DX_PLAYTYPE_BACK);
		}
		//����ȊO�Ȃ�
		else
		{
			PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK);
		}
	}

}

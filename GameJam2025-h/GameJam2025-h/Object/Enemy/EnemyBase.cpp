#include "EnemyBase.h"
#include "DxLib.h"
#include "../Item/ItemBase.h"

EnemyBase::EnemyBase() :DamageSound(),ExplosionSound(),HealSound(),DethSound(),DamageEffect(false),DamageEffect_Image(),
HealEffect(false),Healffect_image()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(location, _box_size);

	DamageSound = LoadSoundMem("Resource/Sounds/Hit08-1.mp3");
	ExplosionSound = LoadSoundMem("Resource/Sounds/se_explode_zun.mp3");
	HealSound = LoadSoundMem("Resource/Sounds/se_kaihuku01.mp3");
	DethSound = LoadSoundMem("Resource/Sounds/se_duwaiwaiwai (1).mp3");

	DamageEffect_Image = LoadGraph("Resource/Images/uHOHwzyHImmzn0W1740545388_1740545551.png");
	Healffect_image = LoadGraph("Resource/Images/WHlnIPyRgZiwsIO1740547760_1740547770.png");

	if (LoadSoundMem("Resource/Sounds/Hit08-1.mp3") == -1)
	{
		throw ("音声ファイルが開けません");
	}


	ChangeVolumeSoundMem(250, DamageSound);
	object_type = eEnemy;
}

void EnemyBase::Update()
{
	__super::Update();

	DamageEffect = false;
	HealEffect = false;

	//hpが0になったら
	if (hp <= 0)
	{
		PlaySoundMem(DethSound, DX_PLAYTYPE_BACK);
		//削除
		this->SetDeleteFlg();
	}
}

void EnemyBase::Draw() const
{
	if (DamageEffect == true)
	{
		DrawGraph(location.x, location.y, DamageEffect_Image, true);
	}
	if (HealEffect == true)
	{
		DrawGraph(location.x, location.y, Healffect_image, true);
	}
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

		//爆弾なら
		if (item->GetItemType() == eBomb)
		{
			PlaySoundMem(ExplosionSound, DX_PLAYTYPE_BACK);
			DamageEffect = true;
		}
		//回復アイテムなら
		else if (item->GetItemType() == eHeal)
		{
			PlaySoundMem(HealSound, DX_PLAYTYPE_BACK);
			HealEffect = true;
		}
		//それ以外なら
		else
		{
			PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK);
			DamageEffect = true;
		}
	}

}

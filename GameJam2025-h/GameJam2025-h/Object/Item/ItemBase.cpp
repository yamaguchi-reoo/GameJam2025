#include "ItemBase.h"
#include <DxLib.h>

ItemBase::ItemBase()
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
	object_type = eItem;

	//�A�C�e�����X�|�[��
	ItemSpawn();
}

void ItemBase::Update()
{
	__super::Update();

	//��ʊO�ɏo����폜
	if (location.y > SCREEN_HEIGHT + box_size.y)
	{
		//Object�폜
		this->SetDeleteFlg();
	}

	//����
	location.y += velocity.y;
	location.x += velocity.x;

	// ��C��R�I�Ȍ�������
	if (is_blowing)
	{
		velocity.x *= 0.98f;
		velocity.y += 0.5f; // �d�͂ŗ���
	}

	// ���̑��x�ȉ��ɂȂ�����ʏ��Ԃɖ߂�
	if (fabs(velocity.x) < 0.5f && fabs(velocity.y) < 0.5f)
	{
		is_blowing = false;
	}
}

void ItemBase::Draw() const
{
	__super::Draw();
	switch (item_type)
	{
	case eApple:
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "type: apple");
		DrawFormatString(location.x, location.y + 24, GetColor(255, 255, 255), "damage: %d", damage);
		break;
	case eRock:
		DrawFormatString(location.x, location.y + 12, GetColor(255, 255, 255), "type: rock");
		DrawFormatString(location.x, location.y + 24, GetColor(255, 255, 255), "damage: %d", damage);

		break;
	default:
		break;
	}

	//DrawCircleAA(location.x + (box_size.x / 2), location.y + (box_size.y / 2), 50.0f, 50, GetColor(0, 255, 0), TRUE);
}

void ItemBase::Finalize()
{
}

void ItemBase::OnHitCollision(ObjectBase* hit_object)
{
	if (hit_object->GetObjectType() == eEnemy)
	{
		//Object�폜
		this->SetDeleteFlg();

		//��������Object�Ƀ_���[�W��^����
		hit_object->ApplyDamage(damage);
	}
}

void ItemBase::ItemSpawn()
{
	switch (ItemRand())
	{
	case eApple:
		velocity.y = 1.0f;
		damage = 1;
		break;
	case eRock:
		velocity.y = 2.0f;
		damage = 2;
		break;
	default:
		break;
	}
}

int ItemBase::ItemRand()
{
	//�����_���Ȓl�i0 �` 9�j������
	int rand = GetRand(9);

	//���
	if (rand >= 0 && rand <= 5)
	{
		SetItemType(eApple);
		return GetItemType();
	}
	//��
	else if (rand > 5 && rand <= 10)
	{
		SetItemType(eRock);
		return GetItemType();
	}

	return 0;
}

void ItemBase::BlowAway(Vector2D _force)
{
	velocity = _force;
	is_blowing = true;
}

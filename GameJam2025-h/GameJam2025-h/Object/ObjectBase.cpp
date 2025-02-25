#include "ObjectBase.h"
#include <DxLib.h>

ObjectBase::ObjectBase()
{
}

ObjectBase::~ObjectBase()
{
	// imageが設定されている場合のみ解放する
	DeleteGraph(image);
}

void ObjectBase::Initialize(Vector2D _location, Vector2D _box_size)
{
	//位置を設定
	location = _location;
	//サイズを設定
	box_size = _box_size;

	//死亡フラグ
	delete_flg = false;

}

void ObjectBase::Update()
{
}

void ObjectBase::Draw() const
{
	//デバッグ用
	DrawBoxAA(location.x, location.y, location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), FALSE);

	switch (object_type)
	{
	case ePlayer:
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "player");
		break;
	case eEnemy:
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "enemy");
		break;
	case eItem:
		DrawFormatString(location.x, location.y, GetColor(255, 255, 255), "item");
		break;
	default:
		break;
	}
}

void ObjectBase::Finalize()
{

}

void ObjectBase::SetLocation(Vector2D _location)
{
	this->location = _location;
}

Vector2D ObjectBase::GetLocation() const
{
	return this->location;
}

Vector2D ObjectBase::GetBoxSize() const
{
	return this->box_size;
}

Vector2D ObjectBase::GetVelocity() const
{
	return this->velocity;
}

void ObjectBase::OnHitCollision(ObjectBase* hit_object)
{
}

bool ObjectBase::CheckBoxCollision(ObjectBase* obj)
{
	//自分の左上座標
	Vector2D my_pos = this->location;
	//自分の幅と高さの半分
	Vector2D my_size = this->box_size / 2.0f;

	//相手の左上座標
	Vector2D sub_pos = obj->GetLocation();
	//相手の幅と高さの半分
	Vector2D sub_size = obj->GetBoxSize() / 2.0f;

	//中心座標の差分
	Vector2D diff = (my_pos + my_size) - (sub_pos + sub_size);

	//当たり判定の演算
	return (fabsf(diff.x) <= my_size.x + sub_size.x &&
		fabsf(diff.y) <= my_size.y + sub_size.y);

}

void ObjectBase::ApplyDamage(int _damage)
{
	this->hp -= _damage;
}

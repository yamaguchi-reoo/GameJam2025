#include "Player.h"
#include "DxLib.h"

Player::Player()
{

}

Player::~Player()
{
}

void Player::Initialize(Vector2D _location, Vector2D _box_size)
{
	__super::Initialize(_location, _box_size);
}

void Player::Update()
{
	__super::Update();
}

void Player::Draw() const
{
	__super::Draw();
}

void Player::Finalize()
{
}

void Player::OnHitCollision(ObjectBase* hit_object)
{
}

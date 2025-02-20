#pragma once
#include "../Utility/Vector2D.h"
#include <vector>

class ObjectBase
{
protected:
	Vector2D location = { 0.0f };	//�I�u�W�F�N�g�̈ʒu
	Vector2D box_size = { 0.0f };	//�I�u�W�F�N�g�̃T�C�Y
	Vector2D velocity = { 0.0f };

	std::vector<int> animation_data = {};//�A�j���[�V�����f�[�^

	int image = NULL;			//�`�悷��摜�f�[�^
	bool flip_flg = false;		//�`�悷�锽�]�t���O
	bool delete_flg = false;

public:
	ObjectBase();
	~ObjectBase();

	//����������
	virtual void Initialize(Vector2D _location, Vector2D _box_size);
	//�X�V����
	virtual void Update();
	//�`�揈��
	virtual void Draw() const;
	//�I��������
	virtual void Finalize();

public:
	//���W��ݒ�
	void SetLocation(Vector2D _location);

	//���W���擾
	Vector2D GetLocation()const;

	//�{�b�N�X�T�C�Y���擾
	Vector2D GetBoxSize()const;

	//���x�擾
	Vector2D GetVelocity()const;

	virtual void OnHitCollision(ObjectBase* hit_object);

	//private:
		//�����蔻��
	bool CheckBoxCollision(ObjectBase* obj);

	//���S�t���O
	void SetDeleteFlg() { delete_flg = true; }
	bool GetDeleteFlg() { return delete_flg; }

};


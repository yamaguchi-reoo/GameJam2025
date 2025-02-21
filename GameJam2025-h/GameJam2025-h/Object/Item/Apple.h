#pragma once
#include "ItemBase.h"
class Apple :
    public ItemBase
{
public:
    //�R���X�g���N�^
    Apple();
    //�f�X�g���N�^
    ~Apple();

    //����������
    // _location �����ʒu
    // _box_size �����蔻��̃T�C�Y
    virtual void Initialize(Vector2D _location, Vector2D _box_size);

    //�X�V�����i�I�[�o�[���C�h���Ďg�p�j
    virtual void Update();

    //�`�揈���i�I�[�o�[���C�h���Ďg�p�j
    virtual void Draw() const;

    //�I�������i�I�[�o�[���C�h���Ďg�p�j
    virtual void Finalize();

    virtual void OnHitCollision(ObjectBase* hit_object);
};


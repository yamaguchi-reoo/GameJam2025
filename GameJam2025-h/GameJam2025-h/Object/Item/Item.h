#pragma once
#include "ItemBase.h"
class Item :
    public ItemBase
{
public:
    //�R���X�g���N�^
    Item();
    //�f�X�g���N�^
    ~Item();

    //����������
    // _location �����ʒu
    // _box_size �����蔻��̃T�C�Y
    void Initialize(Vector2D _location, Vector2D _box_size)override;

    //�X�V�����i�I�[�o�[���C�h���Ďg�p�j
    void Update()override;

    //�`�揈���i�I�[�o�[���C�h���Ďg�p�j
    void Draw() const override;

    //�I�������i�I�[�o�[���C�h���Ďg�p�j
    void Finalize()override;

    void OnHitCollision(ObjectBase* hit_object)override;
};


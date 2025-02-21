#pragma once
#include "../ObjectBase.h"

enum ItemKinds
{
    eApple,
    eRock
};

class ItemBase :
    public ObjectBase
{
private:
public:
    //�R���X�g���N�^
    ItemBase();
    //�f�X�g���N�^
    ~ItemBase();

    //����������
    // _location �����ʒu
    // _box_size �����蔻��̃T�C�Y
    virtual void Initialize(Vector2D _location, Vector2D _box_size)override;

    //�X�V�����i�I�[�o�[���C�h���Ďg�p�j
    virtual void Update()override;

    //�`�揈���i�I�[�o�[���C�h���Ďg�p�j
    virtual void Draw() const override;

    //�I�������i�I�[�o�[���C�h���Ďg�p�j
    virtual void Finalize()override;

    virtual void OnHitCollision(ObjectBase* hit_object)override;
};


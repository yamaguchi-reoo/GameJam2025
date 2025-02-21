#pragma once
#include "../ObjectBase.h"

enum eItemType
{
    eApple,
    eRock
};

class ItemBase :
    public ObjectBase
{
protected:
    eItemType item_type = {};

    bool is_blowing = false;
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

    //ItemType�擾
    eItemType GetItemType() { return item_type; }

    //ItemType�Z�b�g
    void SetItemType(eItemType _type) { item_type = _type; }

    void BlowAway(Vector2D _force);

private:
    //�A�C�e������
    void ItemSpawn();

    //�A�C�e�����I
    int ItemRand();


};


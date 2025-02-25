#pragma once
#include "../ObjectBase.h"

enum eItemType
{
    eApple,
    eRock,
    eBomb,
    eHeal,
    ePowerup
};

class ItemBase :
    public ObjectBase
{
protected:
    eItemType item_type = {};

    bool is_blowing = false;

    int color = 0;

    Vector2D offset = {}; //�摜���炵�悤

    int animation_time = 0;
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

    void DamageUp() { damage = damage * 2; }

    int GetAnimationTime() { return animation_time; }

private:
    //�A�C�e������
    void ItemSpawn();

    //�A�C�e�����I
    int ItemRand();



};


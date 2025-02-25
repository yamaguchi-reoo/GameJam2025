#pragma once
#include "EnemyBase.h"
class HardEnemy :
    public EnemyBase
{
private:
    //�G�̌����ڂ�ς���ϐ�
    int EnemyChange;
public:
    HardEnemy();

    ~HardEnemy();

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


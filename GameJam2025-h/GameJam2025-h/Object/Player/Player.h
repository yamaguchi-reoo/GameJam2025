#pragma once
#include "../ObjectBase.h"
class Player :
    public ObjectBase
{
private:
    int move_count;
    bool is_attack;
    int attack_timer;

    Vector2D player_pos = {};
    Vector2D player_box = {};

    bool is_power;
    int power_time;
    int cool_time;

    int hit_se;
    int miss_se;
    bool is_hit;

    int explosion_se;
    int power_se;
public:
   
    Player();

    ~Player();

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

public:
    void Movement();

    void Attack();

    bool GetIsAttack() { return is_attack; }
};



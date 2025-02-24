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
public:
   
    Player();

    ~Player();

    //初期化処理
    // _location 初期位置
    // _box_size 当たり判定のサイズ
    virtual void Initialize(Vector2D _location, Vector2D _box_size)override;

    //更新処理（オーバーライドして使用）
    virtual void Update()override;

    //描画処理（オーバーライドして使用）
    virtual void Draw() const override;

    //終了処理（オーバーライドして使用）
    virtual void Finalize()override;

    virtual void OnHitCollision(ObjectBase* hit_object)override;

public:
    void Movement();

    void Attack();
};



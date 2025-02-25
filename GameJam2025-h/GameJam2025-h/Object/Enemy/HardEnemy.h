#pragma once
#include "EnemyBase.h"
class HardEnemy :
    public EnemyBase
{
private:
    //敵の見た目を変える変数
    int EnemyChange;
public:
    HardEnemy();

    ~HardEnemy();

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
};


#pragma once
#include "../ObjectBase.h"

enum ItemKinds
{
    eWeekEnemy,
    eNomalEnemy,
    eHardEnemy,
    eBossEnemy
};

class EnemyBase :
    public ObjectBase
{
public:
    int DamageSound;
    //コンストラクタ
    EnemyBase();
    //デストラクタ
    ~EnemyBase();

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


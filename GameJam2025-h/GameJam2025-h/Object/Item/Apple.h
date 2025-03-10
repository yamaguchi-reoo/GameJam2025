#pragma once
#include "ItemBase.h"
class Apple :
    public ItemBase
{
public:
    //コンストラクタ
    Apple();
    //デストラクタ
    ~Apple();

    //初期化処理
    // _location 初期位置
    // _box_size 当たり判定のサイズ
    void Initialize(Vector2D _location, Vector2D _box_size)override;

    //更新処理（オーバーライドして使用）
    void Update()override;

    //描画処理（オーバーライドして使用）
    void Draw() const override;

    //終了処理（オーバーライドして使用）
    void Finalize()override;

    void OnHitCollision(ObjectBase* hit_object)override;
};


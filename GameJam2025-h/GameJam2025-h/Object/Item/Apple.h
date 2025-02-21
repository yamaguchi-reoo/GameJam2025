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
    virtual void Initialize(Vector2D _location, Vector2D _box_size);

    //更新処理（オーバーライドして使用）
    virtual void Update();

    //描画処理（オーバーライドして使用）
    virtual void Draw() const;

    //終了処理（オーバーライドして使用）
    virtual void Finalize();

    virtual void OnHitCollision(ObjectBase* hit_object);
};


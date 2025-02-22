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
    //コンストラクタ
    ItemBase();
    //デストラクタ
    ~ItemBase();

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

    //ItemType取得
    eItemType GetItemType() { return item_type; }

    //ItemTypeセット
    void SetItemType(eItemType _type) { item_type = _type; }

    void BlowAway(Vector2D _force);

private:
    //アイテム生成
    void ItemSpawn();

    //アイテム抽選
    int ItemRand();


};


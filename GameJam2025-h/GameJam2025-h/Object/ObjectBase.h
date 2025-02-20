#pragma once
#include "../Utility/Vector2D.h"
#include <vector>

//ゲーム内の全てのオブジェクトの基底クラス
//位置・サイズ・速度・アニメーションデータ・描画情報などを管理
class ObjectBase
{
protected:
    Vector2D location = { 0.0f };  //オブジェクトの位置
    Vector2D box_size = { 0.0f };  //オブジェクトのサイズ（当たり判定用）
    Vector2D velocity = { 0.0f };  //オブジェクトの移動速度

    std::vector<int> animation_data = {}; ///< アニメーションデータ（フレーム情報など）

    int image = NULL;          //描画する画像データのハンドル
    bool flip_flg = false;     //画像を左右反転するフラグ
    bool delete_flg = false;   //削除フラグ（true の場合オブジェクトは削除される）

public:
    //コンストラクタ
    ObjectBase();

    //デストラクタ
    ~ObjectBase();

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

public:
    //座標を設定
    //_location 設定する座標
    void SetLocation(Vector2D _location);

    //座標を取得
    //現在の座標
    Vector2D GetLocation() const;

    //ボックスサイズを取得
    //当たり判定のサイズ
    Vector2D GetBoxSize() const;

    //速度を取得
    //現在の速度
    Vector2D GetVelocity() const;

    //オブジェクト同士の衝突時に呼ばれる関数（オーバーライドして使用）
    //hit_object 衝突したオブジェクト
    virtual void OnHitCollision(ObjectBase* hit_object);

    //矩形（ボックス）同士の当たり判定チェック
    //衝突を確認するオブジェクト
    //衝突している場合は true
    bool CheckBoxCollision(ObjectBase* obj);

    //削除フラグを立てる（オブジェクトを削除するための処理）
    void SetDeleteFlg() { delete_flg = true; }

    //削除フラグを取得
    bool GetDeleteFlg() { return delete_flg; }
};

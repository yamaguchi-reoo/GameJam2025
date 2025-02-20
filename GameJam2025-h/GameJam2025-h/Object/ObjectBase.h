#pragma once
#include "../Utility/Vector2D.h"
#include <vector>

class ObjectBase
{
protected:
	Vector2D location = { 0.0f };	//オブジェクトの位置
	Vector2D box_size = { 0.0f };	//オブジェクトのサイズ
	Vector2D velocity = { 0.0f };

	std::vector<int> animation_data = {};//アニメーションデータ

	int image = NULL;			//描画する画像データ
	bool flip_flg = false;		//描画する反転フラグ
	bool delete_flg = false;

public:
	ObjectBase();
	~ObjectBase();

	//初期化処理
	virtual void Initialize(Vector2D _location, Vector2D _box_size);
	//更新処理
	virtual void Update();
	//描画処理
	virtual void Draw() const;
	//終了時処理
	virtual void Finalize();

public:
	//座標を設定
	void SetLocation(Vector2D _location);

	//座標を取得
	Vector2D GetLocation()const;

	//ボックスサイズを取得
	Vector2D GetBoxSize()const;

	//速度取得
	Vector2D GetVelocity()const;

	virtual void OnHitCollision(ObjectBase* hit_object);

	//private:
		//当たり判定
	bool CheckBoxCollision(ObjectBase* obj);

	//死亡フラグ
	void SetDeleteFlg() { delete_flg = true; }
	bool GetDeleteFlg() { return delete_flg; }

};


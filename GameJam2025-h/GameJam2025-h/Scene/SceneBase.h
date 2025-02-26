#pragma once
#include <vector>
#include "../Utility/InputControl.h"
#include "../Object/ObjectBase.h"

#define OBJECT_MAX 10

//シーンの種類を列挙型で定義
enum class eSceneType
{
	eTitle = 0,
	eGameMain,
	eResult,
	eHelp,
	eRanking,
	eInput,
	eCredit,
	eEnd
};

class SceneBase
{
protected:
	// 特定のメンバ変数が必要であれば、ここで定義する
	int limit_time = 0;

	int create_quantity_item = 0;  // 画面内にあるアイテムの数
	int create_enemy_max = 0;  // 敵が生成された累計数
	bool create_enemy = true;  // 敵が生成可能か
	bool create_boss = false;  // ボスが生成可能か
	bool is_boss;  // true = ボスが生きている。又は未生成

	//オブジェクト管理変数
	std::vector<ObjectBase*>objects;
public:
	//コンストラクタ
	SceneBase();
	//デストラクタ
	virtual ~SceneBase();

	virtual void Initialize();		//初期化処理
	virtual eSceneType Update();	//更新処理
	virtual void Draw() const;		//描画処理
	virtual void Finalize();		//終了時処理

	//現在のシーンタイプを取得する
	virtual eSceneType GetNowSceneType()const = 0;

protected:
	//ゲームオブジェクトを生成するテンプレート関数
	template <class T>
	T* CreateObject(const Vector2D& _location, const Vector2D& _box_size)
	{
		//新しいインスタンスを生成
		T* new_instance = new T();

		ObjectBase* new_object = dynamic_cast<ObjectBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("ゲームオブジェクトが生成できませんでした\n");
		}

		new_object->SetLocation(_location);

		new_object->Initialize(_location, _box_size);

		objects.push_back(new_object);
		if (new_object->GetObjectType() == eItem)
		{
			create_quantity_item++;
		}
		if (new_object->GetObjectType() == eEnemy)
		{
			create_enemy_max--;
		}

		//生成したインスタンスを返す
		return new_instance;
	}

public:
	void DeleteObject(ObjectBase* obj);
};


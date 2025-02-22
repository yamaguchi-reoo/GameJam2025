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
	eEnd
};

class SceneBase
{
protected:
	// 特定のメンバ変数が必要であれば、ここで定義する
	int create_quantity = 0;

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
			create_quantity++;
		}

		//生成したインスタンスを返す
		return new_instance;
	}

public:
	void DeleteObject(ObjectBase* obj);
};


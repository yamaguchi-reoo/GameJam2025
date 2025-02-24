#include "SceneBase.h"
#include "../Scene/GameScene/InGameScene.h"
#include <DxLib.h>
#include "SceneManager.h"

SceneBase::SceneBase():
	create_quantity_item(),
	create_enemy_max(),
	create_enemy(),
	create_boss(),
	is_boss()
{
}

SceneBase::~SceneBase()
{
	this->Finalize();
}

void SceneBase::Initialize()
{
}

eSceneType SceneBase::Update()
{
	//Objectの更新
	for (ObjectBase* obj : objects)
	{
		obj->Update();
	}

	// 二重ループで衝突判定
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			if (objects[i]->CheckBoxCollision(objects[j]))
			{
				objects[i]->OnHitCollision(objects[j]);
				objects[j]->OnHitCollision(objects[i]);
			}
		}
	}

	//削除フラグが立っているオブジェクトを削除
	for (auto it = objects.begin(); it != objects.end();)
	{
		//フラグが立っているのなら
		if ((*it)->GetDeleteFlg()) {
			//削除処理
			DeleteObject(*it);
			//削除フラグが立っているオブジェクトを削除
			it = objects.begin();
		}
		else
		{
			++it;
		}
		

	}
	return GetNowSceneType();
}

void SceneBase::Draw() const
{
	//Object描画
	for (ObjectBase* obj : objects)
	{
		obj->Draw();
	}
}

void SceneBase::Finalize()
{
	//オブジェクトが空の場合は処理をスキップ
	if (objects.empty())
	{
		return;
	}

	for (ObjectBase* obj : objects)
	{
		obj->Finalize();

		delete obj;
	}

	objects.clear();
}

void SceneBase::DeleteObject(ObjectBase* obj)
{
	if (obj == nullptr) return;

	auto it = std::find(objects.begin(), objects.end(), obj);

	//削除するObjectがアイテムなら減らす
	if ((*it)->GetObjectType() == eItem)
	{
		create_quantity_item--;
	}
	if ((*it)->GetObjectType() == eEnemy)
	{
		create_enemy = true;
	}
	if ((*it)->GetObjectType() == eBoss)
	{
		is_boss = false;
	}
	if (it != objects.end()) {
		//見つかった場合、オブジェクトを削除
		(*it)->Finalize(); //終了処理
		delete* it;         //メモリ解放
		objects.erase(it);  //リストから削除
	}
}

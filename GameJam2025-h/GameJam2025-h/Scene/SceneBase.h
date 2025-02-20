#pragma once
#include <vector>
#include "../Utility/InputControl.h"

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

};


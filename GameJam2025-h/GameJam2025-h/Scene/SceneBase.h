#pragma once
#include <vector>
#include "../Utility/InputControl.h"

enum class eSceneType
{
	eTitle = 0,
	eGameMain,
	eResult,
	eHelp,
	Ranking,
	eEnd
};

class SceneBase
{
protected:
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


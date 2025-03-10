#pragma once
#include "../SceneBase.h"
class CreditScene :
    public SceneBase
{
private:
	// シーンに必要な変数を定義

public:
	CreditScene();
	~CreditScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;

public:
	//必要に応じて追加する関数をここに定義
};


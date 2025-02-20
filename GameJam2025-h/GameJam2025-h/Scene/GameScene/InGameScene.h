#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;
};
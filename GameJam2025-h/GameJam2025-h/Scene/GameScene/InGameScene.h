#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//‰Šú‰»ˆ—
	eSceneType Update() override;	//XVˆ—
	void Draw() const override;		//•`‰æˆ—
	void Finalize() override;		//I—¹ˆ—

	eSceneType GetNowSceneType()const override;
};
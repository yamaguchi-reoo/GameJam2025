#include "InGameScene.h"
#include <DxLib.h>

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
}

eSceneType InGameScene::Update()
{
	InputControl* input = InputControl::GetInstance();

	//GameMain‚Ö‘JˆÚ
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eTitle;
	}

	return __super::Update();
}

void InGameScene::Draw() const
{
	DrawString(0, 24, "GameMain", GetColor(255, 255, 255));
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eGameMain;
}

#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
}

eSceneType TitleScene::Update()
{
	InputControl* input = InputControl::GetInstance();

	//GameMain‚Ö‘JˆÚ
	if (input->GetKeyDown(KEY_INPUT_Z))
	{
		return eSceneType::eGameMain;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawString(0, 24, "Title", GetColor(255, 255, 255));
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}

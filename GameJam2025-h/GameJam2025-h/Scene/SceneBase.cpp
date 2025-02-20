#include "SceneBase.h"
#include <DxLib.h>

SceneBase::SceneBase()
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
	return GetNowSceneType();
}

void SceneBase::Draw() const
{
}

void SceneBase::Finalize()
{
}

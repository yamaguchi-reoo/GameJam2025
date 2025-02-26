#include "CreditScene.h"

CreditScene::CreditScene()//この関数の後ろに定義した変数を連ねて書く（例 : HelpScene() : a()）
{
}

CreditScene::~CreditScene()
{
}

void CreditScene::Initialize()
{
    //ここで変数の初期化して（例：a = 0;）    
}

eSceneType CreditScene::Update()
{
    InputControl* input = InputControl::GetInstance();
    //シーンの変更がない場合は現在のシーンを返す
    if (input->GetButtonDown(XINPUT_BUTTON_B))
    {
        return eSceneType::eTitle;
    }
    return GetNowSceneType();
}

void CreditScene::Draw() const
{
    int init_font_size = GetFontSize();

    SetFontSize(60);

    DrawString(50, 50, "制作者", 0xffffff);

    SetFontSize(24);
    DrawString(50, 150, "やまお", 0xffffff);
    DrawString(50, 200, "鳴潮復帰したい勢", 0xffffff);
    DrawString(50, 250, "ロン毛", 0xffffff);
    DrawString(50, 300, "たろしゅん", 0xffffff);

    SetFontSize(init_font_size);
}

void CreditScene::Finalize()
{
    
}

eSceneType CreditScene::GetNowSceneType() const
{
    return eSceneType::eCredit;
}
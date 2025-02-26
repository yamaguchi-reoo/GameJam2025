#include "CreditScene.h"

CreditScene::CreditScene()//���̊֐��̌��ɒ�`�����ϐ���A�˂ď����i�� : HelpScene() : a()�j
{
}

CreditScene::~CreditScene()
{
}

void CreditScene::Initialize()
{
    //�����ŕϐ��̏��������āi��Fa = 0;�j    
}

eSceneType CreditScene::Update()
{
    InputControl* input = InputControl::GetInstance();
    //�V�[���̕ύX���Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
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

    DrawString(50, 50, "�����", 0xffffff);

    SetFontSize(24);
    DrawString(50, 150, "��܂�", 0xffffff);
    DrawString(50, 200, "�����A��������", 0xffffff);
    DrawString(50, 250, "������", 0xffffff);
    DrawString(50, 300, "���낵���", 0xffffff);

    SetFontSize(init_font_size);
}

void CreditScene::Finalize()
{
    
}

eSceneType CreditScene::GetNowSceneType() const
{
    return eSceneType::eCredit;
}
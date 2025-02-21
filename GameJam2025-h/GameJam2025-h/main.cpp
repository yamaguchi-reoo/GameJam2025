#include "DxLib.h"
#include "common.h"
#include "Utility/UtiltyList.h"
#include "Scene/SceneManager.h"
#include <string>


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // �����R�[�h��UTF-8�ɐݒ�
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

    // �E�B���h�E�̉𑜓x�ƐF�[�x��ݒ�
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

    // �E�B���h�E���[�h��L���ɂ���i�t���X�N���[���ł͂Ȃ��E�B���h�E�\���j
    ChangeWindowMode(TRUE);

    // DxLib�̏������i���s���ُ͈�I���j
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // �`���𗠉�ʂɐݒ�i�_�u���o�b�t�@�����O�j
    SetDrawScreen(DX_SCREEN_BACK);

    // FPS����p�̃I�u�W�F�N�g���쐬
    FpsController* FPSC = new FpsController(FRAMERATE, 800);

    // �V�[���Ǘ��N���X�̃C���X�^���X���擾
    SceneManager* manager = SceneManager::GetInstance();

    try
    {
        // �V�[���}�l�[�W���[�̏�����
        manager->Initialize();

        // ���͊Ǘ��N���X�̃C���X�^���X���擾
        InputControl* input = InputControl::GetInstance();

        // ���C�����[�v
        while (ProcessMessage() != -1)  // �E�B���h�E��������܂Ŏ��s
        {
            // ���͏��̍X�V
            input->Update();

            // ��ʂ̏������i�N���A�j
            ClearDrawScreen();

            // �V�[���̍X�V
            manager->Update();

            // FPS���䏈��
            FPSC->All();

#ifdef _DEBUG
            // �f�o�b�O���[�h����FPS����\��
            FPSC->Disp();
#endif
            // ESC�L�[�������ꂽ�烋�[�v�𔲂���i�I�������j
            if (input->GetKeyUp(KEY_INPUT_ESCAPE) || input->GetButtonDown(XINPUT_BUTTON_BACK))
            {
                break;
            }

            // ��ʂ̓��e�𔽉f�i����� �� �\��ʁj
            ScreenFlip();
        }
    }
    catch (std::string& error_text)  // ��O�������̏���
    {
        OutputDebugString(error_text.c_str());  // �f�o�b�O�o��
        return -1;
    }

    // �C���X�^���X�̍폜�i����������j
    InputControl::DeleteInstance();
    SceneManager::DeleteInstance();

    // DxLib�̏I������
    DxLib_End();

    return 0;
}

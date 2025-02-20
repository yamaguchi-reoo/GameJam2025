#include "DxLib.h"
#include "common.h"
#include "Utility/UtiltyList.h"
#include "Scene/SceneManager.h"
#include <string>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // �E�C���h�E�̃T�C�Y

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//fps����
	FpsController* FPSC = new FpsController(FRAMERATE, 800);
	SceneManager* manager = SceneManager::GetInstance();


	try {

		manager->Initialize();

		InputControl* input = InputControl::GetInstance();


		while (ProcessMessage() != -1)
		{
			//���͏��̍X�V
			input->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//��ʂ̍X�V
			manager->Update();


			FPSC->All();
#ifdef _DEBUG
			FPSC->Disp();
#endif
			if (input->GetKeyUp(KEY_INPUT_ESCAPE))
			{
				break;
			}
			ScreenFlip();
		}

	}
	catch (std::string& error_text)
	{
		OutputDebugString(error_text.c_str());

		return -1;
	}
	//�C���X�^���X�̍폜
	InputControl::DeleteInstance();
	SceneManager::DeleteInstance();

	DxLib_End();
	return 0;

}
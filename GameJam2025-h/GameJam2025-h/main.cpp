#include "DxLib.h"
#include "common.h"
#include "Utility/UtiltyList.h"
#include "Scene/SceneManager.h"
#include <string>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//fps制御
	FpsController* FPSC = new FpsController(FRAMERATE, 800);
	SceneManager* manager = SceneManager::GetInstance();


	try {

		manager->Initialize();

		InputControl* input = InputControl::GetInstance();


		while (ProcessMessage() != -1)
		{
			//入力情報の更新
			input->Update();

			//画面の初期化
			ClearDrawScreen();

			//画面の更新
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
	//インスタンスの削除
	InputControl::DeleteInstance();
	SceneManager::DeleteInstance();

	DxLib_End();
	return 0;

}
#include "DxLib.h"
#include "common.h"
#include "Utility/UtiltyList.h"
#include "Scene/SceneManager.h"
#include <string>


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // 文字コードをUTF-8に設定
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

    // ウィンドウの解像度と色深度を設定
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

    // ウィンドウモードを有効にする（フルスクリーンではなくウィンドウ表示）
    ChangeWindowMode(TRUE);

    // DxLibの初期化（失敗時は異常終了）
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 描画先を裏画面に設定（ダブルバッファリング）
    SetDrawScreen(DX_SCREEN_BACK);

    // FPS制御用のオブジェクトを作成
    FpsController* FPSC = new FpsController(FRAMERATE, 800);

    // シーン管理クラスのインスタンスを取得
    SceneManager* manager = SceneManager::GetInstance();

    try
    {
        // シーンマネージャーの初期化
        manager->Initialize();

        // 入力管理クラスのインスタンスを取得
        InputControl* input = InputControl::GetInstance();

        // メインループ
        while (ProcessMessage() != -1)  // ウィンドウが閉じられるまで実行
        {
            // 入力情報の更新
            input->Update();

            // 画面の初期化（クリア）
            ClearDrawScreen();

            // シーンの更新
            manager->Update();

            // FPS制御処理
            FPSC->All();

#ifdef _DEBUG
            // デバッグモード時にFPS情報を表示
            FPSC->Disp();
#endif
            // ESCキーが押されたらループを抜ける（終了処理）
            if (input->GetKeyUp(KEY_INPUT_ESCAPE) || input->GetButtonDown(XINPUT_BUTTON_BACK))
            {
                break;
            }

            // 画面の内容を反映（裏画面 → 表画面）
            ScreenFlip();
        }
    }
    catch (std::string& error_text)  // 例外発生時の処理
    {
        OutputDebugString(error_text.c_str());  // デバッグ出力
        return -1;
    }

    // インスタンスの削除（メモリ解放）
    InputControl::DeleteInstance();
    SceneManager::DeleteInstance();

    // DxLibの終了処理
    DxLib_End();

    return 0;
}

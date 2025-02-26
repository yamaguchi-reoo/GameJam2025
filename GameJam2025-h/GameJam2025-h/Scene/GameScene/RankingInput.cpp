#include "RankingInput.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

RankingInput::RankingInput() :backgrouond_image(NULL),
result_time(),result_name(),
name_num(),
cursor_x(),cursor_y()
{
}


RankingInput::~RankingInput()
{

}


//初期化処理
void RankingInput::Initialize()
{
    memset(result_name, NULL, (sizeof(char) * 15));

    //リザルトデータを取得する
    FILE* fp = nullptr;
    //ファイルオープン
    errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

    //エラーチェック
    if (result != 0)
    {
        throw("Resource/Data/Result.csvが読み込めません\n");
    }

    //結果を読み込む
    fscanf_s(fp, "%d,%14s\n", &result_time, result_name[0], (unsigned int)sizeof(result_name));

    //ファイルクローズ
    fclose(fp);
}


//更新処理
eSceneType RankingInput::Update()
{
    bool is_change = false;

    //名前入力処理
    is_change = InputName();

    //シーン変更は可能か?
    if (is_change)
    {

        //リザルトデータを取得する
        FILE* fp = nullptr;
        //ファイルオープン
        errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "w");

        //エラーチェック
        if (result != 0)
        {
            throw("Resource/Data/Result.csvが読み込めません\n");
        }

        //結果を読み込む
        fprintf(fp, "%d,%14s\n", result_time, result_name[0]);

        //ファイルクローズ
        fclose(fp);

        //ランキング表示に遷移
        return eSceneType::eRanking;
    }
    else
    {
        return GetNowSceneType();
    }
}


//描画処理
void RankingInput::Draw()const
{
    int init_font_size = GetFontSize();
    SetFontSize(36);

    //背景画像の描画
    DrawGraph(0, 0, backgrouond_image, TRUE);

    //名前入力指示文字列の描画
    DrawString(350, 100, "ランキングに登録します", 0xffffff);
    DrawFormatString(350, 220, GetColor(255, 255, 255), ">%s", result_name);

    //選択用文字を描画
    const int font_size = GetFontSize();
    for (int i = 0; i < 26; i++)
    {
        int x = (i % 13) * font_size + 300;
        int y = (i / 13) * font_size + 300;
        DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'a' + i);
        y = ((i / 13) + 2) * font_size + 300;
        DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'A' + i);
    }
    DrawString(300, 600, "決定", GetColor(255, 255, 255));
    DrawString(500, 600, "消す", GetColor(255, 255, 255));

    //選択文字をフォーカスする
    if (cursor_y < 4)
    {
        int x = cursor_x * font_size + 293;
        int y = cursor_y * font_size + 303;
        DrawBox(x, y, x + font_size, y + font_size, GetColor(255, 255, 255), FALSE);
    }
    else
    {
        if (cursor_x == 0)
        {
            DrawBox(300, 600, 300 + font_size * 2, 600 + font_size, GetColor(255, 255, 255), FALSE);
        }
        else
        {
            DrawBox(500, 600, 500 + font_size * 2, 600 + font_size, GetColor(255, 255, 255), FALSE);
        }
    }

    SetFontSize(init_font_size);
}


//終了時処理
void RankingInput::Finalize()
{
    //読み込んだ画像を削除
    DeleteGraph(backgrouond_image);
}


//現在のシーン情報を取得
eSceneType RankingInput::GetNowSceneType()const
{
    return eSceneType::eInput;
}


//名前の入力処理
bool RankingInput::InputName()
{
    InputControl* input = InputControl::GetInstance();
    //カーソル操作処理
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
    {
        if (cursor_x > 0)
        {
            if (cursor_y == 4)
            {
                cursor_x = 0;
            }
            else
            {
                cursor_x--;
            }
        }
        else
        {
            cursor_x = 12;
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
    {
        if (cursor_y == 4)
        {
            if (cursor_x == 1)
            {
                cursor_x = 0;
            }
            else
            {
                cursor_x = 1;
            }
        }
        else
        {
            if (cursor_x < 12)
            {
                cursor_x++;
            }
            else
            {
                cursor_x = 0;
            }
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
    {
        if (cursor_y > 0)
        {
            cursor_y--;
        }
        else
        {
            cursor_y = 4;
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
    {
        if (cursor_y < 4)
        {
            cursor_y++;
        }
        else
        {
            cursor_y = 0;
        }
    }

    //カーソル位置の文字を決定する
    if (input->GetButtonDown(XINPUT_BUTTON_B))
    {
        if (cursor_y < 2)
        {
            result_name[0][name_num++] = 'a' + cursor_x + (cursor_y * 13);
            if (name_num == 14)
            {
                cursor_x = 0;
                cursor_y = 4;
            }
        }
        else if (cursor_y < 4)
        {
            result_name[0][name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
            if (name_num == 14)
            {
                cursor_x = 0;
                cursor_y = 4;
            }
        }
        else
        {
            if (cursor_x == 0)
            {
                result_name[0][name_num] = '\0';
                return true;
            }
            else
            {
                result_name[0][--name_num] = NULL;
            }
        }
    }

    return false;
}

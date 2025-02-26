#include "HelpScene.h"

HelpScene::HelpScene()://この関数の後ろに定義した変数を連ねて書く（例 : HelpScene() : a()）
	page(),
	apple_image(),
	rock_image(),
	bomb_image(),
	heal_image(),
	power_image(),
    help_image(),
    cursor()
{
}

HelpScene::~HelpScene()
{
}

void HelpScene::Initialize()
{
	//ここで変数の初期化して（例：a = 0;）

	page = 1;
    cursor = 0;

	//アイテム画像をロード
	apple_image = LoadGraph("Resource/Images/Apple.png");
	rock_image = LoadGraph("Resource/Images/Rock.png");
	bomb_image = LoadGraph("Resource/Images/Bomb.png");
	heal_image = LoadGraph("Resource/Images/Heal.png");
	power_image = LoadGraph("Resource/Images/PowerUp.png");

    help_image = LoadGraph("Resource/Images/GameMain04.png");

    PlaySoundFile("Resource/Sounds/maou_bgm_acoustic10.mp3アコースティック.mp3", DX_PLAYTYPE_BACK);
}

eSceneType HelpScene::Update()
{
	//更新処理

	//入力管理クラスのインスタンスを取得
	InputControl* input = InputControl::GetInstance();

    //上キーで移動
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))cursor = (cursor - 1 + 2) % 2;
    //下キーで移動
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))cursor = (cursor + 1) % 2;


    //Bボタンで選択したシーンに移動
    if (input->GetButtonDown(XINPUT_BUTTON_B))
    {
        if (cursor == 0)
        {
            return eSceneType::eGameMain;  // STARTを選んだらゲーム開始
        }
        else if (cursor == 1)
        {
            return eSceneType::eTitle;  // TITLEを選んだらタイトルへ戻る
        }
    }
	//シーンの変更がない場合は現在のシーンを返す
	return GetNowSceneType();
}

void HelpScene::Draw() const
{
    DrawGraph(0, 0, help_image, TRUE);

    //文字サイズを設定
    SetFontSize(36);

    // 半透明の背景ボックス（黒, 透明度150）
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
    //DrawBox(80, 110, 600, 400, GetColor(0, 0, 0), TRUE);  // 操作説明の背景
    //DrawBox(730, 90, 1200, 660, GetColor(0, 0, 0), TRUE);  // アイテム説明の背景
    DrawBox(20, 10, 1260, 710, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //タイトル「HELP」を中央に配置**
    DrawString(1280 / 2 - 60, 20, "HELP", GetColor(255, 255, 255));

    //プレイヤーの操作説明（左側）
    int control_x = 150;
    int control_y = 120;

    DrawString(control_x, control_y, "プレイヤーの操作方法", GetColor(255, 255, 255));

    SetFontSize(30);
    DrawString(control_x + 50, control_y + 90, "左/右: プレイヤー移動", GetColor(255, 255, 255));
    DrawDPad();

    DrawString(control_x + 50, control_y + 210, "Bボタン: 攻撃", GetColor(255, 255, 255));
    DrawCircleAA(control_x - 20, control_y + 220, 42, 21, GetColor(255, 255, 255), FALSE);
    DrawCircleAA(control_x - 20, control_y + 220, 40, 20, GetColor(255, 20, 20), TRUE);
    DrawString(control_x - 27, control_y + 207, "B", 0xffffff);

    //アイテムの効果（右側
    int item_x = 750;   // アイテムのX座標（右側）
    int item_y = 100;   // アイテムの開始Y座標
    int gap_y = 100;    // アイテムの間隔（画像 + 余白）

    SetFontSize(36);
    DrawString(item_x, item_y + 20, "アイテムの効果", GetColor(255, 255, 255));

    SetFontSize(28);
    //りんご
    DrawGraph(item_x, item_y + gap_y, apple_image, TRUE);
    DrawString(item_x + 120, item_y + gap_y + 30, "りんご: ダメージ１", GetColor(255, 255, 255));

    //岩
    DrawGraph(item_x - 10, item_y + gap_y * 2 + 10, rock_image, TRUE);
    DrawString(item_x + 120, item_y + gap_y * 2 + 30, "岩: ダメージ２", GetColor(255, 255, 255));

    //爆弾（時間が減る）
    DrawGraph(item_x, item_y + gap_y * 3, bomb_image, TRUE);
    DrawString(item_x + 120, item_y + gap_y * 3 + 30, "爆弾: 時間が10秒減る！", GetColor(255, 0, 0));

    //回復アイテム
    DrawGraph(item_x, item_y + gap_y * 4, heal_image, TRUE);
    DrawString(item_x + 120, item_y + gap_y * 4 + 30, "回復: 相手のHP5回復", GetColor(0, 255, 0));

    //強化アイテム（攻撃力UP）
    DrawGraph(item_x, item_y + gap_y * 5, power_image, TRUE);
    DrawString(item_x + 120, item_y + gap_y * 5 + 30, "強化: ダメージ２倍", GetColor(255, 255, 0));


    // メニュー項目のリスト
    const char* menu_items[] = { "START", "TITLE"};

    // 四角形のサイズと間隔の定義
    Vector2D box = { 200.0f, 80.0f };  // ボタンサイズを統一
    int box_spacing = 20;  // ボタン間隔
    int start_y = 400;  // ボタンの開始位置

    for (int i = 0; i < 2; i++)
    {
        int y = start_y + i * (box.y + box_spacing) + 100; // 縦の位置を調整

        // 🔹 選択中の項目は黄色、それ以外は赤
        int color = (i == cursor) ? GetColor(255, 255, 0) : GetColor(255, 0, 0);

        // 🔹 ボタンの描画
        DrawBox(box.x, y, box.x * 2, y + box.y, color, FALSE);

        // 🔹 テキスト描画（中央寄せ）
        DrawFormatString(box.x + 10, y + 7, GetColor(255, 255, 255), menu_items[i]);
    }
}

void HelpScene::Finalize()
{
	DeleteGraph(apple_image);
	DeleteGraph(rock_image);
	DeleteGraph(bomb_image);
	DeleteGraph(heal_image);
	DeleteGraph(power_image);
}

eSceneType HelpScene::GetNowSceneType() const
{
	return eSceneType::eHelp;
}

void HelpScene::DrawDPad() const
{
    // 十字キーの中心座標
    int d_pad_x = 135;
    int d_pad_y = 230;
    int d_pad_size = 15;

    // 縦・横のボタンの背景（黒枠）
    DrawBox(d_pad_x - d_pad_size, d_pad_y - d_pad_size * 3, d_pad_x + d_pad_size, d_pad_y + d_pad_size * 3, GetColor(100, 100, 100), TRUE);
    DrawBox(d_pad_x - d_pad_size * 3, d_pad_y - d_pad_size, d_pad_x + d_pad_size * 3, d_pad_y + d_pad_size, GetColor(100, 100, 100), TRUE);

    // 上ボタン（↑）
    DrawTriangle(d_pad_x, d_pad_y - d_pad_size * 2, d_pad_x - d_pad_size, d_pad_y - d_pad_size, d_pad_x + d_pad_size, d_pad_y - d_pad_size, GetColor(255, 255, 255), TRUE);

    // 下ボタン（↓）
    DrawTriangle(d_pad_x, d_pad_y + d_pad_size * 2, d_pad_x - d_pad_size, d_pad_y + d_pad_size, d_pad_x + d_pad_size, d_pad_y + d_pad_size, GetColor(255, 255, 255), TRUE);

    // 左ボタン（←）
    DrawTriangle(d_pad_x - d_pad_size * 2, d_pad_y, d_pad_x - d_pad_size, d_pad_y - d_pad_size, d_pad_x - d_pad_size, d_pad_y + d_pad_size, GetColor(255, 255, 255), TRUE);

    // 右ボタン（→）
    DrawTriangle(d_pad_x + d_pad_size * 2, d_pad_y, d_pad_x + d_pad_size, d_pad_y - d_pad_size, d_pad_x + d_pad_size, d_pad_y + d_pad_size, GetColor(255, 255, 255), TRUE);

}

#pragma once
#include"DxLib.h"

#define D_KEYCODE_MAX (256)		//キーコードの最大数
#define MOUSE_MAX (256)

#define BUTTON_MAX 16			//ボタンの最大数
#define STICK_X 1				//スティックのX軸
#define STICK_Y 2				//スティックのY軸
#define STICK_TILT_MAX 32767.0f //スティックの最大傾き値

//マウスカーソル
struct Cursor
{
	int x;
	int y;
};

class InputControl

{
private:
	//自クラスのポインタ（アドレスの先にインスタンスを生成する）
	static InputControl* instance;

	//今回の入力キー
	char now_key[D_KEYCODE_MAX];
	//前回の入力キー
	char old_key[D_KEYCODE_MAX];

	//今回の入力
	char now_mouse[MOUSE_MAX];
	//前回の入力
	char old_mouse[MOUSE_MAX];

	//カーソル
	Cursor cursor;

	//今回の入力キー
	char now_button[BUTTON_MAX];
	//前回の入力キー
	char old_button[BUTTON_MAX];
	// 入力デバイスの状態を保存する構造体
	XINPUT_STATE input;

private:
	//コンストラクタをprivateにすることで
	//自クラスのメンバ関数でしかインスタンスを生成できないようにする
	InputControl() = default;

	//コピーガード
	//クラス外インスタンスを生成して渡すことができないようにする
	InputControl(InputControl& v) = delete;
	InputControl& operator = (const InputControl& v) = delete;
	//~コピーガード

public:
	~InputControl() = default;

public:
	//インスタンス取得する処理
	static InputControl* GetInstance();
	//インスタンスの削除
	static void DeleteInstance();

public:
	//キー入力の状態を更新
	void Update();
	//押している間
	bool GetKey(int key_code)const;
	//押した瞬間
	bool GetKeyDown(int key_code)const;
	//離した瞬間
	bool GetKeyUp(int key_code)const;

	//押している間
	bool GetMouse(int mouse);
	//押した瞬間
	bool GetMouseDown(int mouse);
	//離した瞬間
	bool GetMouseUp(int mouse);

	//マウスカーソルの取得
	Cursor GetMouseCursor();

	//押している間
	bool GetButton(int button)const;
	//押した瞬間
	bool GetButtonDown(int button)const;
	//離した瞬間
	bool GetButtonUp(int button)const;

	//左スティックの傾き（指定された軸）を取得する
	float LeftStickTilt(short l_stick);
	//右スティックの傾き（指定された軸）を取得する
	float RightStickTilt(short r_stick);

private:
	//キーコードが有効な範囲にあるかを確認
	static bool CheckKeyCodeRange(int key_code);
};
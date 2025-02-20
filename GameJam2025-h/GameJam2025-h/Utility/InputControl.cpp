#include "InputControl.h"
#include "DxLib.h"

//静的メンバ変数定義
InputControl* InputControl::instance = nullptr; //クラスのインスタンスのポインタ

//入力制御クラスのインスタンス取得する処理
InputControl* InputControl::GetInstance()
{
	//インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new InputControl();
	}

	//自分自身でポインタを返却する
	return instance;
}

//入力制御クラスのインスタンス削除する処理
void InputControl::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputControl::Update()
{
	//前回のキーの更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//現在のキー状態の更新
	GetHitKeyStateAll(now_key);

	//前回のキーの更新
	memcpy(old_mouse, now_mouse, (sizeof(char) * MOUSE_MAX));

	//現在のキー状態の更新
	for (int i = 0; i < MOUSE_MAX; i++)
	{
		if (GetMouseInput() == i)
		{
			now_mouse[i] = 1;
		}
		else
		{
			now_mouse[i] = 0;
		}
	}
	GetMousePoint(&cursor.x, &cursor.y);


	//前回のキーの更新
	memcpy(old_button, now_button, (sizeof(char) * BUTTON_MAX));
	//現在のキー状態の更新
	if (GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input) == 0)
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			now_button[i] = input.Buttons[i];
		}
	}
}

bool InputControl::GetKey(int key_code)const
{
	//キーが押されているかを確認する処理
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == TRUE));
}

bool InputControl::GetKeyDown(int key_code)const
{
	//キーが押された瞬間か確認する処理
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == FALSE));
}

bool InputControl::GetKeyUp(int key_code)const
{
	//キーが離された瞬間か確認する処理
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) && (old_key[key_code] == TRUE));
}

bool InputControl::GetMouse(int mouse)
{
	//ボタンが押されているかを確認する処理
	return (now_mouse[mouse] == TRUE) && (old_mouse[mouse] == TRUE);
}

bool InputControl::GetMouseDown(int mouse)
{
	//ボタンが押された瞬間か確認する処理
	return (now_mouse[mouse] == TRUE) && (old_mouse[mouse] == FALSE);
}

bool InputControl::GetMouseUp(int mouse)
{
	//ボタンが離された瞬間か確認する処理
	return (now_mouse[mouse] == FALSE) && (old_mouse[mouse] == TRUE);
}

Cursor InputControl::GetMouseCursor()
{
	//カーソルを返す
	return cursor;
}

bool InputControl::GetButton(int button) const
{
	//ボタンが押されているかを確認する処理
	return ((now_button[button] == TRUE) && (old_button[button] == TRUE));
}

bool InputControl::GetButtonDown(int button) const
{
	//ボタンが押された瞬間か確認する処理
	return ((now_button[button] == TRUE) && (old_button[button] == FALSE));
}

bool InputControl::GetButtonUp(int button) const
{
	//ボタンが離された瞬間か確認する処理
	return ((now_button[button] == FALSE) && (old_button[button] == TRUE));
}

float InputControl::LeftStickTilt(short l_stick)
{
	// 左スティックの傾き割合を返す
	if (l_stick == STICK_X)
	{
		return static_cast<float>(input.ThumbLX) / STICK_TILT_MAX;
	}
	else if (l_stick == STICK_Y)
	{
		return static_cast<float>(input.ThumbLY) / STICK_TILT_MAX;
	}
	return 0.0f;
}

float InputControl::RightStickTilt(short r_stick)
{
	// 右スティックの傾き割合を返す
	if (r_stick == STICK_X)
	{
		return static_cast<float>(input.ThumbRX) / STICK_TILT_MAX;
	}
	else if (r_stick == STICK_Y)
	{
		return static_cast<float>(input.ThumbRY) / STICK_TILT_MAX;
	}
	return 0.0f;
}

bool InputControl::CheckKeyCodeRange(int key_code)
{
	//キーコードの範囲内か確認する処理
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}
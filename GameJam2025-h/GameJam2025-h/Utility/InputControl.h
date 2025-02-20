#pragma once
#include"DxLib.h"

#define D_KEYCODE_MAX (256)		//�L�[�R�[�h�̍ő吔
#define MOUSE_MAX (256)

#define BUTTON_MAX 16			//�{�^���̍ő吔
#define STICK_X 1				//�X�e�B�b�N��X��
#define STICK_Y 2				//�X�e�B�b�N��Y��
#define STICK_TILT_MAX 32767.0f //�X�e�B�b�N�̍ő�X���l

//�}�E�X�J�[�\��
struct Cursor
{
	int x;
	int y;
};

class InputControl

{
private:
	//���N���X�̃|�C���^�i�A�h���X�̐�ɃC���X�^���X�𐶐�����j
	static InputControl* instance;

	//����̓��̓L�[
	char now_key[D_KEYCODE_MAX];
	//�O��̓��̓L�[
	char old_key[D_KEYCODE_MAX];

	//����̓���
	char now_mouse[MOUSE_MAX];
	//�O��̓���
	char old_mouse[MOUSE_MAX];

	//�J�[�\��
	Cursor cursor;

	//����̓��̓L�[
	char now_button[BUTTON_MAX];
	//�O��̓��̓L�[
	char old_button[BUTTON_MAX];
	// ���̓f�o�C�X�̏�Ԃ�ۑ�����\����
	XINPUT_STATE input;

private:
	//�R���X�g���N�^��private�ɂ��邱�Ƃ�
	//���N���X�̃����o�֐��ł����C���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
	InputControl() = default;

	//�R�s�[�K�[�h
	//�N���X�O�C���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
	InputControl(InputControl& v) = delete;
	InputControl& operator = (const InputControl& v) = delete;
	//~�R�s�[�K�[�h

public:
	~InputControl() = default;

public:
	//�C���X�^���X�擾���鏈��
	static InputControl* GetInstance();
	//�C���X�^���X�̍폜
	static void DeleteInstance();

public:
	//�L�[���͂̏�Ԃ��X�V
	void Update();
	//�����Ă����
	bool GetKey(int key_code)const;
	//�������u��
	bool GetKeyDown(int key_code)const;
	//�������u��
	bool GetKeyUp(int key_code)const;

	//�����Ă����
	bool GetMouse(int mouse);
	//�������u��
	bool GetMouseDown(int mouse);
	//�������u��
	bool GetMouseUp(int mouse);

	//�}�E�X�J�[�\���̎擾
	Cursor GetMouseCursor();

	//�����Ă����
	bool GetButton(int button)const;
	//�������u��
	bool GetButtonDown(int button)const;
	//�������u��
	bool GetButtonUp(int button)const;

	//���X�e�B�b�N�̌X���i�w�肳�ꂽ���j���擾����
	float LeftStickTilt(short l_stick);
	//�E�X�e�B�b�N�̌X���i�w�肳�ꂽ���j���擾����
	float RightStickTilt(short r_stick);

private:
	//�L�[�R�[�h���L���Ȕ͈͂ɂ��邩���m�F
	static bool CheckKeyCodeRange(int key_code);
};
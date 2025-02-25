#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
private:
	//�Q�[���V�[���ɕK�v�ȕϐ����`
	int time_count;  // �������Ԃ����炷���߂̃J�E���g  60count = 1�b
	int create_span_item; // �A�C�e���𐶐�����Ԋu
	int create_span_enemy;  // �G�𐶐�����Ԋu

	int in_game_image;

	int shake_timer;  // �j���h��鎞��
	float shake_amount;  // �j�̗h�ꕝ
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;
public:
	void DecTime(int dectime);
	void WriteData();

	void DrawTimer()const;
};
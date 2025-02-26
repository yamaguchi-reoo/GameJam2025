#pragma once
#include "../SceneBase.h"
class HelpScene :
    public SceneBase
{
private:
	//�V�[���ɕK�v�ȕϐ����`
	int page; //���݂̃y�[�W (1 or 2)
	int cursor;

	//�A�C�e���摜
	int apple_image;
	int	rock_image;
	int bomb_image;
	int	heal_image;
	int	power_image;

	int help_image;

public:
	HelpScene();
	~HelpScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;

public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
	void DrawDPad()const;
};


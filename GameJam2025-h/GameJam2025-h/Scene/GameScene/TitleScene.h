#pragma once
#include "../SceneBase.h"
class TitleScene :
    public SceneBase
{
private:
	int cursor;
	//�^�C�g���V�[���ɕK�v�ȕϐ����`
public:
	TitleScene();
	~TitleScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;

public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
};


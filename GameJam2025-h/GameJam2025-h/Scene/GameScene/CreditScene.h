#pragma once
#include "../SceneBase.h"
class CreditScene :
    public SceneBase
{
private:
	// �V�[���ɕK�v�ȕϐ����`

public:
	CreditScene();
	~CreditScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;

public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
};


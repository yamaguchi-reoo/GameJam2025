#pragma once
#include "../SceneBase.h"

class InGameScene :
	public SceneBase
{
private:
	//�Q�[���V�[���ɕK�v�ȕϐ����`
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;
public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
};
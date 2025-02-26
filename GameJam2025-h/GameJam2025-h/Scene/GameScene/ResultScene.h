#pragma once
#include "../SceneBase.h"
class ResultScene :
    public SceneBase
{
private:
	//�V�[���ɕK�v�ȕϐ����`		
	int bgi;
	int result_time;

public:
	ResultScene();
	~ResultScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;

public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
	void LoadData();
};


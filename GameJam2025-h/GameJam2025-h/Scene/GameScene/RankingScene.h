#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//�V�[���ɕK�v�ȕϐ����`
public:
	RankingScene();
	~RankingScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;

public:
	//�K�v�ɉ����Ēǉ�����֐��������ɒ�`
};


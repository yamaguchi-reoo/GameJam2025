#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//�V�[���ɕK�v�ȕϐ����`
	int remain_time[6];
	int result_time;

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
	void SortData();  // �c�莞�Ԃ̑������Ƀ\�[�g
};


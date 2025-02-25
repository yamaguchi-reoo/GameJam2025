#pragma once
#include "../SceneBase.h"
class RankingScene :
    public SceneBase
{
private:
	//�V�[���ɕK�v�ȕϐ����`
	int remain_time[6];  // �^�C���f�[�^
	char player_name[6][15];  // ���O�f�[�^
	int result_time;     // �O��̋L�^������
	char result_name[1][15];     // ����̓��͂���閼�O

	int cursor;   // �I������Ă���{�^���̈ʒu

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


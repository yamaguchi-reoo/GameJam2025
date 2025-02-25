#pragma once
#include "../SceneBase.h"
class RankingInput:
	public SceneBase
{
private:
	int backgrouond_image;   // �w�i�摜
	int remain_time;         // �c�莞��
	char name[15];           // ���O
	int name_num;            // ���O���͐�
	int cursor_x;            // �J�[�\��x���W
	int cursor_y;            // �J�[�\��y���W

public:
	RankingInput();
	virtual ~RankingInput();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowSceneType() const override;

private:
	//���O���͏���
	bool InputName();
};
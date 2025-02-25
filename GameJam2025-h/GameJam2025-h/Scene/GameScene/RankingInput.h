#pragma once
#include "../SceneBase.h"
class RankingInput:
	public SceneBase
{
private:
	int backgrouond_image;   // �w�i�摜
	int result_time;         // �c�莞��
	char result_name[15];           // ���O
	int name_num;            // ���O���͐�
	int cursor_x;            // �J�[�\��x���W
	int cursor_y;            // �J�[�\��y���W

public:
	RankingInput();
	virtual ~RankingInput();

	virtual void Initialize() override;
	virtual void Draw() const override;
	virtual eSceneType Update() override;
	virtual void Finalize() override;

	virtual eSceneType GetNowSceneType() const override;

private:
	//���O���͏���
	bool InputName();
};
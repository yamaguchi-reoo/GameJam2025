#pragma once
#include "../SceneBase.h"
class RankingInput:
	public SceneBase
{
private:
	int backgrouond_image;   // �w�i�摜
	int result_time;         // �c�莞��
	char result_name[1][15];           // ���O
	int name_num;            // ���O���͐�
	int cursor_x;            // �J�[�\��x���W
	int cursor_y;            // �J�[�\��y���W

public:
	RankingInput();
	~RankingInput();

	void Initialize() override;
	eSceneType Update() override;
	void Draw() const override;
	void Finalize() override;

	eSceneType GetNowSceneType() const override;

private:
	//���O���͏���
	bool InputName();
};
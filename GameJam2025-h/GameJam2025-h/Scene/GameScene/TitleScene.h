#pragma once
#include "../SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	void Initialize() override;		//����������
	eSceneType Update() override;	//�X�V����
	void Draw() const override;		//�`�揈��
	void Finalize() override;		//�I��������

	eSceneType GetNowSceneType()const override;
};


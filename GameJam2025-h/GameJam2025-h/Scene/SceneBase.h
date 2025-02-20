#pragma once
#include <vector>
#include "../Utility/InputControl.h"

enum class eSceneType
{
	eTitle = 0,
	eGameMain,
	eResult,
	eHelp,
	Ranking,
	eEnd
};

class SceneBase
{
protected:
public:
	//�R���X�g���N�^
	SceneBase();
	//�f�X�g���N�^
	virtual ~SceneBase();

	virtual void Initialize();		//����������
	virtual eSceneType Update();	//�X�V����
	virtual void Draw() const;		//�`�揈��
	virtual void Finalize();		//�I��������

	//���݂̃V�[���^�C�v���擾����
	virtual eSceneType GetNowSceneType()const = 0;

};


#pragma once
#include <vector>
#include "../Utility/InputControl.h"

//�V�[���̎�ނ�񋓌^�Œ�`
enum class eSceneType
{
	eTitle = 0,
	eGameMain,
	eResult,
	eHelp,
	eRanking,
	eEnd
};

class SceneBase
{
protected:
	// ����̃����o�ϐ����K�v�ł���΁A�����Œ�`����
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


#pragma once
#include <vector>
#include "../Utility/InputControl.h"
#include "../Object/ObjectBase.h"

#define OBJECT_MAX 10

//�V�[���̎�ނ�񋓌^�Œ�`
enum class eSceneType
{
	eTitle = 0,
	eGameMain,
	eResult,
	eHelp,
	eRanking,
	eInput,
	eCredit,
	eEnd
};

class SceneBase
{
protected:
	// ����̃����o�ϐ����K�v�ł���΁A�����Œ�`����
	int limit_time = 0;

	int create_quantity_item = 0;  // ��ʓ��ɂ���A�C�e���̐�
	int create_enemy_max = 0;  // �G���������ꂽ�݌v��
	bool create_enemy = true;  // �G�������\��
	bool create_boss = false;  // �{�X�������\��
	bool is_boss;  // true = �{�X�������Ă���B���͖�����

	//�I�u�W�F�N�g�Ǘ��ϐ�
	std::vector<ObjectBase*>objects;
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

protected:
	//�Q�[���I�u�W�F�N�g�𐶐�����e���v���[�g�֐�
	template <class T>
	T* CreateObject(const Vector2D& _location, const Vector2D& _box_size)
	{
		//�V�����C���X�^���X�𐶐�
		T* new_instance = new T();

		ObjectBase* new_object = dynamic_cast<ObjectBase*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		}

		new_object->SetLocation(_location);

		new_object->Initialize(_location, _box_size);

		objects.push_back(new_object);
		if (new_object->GetObjectType() == eItem)
		{
			create_quantity_item++;
		}
		if (new_object->GetObjectType() == eEnemy)
		{
			create_enemy_max--;
		}

		//���������C���X�^���X��Ԃ�
		return new_instance;
	}

public:
	void DeleteObject(ObjectBase* obj);
};


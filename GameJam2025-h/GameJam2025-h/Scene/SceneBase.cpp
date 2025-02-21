#include "SceneBase.h"
#include <DxLib.h>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
	this->Finalize();
}

void SceneBase::Initialize()
{
}

eSceneType SceneBase::Update()
{
	//Object�̍X�V
	for (ObjectBase* obj : objects)
	{
		obj->Update();
	}

	// ��d���[�v�ŏՓ˔���
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			if (objects[i]->CheckBoxCollision(objects[j]))
			{
				objects[i]->OnHitCollision(objects[j]);
				objects[j]->OnHitCollision(objects[i]);
			}
		}
	}

	//�폜�t���O�������Ă���I�u�W�F�N�g���폜
	for (auto it = objects.begin(); it != objects.end();)
	{
		//�t���O�������Ă���̂Ȃ�
		if ((*it)->GetDeleteFlg()) {
			//�폜����
			DeleteObject(*it);
			//�폜�t���O�������Ă���I�u�W�F�N�g���폜
			it = objects.begin();
		}
		else
		{
			++it;
		}

	}
	return GetNowSceneType();
}

void SceneBase::Draw() const
{
	//Object�`��
	for (ObjectBase* obj : objects)
	{
		obj->Draw();
	}
}

void SceneBase::Finalize()
{
	//�I�u�W�F�N�g����̏ꍇ�͏������X�L�b�v
	if (objects.empty())
	{
		return;
	}

	for (ObjectBase* obj : objects)
	{
		obj->Finalize();

		delete obj;
	}

	objects.clear();
}

void SceneBase::DeleteObject(ObjectBase* obj)
{
	if (obj == nullptr) return;

	auto it = std::find(objects.begin(), objects.end(), obj);

	if (it != objects.end()) {
		//���������ꍇ�A�I�u�W�F�N�g���폜
		(*it)->Finalize(); //�I������
		delete* it;         //���������
		objects.erase(it);  //���X�g����폜
	}
}

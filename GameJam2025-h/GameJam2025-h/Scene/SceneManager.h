#pragma once
#include "SceneBase.h"
#include "GameScene/InGameScene.h"

class SceneManager
{
public:

private:
    static SceneManager* instance;
    SceneBase* current_scene;   //���݃V�[�����̃|�C���^

    int score = 0; // �X�R�A��ۑ�����ϐ�

public:
    //�R���X�g���N�^
    SceneManager();
    //�f�X�g���N�^
    ~SceneManager();

    // �R�s�[�֎~
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    //�C���X�^���X�擾���鏈��
    static SceneManager* GetInstance();
    //�C���X�^���X�̍폜
    static void DeleteInstance();

    void Initialize();  //����������
    void Update();      //�X�V����
    void Finalize();    //�I��������

    //�X�R�A�̐ݒ�
    void SetScore(int _score) { score = _score; }
    //�X�R�A�̎擾
    int GetScore() const { return score; }


    //�Q�[�����C���̎擾
    InGameScene* GetGameMainScene()
    {
        return dynamic_cast<InGameScene*>(current_scene);
    }

private:
    void Draw() const;  //�`�揈��

    //�V�[���ؑ֏���
    void ChangeScene(eSceneType type);

    //�V�[����������
    SceneBase* CreateScene(eSceneType type);
};


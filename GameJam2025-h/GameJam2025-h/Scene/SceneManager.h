#pragma once
#include "SceneBase.h"

class SceneManager
{
public:

private:
    static SceneManager* instance;
    SceneBase* current_scene;   //���݃V�[�����̃|�C���^

    int score = 0; // �X�R�A��ۑ�����ϐ�

public:
    SceneManager();
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

    SceneBase* GetCurrentScene() const;

    void SetScore(int _score) { score = _score; }
    int GetScore() const { return score; }

private:
    void Draw() const;  //�`�揈��

    //�V�[���ؑ֏���
    void ChangeScene(eSceneType type);

    //�V�[����������
    SceneBase* CreateScene(eSceneType type);
};


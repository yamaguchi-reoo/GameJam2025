#pragma once
#include "../Utility/Vector2D.h"
#include <vector>

//�Q�[�����̑S�ẴI�u�W�F�N�g�̊��N���X
//�ʒu�E�T�C�Y�E���x�E�A�j���[�V�����f�[�^�E�`����Ȃǂ��Ǘ�
class ObjectBase
{
protected:
    Vector2D location = { 0.0f };  //�I�u�W�F�N�g�̈ʒu
    Vector2D box_size = { 0.0f };  //�I�u�W�F�N�g�̃T�C�Y�i�����蔻��p�j
    Vector2D velocity = { 0.0f };  //�I�u�W�F�N�g�̈ړ����x

    std::vector<int> animation_data = {}; ///< �A�j���[�V�����f�[�^�i�t���[�����Ȃǁj

    int image = NULL;          //�`�悷��摜�f�[�^�̃n���h��
    bool flip_flg = false;     //�摜�����E���]����t���O
    bool delete_flg = false;   //�폜�t���O�itrue �̏ꍇ�I�u�W�F�N�g�͍폜�����j

public:
    //�R���X�g���N�^
    ObjectBase();

    //�f�X�g���N�^
    ~ObjectBase();

    //����������
    // _location �����ʒu
    // _box_size �����蔻��̃T�C�Y
    virtual void Initialize(Vector2D _location, Vector2D _box_size);

    //�X�V�����i�I�[�o�[���C�h���Ďg�p�j
    virtual void Update();

    //�`�揈���i�I�[�o�[���C�h���Ďg�p�j
    virtual void Draw() const;

    //�I�������i�I�[�o�[���C�h���Ďg�p�j
    virtual void Finalize();

public:
    //���W��ݒ�
    //_location �ݒ肷����W
    void SetLocation(Vector2D _location);

    //���W���擾
    //���݂̍��W
    Vector2D GetLocation() const;

    //�{�b�N�X�T�C�Y���擾
    //�����蔻��̃T�C�Y
    Vector2D GetBoxSize() const;

    //���x���擾
    //���݂̑��x
    Vector2D GetVelocity() const;

    //�I�u�W�F�N�g���m�̏Փˎ��ɌĂ΂��֐��i�I�[�o�[���C�h���Ďg�p�j
    //hit_object �Փ˂����I�u�W�F�N�g
    virtual void OnHitCollision(ObjectBase* hit_object);

    //��`�i�{�b�N�X�j���m�̓����蔻��`�F�b�N
    //�Փ˂��m�F����I�u�W�F�N�g
    //�Փ˂��Ă���ꍇ�� true
    bool CheckBoxCollision(ObjectBase* obj);

    //�폜�t���O�𗧂Ă�i�I�u�W�F�N�g���폜���邽�߂̏����j
    void SetDeleteFlg() { delete_flg = true; }

    //�폜�t���O���擾
    bool GetDeleteFlg() { return delete_flg; }
};

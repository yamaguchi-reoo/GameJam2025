#include "RankingInput.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

RankingInput::RankingInput() :backgrouond_image(NULL),
result_time(),result_name(),
name_num(),
cursor_x(),cursor_y()
{
}


RankingInput::~RankingInput()
{

}


//����������
void RankingInput::Initialize()
{
    memset(result_name, NULL, (sizeof(char) * 15));

    //���U���g�f�[�^���擾����
    FILE* fp = nullptr;
    //�t�@�C���I�[�v��
    errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "r");

    //�G���[�`�F�b�N
    if (result != 0)
    {
        throw("Resource/Data/Result.csv���ǂݍ��߂܂���\n");
    }

    //���ʂ�ǂݍ���
    fscanf_s(fp, "%d,%14s\n", &result_time, result_name[0], (unsigned int)sizeof(result_name));

    //�t�@�C���N���[�Y
    fclose(fp);
}


//�X�V����
eSceneType RankingInput::Update()
{
    bool is_change = false;

    //���O���͏���
    is_change = InputName();

    //�V�[���ύX�͉\��?
    if (is_change)
    {

        //���U���g�f�[�^���擾����
        FILE* fp = nullptr;
        //�t�@�C���I�[�v��
        errno_t result = fopen_s(&fp, "Resource/Data/Result.csv", "w");

        //�G���[�`�F�b�N
        if (result != 0)
        {
            throw("Resource/Data/Result.csv���ǂݍ��߂܂���\n");
        }

        //���ʂ�ǂݍ���
        fprintf(fp, "%d,%14s\n", result_time, result_name[0]);

        //�t�@�C���N���[�Y
        fclose(fp);

        //�����L���O�\���ɑJ��
        return eSceneType::eRanking;
    }
    else
    {
        return GetNowSceneType();
    }
}


//�`�揈��
void RankingInput::Draw()const
{
    int init_font_size = GetFontSize();
    SetFontSize(36);

    //�w�i�摜�̕`��
    DrawGraph(0, 0, backgrouond_image, TRUE);

    //���O���͎w��������̕`��
    DrawString(350, 100, "�����L���O�ɓo�^���܂�", 0xffffff);
    DrawFormatString(350, 220, GetColor(255, 255, 255), ">%s", result_name);

    //�I��p������`��
    const int font_size = GetFontSize();
    for (int i = 0; i < 26; i++)
    {
        int x = (i % 13) * font_size + 300;
        int y = (i / 13) * font_size + 300;
        DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'a' + i);
        y = ((i / 13) + 2) * font_size + 300;
        DrawFormatString(x, y, GetColor(255, 255, 255), "%-3c", 'A' + i);
    }
    DrawString(300, 600, "����", GetColor(255, 255, 255));
    DrawString(500, 600, "����", GetColor(255, 255, 255));

    //�I�𕶎����t�H�[�J�X����
    if (cursor_y < 4)
    {
        int x = cursor_x * font_size + 293;
        int y = cursor_y * font_size + 303;
        DrawBox(x, y, x + font_size, y + font_size, GetColor(255, 255, 255), FALSE);
    }
    else
    {
        if (cursor_x == 0)
        {
            DrawBox(300, 600, 300 + font_size * 2, 600 + font_size, GetColor(255, 255, 255), FALSE);
        }
        else
        {
            DrawBox(500, 600, 500 + font_size * 2, 600 + font_size, GetColor(255, 255, 255), FALSE);
        }
    }

    SetFontSize(init_font_size);
}


//�I��������
void RankingInput::Finalize()
{
    //�ǂݍ��񂾉摜���폜
    DeleteGraph(backgrouond_image);
}


//���݂̃V�[�������擾
eSceneType RankingInput::GetNowSceneType()const
{
    return eSceneType::eInput;
}


//���O�̓��͏���
bool RankingInput::InputName()
{
    InputControl* input = InputControl::GetInstance();
    //�J�[�\�����쏈��
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
    {
        if (cursor_x > 0)
        {
            if (cursor_y == 4)
            {
                cursor_x = 0;
            }
            else
            {
                cursor_x--;
            }
        }
        else
        {
            cursor_x = 12;
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
    {
        if (cursor_y == 4)
        {
            if (cursor_x == 1)
            {
                cursor_x = 0;
            }
            else
            {
                cursor_x = 1;
            }
        }
        else
        {
            if (cursor_x < 12)
            {
                cursor_x++;
            }
            else
            {
                cursor_x = 0;
            }
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
    {
        if (cursor_y > 0)
        {
            cursor_y--;
        }
        else
        {
            cursor_y = 4;
        }
    }
    if (input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
    {
        if (cursor_y < 4)
        {
            cursor_y++;
        }
        else
        {
            cursor_y = 0;
        }
    }

    //�J�[�\���ʒu�̕��������肷��
    if (input->GetButtonDown(XINPUT_BUTTON_B))
    {
        if (cursor_y < 2)
        {
            result_name[0][name_num++] = 'a' + cursor_x + (cursor_y * 13);
            if (name_num == 14)
            {
                cursor_x = 0;
                cursor_y = 4;
            }
        }
        else if (cursor_y < 4)
        {
            result_name[0][name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);
            if (name_num == 14)
            {
                cursor_x = 0;
                cursor_y = 4;
            }
        }
        else
        {
            if (cursor_x == 0)
            {
                result_name[0][name_num] = '\0';
                return true;
            }
            else
            {
                result_name[0][--name_num] = NULL;
            }
        }
    }

    return false;
}

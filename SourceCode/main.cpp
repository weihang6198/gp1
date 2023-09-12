//******************************************************************************
//
//
//      main
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< �ϐ� >----------------------------------------------------------------
int curScene    = SCENE_NONE;
int nextScene   = SCENE_TITLE;
//ssss
//--------------------------------------
//  WinMain�i�G���g���|�C���g�j
//--------------------------------------
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    GameLib::init(L"�Q�[���v���O���~���O�T", SCREEN_W, SCREEN_H);

    // �I�[�f�B�I�̏����ݒ�
    audio_init();

    while (GameLib::gameLoop())
    {
        // �V�[���؂�ւ�����
        if (curScene != nextScene)
        {
            // ���݂̃V�[���ɉ������I������
            switch (curScene)
            {
            case SCENE_TITLE:
                title_deinit();
                break;

            case SCENE_GAME:
                game_deinit();
                break;
            case SCENE_GAMEOVER:
                over_deinit();
            }

            // ���̃V�[���ɉ����������ݒ菈��
            switch (nextScene)
            {
            case SCENE_TITLE:
                title_init();
                break;

            case SCENE_GAME:
                game_init();
                break;
            case SCENE_GAMEOVER:
                over_init();
            }

            curScene = nextScene;
        }

        // ���͂��X�V����
        input::update();

        // ���y�̍X�V����
        music::update();

        // ���݂̃V�[���ɉ������X�V�E�`�揈��
        switch (curScene)
        {
        case SCENE_TITLE:
            title_update();
            title_render();
            break;

        case SCENE_GAME:
            game_update();
            game_render();
            break;
        case SCENE_GAMEOVER:
            over_update();
            over_render();
            break;
        }

        // �f�o�b�O������̕`��
        debug::display(1.0f, 1.0f, 1.0f, 1, 1);

        //debug::setString("GP1_09 SAMPLE");

        // �o�b�N�o�b�t�@�̓��e��\��
        GameLib::present(1, 0);
    }

    // ���݂̃V�[���ɉ������I������
    switch (curScene)
    {
    case SCENE_TITLE:
        title_deinit();
        break;

    case SCENE_GAME:
        game_deinit();
        break;
    case SCENE_GAMEOVER:
        over_deinit();
        break;
    }

    // �I�[�f�B�I�̏I������
    audio_deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();

    return 0;
}
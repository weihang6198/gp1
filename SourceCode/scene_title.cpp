#include "all.h"

int title_state;
int title_timer;
int gamestart = 1;
Sprite* sprbg;
Sprite* sprhelp;

//--------------------------------------
//  �����ݒ�
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
}

//--------------------------------------
//  �I������
//--------------------------------------
void title_deinit()
{
    music::stop(0);

    safe_delete(sprbg);
    safe_delete(sprhelp);
}

//--------------------------------------
//  �^�C�g���̍X�V����
//--------------------------------------
void title_update()
{
    switch (title_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprbg = sprite_load(L"./Data/Images/back1.png");

        sprhelp = sprite_load(L"./Data/Images/help1.png");
        title_state++;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.1f);

        title_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        if ((gamestart==1) && (TRG(0) & PAD_START))
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);

            nextScene = SCENE_GAME;
            break;
        }

        if (TRG(0) & PAD_RIGHT)
        {

            sprbg = sprite_load(L"./Data/Images/back2.png");
            gamestart = 0;
            break;
        }
        else if (TRG(0) & PAD_LEFT) {
            sprbg = sprite_load(L"./Data/Images/back1.png");
            gamestart = 1;

            break;
        }
        if ((gamestart == 0) && (TRG(0) & PAD_START)) {
            sprbg = sprite_load(L"./Data/Images/help1.png");
            gamestart = 2;
            break;
        }
        if ((gamestart == 2) && (TRG(0) & PAD_START)) {
            sprbg = sprite_load(L"./Data/Images/help2.png");
            gamestart = 1;
        }
        

        break;
    

    }
    

    title_timer++;
}

//--------------------------------------
//  �^�C�g���̕`�揈��
//--------------------------------------
void title_render()
{
    // ��ʂ�œh��Ԃ�
    GameLib::clear(0.3f, 0.5f, 1.0f);

    // �^�C�g���̕���
    font::textOut(4, "ECC COMP", VECTOR2(100, 80), VECTOR2(2.4f, 2.4f), VECTOR4(1, 0.8f, 0, 1));
    font::textOut(4, "Game Programming I", VECTOR2(80, 180), VECTOR2(2.0f, 2.0f), VECTOR4(0, 1, 0.6f, 1));

    // "Push Enter Key" �_��
    if (title_timer >> 5 & 0x01)
    {
        font::textOut(4, "Push Enter Key", VECTOR2(120, 560), VECTOR2(1.4f, 1.4f));
    }

    sprite_render(sprbg, 0, 0);
}

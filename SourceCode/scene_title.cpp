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
        music::setVolume(0, 0.15f);

        title_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        if ((gamestart==1) && (TRG(0) & PAD_START))
        {
            sound::play(4, 2);

            nextScene = SCENE_GAME;
            break;
        }

        if (TRG(0) & PAD_RIGHT)
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back2.png");
            gamestart = 0;
            break;
        }
        else if (TRG(0) & PAD_LEFT) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back1.png");
            gamestart = 1;

            break;
        }
        if ((gamestart == 0) && (TRG(0) & PAD_START)) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help1.png");
            gamestart = 2;
            break;
        }
        if ((gamestart == 2) && (TRG(0) & PAD_START)) {
            sound::play(4, 2);
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
   

    // "Push Enter Key" �_��
    

    sprite_render(sprbg, 0, 0);

    font::textOut(4, "A<-   |   D->", VECTOR2(460, 630), VECTOR2(1.4f, 1.4f));
    font::textOut(4, "Press ENTER to select", VECTOR2(320, 670), VECTOR2(1.4f, 1.4f));
}

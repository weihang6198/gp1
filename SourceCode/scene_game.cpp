//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< �C���N���[�h >-----------------------------------------------------------
#include "all.h"
#include "player.h"
#include "enemy.h"
#include "item.h"


//------< �萔 >----------------------------------------------------------------


//------< �\���� >---------------------------------------------------------------


//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;
int mapPosX;
int map2PosX = 1280;
bool moveFirstMap = true;
bool moveSecondMap = false;
Sprite* sprBack;

//--------------------------------------
//  �Q�[���̏����ݒ�
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
    //consumable_init();
}

//--------------------------------------
//  �Q�[���̏I������
//--------------------------------------
void game_deinit()
{
#if 11
//******************************************************************************
// TODO:11 �v���C���[�̏I�������֐����Ăяo��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player_deinit�֐����Ăт܂��傤�B
*/
//******************************************************************************
#endif
    //TODO_11

    item_deinit();
    meteor_deinit();
    player_deinit();
    safe_delete(sprBack);
}

//--------------------------------------
//  �Q�[���̍X�V����
//--------------------------------------
void game_update()
{
    switch (game_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprBack = sprite_load(L"./Data/Images/space.png");

#if 10
//******************************************************************************
// TODO:10 �v���C���[�̏����ݒ�֐����Ăяo��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player_init�֐����Ăт܂��傤�B

����j
    ��������Aplayer�֘A�̊֐����Ăяo���Ă����܂��B�ǂ��ŉ��̊֐����Ăяo����
    ����̂���c�����Ă����܂��傤�B
*/
//******************************************************************************
#endif
        //TODO_10


        game_state++;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //GameLib::setBlendMode(Blender::BS_ALPHA);

       mapPosX = 0;
        game_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        debug::setString("");
        debug::setString("A D   : LEFT, RIGHT");
        debug::setString("SPACE : JUMP");
        debug::setString("");
        debug::setString("map pos x is %d", mapPosX);
        debug::setString("map 2 pos x is %d", map2PosX);
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }
        //screen size is 1280
        //image is 1920x1080
        //1920-1280=640
        //640 is where the blank will appear and it has to be replace with the new image
    /*    if (mapPosX <= -645)
        {

        }
        else
        {
            mapPosX -= 10;
        }*/
        if (mapPosX < -1900  ) // #3
        {
            mapPosX = 1280;
            moveFirstMap = false;
        }
        else if(moveFirstMap)  // #1
        {
            mapPosX -= 5;
        }
      
        if (mapPosX < -640 ||moveSecondMap ) //#2
        {
            moveSecondMap = true;
            map2PosX -= 5;
        }
        if (map2PosX < -1900) //#5
        {
            map2PosX = 1280;
            moveSecondMap = false;
        }
         if (map2PosX < -640)  //#4
        {
            moveFirstMap = true;   
        }

     
       
        item_update();
        player_update();
        meteor_update(); 
        spaceShip->collisionDetector(spaceShip, &meteor);
        for (int i = 0; i < MAX_ITEM; i++)
        {
            if (item[i]) 
            {
                spaceShip->collisionDetector(spaceShip, item[i]);
            }
          
        }
      

       
        break;
    }

    game_timer++;
}

//--------------------------------------
//  �Q�[���̕`�揈��
//--------------------------------------
void game_render()
{
    GameLib::clear(0.2f, 0.2f, 0.4f);
    //firrst screen
    if (moveFirstMap)
        {
        sprite_render(sprBack, mapPosX, 0,
            1.1, 1.1); //scale
        }
      
        if (moveSecondMap)
        {
            debug::setString("second screen");
            sprite_render(sprBack, map2PosX , 0,
                1.1, 1.1); //scale
        }
  
    item_render();
    player_render();
    meteor_render(); 


#if 13
//******************************************************************************
// TODO:13 �v���C���[�̕`��֐����Ăяo��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player_render�֐����Ăт܂��傤�B

    ����ŁA�v���C���[����ʂɕ\������܂��B���s���Ă݂܂��傤�B
*/
//******************************************************************************
#endif
    //TODO_13

}

void game_reset()
{
    game_state = 0;
    meteor_state = 0;
    player_state = 0;
    item_state = 0;

  
}

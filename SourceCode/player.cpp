#include "all.h"
#include<string>
using namespace std;
int     player_state;

#if 3
//******************************************************************************
// TODO:03 OBJ2D�^�̕ϐ�player��錾
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��OBJ2D�^�̕ϐ�player��錾���܂��傤�B
*/
//******************************************************************************
#endif
//TODO_03


Sprite* spaceShipSpr;
SPACE_SHIP spaceShip;
Sprite* beamSpr;
BEAM beam;
//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{ 

    player_state = 0;

}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{

    safe_delete(spaceShipSpr);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        spaceShipSpr = sprite_load(L"./Data/Images/spaceship3.png");
        beamSpr = sprite_load(L"./Data/Images/beam.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        spaceShip.spaceShipInit();
        beam.beamInit();
        ++player_state;
        /*fallthrough*/
        
    case 2:
        spaceShip.pos.x += spaceShip.speed.x;
        spaceShip.pos.y += spaceShip.speed.y;
        //testing for pushing and pull
        spaceShip.updateCollisionCoord(&spaceShip.collisionCoord, spaceShip.pos.x, spaceShip.pos.x + spaceShip.inGameSize.x,
            spaceShip.pos.y, spaceShip.pos.y + spaceShip.inGameSize.y);
        player_moveX();
        player_moveY();
        triggerAccelerateMode();


        debug::setString("turbo mode is %d", spaceShip.turboMode);
        debug::setString("player speed x is %f", spaceShip.speed.x);

    
        break;
    }
}

void player_render()
{
#if 9
    //******************************************************************************
    // TODO:09 �v���C���[�̕`��
    //------------------------------------------------------------------------------
    /*
    �ۑ�j
        ���L��spaceShipSpr��`�悵�܂��傤�B

    ����j
        ���ɕK�v�ȃp�����[�^�͊�{�I��OBJ2D�\���̂̃����o�ϐ��ɂȂ��Ă��܂��BOBJ2D�^��
        player�̃����o�ϐ����L�q���Ă����܂��傤�B�p�x�̂݁AToRadian(0)��OK�ł��B
        �F��VECTOR4�^�ł��BVECTOR4�^�̒��g��x, y, z, w�ł��B�F��r, g, b, a�Ȃ̂ŁA
        ���̏��ԂőΉ����Ă��܂��B�i�Ⴆ��r��x�ŁAa��w�ŕ\���Ȃǁj
    */
    //******************************************************************************
#endif
    //TODO_09

    //rendering for spaceship
    sprite_render(spaceShipSpr,
        spaceShip.pos.x, spaceShip.pos.y, //pos
        spaceShip.scale.x, spaceShip.scale.y, //scale
        spaceShip.texPos.x, spaceShip.texPos.y, //texture pos
        spaceShip.texSize.x, spaceShip.texSize.y,//texture width and height
        spaceShip.pivot.x, spaceShip.pivot.y, 0);
    spaceShip.drawCollision(spaceShip.pos.x, spaceShip.pos.y,spaceShip.inGameSize.x, spaceShip.inGameSize.y);
            
    //rendering for beam
    sprite_render(beamSpr,
       beam.pos.x,beam.pos.y, //pos
       beam.scale.x,beam.scale.y, //scale
       beam.texPos.x,beam.texPos.y, //texture pos
       beam.texSize.x,beam.texSize.y,//texture width and height
       beam.pivot.x,beam.pivot.y, 0);
   beam.drawCollision(spaceShip.pos.x,beam.pos.y,beam.inGameSize.x, beam.inGameSize.y);
}

void player_moveY()
{
    if (STATE(0) & PAD_DOWN)
    {
        spaceShip.speed.y += 1;
        if (spaceShip.speed.y > spaceShip.maxSpeed.y)
        {
            spaceShip.speed.y = spaceShip.maxSpeed.y;
        }
    }
    else if (STATE(0) & PAD_UP)
    {
        spaceShip.speed.y += -1;
        if (spaceShip.speed.y < -spaceShip.maxSpeed.y)
        {
            spaceShip.speed.y = -spaceShip.maxSpeed.y;
        }
    }
    else
    {
        spaceShip.speed.y = 0;
    }
}

void triggerAccelerateMode()
{
    if (TRG(0) &PAD_TRG1 )
    {
        if (spaceShip.maxSpeed.x == 15)
        {
            spaceShip.maxSpeed = { 7,7 };
            spaceShip.turboMode = false;
        }
        else
        {
            spaceShip.maxSpeed = { 15,15 };
           spaceShip.turboMode = true;
        }
     
    }
}

void player_moveX()
{
    //move right
    if (STATE(0) & PAD_RIGHT)
    {
        spaceShip.speed.x += 1;
        if (spaceShip.speed.x > spaceShip.maxSpeed.x)
        {
            spaceShip.speed.x = spaceShip.maxSpeed.x;
        }
      
    }
    else if (STATE(0) & PAD_LEFT)
    {
        spaceShip.speed.x +=- 1;
        if (spaceShip.speed.x < -spaceShip.maxSpeed.x)
        {
            spaceShip.speed.x = -spaceShip.maxSpeed.x;
        }
     
    }
    else
    {
       
       /* player.speed.x -= 0.1;
        if (player.speed.x < 0)
        {
            player.speed.x = 0;
        }*/
        spaceShip.speed.x = 0;
    }
       
    


}

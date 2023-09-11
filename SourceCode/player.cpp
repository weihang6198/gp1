#include "all.h"
#include<string>
using namespace std;


#if 3
//******************************************************************************
// TODO:03 OBJ2D型の変数playerを宣言
//------------------------------------------------------------------------------
/*
課題）
    下記でOBJ2D型の変数playerを宣言しましょう。
*/
//******************************************************************************
#endif
//TODO_03


Sprite* spaceShipSpr;
SPACE_SHIP* spaceShip;
Sprite* beamSpr;
BEAM *beam[99];
int player_state = 0;
//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{ 

    player_state = 0;

}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{

    safe_delete(spaceShipSpr);
    safe_delete(spaceShip);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        spaceShipSpr = sprite_load(L"./Data/Images/spaceship_renya.png");
        beamSpr = sprite_load(L"./Data/Images/beam.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        spaceShip = new SPACE_SHIP(); 
        spaceShip->spaceShipInit();
        //for (int i = 0; i <MAX_BULLET; i++)
        //{
        //    beam[i] = new BEAM();
        //    beam[i]->beamInit();
        //   // beam[i]->canFire = false;
        //}
      
        ++player_state;
        /*fallthrough*/
        
    case 2:
        spaceShip->pos.x += spaceShip->speed.x;
        spaceShip->pos.y += spaceShip->speed.y;
        //testing for pushing and pull
        spaceShip->updateCollisionCoord(&spaceShip->collisionCoord, spaceShip->pos.x, spaceShip->pos.x + spaceShip->inGameSize.x,
            spaceShip->pos.y, spaceShip->pos.y + spaceShip->inGameSize.y);
        //player movement
        player_moveX();
        player_moveY();
        triggerAccelerateMode();
        fireBeam();
        debug::setString("player life is %d", spaceShip->life);
        debug::setString("turbo mode is %d", spaceShip->turboMode);
        debug::setString("player speed x is %f", spaceShip->speed.x);
        
       
    
        break;
    }
}

void player_render()
{
#if 9
    //******************************************************************************
    // TODO:09 プレイヤーの描画
    //------------------------------------------------------------------------------
    /*
    課題）
        下記でspaceShipSprを描画しましょう。

    解説）
        他に必要なパラメータは基本的にOBJ2D構造体のメンバ変数になっています。OBJ2D型の
        playerのメンバ変数を記述していきましょう。角度のみ、ToRadian(0)でOKです。
        色はVECTOR4型です。VECTOR4型の中身はx, y, z, wです。色はr, g, b, aなので、
        その順番で対応しています。（例えばrはxで、aはwで表すなど）
    */
    //******************************************************************************
#endif
    //TODO_09

    //rendering for spaceship
    sprite_render(spaceShipSpr,
        spaceShip->pos.x, spaceShip->pos.y, //pos
        spaceShip->scale.x, spaceShip->scale.y, //scale
        spaceShip->texPos.x, spaceShip->texPos.y, //texture pos
        spaceShip->texSize.x, spaceShip->texSize.y,//texture width and height
        spaceShip->pivot.x, spaceShip->pivot.y, 0);
    spaceShip->drawCollision(spaceShip->pos.x, spaceShip->pos.y,spaceShip->inGameSize.x, spaceShip->inGameSize.y);
            
    //rendering for beam
    for (int i = 0; i < 90; i++)
    {
        if (beam[i])
        {
            if (beam[i]->visibility)
            {
                sprite_render(beamSpr,
                    beam[i]->pos.x, beam[i]->pos.y, //pos
                    beam[i]->scale.x, beam[i]->scale.y, //scale
                    beam[i]->texPos.x, beam[i]->texPos.y, //texture pos
                    beam[i]->texSize.x, beam[i]->texSize.y,//texture width and height
                    beam[i]->pivot.x, beam[i]->pivot.y, 0);
             
                beam[i]->drawCollision(beam[i]->collisionCoord.left, beam[i]->collisionCoord.top, beam[i]->inGameSize.x, beam[i]->inGameSize.y);
            }
        }
      
      
    }
  
   //beam.drawCollision(beam.pos.x,beam.pos.y,beam.inGameSize.x, beam.inGameSize.y);
}

void player_moveY()
{
    if (STATE(0) & PAD_DOWN)
    {
        spaceShip->speed.y += 1;
        if (spaceShip->speed.y > spaceShip->maxSpeed.y)
        {
            spaceShip->speed.y = spaceShip->maxSpeed.y;
        }
    }
    else if (STATE(0) & PAD_UP)
    {
        spaceShip->speed.y += -1;
        if (spaceShip->speed.y < -spaceShip->maxSpeed.y)
        {
            spaceShip->speed.y = -spaceShip->maxSpeed.y;
        }
    }
    else
    {
        spaceShip->speed.y = 0;
    }
}

void triggerAccelerateMode()
{
    if (TRG(0) &PAD_TRG1 )
    {
        if (spaceShip->maxSpeed.x == 15)
        {
            spaceShip->maxSpeed = { 7,7 };
            spaceShip->turboMode = false;
        }
        else
        {
            spaceShip->maxSpeed = { 15,15 };
           spaceShip->turboMode = true;
        }
     
    }
}

void fireBeam()
{
    if (TRG(0) & PAD_TRG4)
    {
      //  OutputDebugStringA("firing beam");
        //create beam obj as soon as fire trigger is pressed
        beam[spaceShip->beamCount] = new BEAM();
        beam[spaceShip->beamCount]->beamInit();
        beam[spaceShip->beamCount]->canFire = true;
        beam[spaceShip->beamCount]->visibility = true;
        spaceShip->beamCount++;
       
    }
   for (int i=0;i< spaceShip->beamCount;i++  )
   {
       if (beam[i])
       {
           if (beam[i]->canFire)
           {
              /* debug::setString("obj1->collided is %d", beam[i]->collided);
               debug::setString(" i is %d", i);*/
               //set init spawn loc of the beam
               if (!beam[i]->setInitLoc)
               {
                   beam[i]->setInitLoc = true;
                   beam[i]->pos.x = spaceShip->pos.x+45;
                   beam[i]->pos.y = spaceShip->pos.y+43;
                   beam[i]->collisionCoord =
                   { beam[i]->pos.x,beam[i]->pos.x + beam[i]->inGameSize.x ,
                     beam[i]->pos.y,beam[i]->pos.y + beam[i]->inGameSize.y };
               }
               //update beam's loc,collision cord and check for collision detector
               beam[i]->pos.x += beam[i]->maxSpeed.x;
               beam[i]->updateCollisionCoord(&beam[i]->collisionCoord, beam[i]->pos.x, beam[i]->pos.x + beam[i]->inGameSize.x,
                   beam[i]->pos.y, beam[i]->pos.y + beam[i]->inGameSize.y);
               beam[i]->collisionDetector(beam[i], &meteor);
               if (beam[i]->destroySelf)
               {
                   safe_delete(beam[i]);
                   break;
               }
               if (beam[i]->pos.x > SCREEN_W)
               {
                   safe_delete(beam[i]);
               }
              
           }
       }
     
    }
}


void player_moveX()
{
    //move right
    if (STATE(0) & PAD_RIGHT)
    {
        spaceShip->speed.x += 1;
        if (spaceShip->speed.x > spaceShip->maxSpeed.x)
        {
            spaceShip->speed.x = spaceShip->maxSpeed.x;
        }
      
    }
    else if (STATE(0) & PAD_LEFT)
    {
        spaceShip->speed.x +=- 1;
        if (spaceShip->speed.x < -spaceShip->maxSpeed.x)
        {
            spaceShip->speed.x = -spaceShip->maxSpeed.x;
        }
     
    }
    else
    {
       
  
        spaceShip->speed.x = 0;
    }       
    

}


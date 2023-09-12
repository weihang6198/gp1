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
Sprite* HPSpr[3];

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
    for (int i = 0; i < spaceShip->beamCount; i++)
    {
        if (beam[i])
        {
            safe_delete(beam[i]);
        }
    }
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
        for (int i = 0; i < MAX_LIFE; i++)
        {
           HPSpr[i] = sprite_load(L"./Data/Images/filled_HP.png");
        }
       
        ++player_state;
        /*fallthrough*/

    case 1:
        spaceShip = new SPACE_SHIP(); 
        spaceShip->spaceShipInit();
        for (int i = 0; i < MAX_LIFE; i++)
        {
            spaceShip->HPSpr[i] = HPSpr[i];
      }
      
        ++player_state;
        /*fallthrough*/
        
    case 2:
      
        //player movement
        spaceShipLogic();

        debug::setString("player life is %d", spaceShip->currentLife);
        debug::setString("turbo mode is %d", spaceShip->turboMode);
        debug::setString("player speed x is %f", spaceShip->speed.x);
        //debug::setString("player hp is %d",spaceShip->)
      
        break;
    }
}

void player_render()
{
    // spaceShip->sprImg = sprite_load(L"./Data/Images/empty_HP.png");
   
        for (int i = 0; i < MAX_LIFE ; i++)
        {

            sprite_render(spaceShip->HPSpr[i], 25 + i * 70, 10,
                0.6, 0.6); //scale
        }
    
    
 
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
             
               // beam[i]->drawCollision(beam[i]->collisionCoord.left, beam[i]->collisionCoord.top, beam[i]->inGameSize.x, beam[i]->inGameSize.y);
            }
        }
    }
  
}

void spaceShipLogic()
{
    spaceShip->pos.x += spaceShip->speed.x;
    spaceShip->pos.y += spaceShip->speed.y;
    //testing for pushing and pull
    spaceShip->updateCollisionCoord(&spaceShip->collisionCoord, spaceShip->pos.x, spaceShip->pos.x + spaceShip->inGameSize.x,
        spaceShip->pos.y, spaceShip->pos.y + spaceShip->inGameSize.y);
    player_moveX();
    player_moveY();
    triggerAccelerateMode();
    fireBeam();
    LimitSpaceShipToScreen();
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
        if (spaceShip->maxSpeed.x == MAX_SPEED)
        {
            spaceShip->maxSpeed = { MIN_SPEED,MIN_SPEED };
            spaceShip->turboMode = false;
        }
        else
        {
            spaceShip->maxSpeed = { MAX_SPEED,MAX_SPEED };
           spaceShip->turboMode = true;
        }
     
    }
}

void fireBeam()
{
    if (TRG(0) & PAD_TRG4)
    {
        sound::play(4, 1);
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
                   beam[i]->pos.y = spaceShip->pos.y+25;
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

void  LimitSpaceShipToScreen()
{
    if (spaceShip->pos.x < 0)
    {
        spaceShip->pos.x = 0;
    }

    if (spaceShip->pos.y < 0)

    {
        spaceShip->pos.y = 0;

    }

    if (spaceShip->pos.y + spaceShip->inGameSize.y > SCREEN_H)
    {
        debug::setString("over the line");
        spaceShip->pos.y = SCREEN_H - spaceShip->inGameSize.y;
    }

    if (spaceShip->pos.x + spaceShip->inGameSize.x > SCREEN_W)
    {
        spaceShip->pos.x = SCREEN_W - spaceShip->inGameSize.x;
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


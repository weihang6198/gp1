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
Sprite* batterySpr;
Sprite* panelSpr;

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
        batterySpr = sprite_load(L"./Data/Images/battery.png");
        panelSpr= sprite_load(L"./Data/Images/panel.png");
        
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
        batteryLogic();
       /* debug::setString("player life is %d", spaceShip->currentLife);
        debug::setString("turbo mode is %d", spaceShip->turboMode);
        debug::setString("player speed x is %f", spaceShip->speed.x);
        debug::setString("battery life  is %f", spaceShip->batteryLife);*/
       
        //debug::setString("player hp is %d",spaceShip->)
        if (spaceShip->processTimer)
        {
            if (spaceShip->timer < 100)
            {
                spaceShip->timer++;
                spaceShip->color.a = spaceShip->timer%7;
               // debug::setString("timer is %d", spaceShip->timer);
            }
            else
            {
                spaceShip->color.a = 1;
                spaceShip->timer = 0;
                spaceShip->collided = false;
                spaceShip->processTimer = false;
            }
          
        }
        break;
    }
}

void player_render()
{
  //  sprite_render(panelSpr)
    

   
    sprite_render(panelSpr, 0, 560,0.68,0.6);
    //background rect
   // primitive::rect(900, 640, 350, 40);
    //the battery gauge panel
    primitive::rect(895, 632, 340*(spaceShip->batteryLife/100), 45,
        0,0,0,
        1,0,0);
    //primitive::line(0, 600, 1280, 600, 1, 1, 1, 1, 5);
    //for hp
        for (int i = 0; i < MAX_LIFE ; i++)
        {
            sprite_render(spaceShip->HPSpr[i], 30 + i * 80, 627,
                0.6, 0.6); //scale
        }
    
     //sprite_render(batterySpr, 860, 635, 0.4, 0.6);
 
    //rendering for spaceship
    sprite_render(spaceShipSpr,
        spaceShip->pos.x, spaceShip->pos.y, //pos
        spaceShip->scale.x, spaceShip->scale.y, //scale
        spaceShip->texPos.x, spaceShip->texPos.y, //texture pos
        spaceShip->texSize.x, spaceShip->texSize.y,//texture width and height
        spaceShip->pivot.x, spaceShip->pivot.y, 0,
        spaceShip->color.r, spaceShip->color.g, spaceShip->color.b, spaceShip->color.a);
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
    /*if (spaceShip->battery == 0)
    {
        spaceShip->batteryDepleted =true;
    }*/
    if (spaceShip->batteryLife>0)
    {
      //  debug::setString("inside moving");
        spaceShip->pos.x += spaceShip->speed.x;
        spaceShip->pos.y += spaceShip->speed.y;
        //testing for pushing and pull
        spaceShip->updateCollisionCoord(&spaceShip->collisionCoord, spaceShip->pos.x, spaceShip->pos.x + spaceShip->inGameSize.x,
            spaceShip->pos.y, spaceShip->pos.y + spaceShip->inGameSize.y);
        player_moveX();
        player_moveY();
        triggerAccelerateMode();
        
        LimitSpaceShipToScreen();
    }
    fireBeam();
  
}
void batteryLogic()
{
    if (spaceShip->batteryLife < 0)
    {
        spaceShip->batteryLife = 0;
    }
    else
    {
        if (spaceShip->turboMode)
        {
            spaceShip->batteryLife -= TURBO_BATTERY_USAGE;
        }
        else
        {
            spaceShip->batteryLife -= DEFAULT_BATTERY_USAGE;
        }
    }
   
   
 
}
void player_moveY()
{
    if (STATE(0) & PAD_DOWN)
    {
        if (spaceShip->speed.y < 0)
        {
            spaceShip->speed.y = 0;
        }
        spaceShip->speed.y += 1;
        if (spaceShip->speed.y > spaceShip->maxSpeed.y)
        {
            spaceShip->speed.y = spaceShip->maxSpeed.y;
        }
    }
    else if (STATE(0) & PAD_UP)
    {
        if (spaceShip->speed.y > 0)
        {
            spaceShip->speed.y = 0;
        }
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
            sound::stop(4, 5);
            sound::setVolume(4, 6, 3.0f);
            sound::play(4, 6);
         
            spaceShip->maxSpeed = { MIN_SPEED,MIN_SPEED };
            spaceShip->turboMode = false;
        }
        else
        {
            sound::stop(4, 6);
            sound::setVolume(4, 5, 0.4f);
            sound::play(4, 5);
            spaceShip->maxSpeed = { MAX_SPEED,MAX_SPEED };
           spaceShip->turboMode = true;
        }
     
    }
}

void fireBeam()
{
    
    if (TRG(0) & PAD_TRG4)
    {
        if (spaceShip->batteryLife>0)
        {

            sound::play(4, 1);
            //  OutputDebugStringA("firing beam");
              //create beam obj as soon as fire trigger is pressed
            beam[spaceShip->beamCount] = new BEAM();
            beam[spaceShip->beamCount]->beamInit();
            beam[spaceShip->beamCount]->canFire = true;
            beam[spaceShip->beamCount]->visibility = true;
            spaceShip->beamCount++;
            spaceShip->batteryLife-=3;
        }
    }
        for (int i = 0; i < spaceShip->beamCount; i++)
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
                        beam[i]->pos.x = spaceShip->pos.x + 45;
                        beam[i]->pos.y = spaceShip->pos.y + 25;
                        beam[i]->collisionCoord =
                        { beam[i]->pos.x,beam[i]->pos.x + beam[i]->inGameSize.x ,
                          beam[i]->pos.y,beam[i]->pos.y + beam[i]->inGameSize.y };
                    }
                    //update beam's loc,collision cord and check for collision detector
                    beam[i]->pos.x += beam[i]->maxSpeed.x;
                    beam[i]->updateCollisionCoord(&beam[i]->collisionCoord, beam[i]->pos.x, beam[i]->pos.x + beam[i]->inGameSize.x,
                        beam[i]->pos.y, beam[i]->pos.y + beam[i]->inGameSize.y);
                    for (int z = 0; z < METEOR_MAX; z++)
                    {
                        if (meteor[z])
                        {
                            beam[i]->collisionDetector(beam[i], meteor[z]);
                        }

                    }
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

    if (spaceShip->pos.y + spaceShip->inGameSize.y > SCREEN_H-120)
    {
        debug::setString("over the line");
        spaceShip->pos.y = SCREEN_H-120 - spaceShip->inGameSize.y;
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
        if (spaceShip->speed.x < 0)
        {
            spaceShip->speed.x = 0; //this is to make sure the ship doesnt have the short delay
        }
        spaceShip->speed.x += 1;
        if (spaceShip->speed.x > spaceShip->maxSpeed.x)
        {
            spaceShip->speed.x = spaceShip->maxSpeed.x;
        }
      
    }
    else if (STATE(0) & PAD_LEFT)
    {
        if (spaceShip->speed.x > 0)
        {
            spaceShip->speed.x = 0; //this is to make sure the ship doesnt have the short delay
        }
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


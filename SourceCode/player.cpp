#include "all.h"
#include<string>
using namespace std;
int     player_state;

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

//test retarget
//test 
//test
//msg to pain
//
//msg from 
Sprite* spaceShipSpr;
SPACE_SHIP spaceShip;
bool turboMode;
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
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        spaceShipSpr = sprite_load(L"./Data/Images/spaceship3.png");


        ++player_state;
        /*fallthrough*/

    case 1:
        spaceShip.pos = { 300,100 };
        spaceShip.scale = { 1,1 };
        spaceShip.texPos = { 0,0 };
        spaceShip.texSize = {173,231}; //spaceship size is 173x231
        spaceShip.pivot = { 0,0 };
        spaceShip.color = { 1,1,1,1 };
        spaceShip.speed = { 0 ,0 };
        spaceShip.maxSpeed = { 7,7 };
        spaceShip.fuel = 100;
        turboMode = false;
        ++player_state;
        /*fallthrough*/
        
    case 2:
        spaceShip.pos.x += spaceShip.speed.x;
        spaceShip.pos.y += spaceShip.speed.y;
        //testing for pushing and pull
        player_moveX();
        player_moveY();
        triggerAccelerateMode();
        debug::setString("turbo mode is %d", turboMode);
        debug::setString("player speed x is %f", spaceShip.speed.x);

    
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

    sprite_render(spaceShipSpr,
        spaceShip.pos.x, spaceShip.pos.y, //pos
        spaceShip.scale.x, spaceShip.scale.y, //scale
        spaceShip.texPos.x, spaceShip.texPos.y, //texture pos
        spaceShip.texSize.x, spaceShip.texSize.y,//texture width and height
        spaceShip.pivot.x, spaceShip.pivot.y, 0);
    spaceShip.drawCollision(spaceShip.pos.x, spaceShip.pos.y, spaceShip.texSize.x, spaceShip.texSize.y);
            
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
            turboMode = false;
        }
        else
        {
            spaceShip.maxSpeed = { 15,15 };
            turboMode = true;
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
        OutputDebugStringA("button pressed");
    }
    else if (STATE(0) & PAD_LEFT)
    {
        spaceShip.speed.x +=- 1;
        if (spaceShip.speed.x < -spaceShip.maxSpeed.x)
        {
            spaceShip.speed.x = -spaceShip.maxSpeed.x;
        }
        OutputDebugStringA("button pressed");
    }
    else
    {
        debug::setString("pad right rleeased");
       /* player.speed.x -= 0.1;
        if (player.speed.x < 0)
        {
            player.speed.x = 0;
        }*/
        spaceShip.speed.x = 0;
    }
       
    


}

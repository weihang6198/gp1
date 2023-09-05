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

//test 
//test
//msg to pain
//msg from miya
Sprite* sprPlayer;
OBJ2D player;
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

    safe_delete(sprPlayer);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        sprPlayer = sprite_load(L"./Data/Images/spaceship.png");


        ++player_state;
        /*fallthrough*/

    case 1:
        player.pos = { 300,100 };
        player.scale = { 0.3,0.3 };
        player.texPos = { 0,0 };
        player.texSize = { 500,500 };
        player.pivot = { 0,0 };
        player.color = { 1,1,1,1 };
        player.speed = { 0 ,0 };
        player.maxSpeed = { 7,7 };

        turboMode = false;
        ++player_state;
        /*fallthrough*/
        
    case 2:
        player.pos.x += player.speed.x;
        player.pos.y += player.speed.y;
        //testing for pushing and pull
        player_moveX();
        player_moveY();
       triggerAccelerateMode();
        debug::setString("turbo mode is %d", turboMode);
        debug::setString("player speed x is %f", player.speed.x);
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
        下記でsprPlayerを描画しましょう。

    解説）
        他に必要なパラメータは基本的にOBJ2D構造体のメンバ変数になっています。OBJ2D型の
        playerのメンバ変数を記述していきましょう。角度のみ、ToRadian(0)でOKです。
        色はVECTOR4型です。VECTOR4型の中身はx, y, z, wです。色はr, g, b, aなので、
        その順番で対応しています。（例えばrはxで、aはwで表すなど）
    */
    //******************************************************************************
#endif
    //TODO_09
    sprite_render(sprPlayer,
        player.pos.x, player.pos.y, //pos
        player.scale.x, player.scale.y, //scale
        player.texPos.x, player.texPos.y, //texture pos
        player.texSize.x, player.texSize.y,//texture width and height
        player.pivot.x, player.pivot.y, ToRadian(90));

}

void player_moveY()
{
    if (STATE(0) & PAD_DOWN)
    {
        player.speed.y += 1;
        if (player.speed.y > player.maxSpeed.y)
        {
            player.speed.y = player.maxSpeed.y;
        }
    }
    else if (STATE(0) & PAD_UP)
    {
        player.speed.y += -1;
        if (player.speed.y < -player.maxSpeed.y)
        {
            player.speed.y = -player.maxSpeed.y;
        }
    }
    else
    {
        player.speed.y = 0;
    }
}

void triggerAccelerateMode()
{
    if (TRG(0) &PAD_TRG1 )
    {
        if (player.maxSpeed.x == 15)
        {
            player.maxSpeed = { 7,7 };
            turboMode = false;
        }
        else
        {
            player.maxSpeed = { 15,15 };
            turboMode = true;
        }
     
    }
}

void player_moveX()
{
    //move right
    if (STATE(0) & PAD_RIGHT)
    {
        player.speed.x += 1;
        if (player.speed.x > player.maxSpeed.x)
        {
            player.speed.x = player.maxSpeed.x;
        }
        OutputDebugStringA("button pressed");
    }
    else if (STATE(0) & PAD_LEFT)
    {
        player.speed.x +=- 1;
        if (player.speed.x < -player.maxSpeed.x)
        {
            player.speed.x = -player.maxSpeed.x;
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
        player.speed.x = 0;
    }
       
    


}

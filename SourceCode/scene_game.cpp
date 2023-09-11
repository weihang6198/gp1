//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< インクルード >-----------------------------------------------------------
#include "all.h"
#include "player.h"
#include "enemy.h"
#include "item.h"


//------< 定数 >----------------------------------------------------------------


//------< 構造体 >---------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;
int mapPosX;
int map2PosX = 1280;
bool moveFirstMap = true;
bool moveSecondMap = false;
Sprite* sprBack;

//--------------------------------------
//  ゲームの初期設定
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
    //consumable_init();
}

//--------------------------------------
//  ゲームの終了処理
//--------------------------------------
void game_deinit()
{
#if 11
//******************************************************************************
// TODO:11 プレイヤーの終了処理関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_deinit関数を呼びましょう。
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
//  ゲームの更新処理
//--------------------------------------
void game_update()
{
    switch (game_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprBack = sprite_load(L"./Data/Images/space.png");

#if 10
//******************************************************************************
// TODO:10 プレイヤーの初期設定関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_init関数を呼びましょう。

解説）
    ここから、player関連の関数を呼び出していきます。どこで何の関数を呼び出して
    いるのかを把握しておきましょう。
*/
//******************************************************************************
#endif
        //TODO_10


        game_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //GameLib::setBlendMode(Blender::BS_ALPHA);

       mapPosX = 0;
        game_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

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
//  ゲームの描画処理
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
// TODO:13 プレイヤーの描画関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_render関数を呼びましょう。

    これで、プレイヤーが画面に表示されます。実行してみましょう。
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

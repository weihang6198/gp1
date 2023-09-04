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

//------< 定数 >----------------------------------------------------------------


//------< 構造体 >---------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;

Sprite* sprBack;

//--------------------------------------
//  ゲームの初期設定
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
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

        sprBack = sprite_load(L"./Data/Images/ruins.jpg");

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

        GameLib::setBlendMode(Blender::BS_ALPHA);

        game_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        debug::setString("");
        debug::setString("A D   : LEFT, RIGHT");
        debug::setString("SPACE : JUMP");
        debug::setString("");

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }

#if 12
//******************************************************************************
// TODO:12 プレイヤーの更新関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_update関数を呼びましょう。
*/
//******************************************************************************
#endif
        //TODO_12

        player_update();
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

    sprite_render(sprBack, 0, 0);

    player_render();

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

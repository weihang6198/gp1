#include "all.h"
int over_state;
int over_timer;

Sprite* sprGO;

//--------------------------------------
//  初期設定
//--------------------------------------
void over_init()
{
    over_state = 0;
    over_timer = 0;
}

//--------------------------------------
//  終了処理
//--------------------------------------
void over_deinit()
{
    music::stop(0);

   
    safe_delete(sprGO);
}

//--------------------------------------
//  タイトルの更新処理
//--------------------------------------
void over_update()
{
    switch (over_state)
    {
    case 0:
        //////// 初期設定 ////////

   

        sprGO = sprite_load(L"./Data/Images/gameover.png");
        over_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.15f);

        over_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

      /*  if ((gamestart == 1) && (TRG(0) & PAD_START))
        {
            sound::play(4, 2);

            nextScene = SCENE_GAME;
            break;
        }*/

        

        break;


    }


    over_timer++;
}

//--------------------------------------
//  タイトルの描画処理
//--------------------------------------
void over_render()
{
    // 画面を青で塗りつぶす
    GameLib::clear(0.3f, 0.5f, 1.0f);

    // タイトルの文字


    // "Push Enter Key" 点滅


    sprite_render(sprGO, 0, 0);

    font::textOut(4, "A<-   |   D->", VECTOR2(460, 630), VECTOR2(1.4f, 1.4f));
    font::textOut(4, "Press ENTER to continue", VECTOR2(320, 670), VECTOR2(1.4f, 1.4f));
}

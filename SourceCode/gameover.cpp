#include "all.h"
int over_state;
int over_timer;

Sprite* sprGO;
Sprite* sprGO2;
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
    safe_delete(sprGO2);
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
        sprGO2 = sprite_load(L"./Data/Images/gameover2.png");
        over_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(2);
        music::setVolume(0, 0.15f);

        over_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////
        debug::setString("timer %d", over_timer);
        if (over_timer == 20) {
            // Hoán đổi giá trị của a và b
            Sprite* temp = sprGO;
            sprGO = sprGO2;
            sprGO2 = temp;

            // Đặt lại over_timer về 0 để bắt đầu lại quá trình
            over_timer = 0;
        }

        
        if (TRG(0) & PAD_SELECT)
        {
            sound::play(4, 2);
            music::stop(2);
            nextScene = SCENE_TITLE;
            break;
        }
        if (TRG(0) & PAD_START)
        {
            sound::play(4, 2);
            music::stop(2);
            nextScene = SCENE_SCOREBOARD;
            break;
        }
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

    font::textOut(4, "Press ENTER to check SCOREBOARD", VECTOR2(320, 630), VECTOR2(1.0f, 1.0f));
    font::textOut(4, " Press BACKSPACE to main menu", VECTOR2(320, 670), VECTOR2(1.0f, 1.0f));
}
